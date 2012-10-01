/***************************************************************************
                            sm_view_panel.cpp - SMGIS
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
#include <QMessageBox>
#include "sm_view_panel.h"
#include <QPixmapCache>
#include <qmath.h>
/*
**Constructorn
*/
SmViewPanel::SmViewPanel(QWidget *parent):QGraphicsView(parent)
{
    mouse_max_dragged_point_=QPoint();
    is_ctrl_down_=false;
    is_mouse_dragged_=false;
    is_left_mouse_pressed_=false;
    identify_table_=new SmDataDBFFormat("42000.dbf",this);
    identify_table_->read_dbf_file();
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_center_point_=QPoint();
    is_pan_=false;
    sm_gadget_=smgis::Cursor;
    sm_scale_=1;
    scene_handle_=new QGraphicsScene(this);
    this->setScene(scene_handle_);
    this->setRenderHint(QPainter::Antialiasing);
    this->resize(640,480);
   }

/*
** Return QGraphicsScene pointer(handle)
*/
QGraphicsScene * SmViewPanel::get_scene_handle_(void)
{
    return this->scene_handle_;
}

/*
**Adds new item(Qgraphics item's subclass) to Scene
**why dont we use QGraphicsScene::addItem() ????
**here we allocate new memory for items and add their
**pointer to the vector of pointers.
*/
void SmViewPanel::add_item_to_scene(SmGeoItem * smg)
{
    vector_of_items_.push_back(new SmGeoItem(*smg));

    scene_handle_->addItem((vector_of_items_[vector_of_items_.size()-1]));
}

int SmViewPanel::get_panel_width_(void) const
{
    return this->panel_width_;
}
int SmViewPanel::get_panel_height_(void)const
{
    return this->panel_height_;
}


SmLayerInfo*SmViewPanel::create_new_layer(void)
{
       SmLayerInfo* smlf=new SmLayerInfo();
       this->vector_of_layer_.push_back(smlf);
       return smlf;
}

void SmViewPanel::wheelEvent(QWheelEvent *event)
{

    if (event->delta()>0)
    {
        sm_scale_=1.3;
        scale(sm_scale_,sm_scale_);
        QGraphicsView::wheelEvent(event);
    }
    else
    {
        sm_scale_=1.3;
        scale(1/sm_scale_,1/sm_scale_);
        QGraphicsView::wheelEvent(event);

    }

    centerOn(this->mapToScene(event->pos()));
}

void SmViewPanel::mouseReleaseEvent ( QMouseEvent * event )
{

        is_left_mouse_pressed_=false;
    if ((sm_gadget_==smgis::ZoomIn ||sm_gadget_==smgis::ZoomOut) && is_mouse_dragged_)
    {
        mouse_current_point_=event->pos();

        QRect zoom_extent(mouse_press_point_,mouse_current_point_);
        QPointF first_point=mapToScene(zoom_extent.center());
        double scale_rate=(zoom_extent.width()>zoom_extent.height())?zoom_extent.width():
                          zoom_extent.height();
        double darsad=viewport()->width()>viewport()->height()?viewport()->height():
                          viewport()->width();
        if (sm_gadget_==smgis::ZoomIn)
            scale(qAbs(darsad/scale_rate),qAbs(darsad/scale_rate));
        if(sm_gadget_==smgis::ZoomOut)
            scale(qAbs(scale_rate/darsad),qAbs(scale_rate/darsad));
//        QPointF second_point=mapToScene(zoom_extent.center());
//        std::cout<<first_point.x()<<","<<first_point.y()
//                <<"-------"<<second_point.x()<<","<<second_point.y()<<std::endl;
        centerOn(first_point);
        is_mouse_dragged_=false;
    }

    else if (sm_gadget_==smgis::FullExtent)
    {
        sm_gadget_=smgis::Cursor;

        return;
    }
    else if (sm_gadget_==smgis::Cursor)
    {
        QPointF cl=mapToScene(event->pos());

        temp_item_=(SmGeoItem*)scene_handle_->itemAt(cl);
       if (temp_item_)
       {
       this->viewport()->update();
       }
        return;
    }
    else if (sm_gadget_==smgis::Pan)
    {
        this->setCursor(Qt::OpenHandCursor);
        mouse_press_point_=QPoint();
    }
    else if (sm_gadget_==smgis::Identify)
    {
        QPointF cl=mapToScene(event->pos());
        temp_item_=(SmGeoItem*)scene_handle_->itemAt(cl);
        if (temp_item_)
        {
            identify_table_->execute(temp_item_->get_item_id_());
            this->viewport()->update();
        }
    }

     QGraphicsView::mouseReleaseEvent(event);
}

void SmViewPanel::mouseMoveEvent(QMouseEvent *event)
{

    if (is_left_mouse_pressed_ && (sm_gadget_==smgis::ZoomIn ||sm_gadget_==smgis::ZoomOut))
    {
        is_mouse_dragged_=true;
        mouse_current_point_= event->pos();
        mouse_max_dragged_point_.setX((mouse_max_dragged_point_.x() > mouse_current_point_.x())?
                    mouse_max_dragged_point_.x():mouse_current_point_.x());
        mouse_max_dragged_point_.setY((mouse_max_dragged_point_.y() > mouse_current_point_.y())?
                    mouse_max_dragged_point_.y():mouse_current_point_.y());
        this->viewport()->update();
    }

        if(sm_gadget_==smgis::Pan)
        {
            mouse_current_point_=event->pos();
            QPoint delta_x=mouse_current_point_-mouse_press_point_;
            view_center_point_=view_center_point_-delta_x;
            centerOn(mapToScene( view_center_point_) );
            mouse_press_point_=mouse_current_point_;
            view_center_point_=this->viewport()->rect().center();
        }
     QGraphicsView::mouseMoveEvent(event);
}




void SmViewPanel::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(this->viewport());
    QBrush b_r;
    if ((sm_gadget_==smgis::ZoomIn||sm_gadget_==smgis::ZoomOut) && is_left_mouse_pressed_)
    {
        b_r.setColor(QColor(0,0,0,100));
        b_r.setStyle(Qt::SolidPattern);
        painter.setBrush(b_r);
        painter.drawRect(mouse_press_point_.x(),mouse_press_point_.y(),
                         mouse_current_point_.x()-mouse_press_point_.x(),
                         mouse_current_point_.y()-mouse_press_point_.y());
        /*mouse_press_point_,mouse_current_point_*/
    }

    if(temp_item_)
    {

        if (temp_item_->get_item_shape_type_()==smgis::Polygon)
        {
            b_r.setColor(QColor(255,255,0,255));
            b_r.setStyle(Qt::SolidPattern);
        }
        else if (temp_item_->get_item_shape_type_()==smgis::PolyLine)
        {
            b_r.setColor(QColor(0,0,255,255));
            b_r.setStyle(Qt::NoBrush);
        }
        else if (temp_item_->get_item_shape_type_()==smgis::Ponit)
        {
            b_r.setColor(QColor(0,0,0,100));
            b_r.setStyle(Qt::SolidPattern);
        }
        painter.setBrush(b_r);
        painter.drawPath( mapFromScene(*(temp_item_->create_qpainter_path())));
        temp_item_=0;
    }

}

void SmViewPanel::mousePressEvent(QMouseEvent *event)
{
    mouse_press_point_= event->pos();
    is_left_mouse_pressed_=true;
    if (sm_gadget_==smgis::Pan)
    {
      view_center_point_=viewport()->rect().center();
      this->setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}


