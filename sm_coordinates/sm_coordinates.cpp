/***************************************************************************
                        sm_coordinates.cpp - SMGIS
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

#include <string.h>
#include <math.h>
#include "sm_coordinates.h"
#include <stdio.h>


SmCoordinates::SmCoordinates()
{
    current_datum_=new smgis::SmDatum[1];
    last_error_="";
    current_datum_->stDatum=smgis::WGS84;
    current_datum_->stER=kWGS84_ER;
    current_datum_->stPR=kWGS84_PR;
    current_datum_->stFT=kWGS84_FT;
    current_datum_->stOOF=kWGS84_OOF;

}



std::string SmCoordinates::get_last_error(void)
{
    return last_error_;
}


 smgis::SmDatum *SmCoordinates::get_current_datum_(void)
{

    return current_datum_;
}

 int SmCoordinates::set_current_datum_(smgis::Datum dt)
 {
     switch(dt){
     case(smgis::NAD83):{
            current_datum_->stDatum=smgis::NAD83;
            current_datum_->stER=kNAD83_ER;
            current_datum_->stFT=kNAD83_FT;
            current_datum_->stPR=kNAD83_PR;
            current_datum_->stOOF=kNAD83_OOF;
            return 0;
     }
     case(smgis::WGS84):{
         current_datum_->stDatum=smgis::WGS84;
         current_datum_->stER=kWGS84_ER;
         current_datum_->stFT=kWGS84_FT;
         current_datum_->stPR=kWGS84_PR;
         current_datum_->stOOF=kWGS84_OOF;
         return 0;
     }
     case(smgis::WGS72):{
         current_datum_->stDatum=smgis::WGS72;
         current_datum_->stER=kWGS72_ER;
         current_datum_->stFT=kWGS72_FT;
         current_datum_->stPR=kWGS72_PR;
         current_datum_->stOOF=kWGS72_OOF;
         return 0;
     }
     case(smgis::Australian1965):{
         current_datum_->stDatum=smgis::Australian1965;
         current_datum_->stER=kAustralian1965_ER;
         current_datum_->stFT=kAustralian1965_FT;
         current_datum_->stPR=kAustralian1965_PR;
         current_datum_->stOOF=kAustralian1965_OOF;
         return 0;
     }
     case(smgis::Krasovsky1940):{
         current_datum_->stDatum=smgis::Krasovsky1940;
         current_datum_->stER=kKrasovsky1940_ER;
         current_datum_->stFT=kKrasovsky1940_FT;
         current_datum_->stPR=kKrasovsky1940_PR;
         current_datum_->stOOF=kKrasovsky1940_OOF;
         return 0;
     }
     case(smgis::NorthAmerican1927):{
         current_datum_->stDatum=smgis::NorthAmerican1927;
         current_datum_->stER=kNorthAmerican1927_ER;
         current_datum_->stFT=kNorthAmerican1927_FT;
         current_datum_->stPR=kNorthAmerican1927_PR;
         current_datum_->stOOF=kNorthAmerican1927_OOF;
         return 0;
     }
     case(smgis::International1924):{
         current_datum_->stDatum=smgis::International1924;
         current_datum_->stER=kInternational1924_ER;
         current_datum_->stFT=kInternational1924_FT;
         current_datum_->stPR=kInternational1924_PR;
         current_datum_->stOOF=kInternational1924_OOF;
         return 0;
     }
     case(smgis::Hayford1909):{
         current_datum_->stDatum=smgis::Hayford1909;
         current_datum_->stER=kHayford1909_ER;
         current_datum_->stFT=kHayford1909_FT;
         current_datum_->stPR=kHayford1909_PR;
         current_datum_->stOOF=kHayford1909_OOF;
         return 0;
     }
     case(smgis::Clarke1880):{
         current_datum_->stDatum=smgis::Clarke1880;
         current_datum_->stER=kClarke1880_ER;
         current_datum_->stFT=kClarke1880_FT;
         current_datum_->stPR=kClarke1880_PR;
         current_datum_->stOOF=kClarke1880_OOF;
         return 0;
     }
     case(smgis::Clarke1866):{
         current_datum_->stDatum=smgis::Clarke1866;
         current_datum_->stER=kClarke1866_ER;
         current_datum_->stFT=kClarke1866_FT;
         current_datum_->stPR=kClarke1866_PR;
         current_datum_->stOOF=kClarke1866_OOF;
         return 0;
     }
     case(smgis::Airy1830):{
         current_datum_->stDatum=smgis::Airy1830;
         current_datum_->stER=kAiry1830_ER;
         current_datum_->stFT=kAiry1830_FT;
         current_datum_->stPR=kAiry1830_PR;
         current_datum_->stOOF=kAiry1830_OOF;
         return 0;
     }
     case(smgis::Bessel1841):{
         current_datum_->stDatum=smgis::Bessel1841;
         current_datum_->stER=kBessel1841_ER;
         current_datum_->stFT=kBessel1841_FT;
         current_datum_->stPR=kBessel1841_PR;
         current_datum_->stOOF=kBessel1841_OOF;
         return 0;
     }
     case(smgis::Everest1830):{
         current_datum_->stDatum=smgis::Everest1830;
         current_datum_->stER=kEverest1830_ER;
         current_datum_->stFT=kEverest1830_FT;
         current_datum_->stPR=kEverest1830_PR;
         current_datum_->stOOF=kEverest1830_OOF;
         return 0;
     }
     default:{
         current_datum_->stDatum=smgis::WGS84;
         current_datum_->stER=kWGS84_ER;
         current_datum_->stFT=kWGS84_FT;
         current_datum_->stPR=kWGS84_PR;
         current_datum_->stOOF=kWGS84_OOF;
         return 0;
     }
     };

 }

int SmCoordinates::convetrtLatLong2UTM(double & x,double & y, bool & aboveEquator)
{
    /*x is longitude and y is latitude*/
    if ( x>180 || x<-180  || y>90 || y<-90){
        last_error_="Wrong Latitude or Longitude as Parameters";
        return -1;
    }
    if (y<0)
        aboveEquator=false;
    else
        aboveEquator=true;
    double zone;   /*zone is between 1 to 60,each zone is 6 degree*/


    zone=x+180.0;
    zone=zone/6.0;
    zone=floor(zone);
    zone+=1;

    //std::cout<<"Zone Number : "<<zone<<std::endl;
    double P;

    P=this->convertDecimalDegree2Radian((180.0+x)-(zone*6.0-3.0));
    x=convertDecimalDegree2Radian(x);
    y=convertDecimalDegree2Radian(y);
   // zone=convertDecimalDegree2Radian(zone);
   // std::cout<<"P is : "<<P<<std::endl;





    double M=current_datum_->stER * (((1-(SM_E*SM_E/4.0)-(3.0* SM_E*SM_E*SM_E*SM_E/64.0)
                                     -(5.0*SM_E*SM_E*SM_E*SM_E*SM_E*SM_E/256.0))*y)-
                                     (  (3.0*SM_E*SM_E/8.0 + 3.0*SM_E*SM_E*SM_E*SM_E/32.0
                                         + 45.0*SM_E*SM_E*SM_E*SM_E*SM_E*SM_E/1024.0)*sin(2.0*y))
                                     + ((15.0*SM_E*SM_E*SM_E*SM_E/256.0 + 45.0*SM_E*SM_E*SM_E
                                         *SM_E*SM_E*SM_E/1024.0 )*sin(4.0*y) )
                                     - ((35.0*SM_E*SM_E*SM_E*SM_E*SM_E*SM_E/3072.0)*sin(6.0*y)));
    double  k1=M*SM_K0;
    double nu=current_datum_->stER/(sqrt(((1-SM_E*SM_E*sin(y)*sin(y)))));
    double k2=SM_K0 * nu*sin(2*y)/4.0;
    double k3=(SM_K0*nu *sin(y)* cos(y)*cos(y)*cos(y)/24.0)*
            (5.0-tan(y)*tan(y)+ 9.0*SM_EPRIME_POWER_2*SM_EPRIME_POWER_2*
             cos(y)*cos(y)+4.0*SM_EPRIME_POWER_2*SM_EPRIME_POWER_2*
             SM_EPRIME_POWER_2*SM_EPRIME_POWER_2*cos(y)*cos(y)*cos(y)*cos(y));

    double k4=SM_K0*nu*cos(y);
    double k5=(SM_K0*nu*cos(y)*cos(y)*cos(y)/6.0)*(1-tan(y)*tan(y)+
                                                   SM_EPRIME_POWER_2*SM_EPRIME_POWER_2*cos(y)*cos(y));
    x=k4*P+k5*P*P*P;
    y=k1+k2*P*P+k3*P*P*P*P;
    /*Easting x is relative to the central meridian.
 For conventional UTM easting add 500,000 meters to x.*/
    x+=500000;
    if (aboveEquator==false)
        y+=10000000;
    return zone;
}

int  SmCoordinates::convertUTM2LatLong(double & x,double & y,int zone,bool aboveEquator)
{

    if (zone > 60 || zone<1){
        last_error_="Central Meridian could be between 1~60";
        return -1;
    }
    double Zone=(double)zone;
    if (aboveEquator==false)
       y-=10000000;
    x-=500000;

    double M=y/SM_K0;
    double mu=M/( current_datum_->stER*(1-SM_E*SM_E/4-3*SM_E*SM_E*SM_E*SM_E/64
                                      -5*SM_E*SM_E*SM_E*SM_E*SM_E*SM_E/256));
    double e1=(1-sqrt(1-SM_E*SM_E))/( 1+sqrt(1-SM_E*SM_E));
    double j1=3*e1/2-27*e1*e1*e1/32;
    double j2=21*e1*e1/16-55*e1*e1*e1*e1/32;
    double j3=151*e1*e1*e1/96;
    double j4=1097*e1*e1*e1*e1/512;
    double fp=mu+j1*sin(2*mu)+j2*sin(4*mu)+j3*sin(6*mu)+j4*sin(8*mu);
    double c1=SM_EPRIME_POWER_2*SM_EPRIME_POWER_2*cos(fp)*cos(fp);
    double t1=tan(fp)*tan(fp);
    double n1=current_datum_->stER/(sqrt(1-SM_E*SM_E*sin(fp)*sin(fp)));
    double d=x/(n1*SM_K0);
    double r1=(current_datum_->stER*(1-SM_E*SM_E))/((1-SM_E*SM_E*sin(fp)*sin(fp))*
                                     (sqrt(1-SM_E*SM_E*sin(fp)*sin(fp))));
    double q1=n1*tan(fp)/r1;
    double q2=d*d/2;
    double q3=(5+3*t1+10*c1-4*c1*c1-9*SM_EPRIME_POWER_2*SM_EPRIME_POWER_2)*d*d*d*d/24;
    double q4=(61+90*t1+298*c1+45*t1*t1-3*c1*c1-252*SM_EPRIME_POWER_2*SM_EPRIME_POWER_2)
            *d*d*d*d*d*d/720;
    double q5=d;
    double q6=(1+2*t1+c1)*d*d*d/6;
    double q7=(5-2*c1+28*t1-3*c1*c1+8*SM_EPRIME_POWER_2*SM_EPRIME_POWER_2+24*t1*t1)
            *d*d*d*d*d/120;
     y=fp-q1*(q2-q3+q4);
     Zone=(Zone*6)-3-180;
     Zone=this->convertDecimalDegree2Radian(Zone);
     x=Zone+((q5-q6+q7)/cos(fp));
    x=this->convertRadian2DecimalDegree(x);
    y=this->convertRadian2DecimalDegree(y);

}


double  SmCoordinates::convertDecimalDegree2Radian(double dd_ff)
{
    //std::cout<<"x in radius is : "<<dd_ff*kSmPi/180<<std::endl;
    return double(dd_ff*kSmPi/180);

}

double SmCoordinates::convertRadian2DecimalDegree(double rad)
{
    return double(rad*180/kSmPi);
}

