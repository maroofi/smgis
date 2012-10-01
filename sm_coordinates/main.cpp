/***************************************************************************
                            main_test.cpp - SMGIS
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

#include "sm_coordinates.h"
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

int main(){
    SmCoordinates * s=new SmCoordinates();
    double x,y;
    bool aE;
    x=59.569936;
    y=36.310898;
    int zone;
    zone=s->convetrtLatLong2UTM(x,y,aE);

    cout<<setprecision(15)<<"x in UTM is : "<<x<<endl<<"y in UTM is :"<<y<<endl;
    cout<<"position relative to equator :";
    if (aE)
        cout<<"N"<<endl;
    else
        cout<<"S"<<endl;

    x=730733;
    y=4021498;

    s->convertUTM2LatLong(x,y,40,true);
    //cout<<"Zone number is: "<<zone;
    cout<<endl<<"lat is :"<<y<<endl<<"long is :"<<x<<endl;
    return 0;
}
