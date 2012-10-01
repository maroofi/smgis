/***************************************************************************
                            sm_connection_dialog.h - SMGIS
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

#include "sm_connection_dialog.h"
#include <QMessageBox>

SmConnectionDialog::SmConnectionDialog(QWidget* parent ):QDialog(parent)
{
    selected_table_="";
    connected=false;
    port_number_=1433;
    port_="";
    database_="";
    server_name_="";
    user_name_="";
    password_="";
    driver_type_="ARCSDE";
    txt_password_=new QLineEdit("");
    txt_password_->setEchoMode(QLineEdit::Password);
    txt_username_=new QLineEdit("");
    txt_port_=new QLineEdit("default");
    txt_server_name_=new QLineEdit("127.0.0.1");
    txt_database_name_=new QLineEdit("netmanager_101");
     lst_list_=new QListWidget();
    QPushButton * btn_ok=new QPushButton("   Ok  ");
    QPushButton *btn_cancel=new QPushButton("Cancel");
    QPushButton * btn_connect=new QPushButton("Connect");
    QPushButton * btn_clear=new QPushButton("Clear");
    QLabel* lbl_user=new QLabel("Username");
    QLabel* lbl_pass=new QLabel("Password");
    QLabel* lbl_server=new QLabel("Server ");
    QLabel* lbl_database=new QLabel("Database");
    QLabel* lbl_port=new QLabel("Port   ");
    this->setWindowTitle("Database Connection");
    cmb_driver_=new QComboBox();
    cmb_driver_->addItem("ARCSDE10.1--MSSQL");
    cmb_driver_->addItem("MSSQL");
    cmb_driver_->addItem("MYSQL");
    cmb_driver_->addItem("POSTGRE");
    QHBoxLayout* hl1 =new QHBoxLayout();
    QVBoxLayout *vl=new QVBoxLayout();
    QLabel* lbl_driver=new QLabel("Driver");
    hl1->addWidget(lbl_driver);
    hl1->addWidget(cmb_driver_,1);
    vl->addLayout(hl1);
    QHBoxLayout* hl2 =new QHBoxLayout();
    hl2->addWidget(lbl_server);
    hl2->addWidget(txt_server_name_);
    vl->addLayout(hl2);
    QHBoxLayout* hl3 =new QHBoxLayout();
    hl3->addWidget(lbl_database);
    hl3->addWidget(txt_database_name_);
    vl->addLayout(hl3);
    QHBoxLayout* hl4 =new QHBoxLayout();
    hl4->addWidget(lbl_user);
    hl4->addWidget(txt_username_);
    vl->addLayout(hl4);
    QHBoxLayout *hl5=new QHBoxLayout();
    hl5->addWidget(lbl_pass);
    hl5->addWidget(txt_password_);
    vl->addLayout(hl5);
    QHBoxLayout *hl6=new QHBoxLayout();
    hl6->addWidget(btn_ok);
    hl6->addWidget(btn_cancel);
    hl6->addWidget(btn_clear);
    hl6->addWidget(btn_connect);
    QHBoxLayout *hl7=new QHBoxLayout();
    hl7->addWidget(lbl_port);
    hl7->addWidget(txt_port_);
    vl->addLayout(hl7);
    vl->addWidget(lst_list_);
    vl->addLayout(hl6);
    this->connect(btn_ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));
    this->connect(btn_cancel,SIGNAL(clicked()),this,SLOT(cancel_clicked()));
    this->connect(btn_connect,SIGNAL(clicked()),this,SLOT(connect_clicked()));
     this->connect(btn_clear,SIGNAL(clicked()),this,SLOT(clear_clicked()));
    this->setLayout(vl);
    db_=new QSqlDatabase();
    this->connect(lst_list_,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(lst_selected(QListWidgetItem*)));

}

void SmConnectionDialog::connect_clicked(void)
{
    QSqlError err;
    QString table_name;
    QString str_query;
    QString con_string_="";
    QSqlQuery *query_handle;
    database_=txt_database_name_->text().toStdString();
    server_name_=txt_server_name_->text().toStdString();
    user_name_=txt_username_->text().toStdString();
    password_=txt_password_->text().toStdString();
    port_=txt_port_->text().toStdString();
    driver_type_=cmb_driver_->currentText().toStdString();

    if (driver_type_=="ARCSDE10.1--MSSQL" || driver_type_=="MSSQL")
    {
        con_string_="DRIVER={SQL Server};SERVER=";
        con_string_=con_string_+QString( get_server_name_().c_str())+";DATABASE="+QString(get_database_().c_str())+";UID="
                   +QString(get_user_name_().c_str())+ ";PWD="+ QString(get_password_().c_str()) +";WSID=";
        QSqlDatabase db=QSqlDatabase::addDatabase("QODBC","connection");
        db_=new QSqlDatabase(db);
        query_handle=new QSqlQuery("",*db_);
        std::cout<<con_string_.toStdString()<<std::endl;
        db_->setHostName(txt_server_name_->text());
        db_->setDatabaseName(con_string_);
        if (!db_->open())
        {
            QString error_message="Can Not Connect to ";
            error_message=error_message + QString(database_.c_str())+";;";
            err=db_->lastError();
            error_message=error_message+err.text();
            QMessageBox::information(this,"Connection Report",error_message);
        }
        else
        {
            connected=true;
            QMessageBox::information(this,"Connection Report",
                                         "Connection was Successfull");
        }
         str_query="SELECT SCHEMA_NAME(schema_id) AS SchemaTable FROM ";
         str_query+=QString(database_.c_str());
         str_query+= ".sys.tables ";
        if (query_handle->exec(str_query)==false)
             std::cout<<"error occured!!!";
        query_handle->next();
        owner_name_=query_handle->value(0).toString().toStdString();
    }

    if (driver_type_=="ARCSDE10.1--MSSQL")
    {
        str_query="SELECT table_name from " +
                QString(database_.c_str())+"."+QString(owner_name_.c_str())
                    +"."+"SDE_layers";
        if (query_handle->exec(str_query)==false)
        {
            QSqlError err=query_handle->lastError();
            QMessageBox::information(this,"Query Error",err.text());
        }
        else
        {
            while(query_handle->next())
            {
                table_name=query_handle->value(0).toString();
                lst_list_->addItem(table_name);
            }
        }
    }
    else if (driver_type_=="MSSQL")
    {
        QMessageBox::information(this,"Error","MsSql not supported yet");
        std::cout<<"mssql not sopported yet"<<std::endl;
    }
    else if (driver_type_=="MYSQL")
    {
        std::cout<<"mysql not sopported yet"<<std::endl;
        QMessageBox::information(this,"Error","MySql not supported yet");
    }
    else if (driver_type_=="POSTGRE")
    {
        std::cout<<"postgre not supported yet"<<std::endl;
        QMessageBox::information(this,"Error","PostGre not supported yet");
    }
}

/*
SELECT g_table_name from basemap.sde.SDE_geometry_columns
where f_table_name = 'B1_start'
*/


void SmConnectionDialog::clear_clicked(void)
{
    lst_list_->clear();
}

void SmConnectionDialog::ok_clicked(void)
{
    if (connected)
    {
        accept();
    }

}

void SmConnectionDialog::cancel_clicked(void)
{
    reject();
}


std::string SmConnectionDialog::get_user_name_(void)
{
       return user_name_;
}

std::string SmConnectionDialog::get_password_(void)
{
    return password_;
}

std::string SmConnectionDialog::get_server_name_(void)
{
    return server_name_;
}

std::string SmConnectionDialog::get_port_(void)
{
    return port_;
}

std::string SmConnectionDialog::get_database_(void)
{
    return database_;
}

std::string SmConnectionDialog::get_driver_type_(void)
{
    return driver_type_;
}

QSqlDatabase * SmConnectionDialog::get_db_(void)
{
    return db_;
}

QListWidget * SmConnectionDialog::get_lst_list_(void)
{
    return lst_list_;
}

std::string SmConnectionDialog::get_owner_name_(void)
{
    return owner_name_;
}

void SmConnectionDialog::lst_selected(QListWidgetItem* ind)
{
    selected_table_=lst_list_->currentItem()->text().toStdString();
    std::cout<<selected_table_<<std::endl;
}

std::string SmConnectionDialog::get_selected_table_(void)const
{
    return selected_table_;
}
