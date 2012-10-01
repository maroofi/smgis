/***************************************************************************
                           sm_rest_dialog.cpp - SMGIS
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
#include "sm_rest_dialog.h"


SmRESTDialog::SmRESTDialog(QWidget *parent) :
    QDialog(parent)

{
    QLabel * lbl_name=new QLabel("Name");
    QLabel* lbl_url=new QLabel("Url     ");
    QLabel * lbl_desc=new QLabel("Enter your REST service address like :\nhttp://172.18.101.38:6080/arcgis/rest/services");
    QPushButton * btn_connect=new QPushButton("Connect");
    QPushButton * btn_close=new QPushButton("Close");
    txt_url=new QLineEdit();
    txt_name=new QLineEdit();
    QHBoxLayout *h1=new QHBoxLayout();
    QHBoxLayout *h2=new QHBoxLayout();
    QHBoxLayout *h3=new QHBoxLayout();
    QVBoxLayout *v1=new QVBoxLayout();
    QListWidget* lst_rest=new QListWidget();
    h1->addWidget(lbl_name);
    h1->addWidget(txt_name);
    h2->addWidget(lbl_url);
    h2->addWidget(txt_url);
    h3->addStretch();
    h3->addStretch();
    h3->addWidget(btn_close);
    h3->addWidget(btn_connect);
    v1->addWidget(lbl_desc);
    v1->addLayout(h1);
    v1->addLayout(h2);
    v1->addLayout(h3);
    v1->addWidget(lst_rest);
    this->setLayout(v1);
    this->setWindowTitle("REST Service Connection");
   txt_url->setText("http://172.18.101.38:6080/arcgis/rest/services?f=json&");
   txt_name->setText("my connection");
    if_connected_=false;
    connection_name_="";
    rest_url_="";
    connect(btn_close,SIGNAL(clicked()),this,SLOT(reject()));
    connect(btn_connect,SIGNAL(clicked()),this,SLOT(on_btn_connect_clicked_()));

}


int SmRESTDialog::on_btn_connect_clicked_(void)
{
    if (txt_name->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Please provide some name for Connection!!");
        return -1;
    }
    if(txt_url->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Please provide Address for REST Service!!");
        return -1;
    }
    this->connection_name_=txt_name->text().toStdString();
    this->rest_url_=txt_url->text().toStdString();
    QNetworkAccessManager *qnam=new QNetworkAccessManager();
    QString rest_addr=QString(rest_url_.c_str());
    QUrl url(rest_addr);
    if (!url.isValid())
    {
        std::cout<<"url is not valid"<<std::endl;
        QMessageBox::information(this,"Error","This is not a valid http address...try Again");
        return -1;

    }
    reply=qnam->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(rest_ready_read()));
    connect (reply,SIGNAL(finished()),this,SLOT(request_finished()));
    return 0;
}

void SmRESTDialog::rest_ready_read(void)
{
    recieved_data_=recieved_data_+ QString(reply->readAll()).toStdString();
}

void SmRESTDialog::request_finished(void)
{
    std::cout<<recieved_data_<<std::endl;
    parse_json();
    recieved_data_.clear();
}

void SmRESTDialog::parse_json(void)
{
    std::string image_address;
    int image_width,image_height;
    double extent_xmin,extent_ymin,extent_xmax,extent_ymax,image_scale;
    //href,width,height,xmin,ymin,xmax,ymax,scale
    size_t pos_first,pos_second;
    size_t pos;
    pos_first=recieved_data_.find("http://");
    pos_second=recieved_data_.find(".png");
    pos_second+=4;
    pos=pos_second-pos_first;
    image_address=recieved_data_.substr(pos_first,pos);
    //
    pos_first=recieved_data_.find("width");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+7;
    pos=pos_second-pos_first;
    image_width=QString (recieved_data_.substr(pos_first,pos).c_str()).toInt();
    //
    pos_first=recieved_data_.find("height");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+8;
    pos=pos_second-pos_first;
    image_height=QString (recieved_data_.substr(pos_first,pos).c_str()).toInt();
    //
    pos_first=recieved_data_.find("xmin");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+6;
    pos=pos_second-pos_first;
    extent_xmin=QString (recieved_data_.substr(pos_first,pos).c_str()).toDouble();
    //
    pos_first=recieved_data_.find("ymin");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+6;
    pos=pos_second-pos_first;
    extent_ymin=QString (recieved_data_.substr(pos_first,pos).c_str()).toDouble();
    //
    pos_first=recieved_data_.find("xmax");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+6;
    pos=pos_second-pos_first;
    extent_xmax=QString (recieved_data_.substr(pos_first,pos).c_str()).toDouble();
    //
    pos_first=recieved_data_.find("ymax");
    pos_second=recieved_data_.find(",",pos_first);
    pos_first=pos_first+6;
    pos=pos_second-pos_first;
    extent_ymax=QString (recieved_data_.substr(pos_first,pos).c_str()).toDouble();
    //
    pos_first=recieved_data_.find("scale");
    pos_second=recieved_data_.find("}",pos_first);
    pos_first=pos_first+7;
    pos=pos_second-pos_first;
    image_scale= QString(recieved_data_.substr(pos_first,pos).c_str()).toDouble();
    //

    std::cout<<image_address<<std::endl;
    std::cout<<image_width<<std::endl;
    std::cout<<image_height<<std::endl;
    std::cout<<extent_xmin<<std::endl;
    std::cout<<extent_ymin<<std::endl;
    std::cout<<extent_xmax<<std::endl;
    std::cout<<extent_ymax<<std::endl;
    std::cout<<image_scale<<std::endl;
}
