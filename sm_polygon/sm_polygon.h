/***************************************************************************
                            sm_polygon.h - SMGIS
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
#ifndef SM_POLYGON_H
#define SM_POLYGON_H

#include<QPolygonF>
#include <iostream>
#include <string>
#include "../sm_point/sm_point.h"
class SmPolygon//:public QPolygonF
{
public:
    static int cstr_cntr;
    /*
    **default constructor for the polygon class
    */
    SmPolygon();
    /*this constructor get number_of_part and total_number_of_points and allocate memory
    **for them and assign them to part_index and point_array_.
    */
    SmPolygon(const unsigned int &,const unsigned int &);
    ~SmPolygon();
    SmPolygon(const SmPolygon&);
    void set_bounding_box_(const double *bb);
    const double get_x_min(void);
    const double get_x_max(void);
    const double get_y_min(void);
    const double get_y_max(void);
    const int get_number_of_part_(void);
    const int get_total_number_of_points_(void);
    void set_point_array_(const unsigned int &,SmPoint *);
    void set_part_index_(const unsigned int &,const int &);
    SmPoint *get_point_at(const unsigned int & index)const;
    SmPoint * get_point_array_(void);
    int * get_part_index_(void);
    int * part_index_;
private:
    double bounding_box_[4];                  // Bounding Box
    unsigned int number_of_part_;            /* Number of rings in polygon based on esri shape format pdf*/
    unsigned int total_number_of_points_;     /* Total Number of Points*/
                           /* Index to First Point in Part*/
    SmPoint* point_array_;                    /* Points for All Parts*/

protected:

};

#endif
