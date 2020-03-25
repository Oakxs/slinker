#include "mylineedit.h"
#include <QKeyEvent>
#include <QProcess>
#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QDateTime>
#include <unordered_map>
#include <lang.h>
#include "mymenu.h"
#include "corecomponents.h"
static std::unordered_map<std::string,void(*)()> basicFuncMap;//在运行状态下会触发的命令-函数映射
static std::unordered_map<std::string,void(*)()> settingFuncMap;//在settings组的运行状态下会触发的命令-函数映射
static std::unordered_map<std::string,QString> langMap;
static QString last_group;
static bool menu_need_to_reload;



//用于存放上下切换记录
HistroyData histroy;
static int &upb=histroy.upb,&lwb=histroy.lwb,&cur=histroy.cur;
static QList<QString> &record=histroy.record;

//-------------------------------func map--------------------------------------
void chang_group_mode(){
    edit->changeState(CHANGE_GROUP);
    edit->setText("");
}

void app_quit(){
    MyApplication::exit();
}

void set_to_startup(){
    edit->setText("");
    main_window->hide();
    QFile::link(MyApplication::applicationFilePath(), QDir::homePath()+"/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup/slinker.lnk");
    QMessageBox::about(NULL, "", t_add_startup_succeed);
}

void set_lang(){
    edit->changeState(SET_LANG);
    edit->setText("");
    auto &cmdSet = edit->cmdSet;
    cmdSet.clear();
    for(auto it=langMap.begin();it!=langMap.end();it++){
        cmdSet.insert(QString::fromStdString(it->first));
    }
}

void check_file_modified(){
    static QDateTime lastModified;
    QFileInfo info("cmdmap.ini");
    if (info.exists())
    {
        auto thisTime = info.lastModified();
        if(thisTime!=lastModified){
            lastModified=thisTime;
            qDebug()<<"Modified";
            edit->reloadIni();
            select_window->notice_to_reload();
            menu_need_to_reload=true;
        }
    }
}


MyLineEdit::MyLineEdit(QWidget * parent):QLineEdit (parent)
{
    edit = this;
    installEventFilter(this);

    fileSetting = new QSettings("cmdmap.ini", QSettings::IniFormat);
    fileSetting->setIniCodec("UTF-8");


    basicFuncMap["cg"] = chang_group_mode;
    basicFuncMap["quit"] = app_quit;
    settingFuncMap["set to startup"] = set_to_startup;
    settingFuncMap["set language to"] = set_lang;
    QSettings* lang = new QSettings("lang/lang.ini", QSettings::IniFormat);
    lang->setIniCodec("UTF-8");
    QStringList langKeys=lang->allKeys();
    foreach(QString key,langKeys){
        langMap[key.toStdString()]=lang->value(key).toString();
    }
    delete lang;
    last_group="settings";

    //自启动
    state = DIRECT;
    groupName="auto launch";
    fileSetting->beginGroup("auto launch");
    QStringList startupList = fileSetting->allKeys();
    foreach(QString startup,startupList){
        qDebug()<<startup;
        runCmd(startup);
    }
    setBasicPath();
    menu = new MyMenu(this);
    state = RUNNING;
}



void MyLineEdit::addFile(const QString& filename){
    if(groupName=="setting") return;
    this->ruleContent = "start \"\" \""+filename+"\"";
    changeState(NAMING_A_LINK);
}

void MyLineEdit::addRule(){
    if(groupName=="setting") return;
    changeState(ADD_RULE1);
}

void MyLineEdit::changeState(State state,const QString& placeholder){
    this->state = state;
    if(placeholder!=0){
        setPlaceholderText(placeholder);
        return;
    }
    switch (state) {
    case RUNNING:
        setPlaceholderText("");
        return;
    case NAMING_A_LINK:
    case ADD_RULE2:
        setPlaceholderText(t_name_a_link);
        return;
    case ADD_RULE1:
        setPlaceholderText(t_new_cmd);
        return;
    case CHANGE_GROUP:
        setPlaceholderText(t_change_group);
        return;
    case SET_LANG:
        setPlaceholderText(t_select_lang);
        return;
    }
}

void MyLineEdit::reloadIni(){    
    qDebug()<<"reloaded";
    delete fileSetting;
    fileSetting = new QSettings("cmdmap.ini", QSettings::IniFormat);
    fileSetting->setIniCodec("UTF-8");
    clearSet();
}

void MyLineEdit::clearSet(){
    cmdSet.clear();
    groupSet.clear();
}

//通过回车或点击触发
bool MyLineEdit::runCmd(const QString& cmdStr){

    switch (state) {
    case RUNNING:{
        auto funcEntry = basicFuncMap.find(cmdStr.toStdString());
        if(funcEntry!=basicFuncMap.end()){
            funcEntry->second();
            return true;
        }
        if(groupName=="settings"){
            funcEntry = settingFuncMap.find(cmdStr.toStdString());
            if(funcEntry!=settingFuncMap.end()){
                funcEntry->second();
                return true;
            }
        }
    }
    case DIRECT:{
        //-------------------start cmd---------------------
        QString cmdResult = fileSetting->value(cmdStr).toString();
        bool is_empty = cmdResult.size()==0;
        if(is_empty){//寻找前缀命令
            initSet();
            if(cmdSet.size()!=0){
                auto it = cmdSet.lower_bound(cmdStr);
                if(it!=cmdSet.begin()){
                    QString prefix = *(--it);
                    if(prefix.size()<text().size()){
                        if(text().left(prefix.size())==prefix){//存在前缀prefix
                            cmdResult = fileSetting->value(prefix).toString();
                            if(cmdResult.size()!=0){//命令是自己创建的
                                cmdResult=cmdResult+text().right(text().size()-prefix.size());
                            }else{//命令是直接通过cmd运行的
                                cmdResult="cd /d"+basicPath +"\nstart "+text();
                            }
                            is_empty=false;
                            qDebug()<<cmdResult;
                        }
                    }
                }
            }
        }
        if(is_empty)
            cmdResult="cd /d"+basicPath +"\nstart "+cmdStr;
        qDebug()<<"execute"<<cmdResult;

        QProcess p(0);
        p.start("cmd");
        p.waitForStarted();
        p.write((cmdResult+"\n").toLocal8Bit());
        p.closeWriteChannel();
        p.waitForFinished();

        QString error = QString::fromLocal8Bit(p.readAllStandardError());
        setText("");
        if(error.size() ==0){
            if(is_empty)
                fileSetting->setValue(cmdStr,"");
        }else {
            return false;
        }
    }break;
    case CHANGE_GROUP:{
        setGroup(cmdStr);
        changeState(RUNNING);
        setText("");
        clearSet();
    }break;
    case SET_LANG:{
        auto it = langMap.find(cmdStr.toStdString());
        if(it==langMap.end()){
            QMessageBox::critical(NULL, "", t_no_such_lang, QMessageBox::Ok, QMessageBox::Ok);
            break;
        }
        auto conf = new QSettings("conf.ini", QSettings::IniFormat);
        qDebug()<<conf->value("lang").toString();
        conf->setValue("lang",it->second);
        conf->value("lang");//重启前确保上一句执行
        conf->deleteLater();
        MyApplication::exit(773);//RETCODE_RESTART
    }break;
    default:;
    }
    return true;
}

void MyLineEdit::setGroup(const QString& name){
    groupName = name;    
    if(groupName=="settings"){
        setBasicPath(QDir::currentPath());
    }else{
        setBasicPath();
    }
}
//--------------------------------------------private--------------------------------------------------
void MyLineEdit::initSet(){
    if(groupSet.empty()){
        fileSetting->endGroup();
        QStringList groups = fileSetting->childGroups();
        foreach(QString group,groups){
            groupSet.insert(group);
        }
//                qDebug()<<groups;
        fileSetting->beginGroup(groupName);
        QStringList str = fileSetting->allKeys();
        foreach(QString key,str){
            cmdSet.insert(key);
        }
    }
}

void MyLineEdit::setBasicPath(QString path){
    basicPath = path;
}


bool MyLineEdit::menuPopup(const QList<QString> & stringList){
    static bool last_return;
    if(menu_need_to_reload){
        menu->clear();
        QList<QAction*> actionList;
        foreach(QString str, stringList){
            QAction *item = new QAction(str, this);
            actionList<<item;
        }
        menu->addActions(actionList);
        if(mapToGlobal(QPoint(0,0)).y()<menu->sizeHint().height()){
            foreach(QAction* act,actionList){
                delete act;
            }
            last_return = false;
            return false;
        }
        menu->exec(this->mapToGlobal(QPoint(0,-menu->sizeHint().height())));
        last_return=true;
        return true;
    }
    return last_return;
}
//-------------------------------------------------event--------------------------------------------------
//特定按键触发
void MyLineEdit::keyPressEvent(QKeyEvent *event){    
    fileSetting->endGroup();
    fileSetting->beginGroup(groupName);
    switch(event->key()){
    case Qt::Key_Return:
        if(text().size()==0){
            check_file_modified();
            if(state==RUNNING){
                setPlaceholderText(placeholderText().size()==0?groupName:"");
            }else{
                changeState(RUNNING);
            }
            return;
        }
        record[upb]=text();
        upb++;
        if(upb==MAX_RECORD)upb=0;
        record[upb]="";
        cur=upb;
        if(lwb==upb)lwb++;
        if(lwb==MAX_RECORD)lwb=0;
        switch (state) {
        case SET_LANG:
        case CHANGE_GROUP:
            runCmd(text());
            break;
        case RUNNING:
            main_window->hide();
            if(!runCmd(text())){
                main_window->show();
                main_window->activateWindow();
            }
            break;
        case NAMING_A_LINK:
            if(basicFuncMap.find(text().toStdString())==basicFuncMap.end()){
                fileSetting->setValue(text(),ruleContent);
                reloadIni();
                select_window->notice_to_reload();
                QMessageBox::about(NULL, "", t_add_link_succeed);
                changeState(RUNNING);
            }else{
                QMessageBox::critical(NULL, "", t_keyword_is_occupied, QMessageBox::Ok, QMessageBox::Ok);
            }
            break;
        case ADD_RULE1:
            ruleContent = text();
            changeState(ADD_RULE2);
            setText("");
            break;
        case ADD_RULE2:
            if(basicFuncMap.find(text().toStdString())==basicFuncMap.end()){
                fileSetting->setValue(text(),ruleContent);
                reloadIni();
                select_window->notice_to_reload();
                QMessageBox::about(NULL, "", t_add_rule_succeed);
                setText("");
                changeState(RUNNING);
            }else{
                QMessageBox::critical(NULL, "", t_keyword_is_occupied, QMessageBox::Ok, QMessageBox::Ok);
            }
            break;
        }
        break;
    case Qt::Key_Escape:
        main_window->hide();
        break;
    case Qt::Key_Up:
        if(cur==lwb)
            break;
        else if(--cur<0)
            cur=MAX_RECORD-1;
        setText(record[cur]);
        qDebug()<<cur<<record[cur];
        break;
    case Qt::Key_Down:
        if(cur==upb)
            break;
        else if(++cur>=MAX_RECORD)
            cur=0;
        setText(record[cur]);
        qDebug()<<cur<<record[cur];
        break;
    case Qt::Key_QuoteLeft:
        if(text().size()==0){
            QString tmp = groupName;
            setGroup(last_group);
            last_group = tmp;
            changeState(RUNNING,groupName);
            clearSet();
            return;
        }
    }
    QLineEdit::keyPressEvent(event);
}


bool MyLineEdit::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Tab){
            //初始化补全集
            initSet();
            set<QString> *the_set;
            switch (state) {
            case SET_LANG:
            case RUNNING:{
                the_set = &cmdSet;
            }break;
            case CHANGE_GROUP:{
                the_set = &groupSet;
            }break;
            default:
                return true;
            }
            QString searchText = this->text();
            auto iter = (*the_set).lower_bound(searchText);
            if(iter!=(*the_set).end()){
                QString upper = searchText;
                upper.append('\xFF');
                auto iter2 = (*the_set).upper_bound(upper);
                qDebug()<<"from"<<searchText<<"to"<<upper;
                qDebug()<<"lower_bound"<<*iter<<"upper_bound"<<(iter2!=(*the_set).end()?*iter2:"end");


                if(iter!=iter2--){
                    int pos;
                    if(iter!=iter2){
                        qDebug()<<"找到多个";
                        qDebug()<<"find prefix:"<<*iter<<"and"<<*iter2;

                        for(pos = this->text().size();pos<iter->size();pos++){
                            if((*iter)[pos]!=(*iter2)[pos])
                                break;
                        }
                        this->setText(iter->left(pos));



                        //弹出菜单
                        QList<QString> stringList;
                        int cnt=0;
                        for(auto it = iter;;it++){
                            cnt++;
                            stringList<<*it;
                            if(it==iter2)
                                break;
                        }
                        if(!menuPopup(stringList)){
                            main_window->hide();
                            select_window->popup(stringList);
                        }
                    }else {
                        qDebug()<<"只找到一个";
                        this->setText(*iter);
                    }
                }//else 没找到
            }
            return true;
        }
    }
    return QLineEdit::eventFilter(target, event);
}

