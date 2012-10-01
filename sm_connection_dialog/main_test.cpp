#include <QApplication>
#include "sm_connection_dialog.h"

int main(int argc,char ** argv)
{
    QApplication app(argc,argv);
    SmConnectionDialog * smcd=new SmConnectionDialog();
    smcd->show();


    return app.exec();

}
