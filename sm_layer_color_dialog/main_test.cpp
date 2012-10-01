/***************************************************************************
                       main_test.cpp - SMGIS
                              -------------------
     begin                :  August 14 2012
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
#include "sm_layer_color_dialog.h"

int main(int argc,char ** argv)
{
    QColor col(100,100,100);
    QApplication app(argc,argv);
   SmLayerColorDialog* smlcd  =new SmLayerColorDialog(col);
   smlcd->setModal(true);
   int res=smlcd->exec();
   switch(res)
{
        case QDialog::Accepted:
        {
                std::cout<<"accepted by ok butt"<<std::endl;
                QColor cl=smlcd->get_layer_color();
                std::cout<<"color is :"<<cl.name().toStdString()<<std::endl;
                delete smlcd;
                break;
        }
        case QDialog::Rejected:
        {
             std::cout<<"rejected anyway"<<std::endl;
             delete smlcd;
            break;
        }
        default:
             std::cout<<"hi"<<std::endl;
}
    app.exec();
}
