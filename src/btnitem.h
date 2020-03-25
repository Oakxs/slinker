#ifndef ORANGEBUTTON_H
#define ORANGEBUTTON_H

#include <QPushButton>


class BtnItem: public QPushButton
{
    Q_OBJECT
public:
    BtnItem(QWidget *);
protected:
    virtual void mouseReleaseEvent (QMouseEvent * event );
signals:
    void rightReleased();
    void leftReleased();
};

#endif // ORANGEBUTTON_H
