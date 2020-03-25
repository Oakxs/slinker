#include "btnitem.h"
#include "style.h"
#include <QPushButton>
#include <QMouseEvent>
#include "style.h"


//-------------------------------------BtnItem------------------------------------------------
BtnItem::BtnItem(QWidget *parent):QPushButton(parent)
{
    setButtonItemStyle(this);
}

void BtnItem::mouseReleaseEvent(QMouseEvent *event) {
    switch (event->button()) {
    case Qt::RightButton:
        emit rightReleased();
        break;
    case Qt::LeftButton:
        emit leftReleased();
        break;
    default:;
    }
}


