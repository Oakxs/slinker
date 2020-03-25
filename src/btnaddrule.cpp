#include "btnaddrule.h"
#include <QPushButton>

BtnAddRule::BtnAddRule(QWidget *parent):QPushButton(parent)
{
    setStyleSheet(
                     //正常状态样式
                     "QPushButton{"
                     "background-color:rgba(100,100,225,30);"//背景色（也可以设置图片）
                     "border-style:outset;"                  //边框样式（inset/outset）
                     "border-width:1px;"                     //边框宽度像素
                     "border-color:rgba(100,100,225,130);"    //边框颜色
                     "font:bold 12px;"                       //字体，字体大小
                     "color:rgba(255,255,255,200);"                //字体颜色
                     "padding:6px;"                          //填衬
                     "}"
                     //鼠标按下样式
                     "QPushButton:pressed{"
                     "background-color:rgba(100,100,255,30);"
                     "border-color:rgba(255,255,255,200);"
                     "border-style:inset;"
                     "color:white;"
                     "}"
                     //鼠标悬停样式
                     "QPushButton:hover{"
                     "background-color:rgba(100,100,255,30);"
                     "border-color:rgba(255,255,255,200);"
                     "color:white;"
                     "}");
}
