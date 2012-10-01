/***************************************************************************
                           main.cpp - SMGIS
                              -------------------
     begin                :  September 29 2012
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
#include <QtGui/QApplication>
#include "sm_rest_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmRESTDialog w;
    w.show();
    
    return a.exec();
}
