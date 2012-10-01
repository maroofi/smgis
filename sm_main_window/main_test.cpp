/***************************************************************************
                            main_test.cpp - SMGIS
                              -------------------
     begin                :  August 5 2012
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
#include "sm_main_window.h"
#include "../sm_esri_shp_format/sm_esri_shp_format.h"
#include <QPixmap>
int main(int argc,char * argv[])
{
    QApplication::setGraphicsSystem("raster");
    QApplication app(argc,argv);
      SmViewPanel * smvp=new SmViewPanel();
    SmMainWindow * smmw=new SmMainWindow(smvp);


    /*
    ** agar az in khate QPainter::Antialiasing nabashad tanha moredi ke darad in ast
    ** ke naghshe yek kami dar noe ghalam keshidan fargh mikone va sotooh smooth nist
    ** vali nemidoonam in harkaat ezafi cheghadr masrafe hafeze ro bala mibare.
    */
    smvp->setRenderHints(QPainter::Antialiasing| QPainter::SmoothPixmapTransform);


    smvp->scale(1,-1);
    smmw->set_graphic_handle_(smvp);
    smmw->setCentralWidget(smvp);
    smmw->showMaximized();
    smmw->show();
    return app.exec();

}
