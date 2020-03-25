#include "btnquit.h"

BtnQuit::BtnQuit(QWidget *parent):QPushButton(parent)
{
    setFixedSize(20,20);
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet(
                     //正常状态样式
                     "QPushButton{"
                     "background-color:rgba(225,100,100,30);"//背景色（也可以设置图片）
                     "border-style:outset;"                  //边框样式（inset/outset）
                     "border-width:4px;"                     //边框宽度像素
                     "border-radius:10px;"                   //边框圆角半径像素
                     "border-color:rgba(255,255,255,30);"    //边框颜色
                     "font:bold 10px;"                       //字体，字体大小
                     "color:rgba(0,0,0,100);"                //字体颜色
                     "padding:6px;"                          //填衬
                     "}"
                     //鼠标按下样式
                     "QPushButton:pressed{"
                     "background-color:rgba(255,100,100,200);"
                     "border-color:rgba(255,255,255,30);"
                     "border-style:inset;"
                     "color:rgba(0,0,0,100);"
                     "}"
                     //鼠标悬停样式
                     "QPushButton:hover{"
                     "background-color:rgba(255,100,100,100);"
                     "border-color:rgba(255,255,255,200);"
                     "color:rgba(0,0,0,200);"
                     "}");
}
