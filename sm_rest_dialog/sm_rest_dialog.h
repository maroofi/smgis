/***************************************************************************
                           sm_rest_dialog.h - SMGIS
                              -------------------
     begin                :  September 29 2012
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
#ifndef SM_REST_DIALOG_H
#define SM_REST_DIALOG_H

#include <QDialog>
#include <iostream>
#include <QLineEdit>
#include<QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSpacerItem>

class SmRESTDialog : public QDialog
{
    Q_OBJECT
    
public:

    SmRESTDialog(QWidget *parent = 0);
    std::string get_connection_name_(void);
    std::string get_rest_url_(void);
    bool get_if_connected_(void);
    
private:

    QLineEdit * txt_name;
    QLineEdit * txt_url;
    QNetworkReply * reply;
    std::string recieved_data_;
    std::string connection_name_;
    std::string rest_url_;
    bool if_connected_;
    void parse_json(void);

private slots:

    void request_finished(void);
    int on_btn_connect_clicked_(void);
    void rest_ready_read(void);
};

#endif // SM_REST_DIALOG_H
