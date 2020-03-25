#include "corecomponents.h"
#include "lang.h"

#include <QTextStream>
#include <QFile>

MyApplication* my_application;
MainWindow* main_window;
SelectWindow* select_window;
MyLineEdit* edit;
QMenu* menu;

QString
    t_btn_add_rule,
    t_name_a_link,
    t_new_cmd,
    t_change_group,
    t_add_link_succeed,
    t_add_rule_succeed,
    t_keyword_is_occupied,
    t_add_startup_succeed,
    t_select_lang,
    t_no_such_lang;

void init_lang(const QString& lang){
    QFile file(("lang/"+lang+".txt"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream floStream(&file);
        floStream.setCodec("System");
        t_btn_add_rule=floStream.readLine();
        t_name_a_link=floStream.readLine();
        t_new_cmd=floStream.readLine();
        t_change_group=floStream.readLine();
        t_add_link_succeed=floStream.readLine();
        t_add_rule_succeed=floStream.readLine();
        t_keyword_is_occupied=floStream.readLine();
        t_add_startup_succeed=floStream.readLine();
        t_select_lang=floStream.readLine();
        t_no_such_lang=floStream.readLine();
    }
    file.close();
}










