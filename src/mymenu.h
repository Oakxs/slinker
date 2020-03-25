#ifndef MYMENU_H
#define MYMENU_H
#include <QMenu>

class MyMenu:public QMenu
{
    Q_OBJECT
public:
    explicit MyMenu(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *) override;

private slots:
    void trigerMenu(QAction*);
};

#endif // MYMENU_H
