/***************************************************************************
                        sm_index_shx_format.cpp - SMGIS
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
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include "../sm_general/sm_general.h"
#include "sm_index_shx_format.h"

SmIndexSHXFormat::SmIndexSHXFormat(std::string fn)
{
    this->file_name_=fn;
    this->header_buffer_=new char[100];
    this->inp_file_=new std::ifstream();
}

int SmIndexSHXFormat::read_shx_file(void)
{
    inp_file_->open(file_name_.c_str(),std::ios::in|std::ios::binary);
    if(!inp_file_->is_open())
    {
        std::cout<<"can not open .shx file"<<std::endl;
        return -1;
    }
    inp_file_->read(header_buffer_,100);
    int file_code=header_buffer_[0]<<24 | header_buffer_[1]<<16|
                header_buffer_[2]<<8|header_buffer_[3];
    std::cout<<"file code is : "<<file_code<<std::endl;
    if (file_code !=9994)
    {
        std::cout<<"This is not a valid .shp file"<<std::endl;
        return -1;
    }
    file_length_=header_buffer_[24]<<24 | header_buffer_[25]<<16|
                header_buffer_[26]<<8|header_buffer_[27];
    file_length_*=2;
    std::cout<<"file Length is : "<<file_length_<<std::endl;
    /*version value is 1000 and little endian*/
    unsigned int file_version_=header_buffer_[28]<<24| header_buffer_[29]<<16|
                header_buffer_[30]<<8|header_buffer_[31];
    big_endian_to_little(file_version_);
    std::cout<<"file Version is : "<<file_version_<<std::endl;
    delete[] header_buffer_;
    header_buffer_=0;
    return 0;
}


std::string SmIndexSHXFormat::get_file_name_(void)
{
    return this->file_name_;
}


unsigned int SmIndexSHXFormat::get_record_address_in_shp(unsigned int & content_length
                                                         ,int record_number)
{
    if (record_number<=0)
    {
        std::cout<<"Invalid record Number"<<std::endl;
        return -1;  /*error*/
    }
    header_buffer_=new char[10];
    unsigned int n_offset=100+(record_number-1)*8;
    //std::cout<<"AAAAAAAAAAAAAAAAAAA"<<n_offset<<std::endl;
    if (n_offset>=this->file_length_)
    {
        std::cout<<"invalid record Number"<<std::endl;
        return -1;
    }
    try{
    inp_file_->seekg(n_offset);
    }catch (std::exception& e)
    {
        std::cout<<"Exception occured!!!!!"<<std::endl;
        return -1;
    }
    inp_file_->read(header_buffer_,8);
    int shp_file_offset=(int)(  (header_buffer_[0]<<24 )|
                          (header_buffer_[1]<<16
                           )|(header_buffer_[2]<<8)|
                            (header_buffer_[3]&0xff));
    content_length=(int)((header_buffer_[4]<<24 )|
                          (header_buffer_[5]<<16
                           )|(header_buffer_[6]<<8)|
                            (header_buffer_[7]&0xff));
    content_length*=2;
    /*content_length+8 = record length in .shp file*/

    std::cout<<"offset of record number "<<std::dec<<record_number<<" is : "
                                        <<shp_file_offset*2<<std::endl;
    delete[] header_buffer_;
    return (shp_file_offset*2);
    /*
    ** shp_file_offset is the offset of the record in the .shp file
    ** to get content offset ,add record header(8 bytes) to it.
    */

}
