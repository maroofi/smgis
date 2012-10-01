/***************************************************************************
                            main_test.cpp - SMGIS
                              -------------------
     begin                : Thursday July 15 2012
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
#include "sm_esri_shp_format.h"
#include <iostream>
using namespace std;
int main()
{

    SmEsriSHPFormat *s=new SmEsriSHPFormat();
    s->set_shp_file_name("MyPoint.shp");
    s->read_shp_file();
    return 0;
}
