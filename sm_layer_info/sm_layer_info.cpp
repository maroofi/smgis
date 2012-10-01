/***************************************************************************
                            sm_layer_info.cpp - SMGIS
                              -------------------
     begin                :  July 24 2012
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
#include "sm_layer_info.h"

int SmLayerInfo::assign_num_to_layer_=0;
SmLayerInfo::SmLayerInfo():layer_number_(0),layer_is_hidden_(false)
  ,width_interval_(0),height_interval_(0),layer_name_("")
{
    layer_color_=new QColor(214,205,104,255);

}

SmLayerInfo::SmLayerInfo(const SmLayerInfo &other)
{
    this->layer_name_=other.layer_name_;
    this->layer_is_hidden_=other.layer_is_hidden_;
    this->layer_number_=other.layer_number_;
    this->bounding_box_[0]=other.bounding_box_[0];
    this->bounding_box_[1]=other.bounding_box_[1];
    this->bounding_box_[2]=other.bounding_box_[2];
    this->bounding_box_[3]=other.bounding_box_[3];
    this->layer_color_=other.layer_color_;

}

bool SmLayerInfo::get_layer_is_hidden_() const
{
    return layer_is_hidden_;
}

int SmLayerInfo::get_layer_number_(void) const
{
    return layer_number_;
}

/*
**True if layer is hidden and false in else
*/
void SmLayerInfo::set_layer_is_hidden_(bool lyih)
{
    this->layer_is_hidden_=lyih;
}

/*
**Set the layer number to ln..the highest number means the layer is in the most top level
**and the lowest number means that the layer is down in the lowest level.
*/
void SmLayerInfo::set_layer_number_(int ln)
{
    this->layer_number_=ln;
}
/*
** bounding box of the layer is the most important part of the layer.
** This property specifies the width and height of the drawing area in the layer.
*/
void SmLayerInfo::set_bounding_box_(double *bb)
{
    this->bounding_box_[0]=bb[0];
    this->bounding_box_[1]=bb[1];
    this->bounding_box_[2]=bb[2];
    this->bounding_box_[3]=bb[3];
}

void SmLayerInfo::calculate_intervals(const int & w, const int & h)
{
   this->width_interval_=(bounding_box_[2]-bounding_box_[0])/(double)w;
    this->height_interval_=(bounding_box_[3]-bounding_box_[1])/(double)h;
    std::cout<<"width and height intervals is : "<<width_interval_
            <<"    "<<height_interval_<<std::endl;
}

double SmLayerInfo::get_x_min()
{
    return this->bounding_box_[0];
}

double SmLayerInfo::get_y_min()
{
    return this->bounding_box_[1];
}

double SmLayerInfo::get_width_interval_(void) const
{
    return this->width_interval_;
}

double SmLayerInfo::get_height_interval_(void) const
{
    return this->height_interval_;
}

void SmLayerInfo::set_layer_name_(std::string name)
{
    this->layer_name_=name;
}

std::string SmLayerInfo::get_layer_name_(void)
{
    return this->layer_name_;
}
int SmLayerInfo::get_assign_num_to_layer_()
{
    return assign_num_to_layer_;
}
void SmLayerInfo::set_increament_assign_num_to_layer()
{
    assign_num_to_layer_+=1;
}

smgis::SmShapeType SmLayerInfo::get_layer_shape_type_(void)const
{
    return layer_shape_type_;
}

void SmLayerInfo::set_layer_shape_type_(smgis::SmShapeType shpt)
{
    layer_shape_type_=shpt;
}

void SmLayerInfo::set_db_layer_id_(int dbli)
{
    db_layer_id=dbli;
}

int SmLayerInfo::get_db_layer_id_()
{
    return db_layer_id;
}
double SmLayerInfo::get_x_max(void)
{
    return bounding_box_[2];
}
double SmLayerInfo::get_y_max(void)
{
    return bounding_box_[3];
}
