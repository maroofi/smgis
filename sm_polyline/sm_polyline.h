/***************************************************************************
                            sm_polyline.h - SMGIS
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
#ifndef SM_POLYLINE_H
#define SM_POLYLINE_H
#include <string>
#include "../sm_point/sm_point.h"
/*stored in ESRI .shp file in little endian style.*/
/*what the fuck*/
class SmPolyline
{
  public:
    static int cstr_cntr;
    SmPolyline();
    SmPolyline(const unsigned int& ,const unsigned int &);
    SmPolyline(const SmPolyline&);
    ~SmPolyline();
    void set_line_index_(const unsigned int &,const int &);
    int * get_line_index_(void);
    void set_point_array_(const unsigned int &,SmPoint *);
    void set_bounding_box_(const double *);
const double get_x_min(void);
const double get_x_max(void);
const double get_y_min(void);
const double get_y_max(void);
const int get_number_of_lines(void);
const int get_total_number_of_points_(void);
SmPoint *get_point_at(const unsigned int &index) const;

  private:

  /*
  **The Bounding Box for the PolyLine stored in the order Xmin, Ymin, Xmax,
  **  Ymax.
  */
  double bounding_box_[4];                  // Bounding Box
  unsigned int number_of_lines_;            // Number of Parts
  unsigned int total_number_of_points_;     // Total Number of Points
  int * line_index_;                        // Index to First Point in Part
  SmPoint* point_array_;                    // Points for All Parts

};
#endif
