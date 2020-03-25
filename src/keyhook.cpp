#include "keyhook.h"
#include "windows.h"
#include <QDebug>
#include "corecomponents.h"

HHOOK keyHook = NULL;
//HHOOK mouseHook = NULL;

//键盘钩子过程
LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    static bool first_press=true,release_r=true,release_win=true;

    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
    //if (nCode == HC_ACTION){
    if (pkbhs->vkCode == 'R' && GetAsyncKeyState(VK_LWIN) & 0x8000){
//        qDebug() << "WIN+R";
        if(first_press){
            main_window->start();
            first_press=false;
            release_r=false;
            release_win=false;
            return 1;
        }
    }
    if(pkbhs->vkCode == 'R'&&!first_press){
        switch (wParam)
        {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            return 1;
        case WM_SYSKEYUP:
        case WM_KEYUP:
            release_r=true;
            if(release_win)first_press=true;
            return 0;
        }
    }
    if(pkbhs->vkCode == VK_LWIN&&!first_press){
        switch (wParam)
        {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            return 1;
        case WM_SYSKEYUP:
        case WM_KEYUP:
            release_win=true;
            if(release_r)first_press=true;
            return 0;
        }
    }

    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}

////鼠标钩子过程
//LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//    return 1;
//}

//卸载钩子
void unHook()
{
    UnhookWindowsHookEx(keyHook);
    //  UnhookWindowsHookEx(mouseHook);
}

//安装钩子,调用该函数即安装钩子
void setHook()
{
    //这两个底层钩子,不要DLL就可以全局r
    //底层键盘钩子
    keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyProc, GetModuleHandle(NULL), 0);
    //底层鼠标钩子
    //    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);
}

//extern
void hookSetup(bool state){
    if(state)
        setHook();
    else
        unHook();
}
