/***************************************************************************
                        sm_index_shx_format.h - SMGIS
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
#ifndef SM_INDEX_SHX_FORMAT_H
#define SM_INDEX_SHX_FORMAT_H
#include <iostream>
#include <fstream>
#include <string>
class SmIndexSHXFormat
{
    private:

    unsigned int file_length_;
    std::ifstream *inp_file_;
    char * header_buffer_;
    std::string file_name_;

    public:
    unsigned int get_record_address_in_shp(unsigned int&,int record_number=1 );
    std::string get_file_name_(void);
    SmIndexSHXFormat(std::string);
    int read_shx_file(void);

};






#endif
