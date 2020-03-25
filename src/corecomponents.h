#ifndef OBJCONTROLLER_H
#define OBJCONTROLLER_H
#include <myapplication.h>
#include <selectwindow.h>
#include <mainwindow.h>
#include <mylineedit.h>
#include <QMenu>

extern MyApplication* my_application;
extern MainWindow* main_window;
extern SelectWindow* select_window;
extern MyLineEdit* edit;
extern QMenu* menu;

extern void check_file_modified();

#endif // OBJCONTROLLER_H
