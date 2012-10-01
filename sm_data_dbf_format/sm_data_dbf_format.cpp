/***************************************************************************
                     sm_data_dbf_format.cpp - SMGIS
                              -------------------
     begin                : Thursday July 10 2012
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

#include <string>
#include <iostream>
#include "sm_data_dbf_format.h"
#include <fstream>

/*
NON-Member Function
*/
std::string left_trim(std::string str)
{
    std::string temp_str="";
    bool beyn=false;
    for(unsigned int i=0;i<str.length();i++)
    {

        if(str[i] ==0x20  && beyn==false)
            continue;

            beyn=true;
            temp_str.push_back(str[i]);

    }
    return temp_str;
}



SmDataDBFFormat::SmDataDBFFormat(QWidget* parent):QDialog(parent)
{

    identify_table_=new QTableWidget(this);
    QHBoxLayout* hl=new QHBoxLayout();
    hl->addWidget(identify_table_);
    this->setLayout(hl);
    QStringList label;
    label<<"Field"<<"Value";
    identify_table_->setColumnCount(2);
    identify_table_->setHorizontalHeaderLabels(label);
//    this->setModal(false);
     this->setWindowModality(Qt::NonModal);
    dbase_version_=0;
    dbase_update_date_=0;
    record_length_in_byte_=0;
    num_of_byte_header_=0;
    n_offset_=0;
    num_of_records_=0;
    num_of_field_=0;
    field_descriptor_=0;
    in_file_=new std::ifstream();

}

SmDataDBFFormat::SmDataDBFFormat(std::string file_name,QWidget* parent):QDialog(parent)
    {
    identify_table_=new QTableWidget(this);
    QStringList label;
    label<<"Field"<<"Value";
    identify_table_->setColumnCount(2);
    identify_table_->setHorizontalHeaderLabels(label);
//    this->setModal(false);
     this->setWindowModality(Qt::NonModal);
    dbase_version_=0;
    dbase_update_date_=0;
    record_length_in_byte_=0;
    num_of_byte_header_=0;
    n_offset_=0;
    num_of_records_=0;
    num_of_field_=0;
    field_descriptor_=0;
    in_file_=new std::ifstream();

    dbf_file_name_=file_name;
    }

SmDataDBFFormat::SmDataDBFFormat(const char * file_name,QWidget* parent):QDialog(parent)

    {
    identify_table_=new QTableWidget(this);
    QStringList label;
    label<<"Field"<<"Value";
    identify_table_->setColumnCount(2);
    identify_table_->setHorizontalHeaderLabels(label);
//    this->setModal(false);
    this->setWindowModality(Qt::NonModal);
    dbase_version_=0;
    dbase_update_date_=0;
    record_length_in_byte_=0;
    num_of_byte_header_=0;
    n_offset_=0;
    num_of_records_=0;
    num_of_field_=0;
    field_descriptor_=0;
    in_file_=new std::ifstream();

    dbf_file_name_=file_name;
    }



int SmDataDBFFormat::get_dbase_update_date(void){
    return dbase_update_date_;

}

int SmDataDBFFormat::get_dbase_version(void){
    return ((dbase_version_>0)?dbase_version_:-1 );
}

unsigned int SmDataDBFFormat::get_num_of_record(void){
    return ( (num_of_records_>0)?num_of_records_:-1 );
}

int SmDataDBFFormat::get_record_length_in_byte(void){
    return ( (record_length_in_byte_>0)?record_length_in_byte_:-1 );
}

int SmDataDBFFormat::read_dbf_file(void)
{
    if (dbf_file_name_=="")
        {
            std::cout<<"There is NO valid .dbf file name "<<std::endl;
            return -1;
        }
    in_file_->open(dbf_file_name_.c_str(),std::ios::in|std::ios::binary);
    if (!in_file_->is_open())
        {
            std::cout<<"can not open input .dbf file"<<std::endl;
            return -1;
        }
    in_file_->seekg(8,std::ios::beg);
    unsigned char * byte=new unsigned char [2];
    in_file_->read((char*)byte,2);
    this->num_of_byte_header_=(int)byte[0];
    num_of_byte_header_=num_of_byte_header_+(byte[1]<<8);
    unsigned char * header_buffer=new unsigned char[num_of_byte_header_];
    in_file_->seekg(0,std::ios::beg);
    in_file_->read((char*)header_buffer,num_of_byte_header_);
    dbase_version_=(int)header_buffer[0];
    record_length_in_byte_=(int)header_buffer[10];
    /*
    byte 10-11  16-bit      Number of bytes in the record.(least first)
    */
    record_length_in_byte_=record_length_in_byte_|( (int)header_buffer[11]<<8 );
    /*
    byte 4-7   32-bit      Number of records in the table.(least first)
    */
    num_of_records_=(int)(  (header_buffer[4])+
                          (header_buffer[5]<<8)+(header_buffer[6]<<16)+(header_buffer[7]<<24));
    n_offset_=header_buffer[num_of_byte_header_-2];
    if (n_offset_!=0)
        std::cout<<"n_offset is not zero !!!! maybe error occured"<<std::endl;
    unsigned int file_offset=32-n_offset_;
    int block_counter=(num_of_byte_header_-32)/32;
    num_of_field_=block_counter;
    field_descriptor_=new FieldDescriptor[block_counter];
    int temp=0;
    std::cout<<"num of field is : "<<num_of_field_<<std::endl;
    while (block_counter>0)
    {
        for(int i=0;i<11;i++)
        {
            if(header_buffer[file_offset])
            {
                field_descriptor_[temp].field_name_+=header_buffer[file_offset];
            }
            file_offset++;

        }

        switch(header_buffer[file_offset])
        {
            case 'C':
            case 'c':
                field_descriptor_[temp].field_type_=smgis::Character;break;
            case 'N':
            case 'n' :
                field_descriptor_[temp].field_type_=smgis::Numeric;break;
            case 'L':
            case 'l':
                field_descriptor_[temp].field_type_=smgis::Logical;break;
            case 'M':
            case 'm':
                field_descriptor_[temp].field_type_=smgis::Memo;break;
            case 'D':
            case 'd':
                field_descriptor_[temp].field_type_=smgis::Date;break;
            default:
                field_descriptor_[temp].field_type_=smgis::Character;break;
        }
        file_offset+=5;
        field_descriptor_[temp].field_length_=header_buffer[file_offset];
        file_offset+=16;
        block_counter--;
        temp++;
    }
    file_offset=num_of_byte_header_;
    //here read record from file if anyone asked to
    identify_table_->setRowCount(num_of_field_);
    return 0;
}

void SmDataDBFFormat::print_field_information(int record_num)
{
    if (record_num>num_of_records_)
    {
        QMessageBox::information(this,"Error","This is not a valid record Number....Try again");
//      std::cout<<"This is not a valid record Number....Try again"<<std::endl;
        return;
    }
    if (record_num==0)
    {


        for (int i=0;i<num_of_field_;i++)
        {
//            std::cout<<"************************"<<std::endl;
//            std::cout<<"Field Name is : "<<field_descriptor_[i].field_name_<<std::endl;
            QTableWidgetItem* tab_item=new QTableWidgetItem();
            tab_item->setText(QString(field_descriptor_[i].field_name_.c_str()));
            identify_table_->setItem(i,0,tab_item);
//            std::cout<<"field Type is : "<<get_data_field_type(field_descriptor_[i].field_type_)<<std::endl;
//            std::cout<<"Field Length is : "<<field_descriptor_[i].field_length_<<std::endl;
//            std::cout<<"***********************"<<std::endl;
        }
    }
    else
    {
        //record number is not 0
        in_file_->seekg(num_of_byte_header_+((record_num-1)*record_length_in_byte_)
                        ,std::ios::beg);
        unsigned char * record_buffer=new unsigned char[record_length_in_byte_];
        in_file_->read((char *)record_buffer,record_length_in_byte_);
        if(record_buffer[0]==RECORD_IS_DELETED)
        {
            std::cout<<"This Record is Deleted"<<std::endl;
            return;
        }
        else
        {
            int temp=0;
            int buffer_offset=0;
            buffer_offset++;
            std::string temp_buffer="";

            while(temp<num_of_field_)
            {
                for(int i=0;i<field_descriptor_[temp].field_length_;i++)
                {
                    temp_buffer+=record_buffer[buffer_offset];
                    buffer_offset++;
                }
//                std::cout<<left_trim(temp_buffer);
                QTableWidgetItem* tab_item=new QTableWidgetItem();
                tab_item->setText(QString(left_trim(temp_buffer).c_str()));
                identify_table_->setItem(temp,1,tab_item);
//                std::cout<<"  ";
                temp_buffer="";
                temp++;
            }
        }

    }
}
std::string SmDataDBFFormat::get_data_field_type(smgis::DataFieldType dtf)
{
    if (dtf==smgis::Character)
        return "Character";
    else if (dtf==smgis::Logical)
        return "Logical";
    else if (dtf==smgis::Memo)
        return "Memo";
    else if    (dtf==smgis::Numeric)
        return "Numeric";
    else if (dtf==smgis::Date)
         return "Date";
    else
         return "No valid Data Type";
}

int SmDataDBFFormat::set_dbf_file_name(const char* fn)
{
    dbf_file_name_=fn;
    return 0;
}

int SmDataDBFFormat::set_dbf_file_name(std::string fn)
{
    dbf_file_name_=fn;
    return 0;
}


void SmDataDBFFormat::execute(unsigned int id)
{
    this->identify_table_->clearContents();
    this->print_field_information(0);
    this->print_field_information(id);
//    std::cout<<id<<std::endl;

    this->resize(260,210);
//    this->exec();
    this->show();
}

