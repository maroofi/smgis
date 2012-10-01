/***************************************************************************
                            main_test.cpp - SMGIS
                              -------------------
     begin                : Thursday July 21 2012
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
#include <QApplication>
#include "sm_geo_item.h"
#include "../sm_esri_shp_format/sm_esri_shp_format.h"

int main(int argc,char ** argv)
{
    QApplication app(argc,argv);

    SmEsriSHPFormat * t=new SmEsriSHPFormat("MyPoint.shp",vi);


    return app.exec();
}
