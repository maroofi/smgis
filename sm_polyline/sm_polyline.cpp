/***************************************************************************
                        sm_polyline.cpp - SMGIS
                              -------------------
     begin                :  July 10 2012
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
#include "sm_polyline.h"
#include <string>
int SmPolyline::cstr_cntr=0;
SmPolyline::SmPolyline():number_of_lines_(0),total_number_of_points_(0),point_array_(0),line_index_(0)
{
cstr_cntr++;
}

SmPolyline::SmPolyline(const unsigned int &num_of_line, const unsigned int &num_of_point)
    :number_of_lines_(num_of_line),total_number_of_points_(num_of_point),point_array_(0),line_index_(0)
{
    cstr_cntr++;
    number_of_lines_=num_of_line;
    total_number_of_points_=num_of_point;
    line_index_=new int[number_of_lines_];
    point_array_=new SmPoint[total_number_of_points_];

}

SmPolyline::~SmPolyline()
{
    cstr_cntr--;
    if (line_index_)
        delete[] this->line_index_;
    if (point_array_)
        delete[] this->point_array_;
}
SmPolyline::SmPolyline(const SmPolyline & other)
{
    cstr_cntr++;
    this->number_of_lines_=other.number_of_lines_;
    this->total_number_of_points_=other.total_number_of_points_;
    this->bounding_box_[0]=other.bounding_box_[0];
    this->bounding_box_[1]=other.bounding_box_[1];
    this->bounding_box_[2]=other.bounding_box_[2];
    this->bounding_box_[3]=other.bounding_box_[3];
    this->point_array_=new SmPoint[this->total_number_of_points_];
    this->line_index_=new int[this->number_of_lines_];
    for (unsigned int i=0;i<this->total_number_of_points_;i++){
        point_array_[i].set_x_(other.point_array_[i].get_x_());
        point_array_[i].set_y_(other.point_array_[i].get_y_());
    }
    for(unsigned int i=0;i<this->number_of_lines_;i++)
        this->line_index_[i]=other.line_index_[i];
}

const double SmPolyline::get_y_max(void)
{
    return this->bounding_box_[3];
}


const double SmPolyline::get_y_min(void)
{
    return this->bounding_box_[1];
}


const double SmPolyline::get_x_max(void)
{
    //std::cout<<"X max is : "<<bounding_box_[2]<<std::endl;
    return this->bounding_box_[2];
}


const double SmPolyline::get_x_min(void)
{
   //std::cout<<"X min is : "<<bounding_box_[0]<<std::endl;
    return this->bounding_box_[0];
}
const int SmPolyline::get_number_of_lines(void)
{
    return this->number_of_lines_;
}

void SmPolyline::set_bounding_box_(const double *bb)
{
    this->bounding_box_[0]=bb[0];
    this->bounding_box_[1]=bb[1];
    this->bounding_box_[2]=bb[2];
    this->bounding_box_[3]=bb[3];
}
void  SmPolyline::set_line_index_(const unsigned int &index,const int & val)
{
    if (this->line_index_ && index< number_of_lines_ )
    {
        line_index_[index]=val;
    }
}

void SmPolyline::set_point_array_(const unsigned int& index, SmPoint* smp)
{
    if (index<total_number_of_points_ && point_array_)
    {
       this->point_array_[index].set_x_(smp->get_x_());
        this->point_array_[index].set_y_(smp->get_y_());
    }
}

const int  SmPolyline::get_total_number_of_points_(void)
{
    return this->total_number_of_points_;
}
 SmPoint *SmPolyline::get_point_at(const unsigned int & index)const
{
    if (index<this->total_number_of_points_)
    {
        return &(point_array_[index]);
    }
    return NULL;
}

 int * SmPolyline::get_line_index_()
 {
     return line_index_;
 }
