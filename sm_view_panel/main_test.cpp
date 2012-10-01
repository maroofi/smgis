/***************************************************************************
                            ain_test.cpp - SMGIS
                              -------------------
     begin                : Thursday July 23 2012
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
#include <QApplication>
#include "../sm_esri_shp_format/sm_esri_shp_format.h"
#include <QVBoxLayout>

int main(int argc,char** argv)
{
    QApplication::setGraphicsSystem("raster");
    QApplication app(argc,argv);

    SmViewPanel *smvp=new SmViewPanel();
    SmEsriSHPFormat * esri=new SmEsriSHPFormat("LPoint.shp",smvp); //LotPoint.shp",smvp);
//    std::cout<<(int)smvp->width()<<":"<<(int)smvp->height()<<std::endl;
    smvp->show();
    //wi->show();
//    std::cout<<"counter is:(SmGeoItem)  "<<SmGeoItem::ret_cstr() <<std::endl;
//    std::cout<<"counter is:(SmPolyline)  "<<SmPolyline::cstr_cntr <<std::endl;
//    std::cout<<"counter is:(SmPoint)  "<<SmPoint::cstr_cntr <<std::endl;
//    std::cout<<"counter is:(SmPolygon)  "<<SmPolygon::cstr_cntr <<std::endl;
    return app.exec();

}
