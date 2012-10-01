/***************************************************************************
                           sm_connection_dialog.cpp - SMGIS
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
#ifndef SM_CONNECTION_DIALOG_H
#define SM_CONNECTION_DIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <iostream>
#include <string>

class SmConnectionDialog:public QDialog
{
    Q_OBJECT
private:
   QListWidget * lst_list_;
    QComboBox *cmb_driver_;
    QLineEdit * txt_password_;
    QLineEdit * txt_username_;
    QLineEdit * txt_port_;
    QLineEdit * txt_server_name_;
    QLineEdit * txt_database_name_;
    std::string selected_table_;
    std::string owner_name_;
    std::string user_name_;
    std::string password_;
    std::string server_name_;
    std::string port_;
    int port_number_;
    std::string database_;
    std::string driver_type_;
    QSqlDatabase * db_;
    bool connected;
public:

    SmConnectionDialog(QWidget * parent=0);
    std::string get_user_name_(void);
    std::string get_password_(void);
    std::string get_server_name_(void);
    std::string get_port_(void);
    std::string get_database_(void);
    std::string get_driver_type_(void);
    std::string get_owner_name_(void);
    QSqlDatabase *get_db_(void);
    QListWidget * get_lst_list_(void);
    std::string get_selected_table_(void)const;

private slots:
    void ok_clicked(void);
    void cancel_clicked(void);
    void connect_clicked(void);
    void clear_clicked(void);
    void lst_selected(QListWidgetItem *);

};
#endif
