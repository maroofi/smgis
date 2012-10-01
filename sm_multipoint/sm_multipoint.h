/***************************************************************************
                            sm_multipoint.h - SMGIS
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
#ifndef SM_MULTIPOINT_H
#define MULTIPOINT_H
#include <string>
#include <iostream>
#include "../sm_point/sm_point.h"
#include "../sm_shape_general/sm_shape_general.h"
class SmMultipoint
{
  private:
  /*    this is bounding box number in order of
  **    Xmin,Ymin,Xmax,Ymax
  */
  double bounding_box_[4];
  int number_of_points_;
  SmPoint* point_array_;

  public:

    const double get_x_min(void);
    const double get_y_min(void);
    const double get_x_max(void);
    const double get_y_max(void);
    const int get_number_of_points_(void);

};








#endif
