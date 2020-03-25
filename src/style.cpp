#include "style.h"

//-------------------------------------BtnItem------------------------------------------------
void setButtonItemStyle(QPushButton* btn){
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setStyleSheet(
                     //正常状态样式
                     "QPushButton{"
                     "background-color:rgba(100,100,225,0);"//背景色（也可以设置图片）
                     "border-style:outset;"                  //边框样式（inset/outset）
                     "border-width:1px;"                     //边框宽度像素
                     "border-color:rgba(235,110,36,0);"    //边框颜色
                     "font:bold 12px;"                       //字体，字体大小
                     "color:rgba(255,255,255,200);"                //字体颜色
                     "padding:6px;"                          //填衬
                     "}"
                     //鼠标按下样式
                     "QPushButton:pressed{"
                     "background-color:rgba(100,100,255,0);"
                     "border-color:rgba(235,110,36,255);"
                     "border-style:inset;"
                     "color:white;"
                     "}"
                     //鼠标悬停样式
                     "QPushButton:hover{"
                     "background-color:rgba(235,110,36,200);"
                     "border-color:rgba(235,110,36,0);"
                     "color:white;"
                     "}");
}

//-------------------------------------BtnAddRule------------------------------------------------
void setButtonAddRuleStyle(QPushButton* btn){
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setStyleSheet(
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

//-------------------------------------BtnQuit------------------------------------------------
void setButtonQuitStyle(QPushButton* btn){
    btn->setFixedSize(20,20);
    btn->setFocusPolicy(Qt::NoFocus);
    btn->setStyleSheet(
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

void setScrollAreaTransparentStyle(QScrollArea* sa){
    sa->setStyleSheet("QScrollArea{"
                      "background-color: rgba(45,45,48,200);"//整体背景图片
                      "}"

                      "QScrollArea QScrollBar:vertical{"             //滚动条主体部分(滑道)
                      "min-width: 10;"//滑道最小宽度
                      "min-height:100;"//滑道最小高度
                      "border-radius:2px;"//滑道圆角
                      "background-color: rgba(255,192,0,0);"//设置外边框一小丢的图片
    //                  "image: url(./UI/scroll_area/A-drop-down-box.png);"//不知道为什么加上这句话上下按钮会消失
                      "}"

                      "QScrollArea QScrollBar::handle:vertical{"     //滑块主体
                      "border-radius:2px;"//滑块圆形角度
                      "background-color: rgba(235,110,36,200);"//滑块的图片
                      "}"

                      "QScrollArea QScrollBar::add-page:vertical{"
                      "background-color: transparent;"//未滑过区域的滑道图片
                      "}"
                      "QScrollArea QScrollBar::sub-page:vertical{"
                      "background-color: transparent;"//已滑过区域的滑道图片
                      "}"

                      "QScrollArea QScrollBar::add-line:vertical {"//设置下调按钮
                      "background-color: transparent;"//解决滚动条到达底部会出现小白点的问题
                      "}"

                      "QScrollArea QScrollBar::sub-line:vertical {"//设置上调按钮
                      "background-color: transparent;"//解决滚动条到达顶部会出现小白点的问题
                      "}"
           );
}
