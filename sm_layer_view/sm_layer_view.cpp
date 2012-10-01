/***************************************************************************
                            sm_layer_view.cpp - SMGIS
                              -------------------
     begin                :  August 11 2012
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
#include "sm_layer_view.h"
#include <QBrush>
#include <QColor>
SmLayerView::SmLayerView(SmViewPanel *smvp):QStandardItemModel()
{
    graphic_handle=smvp;
    num_of_row_=0;

   this->connect(this, SIGNAL(itemChanged(QStandardItem*)),
                 this, SLOT(myslot(QStandardItem*) ));
}


void SmLayerView::myslot(QStandardItem * item)
{
    int a=this->graphic_handle->vector_of_layer_.size();
    for(int i=0;i<a;++i)
    {
        if (this->graphic_handle->vector_of_layer_[i]->get_layer_name_()==
                item->text().toStdString() )
        {
            if(item->checkState()==Qt::Unchecked)
            {
                this->graphic_handle->vector_of_layer_[i]->set_layer_is_hidden_(true);
                graphic_handle->get_scene_handle_()->update();
            }
            else
            {
                this->graphic_handle->vector_of_layer_[i]->set_layer_is_hidden_(false);
                graphic_handle->get_scene_handle_()->update();
            }
        }
    }
}

void SmLayerView::add_layer(std::string str,std::string shp)
{

    QStandardItem *item = new QStandardItem();
    QString st(str.c_str());
    item->setText(st);
    item->setCheckable(true);
    if (shp=="Polygon")
        item->setIcon(QIcon("../sm_icons/sm_polygon.png"));
    else if (shp=="Polyline")
        item->setIcon(QIcon("../sm_icons/sm_line.png"));
    else if (shp=="Point")
        item->setIcon(QIcon("../sm_icons/sm_point.png"));
    item->setToolTip(item->text());
    item->setEditable(false);
    item->setSelectable(true);
    item->setCheckState(Qt::Checked);
    QStandardItem* chld=new QStandardItem();
    chld->setCheckable(false);
    chld->setSelectable(true);
    chld->setEditable(false);
    //chld->setBackground();
    QString str_color;
    str_color="RGB(";
    str_color+=this->graphic_handle->vector_of_layer_[
            this->graphic_handle->vector_of_layer_.size()-1]->layer_color_->name();
    str_color+=")";
    chld->setText(str_color);
    chld->setForeground(QBrush(*(this->graphic_handle->vector_of_layer_[
                               this->graphic_handle->vector_of_layer_.size()-1]->layer_color_)));

    item->setChild(0,chld);
    this->setItem(num_of_row_,item);
    num_of_row_+=1;
}
