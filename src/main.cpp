#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QSettings>
#include <QProcess>
#include <QDir>
#include "corecomponents.h"
#include "lang.h"
#include <QDebug>



int main(int argc, char *argv[])
{    
    //单例运行
    QSystemSemaphore sema("JAMKey",1,QSystemSemaphore::Open);
    sema.acquire();// 在临界区操作共享内存   SharedMemory
    QSharedMemory mem("SLINKER");// 全局对象名
    if (!mem.create(1))// 如果全局对象以存在则退出
    {
        sema.release();
        return 0;
    }
    sema.release();


    //读取ini配置和运行参数
    QSettings* conf = new QSettings("conf.ini", QSettings::IniFormat);
    QString lang = conf->value("lang").toString();
    init_lang(lang);
    const QString &groupName = argc>1&&QString(argv[1])!="0"?argv[1]:conf->value("default_group").toString();
    bool show = argc>2?QString(argv[2])=="true":false;
    delete conf;
    //读取历史文件
    {
        QFile file("./.histroy");
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream output(&file);
            output >> histroy;
            file.close();
        }
    }



    //启动
    MyApplication a(argc, argv);        
    MainWindow w;
//    a.setup();
    w.start(groupName,show);
    int rtn = a.exec();


    //保存历史数据
    {
        QFile file("./.histroy");
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream input(&file);
            input << histroy;
            file.close();
        }
    }



    // 重启
    if(rtn == 773){//RETCODE_RESTART
        QProcess::startDetached(QDir::currentPath()+"/scripts/reboot.bat",QStringList());
        return 0;
    }

    //为了避免关闭时崩溃的弱智问题。。。只好我杀我自己
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    QString cmd=(QString("taskkill /F /PID %1 /T").arg(MyApplication::applicationPid()) +"\n");
    p.write(cmd.toLocal8Bit());
    p.closeWriteChannel();
    p.waitForFinished();
    return 0;
}
