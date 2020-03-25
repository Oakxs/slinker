#include "mymenu.h"
#include <QMenu>
#include <QDebug>
#include <QKeyEvent>
#include <corecomponents.h>


MyMenu::MyMenu(QWidget *parent):QMenu(parent)
{
    menu = this;
    setAttribute(Qt::WA_TranslucentBackground);
    connect(this,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));
    setStyleSheet(
                "\
                QMenu {\
                background-color:rgb(89,87,87,20); /*整个背景*/\
                border: 3px solid rgb(235,110,36,200);/*整个菜单边缘*/\
                }\
            QMenu::item {\
                font-size: 10pt; \
                color: rgb(225,225,225);  /*字体颜色*/\
                border: 3px solid rgb(60,60,60,100);    /*item选框*/\
                background-color:rgb(89,87,87,50);\
                 }\
            QMenu::item:selected { \
                background-color:rgb(235,110,36,50);/*选中的样式*/\
                }\
            QMenu::item:pressed {/*菜单项按下效果*/\
                                      border: 1px solid rgb(60,60,61); \
                                      background-color: rgb(220,80,6); \
                                  }\
               "
                );
}

void MyMenu::keyPressEvent(QKeyEvent *event){
//    qDebug()<<"key pressed";
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Return:
        QMenu::keyPressEvent(event);
        return;
    }
    this->close();
    if(event->key()!=Qt::Key_Tab)
        edit->setText(edit->text().append(event->text()));
}

//slots
void MyMenu::trigerMenu(QAction* act)
{
   qDebug()<<act->text();
   edit->setText(act->text());
}
