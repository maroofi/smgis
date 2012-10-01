/***************************************************************************
                            main_test.cpp - SMGIS
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
int main(int argc,char ** argv)

{

    SmDataDBFFormat *s;
    s=new SmDataDBFFormat();
    s->set_dbf_file_name("93000.dbf");
    if (s->read_dbf_file() ==-1)
    {
        std::cout<<"ERROR occured!!!!"<<std::endl;
        return -1;
    }
    std::cout<<"dBase version is : "<<s->get_dbase_version()<<std::endl;
    std::cout<<"record length in bytes : "<<s->get_record_length_in_byte()<<std::endl;
    std::cout<<"num of records is : "<<s->get_num_of_record()<<std::endl;
    for(unsigned int i=0;i<s->get_num_of_record();i++)
    {
            s->print_field_information(i);
            std::cout<<std::endl;
    }


}
