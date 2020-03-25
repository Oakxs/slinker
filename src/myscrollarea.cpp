#include "myscrollarea.h"

MyScrollArea::MyScrollArea(QWidget *parent):QScrollArea (parent)
{
    setStyleSheet("QScrollArea{"
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
