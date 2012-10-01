/***************************************************************************
                            sm_esri_shp_format.h - SMGIS
                              -------------------
     begin                :  July 15 2012
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
#ifndef SM_ESRI_SHP_FORMAT_H
#define SM_ESRI_SHP_FORMAT_H
#include <string>
#include <iostream>
#include <fstream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMessageBox>
#include "../sm_general/sm_general.h"
#include "../sm_point/sm_point.h"
#include "../sm_shape_general/sm_shape_general.h"
#include "../sm_geo_item/sm_geo_item.h"
#include "../sm_view_panel/sm_view_panel.h"
class SmEsriSHPFormat
{
    private:
    int read_point_feature(void);
    int read_polyline_feature(void);
    int read_polygon_feature(void);
            /*only read Xmin,Ymin,Xmax,Ymax*/
    double bounding_box_[4];
    smgis::SmShapeType esri_shape_type_;
             /*file_length_ is 16-bit word should multiply by 2*/
    unsigned int file_length_;
    std::ifstream* inp_file_;
    char * header_buffer_;
    std::string shp_file_name_;
    smgis::SmShapeType specify_shp_type(int);
    SmViewPanel * graphic_handle_;
    public:
    SmEsriSHPFormat(SmViewPanel * qgv=0);
    SmEsriSHPFormat(std::string,SmViewPanel * qgv=0);
    SmEsriSHPFormat(const char *,SmViewPanel * qgv=0);
    int set_shp_file_name(std::string );
    int read_shp_file(void);
    std::string get_shp_file_name_(void);
    std::string get_shape_type_string(void);
    unsigned int get_file_length_(void);
};
#endif
