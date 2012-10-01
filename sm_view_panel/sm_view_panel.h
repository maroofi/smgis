/***************************************************************************
                            sm_view_panel.h - SMGIS
                              -------------------
     begin                :  July 23 2012
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

#ifndef SM_VIEW_PANEL_H
#define SM_VIEW_PANEL_H

#include <iostream>
#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <QWheelEvent>
#include <QScrollBar>
#include <QPainter>
#include <QPixmap>
#include "../sm_geo_item/sm_geo_item.h"
#include "../sm_layer_info/sm_layer_info.h"
#include "../sm_data_dbf_format/sm_data_dbf_format.h"
class SmViewPanel : public QGraphicsView
{
   Q_OBJECT
public:
    smgis::SmGadget sm_gadget_;
    SmViewPanel(QWidget * parent=0);
    QGraphicsScene * get_scene_handle_(void);
    void add_item_to_scene(SmGeoItem *);
    std::vector<class SmLayerInfo *> vector_of_layer_;
    int get_panel_width_(void) const;
    int get_panel_height_(void)const;
    SmLayerInfo*  create_new_layer(void);

private:

    QPointF CurrentCenterPoint;
    QPoint LastPanPoint;
    SmGeoItem *temp_item_;
    SmDataDBFFormat * identify_table_;
  //SmLayerView* sm_layer_view_;
    QPoint view_center_point_;
    bool is_pan_;
    bool is_left_mouse_pressed_;
    bool is_mouse_dragged_;
    QPoint mouse_current_point_;
    QPoint mouse_press_point_;
    QGraphicsScene *scene_handle_;
    double sm_scale_;
    std::vector<SmGeoItem *>  vector_of_items_;
    bool is_ctrl_down_;
    QPoint mouse_max_dragged_point_;
    int panel_width_;
    int panel_height_;
protected:

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseReleaseEvent ( QMouseEvent * event ) ;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


};
#endif // SM_VIEW_PANEL_H
