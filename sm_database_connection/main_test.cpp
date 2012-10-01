#include "sm_sde_connection.h"
#include <QApplication>
#include <string>
#include <iostream>

int main(int argc,char ** argv)
{
    QApplication app(argc,argv);
    std::string user="user_maroofi";
    std::string pass="7410";
     int port=1433;
    std::string server="172.18.90.47\officebase";
    std::string database="basemap";
    SmDatabaseConnection *sm=new SmDatabaseConnection();
    //delete sm;
    sm->create_database_connection(user,pass,server,database,port);

    return app.exec();
}
