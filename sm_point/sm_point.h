/***************************************************************************
                            sm_point.h - SMGIS
                              -------------------
     begin                :  July 12 2012
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
#ifndef SM_POINT_H
#define SM_POINT_H
#include <QPointF>
#include <string>
#include <iostream>
class SmPoint:public QPointF
{

    private:
    unsigned int sm_x_pixel;    /*these are pixel values on device screen*/
    unsigned int sm_y_pixel;
    double sm_x_;
    double sm_y_;

    public:
    static int cstr_cntr;
   // void calculate_real_pixel(const double&,const double &);
    SmPoint(double x=0,double y=0);
    SmPoint (const SmPoint&);
    ~SmPoint();
    std::string well_known_text() const;
    const double get_x_(void);
    const double get_y_(void);
    int set_x_(const double x);
    int set_y_(const double y);
    SmPoint & operator=(const SmPoint& other);
    bool operator==(const SmPoint &);
    SmPoint operator+(const SmPoint &);
    SmPoint operator+(const double&);
    SmPoint operator+(const int &);
    SmPoint operator*(const int &);
    SmPoint operator*(const double &);
    SmPoint operator*(const SmPoint &);


};
#endif
