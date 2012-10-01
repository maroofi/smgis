/***************************************************************************
                            main_test.cpp - SMGIS
                              -------------------
     begin                : Thursday July 16 2012
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
#include <iostream>
#include <string>
#include "sm_index_shx_format.h"

int main()
{
    SmIndexSHXFormat *s=new SmIndexSHXFormat("MyShape.shx");
    s->read_shx_file();
    std::cout<<"file name is : "<<s->get_file_name_()<<std::endl;
    unsigned int content_len=0;
    s->get_record_address_in_shp(content_len,2);
    std::cout<<"content length is : "<<content_len<<std::endl;
    s->get_record_address_in_shp(content_len,1);
    std::cout<<"content length is : "<<content_len<<std::endl;
    s->get_record_address_in_shp(content_len,5);
    std::cout<<"content length is : "<<content_len<<std::endl;
    return 0;
}
