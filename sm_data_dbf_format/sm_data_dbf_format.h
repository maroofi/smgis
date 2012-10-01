/***************************************************************************
                     sm_data_dbf_format.h - SMGIS
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


#ifndef SM_DATA_DBF_FORMAT_H
#define SM_DATA_DBF_FORMAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QMessageBox>
#define RECORD_IS_NOT_DELETED 0x20
#define RECORD_IS_DELETED 0x2a
#define JUNK_DATA_IN_DBF 0x20
#define FIELD_TERMINATOR 0x0d
#define FIELD_DESCRIPTOR_LENGTH 0X20


namespace smgis {
enum DataFieldType {

    Character,Date,Numeric,Logical,Memo
    };
};
class FieldDescriptor
{
    private:

    public:
    FieldDescriptor()
    {
        field_name_="";
        field_length_=0;
        next=0;
        field_type_=smgis::Character;
    }
    std::string field_name_;
    int field_length_;
    smgis::DataFieldType field_type_;
    FieldDescriptor * next;
};





class SmDataDBFFormat: public QDialog
{

public:

    SmDataDBFFormat(QWidget* parent=0);
    SmDataDBFFormat(const char *,QWidget* parent=0);
    SmDataDBFFormat(std::string,QWidget* parent=0);
    void print_field_information(int);
    int read_dbf_file(void);
    int get_dbase_version(void);
    int get_dbase_update_date(void);
    int get_record_length_in_byte(void);
    unsigned int get_num_of_record(void);
    int set_dbf_file_name(const char *);
    int set_dbf_file_name(std::string);
    void execute(unsigned int);
private:

    QTableWidget * identify_table_;
    std::string get_data_field_type(smgis::DataFieldType);
    FieldDescriptor* field_descriptor_;
    std::ifstream* in_file_;
    std::string dbf_file_name_;
    int num_of_field_;
    int dbase_version_;
    int dbase_update_date_;
    int record_length_in_byte_;
    int num_of_byte_header_;
    int n_offset_;
    int num_of_records_;
};
#endif
