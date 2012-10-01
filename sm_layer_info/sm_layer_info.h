/***************************************************************************
                            sm_layer_info.h - SMGIS
                              -------------------
     begin                :  July 24 2012
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
#ifndef SM_LAYER_INFO_H
#define SM_LAYER_INFO_H
#include <iostream>
#include <QStandardItem>
#include <QColor>
#include "../sm_shape_general/sm_shape_general.h"
class SmLayerInfo
{
private:

    smgis::SmShapeType layer_shape_type_;
    static int assign_num_to_layer_;
    std::string layer_name_;
    double width_interval_;
    double height_interval_;
    double bounding_box_[4];
    bool layer_is_hidden_;
    int layer_number_;
    int db_layer_id;
public:
    smgis::SmShapeType get_layer_shape_type_(void)const;
    void set_layer_shape_type_(smgis::SmShapeType);
     QColor* layer_color_;
    static int get_assign_num_to_layer_(void);
    static void set_increament_assign_num_to_layer(void);
    std::string get_layer_name_(void);
    void set_layer_name_(std::string);
    double get_width_interval_(void) const;
    double get_height_interval_(void) const;
   double  get_x_min(void);
   double get_y_min(void);
   double get_x_max(void);
   double get_y_max(void);
    void calculate_intervals(const int&,const int &); /*get view's width and height as input*/
    SmLayerInfo();
    SmLayerInfo(const SmLayerInfo&);
    void set_layer_is_hidden_(bool);
    bool get_layer_is_hidden_() const;
    int get_layer_number_(void) const;
    void set_layer_number_(int) ;
    void set_db_layer_id_(int);
    int get_db_layer_id_(void);
    void set_bounding_box_(double *);

};

#endif
