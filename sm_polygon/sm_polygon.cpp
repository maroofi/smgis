/***************************************************************************
                            sm_polygon.cpp - SMGIS
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
#include "sm_polygon.h"
int SmPolygon::cstr_cntr=0;
SmPolygon::SmPolygon()
    :number_of_part_(0),total_number_of_points_(0),part_index_(0),point_array_(0)
{
    cstr_cntr++;
}
SmPolygon::SmPolygon(const unsigned int & num_parts, const unsigned int & num_points)
    :number_of_part_(num_parts),total_number_of_points_(num_points),point_array_(0),part_index_(0)
{
    cstr_cntr++;
    this->number_of_part_=num_parts;
    this->total_number_of_points_=num_points;
    part_index_=new int[number_of_part_];
    point_array_=new SmPoint[total_number_of_points_];
}

SmPolygon::SmPolygon(const SmPolygon & other)
{
    cstr_cntr++;
    this->number_of_part_=other.number_of_part_;
    this->total_number_of_points_=other.total_number_of_points_;
    this->bounding_box_[0]=other.bounding_box_[0];
    this->bounding_box_[1]=other.bounding_box_[1];
    this->bounding_box_[2]=other.bounding_box_[2];
    this->bounding_box_[3]=other.bounding_box_[3];
    this->point_array_=new SmPoint[this->total_number_of_points_];
    this->part_index_=new int[this->number_of_part_];
    for (unsigned int i=0;i<this->total_number_of_points_;i++)
    {
        point_array_[i].set_x_(other.point_array_[i].get_x_());
        point_array_[i].set_y_(other.point_array_[i].get_y_());
//        this->push_back(this->point_array_[i]);
    }
    for(unsigned int i=0;i<this->number_of_part_;i++)
        this->part_index_[i]=other.part_index_[i];


}
SmPolygon::~SmPolygon()
{
    cstr_cntr--;
    if (part_index_)
        delete[] this->part_index_;
    if (point_array_)
        delete[] this->point_array_;
}

void SmPolygon::set_point_array_(const unsigned int& index, SmPoint* smp)
{
    if (index<total_number_of_points_ && point_array_)
    {
       this->point_array_[index].set_x_(smp->get_x_());
        this->point_array_[index].set_y_(smp->get_y_());
//       this->push_back(this->point_array_[index]);
    }
}

void SmPolygon::set_part_index_(const unsigned int & index, const int & val)
{
    if (this->part_index_ && index< number_of_part_ )
    {
        part_index_[index] =val;
    }
}

const double SmPolygon::get_x_min(void)
{
    return this->bounding_box_[0];
}
const double SmPolygon::get_y_min(void)
{
    return this->bounding_box_[1];
}

const double SmPolygon::get_x_max(void)
{
    return this->bounding_box_[2];
}

const double SmPolygon::get_y_max(void)
{
    return this->bounding_box_[3];
}
void SmPolygon::set_bounding_box_(const double *bb)
{
    this->bounding_box_[0]=bb[0];
    this->bounding_box_[1]=bb[1];
    this->bounding_box_[2]=bb[2];
    this->bounding_box_[3]=bb[3];
}
const int SmPolygon::get_number_of_part_(void)
{
    return this->number_of_part_;
}

const int SmPolygon::get_total_number_of_points_(void)
{
    return this->total_number_of_points_;
}

SmPoint *SmPolygon::get_point_at(const unsigned int & index)const
{
   if (index<this->total_number_of_points_)
   {
       return &(point_array_[index]);
   }
   return NULL;
}

SmPoint *SmPolygon::get_point_array_(void)
{
        return this->point_array_;
}

int * SmPolygon::get_part_index_(void)
{
    return part_index_;
}
