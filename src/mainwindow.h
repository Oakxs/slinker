#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void start(QString groupName=0,bool show=true);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
//    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void closeEvent(QCloseEvent *event);
private:    
    Ui::MainWindow *ui;
    QPushButton *btn_quit;
    QPushButton *btn_add_rule;
//    void topWindow();
private slots:
    void exit();
    void add_rule();

};

#endif // MAINWINDOW_H
