/***************************************************************************
                            sm_multipoint.cpp - SMGIS
                              -------------------
     begin                : Thursday July 12 2012
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
#include "sm_multipoint.h"

    const double SmMultipoint::get_x_min(void)
    {
        return (this->bounding_box_[0]);
    }
    const double SmMultipoint::get_y_min(void)
    {
        return this->bounding_box_[1];
    }
    const double SmMultipoint::get_x_max(void)
    {
        return this->bounding_box_[2];
    }
    const double SmMultipoint::get_y_max(void)
    {
        return this->bounding_box_[3];
    }
    const int SmMultipoint::get_number_of_points_(void)
    {
        return this->number_of_points_;
    }
