#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QSettings>
#include <QDir>
#include <set>
using std::set;

enum State{
    DIRECT,
    RUNNING,
    NAMING_A_LINK,
    ADD_RULE1,
    ADD_RULE2,
    CHANGE_GROUP,
    SET_LANG
};
static int MAX_RECORD = 40;
extern struct HistroyData{
    HistroyData(){
        QString blank="";
        for(int i=MAX_RECORD;i>0;i--){
            record.push_back(blank);
        }
    }
    QList<QString> record;
    int upb,lwb,cur;
    //序列化
    friend QDataStream &operator<<(QDataStream& input,const HistroyData &data)
    {
        input << data.upb << data.lwb << data.cur<<data.record;
        return input;
    }
    //反序列化
    friend QDataStream &operator>>(QDataStream& output,HistroyData& data)
    {
        output >> data.upb >>data.lwb >> data.cur >> data.record;
        return output;
    }
}histroy;

class MyLineEdit:public QLineEdit
{
public:
    friend class MainWindow;

    MyLineEdit(QWidget *);
    bool runCmd(const QString& cmdStr);    //from slots SelectWindow::runCmd

protected:
    void keyPressEvent(QKeyEvent *) override;
    bool eventFilter(QObject *target, QEvent *qevent) override;

private:
    State state;
    QSettings *fileSetting;
    set<QString> cmdSet;
    set<QString> groupSet;
    QString ruleContent;
    QString groupName;
    QString basicPath;

    void setBasicPath(QString path = QDir::homePath());
    bool menuPopup(const QList<QString> &);
    void initSet();
    void reloadIni();
    void clearSet();

    void addFile(const QString&);   //from MainWindow::dropEvent
    void addRule();                 //from MainWindow::add_rule
    void setGroup(const QString&);    //from MainWindow::start
    void changeState(State,const QString& placeholder=0);        //from MainWindow::start



    friend void chang_group_mode();
    friend void app_quit();
    friend void set_to_startup();
    friend void set_lang();
    friend void check_file_modified();

};

#endif // MYLINEEDIT_H
