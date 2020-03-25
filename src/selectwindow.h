#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

namespace Ui {
class SelectWindow;
}

class SelectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectWindow(QWidget *parent = nullptr);
    ~SelectWindow();
    void popup(const QList<QString>&);
    void notice_to_reload();
protected:
    bool eventFilter(QObject *target, QEvent *event) override;
private:
    Ui::SelectWindow *ui;        
private slots:
    void runCmd();
    void fillLine();

};

#endif // SELECTWINDOW_H
