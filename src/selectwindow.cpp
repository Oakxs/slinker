#include "selectwindow.h"
#include "ui_selectwindow.h"
#include <QPainter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QScrollBar>
#include <QKeyEvent>
#include <QScrollArea>
#include "btnitem.h"
#include "style.h"
#include "corecomponents.h"

static QVBoxLayout* vLayout;
static QList<QHBoxLayout*> hLayoutList;
static QList<QPushButton*> btnList;
static QScrollArea* scrollArea;
static QWidget* container;
static bool need_to_reload;

SelectWindow::SelectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectWindow)
{
    ui->setupUi(this);
    select_window = this;
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    installEventFilter(this);
}

SelectWindow::~SelectWindow()
{
    delete ui;
}

void releaseResources(){
    #define SafeDelete(pData) { if(pData!=NULL) { delete pData; pData=NULL;}  }

//    foreach(QPushButton* btn,btnList){
//        SafeDelete  (btn);
//    }
//    foreach(QHBoxLayout* hl,hLayoutList){
//        SafeDelete  (hl);
//    }
//    SafeDelete (vLayout);
//    SafeDelete  (container);
    //Qt会自动释放子节点
    SafeDelete (scrollArea);
    hLayoutList.clear();
    btnList.clear();
}

void SelectWindow::popup(const QList<QString>& content){

    if(need_to_reload){
        need_to_reload=false;
        releaseResources();
        int size = content.size();
        int colNum = (width()-20)/130;
        int rowNum = (size-1)/colNum+1;
        int cnt=0;
        qDebug()<<"colNum"<<colNum<<"contentSize"<<content.size();

        scrollArea = new QScrollArea(this);
        setScrollAreaTransparentStyle(scrollArea);
        container = new QWidget;
        vLayout = new QVBoxLayout();//网格布局
        for(int i = 0; i < rowNum; i++)
        {
            QHBoxLayout *hLayout = new QHBoxLayout();//网格布局
            hLayoutList<<hLayout;
            hLayout->setSpacing(10);
            for(int j=0;j<colNum;j++)
            {

                if(cnt<size){
                    BtnItem *pBtn = new BtnItem(this);
                    btnList<<pBtn;
                    pBtn->setFixedSize(120,30);   //width height
                    hLayout->addWidget(pBtn);//把按钮添加到布局控件中
                    pBtn->setText(content[cnt]);
                    pBtn->setToolTip(content[cnt]);
                    cnt++;
                    connect(pBtn,SIGNAL(rightReleased()),this,SLOT(fillLine()));
                    connect(pBtn,SIGNAL(leftReleased()),this,SLOT(runCmd()));
                }else {
                    hLayout->setAlignment(Qt::AlignLeft);
                    break;
                }
            }
            vLayout->addLayout(hLayout);
            if(cnt>=size)
                break;
        }
        container->setLayout(vLayout);
        this->setStyleSheet("background:rgba(0,0,0,0);border-radius:2px;");

        scrollArea->setWidget(container);
        setCentralWidget(scrollArea);
    }

    this->show();
    this->activateWindow();
}
//slots
void SelectWindow::runCmd(){
    QPushButton* sender = dynamic_cast<QPushButton*>(QObject::sender());
    qDebug()<<sender->text();    
    this->hide();
    edit->runCmd(sender->text());
}

void SelectWindow::fillLine(){
    QPushButton* sender = dynamic_cast<QPushButton*>(QObject::sender());
    this->hide();
    edit->setText(sender->text());
}

void SelectWindow::notice_to_reload(){
    need_to_reload = true;
}

//events

bool SelectWindow::eventFilter(QObject *target, QEvent *event){
    switch (event->type()) {
    case QEvent::ActivationChange:{
        if(QApplication::activeWindow() != this){
            this->hide();
            main_window->start();
            return false;
        }
    }break;
    case QEvent::KeyPress:{
        switch(dynamic_cast<QKeyEvent*>(event)->key()){
        case Qt::Key_Tab:
        case Qt::Key_Escape:
            this->hide();
            main_window->start();
            return false;
        }
    }break;
    default:;
    }
    return QMainWindow::eventFilter(target,event);
}
