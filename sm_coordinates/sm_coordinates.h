/***************************************************************************
                            sm_coordinates.h - SMGIS
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

#ifndef SM_COORDINATES_H
#define SM_COORDINATES_H
#include <string>
#include <iostream>
#include "../sm_shape_general/sm_shape_general.h"
//using namespace std;
#define DEGREE_OF_LONGITUDE_AT_EQUATOR    111200   /*In Meters*/
#define MINUTE_IN_METER_AT_EQUATOR        1853
#define SECOND_IN_METER_AT_EQUATOR       30.9
                /*for other latitude we should multiply it by cos(lat)*/
#define SM_K0  0.9996 /*scale along central meridian of zone*/
#define SM_E   .08     /*This is the eccentricity of the earth's elliptical cross-section*/
#define SM_EPRIME_POWER_2    .007





     /*all of the below numbers are standards and in Meter unit*/

           /*this holds the current Datum*/



  const double kSmPi =3.14159265358979;

 static const double kNAD83_ER=6378137;                         /*Equatorial Radius =ER*/
 static const double kNAD83_FT  = 0.0033528106643315515 ;        /*Flattening=FT*/
 static const double kNAD83_PR =  6356752.314247833 ;             /*Polar Radius =PR*/
 static const double kNAD83_OOF=   298.2572236 ;                  /*1/Flattening=OOF*/
 static const double kWGS84_ER=6378137;
 static const double kWGS84_FT=0.0033528106643315515;
 static const double kWGS84_PR=6356752.314247833;
 static const double kWGS84_OOF=298.2572236;
 static const double kWGS72_ER=6378135;
 static const double kWGS72_FT=0.0033527;
 static const double kWGS72_PR=6356750.4;
 static const double kWGS72_OOF=298.2597208;
 static const double kAustralian1965_ER=6378160;
 static const double kAustralian1965_FT=0.0033528;
 static const double kAustralian1965_PR=6356774.7;
 static const double kAustralian1965_OOF=298.2497323;
 static const double kKrasovsky1940_ER=6378245;
 static const double kKrasovsky1940_FT=0.0033523;
 static const double kKrasovsky1940_PR=6356863;
 static const double kKrasovsky1940_OOF=298.2997381;
 static const double kNorthAmerican1927_ER=6378206.4;
 static const double kNorthAmerican1927_FT=0.00339;
 static const double kNorthAmerican1927_PR=6356583.7;
 static const double kNorthAmerican1927_OOF=294.9786982;
 static const double kInternational1924_ER =6378388;
 static const double kInternational1924_FT =0.003367;
 static const double kInternational1924_PR =6356911.9;
 static const double kInternational1924_OOF =296.9993621;
 static const double kHayford1909_ER  =6378388;
 static const double kHayford1909_FT  =0.003367;
 static const double kHayford1909_PR  =6356911.9;
 static const double kHayford1909_OOF  =296.9993621;
 static const double kClarke1880_ER =6378249.1;
 static const double kClarke1880_FT =0.0034075;
 static const double kClarke1880_PR =6356514.9;
 static const double kClarke1880_OOF =293.4660167;
 static const double kClarke1866_ER  =6378206.4;
 static const double kClarke1866_FT  =0.00339;
 static const double kClarke1866_PR  =6356583.7;
 static const double kClarke1866_OOF  =294.9786982;
 static const double kAiry1830_ER    =6377563.4;
 static const double kAiry1830_FT    =0.0033408;
 static const double kAiry1830_PR    =6356256.8;
 static const double kAiry1830_OOF    =299.3247788;
 static const double kBessel1841_ER  =6377397.2;
 static const double kBessel1841_FT  =0.0033427;
 static const double kBessel1841_PR  =6356078.9;
 static const double kBessel1841_OOF  =299.1527052;
 static const double kEverest1830_ER  =6377276.3;
 static const double kEverest1830_FT  =0.0033244;
 static const double kEverest1830_PR  =6356075.3;
 static const double kEverest1830_OOF  =300.8021499;

class SmCoordinates{
    public :

        SmCoordinates();
        std::string get_last_error(void) ;           /*return description About error*/
      struct smgis::SmDatum*get_current_datum_(void);     /*return enum type Datum if succeed*/
       int set_current_datum_(smgis::Datum);      /*return 0 if succeed anything else in fail*/
       int  convetrtLatLong2UTM(double & x,double & y,bool & aboveEquator);
       int  convertUTM2LatLong(double &,double &,int ,bool);    /*return -1 if not succeed*/

    private:
   // double  SM_E;
    //double SM_EPRIME_POWER_2;
    struct  smgis::SmDatum * current_datum_;
        std::string last_error_;

       double convertDecimalDegree2Radian(double);
       double convertRadian2DecimalDegree(double);
};
#endif
