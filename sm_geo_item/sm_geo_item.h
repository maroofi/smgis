/***************************************************************************
                            sm_geo_item.h - SMGIS
                              -------------------
     begin                :  July 21 2012
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
#ifndef SM_GEO_ITEM_H
#define SM_GEO_ITEM_H


#include <QGraphicsItem>
#include <QString>
#include <QRectF>
#include <QPainter>
#include <QPainterPath>
#include "../sm_shape_general/sm_shape_general.h"
#include "../sm_point/sm_point.h"
#include "../sm_polyline/sm_polyline.h"
#include "../sm_layer_info/sm_layer_info.h"
#include "../sm_general/sm_general.h"
#include "../sm_polygon/sm_polygon.h"

class SmGeoItem:public QGraphicsItem
{
   // Q_OBJECT

private:
    static int cstr_cntr;
    QPainterPath* painter_path_;
    unsigned int item_id_;
    SmLayerInfo * layer_info_;
    smgis::SmShapeType item_shape_type_;
    SmPoint   * point_item_;
    SmPolyline* polyline_item_;
    SmPolygon * polygon_item_;



public:
  static  int ret_cstr(void);
    ~SmGeoItem();
    SmGeoItem(const unsigned int &,const SmPolygon &);
     SmGeoItem(const unsigned int &,const SmPolyline &);
     SmGeoItem(const unsigned int &,const SmPoint&);
    SmGeoItem(const SmGeoItem&);
     SmLayerInfo * get_layer_info_(void) const;
    void set_layer_info_(SmLayerInfo*);
    int  set_item_shape_type_(const smgis::SmShapeType shpt);
    smgis::SmShapeType get_item_shape_type_(void);
   unsigned int  get_layer_number_(void);
  const unsigned int  get_item_id_(void);
  QPainterPath* create_qpainter_path(void);

    void set_point_item_(const SmPoint &);

protected:
/*reimplemented virtual QGraphicsItem Function*/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape()const;


};

#endif // SM_GEO_ITEM_H
