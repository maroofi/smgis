/***************************************************************************
                           sm_database_connection.cpp - SMGIS
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

#include "sm_database_connection.h"

SmDatabaseConnection::SmDatabaseConnection(SmViewPanel *graphic_handle)
{
    graphic_handle_=graphic_handle;
    owner_name_="";
    driver_type_="";
    con_string_="";
    user_name_="";
    password_="";
    server_name_="";
    port_number_="";
    database_name_="";
    query_handle_=0;
    db_=0;
}

int  SmDatabaseConnection::establish_connection( )
{
    QSqlError err;
    SmConnectionDialog * dialog=new SmConnectionDialog();
    if (dialog->exec() !=QDialog::Accepted)
    {
        dialog->reject();
        return -1;
    }
    else
    {
        driver_type_=dialog->get_driver_type_();
        if (driver_type_=="ARCSDE10.1--MSSQL")
        {
            SmArcSDE101Connection* smac=new SmArcSDE101Connection(graphic_handle_);
            smac->set_database_name_(dialog->get_database_());
            smac->set_password_(dialog->get_password_());
            smac->set_user_name_(dialog->get_user_name_());
            smac->set_server_name_(dialog->get_server_name_());
            smac->set_port_number_(dialog->get_port_());
            smac->set_db_(new QSqlDatabase (*(dialog->get_db_())));
            query_handle_=smac->get_query_handle_();
            dialog->get_lst_list_()->clear();
            smac->set_owner_name_(dialog->get_owner_name_());
            std::cout<<"The owner name of Database "<<
            smac->get_database_name_()<<" is :"<<smac->get_owner_name_()<<std::endl;
            /*now you selected a table from dialog list and pressed ok button*/
            smac->load_feature_table(dialog->get_selected_table_());

        }
    }
    return 0;
}


std::string SmDatabaseConnection::get_user_name_(void)
{
    return user_name_;
}
std::string SmDatabaseConnection::get_password_(void)
{
    return password_;
}

std::string SmDatabaseConnection::get_server_name_(void)
{
    return server_name_;
}

std::string SmDatabaseConnection::get_database_name_(void)
{
    return database_name_;
}

std::string SmDatabaseConnection::get_port_number_(void)
{
    return port_number_;
}

QSqlQuery * SmDatabaseConnection::get_query_handle_(void)
{
    if (query_handle_)
        return query_handle_;
}

std::string SmDatabaseConnection::get_driver_type_(void)
{
    return driver_type_;
}
