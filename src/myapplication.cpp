#include "corecomponents.h"
//#include "windows.h"
#include "keyhook.h"
#include <QDebug>

static int id;
//static UINT fsModifiers,vk;

MyApplication::MyApplication(int &argc,char **argv):QApplication(argc,argv){
    //设置钩子
    hookSetup(true);
    setQuitOnLastWindowClosed(false);
    my_application = this;
    select_window = new SelectWindow(0);
    select_window->hide();
}

MyApplication::~MyApplication(){
//    //注销热键
//    GlobalDeleteAtom(static_cast<ATOM>(id));
//    UnregisterHotKey(reinterpret_cast<HWND>(main_window->winId()),id);
    //注销钩子
    hookSetup(false);
    qDebug()<<"gg";
}



//void MyApplication::setup(){
//    //注册热键
//    fsModifiers = MOD_WIN;
//    vk = 'R';
//    std::wstring lpString = (L""+std::to_wstring(fsModifiers)+std::to_wstring(vk));
//    id = GlobalAddAtom(lpString.c_str());
//    RegisterHotKey(reinterpret_cast<HWND>(main_window->winId()),id,fsModifiers,vk);
//}


