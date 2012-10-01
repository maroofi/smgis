/***************************************************************************
                           sm_esri_rest.cpp - SMGIS
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
#include "sm_esri_rest.h"

SmEsriREST::SmEsriREST()
{
//    graphic_handle_=g_h;
    connection_name_="";
    rest_url_="";
    extent_xmin_=0;
    extent_xmax_=0;
    extent_ymin_=0;
    extent_ymax=0;
    image_width_=0;
    image_height_=0;
    image_scale_=0;
    image_url_="";
}

int SmEsriREST::load_rest_map(void)
{

}

void SmEsriREST::set_connection_name_(std::string cn)
{
    this->connection_name_=cn;
}

void SmEsriREST::set_rest_url_(std::string ru)
{
    this->rest_url_=ru;
}

std::string SmEsriREST::get_connection_name_(void)
{
    return this->connection_name_;
}

std::string SmEsriREST::get_rest_url_(void)
{
    return this->rest_url_;
}

std::string SmEsriREST::get_map_name_(void)
{
    return this->map_name_;
}
void SmEsriREST::set_map_name_(std::string mn)
{
    map_name_=mn;
}

void SmEsriREST::set_image_width_(int iwh)
{
    image_width_=iwh;
}
void SmEsriREST::set_image_height_(int ihe)
{
    image_height_=ihe;
}

void SmEsriREST::set_image_scale_(double ise)
{
    image_scale_=ise;
}

void SmEsriREST::set_extent_xmin_(double exn)
{
    extent_xmin_=exn;
}

void SmEsriREST::set_extent_ymin_(double eyn)
{
    extent_ymin_=eyn;
}

void SmEsriREST::set_extent_xmax_(double exx)
{
    extent_xmax_=exx;
}

void SmEsriREST::set_extent_ymax_(double eyx)
{
    extent_ymax=eyx;
}

void SmEsriREST::set_image_url_(std::string iu)
{
      image_url_=iu;
}

std::string SmEsriREST::get_image_url_(void)
{
    return image_url_;
}

double SmEsriREST::get_extent_xmin_(void)const
{
    return extent_xmin_;
}

double SmEsriREST::get_extent_ymin_(void)const
{
    return extent_ymin_;
}

double SmEsriREST::get_extent_xmax_(void)const
{
    return extent_xmax_;
}

double SmEsriREST::get_extent_ymax_(void)const
{
    return extent_ymax;
}

int SmEsriREST::get_image_width_(void)const
{
    return image_width_;
}

int SmEsriREST::get_image_height_(void)const
{
    return image_height_;
}

double SmEsriREST::get_image_scale_(void)const
{
    return image_scale_;
}
