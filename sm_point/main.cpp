/***************************************************************************
                            main_test.cpp - SMGIS
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
#include "sm_point.h"
using namespace std;

int main()
{
    SmPoint a(1.23456,-9.34598);
    cout<<"X value is ax: "<<a.get_x_()<<endl;
    cout<<"Y value is ay: "<<a.get_y_()<<endl;
    SmPoint b;
    b.set_x_(4.5678);
    b.set_y_(3.5678998765);
    cout<<"X value is bx: "<<b.get_x_()<<endl;
    cout<<"Y value is by: "<<b.get_y_()<<endl;
    SmPoint c,d,e,f;
    c=a+b;
    d=a+2;
    e=b*4;
    f=a*b;
    SmPoint g(a);
    cout<<"X value is : ax : "<<a.get_x_()<<endl;
    cout<<"Y value is : ay : "<<a.get_y_()<<endl;
    cout<<"X value is : bx : "<<b.get_x_()<<endl;
    cout<<"Y value is : by : "<<b.get_y_()<<endl;
    cout<<"X value is : cx=a+b : "<<c.get_x_()<<endl;
    cout<<"Y value is : cy=a+b : "<<c.get_y_()<<endl;
    cout<<"X value is : dx=a+2 : "<<d.get_x_()<<endl;
    cout<<"Y value is : dy=a+2 : "<<d.get_y_()<<endl;
    cout<<"X value is : ex=b*4 : "<<e.get_x_()<<endl;
    cout<<"Y value is : ey=b*4 : "<<e.get_y_()<<endl;
    cout<<"X value is : fx=a*b : "<<f.get_x_()<<endl;
    cout<<"Y value is : fy=a*b : "<<f.get_y_()<<endl;
    cout<<"X value is : ax : "<<a.get_x_()<<endl;
    cout<<"Y value is : ay : "<<a.get_y_()<<endl;
    cout<<"X value is : bx : "<<b.get_x_()<<endl;
    cout<<"Y value is : by : "<<b.get_y_()<<endl;
    cout<<a.well_known_text()<<endl;
    cout<<b.well_known_text()<<endl;
    cout<<c.well_known_text()<<endl;
    cout<<d.well_known_text()<<endl;
    cout<<e.well_known_text()<<endl;
    cout<<f.well_known_text()<<endl;
    cout<<"a.x from base class QPointf : "<<a.x()<<endl;
    cout<<g.well_known_text()<<endl;
    return 0;
}
