/***************************************************************************
                            sm_ponit.cpp - SMGIS
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

#include <iostream>
#include <string>
#include <sstream>
#include "sm_point.h"
int SmPoint::cstr_cntr=0;
/*
**Deconstructor
*/
SmPoint::~SmPoint(){cstr_cntr--;}



/**
  * Construct point from another point
  */


SmPoint::SmPoint(const SmPoint& other):QPointF(other)
{
    cstr_cntr++;
    this->sm_x_=other.sm_x_;
    this->sm_y_=other.sm_y_;
    this->setX(this->sm_x_);
    this->setY(this->sm_y_);
}

/**
  * Construct point from x,y like SmPoint temp(1.2343,2.676)
  */
SmPoint::SmPoint(double x,double y):QPointF(x,y)
{
    cstr_cntr++;
    this->sm_x_=x;
    this->sm_y_=y;
}

/**
  * overloading * operator useage : temp=temp*other
  */
SmPoint SmPoint::operator*(const SmPoint& other)
{
    SmPoint temp;
    temp.sm_x_=this->sm_x_*other.sm_x_;
    temp.sm_y_=this->sm_y_*other.sm_y_;
    return temp;
}

/**
  * overloading operator * usage : temp=temp*other
  */
SmPoint SmPoint::operator*(const double& other)
{
    SmPoint temp;
    temp.sm_x_=this->sm_x_*other;
    temp.sm_y_=this->sm_y_*other;
    return temp;
}

/**
  * same as above code but for integer
  */
SmPoint SmPoint::operator*(const int & other)
{
   SmPoint temp;
   temp.sm_x_=other*this->sm_x_;
   temp.sm_y_=other*this->sm_y_;
   return temp;

}

/**
  * overloading operator +
  */
SmPoint SmPoint::operator+(const int & other)
{
    SmPoint temp;
    temp.sm_x_=this->sm_x_+(double)other;
    temp.sm_y_=this->sm_y_+(double)other;
    return temp;
}

/**
  * same as above but for double number
  */
SmPoint SmPoint::operator+(const double& other)
{
    SmPoint temp;
    temp.sm_x_+=other;
    temp.sm_y_+=other;
    return temp;
}

/**
  * overloading operator + for adding two Smpoint class variable
  */
SmPoint SmPoint::operator+(const SmPoint & other)
{
    SmPoint temp;
    temp.sm_x_=this->sm_x_+other.sm_x_;
    temp.sm_y_=this->sm_y_+other.sm_y_;
    return temp;
}

/**
  * comparison between two SmPoint class variable
  */
bool SmPoint::operator==(const SmPoint & other)
{
    return ((this->sm_x_==other.sm_x_ && this->sm_y_==other.sm_y_)?true:false);
}

/**
  * assignement operator overloading
  */
SmPoint & SmPoint::operator=(const SmPoint& other)
{
    this->sm_x_=other.sm_x_;
    this->sm_y_=other.sm_y_;
    return *this;
}

/**
  * setter for setting Y value of a point
  */
int SmPoint::set_y_(const double y)
{
    this->sm_y_=y;
    this->setY(y);
    return 0;
}

/**
  * setter for setting X value of the point
  */
int SmPoint::set_x_(const double x)
{
    sm_x_=x;
    this->setX(x);
    return 0;
}

/**
  * return Y value of a point
  */
const double SmPoint::get_y_(void)
{
    return this->sm_y_;
}

/**
  * return X value of the point

  */
const double SmPoint::get_x_(void)
{
    return this->sm_x_;
}

std::string SmPoint::well_known_text() const
{

    std::string res="POINT(";
    std::stringstream strs;
    strs<<this->sm_x_;
    std::string str=strs.str();
    res=res+str+ ",";
    //strs.ignore(100);
    //flush sstream here
    strs.str("");
    strs<<this->sm_y_;
    str=strs.str();
    res=res+str+")";
    return res;
}
