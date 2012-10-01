/***************************************************************************
                            sm_database_connection.h - SMGIS
                              -------------------
     begin                :  September 02 2012
     copyright            : (C) 2012 by Sourena Maroofi
     email                : Maroofi at gmail.com
  ***************************************************************************/

 /***************************************************************************
  *                                                                         *
  *     This program is NOT a free software;                                *
  *     BUT you can use the source if you got                               *
  *     it,Just in your personal Project...                                 *
  ***************************************************************************
*/
#ifndef SM_DATABASE_CONNECTION_H
#define SM_DATABASE_CONNECTION_H
#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringList>
#include "../sm_connection_dialog/sm_connection_dialog.h"
#include "../sm_arcsde101_connection/sm_arcsde101_connection.h"
#include "../sm_esri_rest/sm_esri_rest.h"
#include "../sm_rest_dialog/sm_rest_dialog.h"
#include "../sm_view_panel/sm_view_panel.h"


class SmDatabaseConnection
{
private:

    std::string geometry_column_name_;
    std::string owner_name_;
    std::string con_string_;
    std::string user_name_;
    std::string password_;
    std::string server_name_;
    std::string database_name_;
    std::string port_number_;
    std::string driver_type_;
    QSqlQuery* query_handle_;
    QSqlDatabase * db_;
    SmViewPanel* graphic_handle_;

public:
    SmDatabaseConnection(SmViewPanel* );
    int establish_connection();
    std::string get_user_name_(void);
    std::string get_password_(void);
    std::string get_server_name_(void);
    std::string get_database_name_(void);
    std::string get_port_number_(void);
    std::string get_driver_type_(void);
    QSqlQuery * get_query_handle_(void);
};

#endif
