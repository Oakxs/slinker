#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
//#include "windows.h"
#include "corecomponents.h"
#include "style.h"
#include "lang.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    main_window = this;
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

    QDesktopWidget *deskWgt = QApplication::desktop();
    setAttribute(Qt::WA_TranslucentBackground);
    if (deskWgt) {
        int availableHeight = deskWgt->availableGeometry(0).height();
        select_window->setFixedSize(width(),availableHeight);
        move(0,availableHeight-geometry().height());
    }
    btn_quit = new QPushButton(this);
    setButtonQuitStyle(btn_quit);
    connect(btn_quit,SIGNAL(clicked()),this,SLOT(exit()));
    btn_add_rule = new QPushButton(this);
    setButtonAddRuleStyle(btn_add_rule);
    btn_add_rule->move(500,(this->maximumHeight()-btn_add_rule->height())/2);
    btn_add_rule->setText(t_btn_add_rule);
    connect(btn_add_rule,SIGNAL(clicked()),this,SLOT(add_rule()));

    edit = new MyLineEdit(this);
    edit->setFont(QFont("Timers" , 17 ,  QFont::Thin));
    this->setAcceptDrops(true);

}

void MainWindow::start(QString groupName,bool show)
{
    check_file_modified();
    edit->changeState(RUNNING);
    if(groupName!=0)
        edit->setGroup(groupName);

    if(show){//找了半天设置焦点的方法没有...发现hide show还能用
        this->hide();
        this->show();
        activateWindow();
    }



}


MainWindow::~MainWindow()
{
    delete ui;
}


//----------------------------------------events-----------------------------------
//外观
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    /* 0x20为透明层颜色，可自定义设置为0x0到0xff */
    painter.fillRect(this->rect(), QColor(0x2D,0x2D,0x30,0xEE));
}
void MainWindow::resizeEvent(QResizeEvent *){
    btn_quit->move(geometry().width()-btn_quit->width(),0);
    int width = static_cast<int>(geometry().width()*0.97);
    edit->setFixedWidth(width>450?450:width);
    edit->move(4,(geometry().height()-edit->height())/2);
    menu->setFixedWidth(edit->width());
}


//拖入文件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}
void MainWindow::dropEvent(QDropEvent *event)
{
    QString name = event->mimeData()->urls().first().toString();
    edit->addFile(name);
    activateWindow();
}

////检测热键
//bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result){
//    if(eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
//        {
//            MSG* pMsg = reinterpret_cast<MSG*>(message);
//            if(pMsg->message == WM_HOTKEY)
//            {
//                start();
//                return true;
//            }
//        }
//    return QMainWindow::nativeEvent(eventType,message,result);
//}

//关闭时隐藏
void MainWindow::closeEvent(QCloseEvent *event){
    event->ignore();
    exit();
}


//slots
void MainWindow::exit(){
    edit->setText("");
    this->hide();
}

void MainWindow::add_rule(){
    edit->addRule();
}

