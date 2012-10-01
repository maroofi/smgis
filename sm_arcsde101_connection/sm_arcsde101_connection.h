/***************************************************************************
                           sm_arcsde101_connection.h - SMGIS
                              -------------------
     begin                :  September 15 2012
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
#ifndef SM_ARCSDE101_CONNECTION_H
#define SM_ARCSDE101_CONNECTION_H
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidget>
#include <QMessageBox>
#include <QSqlError>
#include <QListWidget>
#include <QByteArray>
#include <string.h>
#include <algorithm>
#include "../sm_shape_general/sm_shape_general.h"
#include "../sm_layer_info/sm_layer_info.h"
#include "../sm_view_panel/sm_view_panel.h"
class SmArcSDE101Connection
{
private:
    SmViewPanel * graphic_handle_;
    smgis::GeometryType geo_type_;
    std::string database_name_;
    std::string owner_name_;
    std::string port_number_;
    std::string password_;
    std::string user_name_;
    std::string server_name_;
    QSqlQuery* query_handle_;
    QSqlDatabase * db_;

public:
    SmArcSDE101Connection(SmViewPanel*);
    SmArcSDE101Connection(std::string,std::string,std::string,std::string,std::string,std::string);
    /*//
            initializer for the class get user,pass,
            server_name,database_name,port_number respectively
    //*/

    void set_geo_type(void);
    void load_feature_table(std::string table_name);
    void load_feature_table93(std::string table_name);
    /************getters & setters********/
    std::string get_database_name_(void) const;
    std::string get_owner_name_(void)const ;
    std::string get_password_(void)const ;
    std::string get_user_name_(void)const;
    std::string get_port_number_(void)const;
    std::string get_server_name_(void)const;
    QSqlQuery * get_query_handle_(void)const;
    void set_database_name_(std::string);
    void set_server_name_(std::string);
    void set_port_number_(std::string);
    void set_user_name_(std::string);
    void set_password_(std::string);
    void set_owner_name_(std::string);
    void set_db_(QSqlDatabase * db);
    void set_query_handle_(QSqlQuery * query_handle);
    /************************************/
};
#endif  //SM_ARCSDE101_CONNECTION
