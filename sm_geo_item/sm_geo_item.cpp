/***************************************************************************
                            sm_geo_item.cpp - SMGIS
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

#include "sm_geo_item.h"
#include <QMessageBox>
#include <QColor>
int SmGeoItem::cstr_cntr=0;

 int SmGeoItem::ret_cstr(void)
{
    return cstr_cntr;
}

SmGeoItem::SmGeoItem(const unsigned int &id,const SmPolygon & smpg)
    :QGraphicsItem(),item_id_(id),point_item_(0),polyline_item_(0),polygon_item_(0)
{
    cstr_cntr++;
    painter_path_=0;
    polygon_item_=new SmPolygon(smpg);
    item_shape_type_=smgis::Polygon;

}

SmGeoItem::SmGeoItem(const unsigned int &id, const SmPolyline &smpl)
    :QGraphicsItem(),item_id_(id),point_item_(0),polyline_item_(0),polygon_item_(0)
{
    cstr_cntr++;
    painter_path_=0;
    polyline_item_=new SmPolyline(smpl);
    item_shape_type_=smgis::PolyLine;
}

SmGeoItem::~SmGeoItem()
{
    cstr_cntr--;
    if (point_item_)
        delete this->point_item_;
    if (polyline_item_)
        delete polyline_item_;
    if (polygon_item_)
        delete polygon_item_;
}

SmGeoItem::SmGeoItem(const unsigned int &id,const SmPoint& smp)
    :QGraphicsItem(),item_id_(id),point_item_(0),polyline_item_(0),polygon_item_(0)
{
    cstr_cntr++;
    painter_path_=0;
    point_item_=new SmPoint(smp);
    item_shape_type_=smgis::Ponit;
//    this->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

SmGeoItem::SmGeoItem(const SmGeoItem& other):QGraphicsItem()
{

    cstr_cntr++;
    painter_path_=0;
    this->layer_info_=other.get_layer_info_();
    this->item_id_=other.item_id_;
    this->item_shape_type_=other.item_shape_type_;
    if (item_shape_type_==smgis::Ponit)
    {
        this->point_item_=new SmPoint(*other.point_item_);
        polyline_item_=0;
        polygon_item_=0;
//        this->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }
    else if (item_shape_type_== smgis::PolyLine)
    {
        this->polyline_item_=new SmPolyline(*other.polyline_item_);
        point_item_=0;
        polygon_item_=0;
     }

    else if (item_shape_type_==smgis::Polygon)
    {
        this->polygon_item_=new SmPolygon(*other.polygon_item_);
        point_item_=0;
        polyline_item_=0;
    }
}

int SmGeoItem::set_item_shape_type_(const smgis::SmShapeType shpt)
{
    this->item_shape_type_=shpt;
    return 0;
}

unsigned int SmGeoItem::get_layer_number_(void)
{
     return this->layer_info_->get_layer_number_();
}

const unsigned int SmGeoItem::get_item_id_(void)
{
    return item_id_;
}

void SmGeoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(widget)  // widget variable not used in function body(bullshit)
    painter->setPen(QColor(0,0,0));
    if (this->item_shape_type_==smgis::Ponit && point_item_!=0 && !layer_info_->get_layer_is_hidden_())
    {
        QBrush b_r(*(this->layer_info_->layer_color_),Qt::SolidPattern);
        painter->setBrush(b_r);
        if(!this->layer_info_)
            std::cout<<"layer_info_ pointer is damaged!!!"<<std::endl;
        if(painter_path_)
        {
            painter->drawPath(*painter_path_);
            delete painter_path_;
            painter_path_=0;
        }
        else
        {
            create_qpainter_path();
            painter->drawPath(*painter_path_);
//            painter->drawEllipse(*point_item_,700,700);
            delete painter_path_;
            painter_path_=0;
        }
    }
    else if(this->item_shape_type_==smgis::PolyLine && polyline_item_!=0 && !layer_info_->get_layer_is_hidden_())
    {
         painter->setPen( *(this->layer_info_->layer_color_));
        if(!this->layer_info_)
            std::cout<<"layer_info_ pointer is damaged!!!"<<std::endl;
        if(painter_path_)
        {
            painter->drawPath(*painter_path_);
            delete painter_path_;
            painter_path_=0;
        }
        else
        {
            create_qpainter_path();
            painter->drawPath(*painter_path_);
            delete painter_path_;
            painter_path_=0;
        }


    }
    else if(this->item_shape_type_==smgis::Polygon && polygon_item_!=0 && !layer_info_->get_layer_is_hidden_())
    {
        QBrush b_r(*(this->layer_info_->layer_color_),Qt::SolidPattern);
        painter->setBrush(b_r);
            if(painter_path_)
            {
                painter->drawPath(*painter_path_);
                delete painter_path_;
                painter_path_=0;
            }
            else
            {
                create_qpainter_path();
                painter->drawPath(*painter_path_);
                delete painter_path_;
                painter_path_=0;
            }
    }
}

/************************************************************************
**********************boundingRect pure virtual method*******************
*************************************************************************/

QRectF SmGeoItem::boundingRect() const
{
    if(this->item_shape_type_==smgis::Ponit)
    {

        return ( QRectF(point_item_->get_x_(),point_item_->get_y_(),10,10));
    }
    else if (this->item_shape_type_==smgis::PolyLine)
    {
        qreal vasatx=polyline_item_->get_x_max()-polyline_item_->get_x_min();
        qreal vasaty=polyline_item_->get_y_max()-polyline_item_->get_y_min();
        return(QRectF(polyline_item_->get_x_min(),polyline_item_->get_y_min(),
                      vasatx,vasaty));
    }
    else if (this->item_shape_type_==smgis::Polygon)
    {
        qreal vasatx=polygon_item_->get_x_max()- polygon_item_->get_x_min();
        qreal vasaty=polygon_item_->get_y_max()- polygon_item_->get_y_min();
        return(QRectF(polygon_item_->get_x_min(),polygon_item_->get_y_min(),
                      vasatx,vasaty) );

    }
    return QRectF();
}
/******************************************************************************
*******************************************************************************
*******************************************************************************/

void SmGeoItem::set_point_item_(const SmPoint & other)
{
    this->point_item_=new SmPoint(other);
}

void SmGeoItem::set_layer_info_(SmLayerInfo * smlf)
{
    this->layer_info_=smlf;
}

SmLayerInfo * SmGeoItem::get_layer_info_(void) const
{
    return this->layer_info_;
}
/*********************************************************/
/*********************************************************/
/*********************************************************/
QPainterPath* SmGeoItem::create_qpainter_path(void)
{
    if (painter_path_)
    {
        delete painter_path_;
        painter_path_=0;
    }
    painter_path_=new QPainterPath();
    if (this->item_shape_type_==smgis::Polygon)
    {
        if (polygon_item_->get_number_of_part_()==1)
        {
            painter_path_->moveTo(*polygon_item_->get_point_at(0));
            int a=polygon_item_->get_total_number_of_points_();
            for(int i=1;i<a;i++)
            {
                painter_path_->lineTo(*polygon_item_->get_point_at(i));
            }
            return painter_path_;
        }
        else
        {
            //this is multipart item
            unsigned int i=0,j=0,k=0,temp=0;
            while(i<(polygon_item_->get_number_of_part_()-1))
            {
                temp=polygon_item_->get_part_index_()[i+1]-polygon_item_->get_part_index_()[i];
                k=1;
                j=polygon_item_->get_part_index_()[i];
                painter_path_->moveTo(*polygon_item_->get_point_at(j));
                while(k<temp)
                {

                    painter_path_->lineTo(*polygon_item_->get_point_at(j+1));
                    ++k;
                    ++j;
                }
                ++i;
            }
            int a=polygon_item_->get_number_of_part_()-1;
            painter_path_->moveTo(*polygon_item_->get_point_at((polygon_item_->get_part_index_()[a])));
            int inx=polygon_item_->get_part_index_()[a]+1;
            int tota=polygon_item_->get_total_number_of_points_();
             for(int i=inx;i<tota;i++)
             {
                    painter_path_->lineTo(*polygon_item_->get_point_at(i));
             }
             return painter_path_;
         }
    }
    else if (this->item_shape_type_==smgis::PolyLine)
    {
        if (polyline_item_->get_number_of_lines()==1)
        {
            painter_path_->moveTo(*polyline_item_->get_point_at(0));
            int a=polyline_item_->get_total_number_of_points_();
            for(int i=1;i<a;i++)
            {
                painter_path_->lineTo(*polyline_item_->get_point_at(i));
            }
            return painter_path_;
        }
        else
        {
            //this is multipart item
            unsigned int i=0,j=0,k=0,temp=0;
            while(i<(polyline_item_->get_number_of_lines()-1))
            {
                temp=polyline_item_->get_line_index_()[i+1]-polyline_item_->get_line_index_()[i];
                k=1;
                j=polyline_item_->get_line_index_()[i];
                painter_path_->moveTo(*polyline_item_->get_point_at(j));
                while(k<temp)
                {

                    painter_path_->lineTo(*polyline_item_->get_point_at(j+1));
                    ++k;
                    ++j;
                }
                ++i;
            }
            int a=polyline_item_->get_number_of_lines()-1;
            painter_path_->moveTo(*polyline_item_->get_point_at((polyline_item_->get_line_index_()[a])));
            int inx=polyline_item_->get_line_index_()[a]+1;
            int tota=polyline_item_->get_total_number_of_points_();
             for(int i=inx;i<tota;i++)
             {
                    painter_path_->lineTo(*polyline_item_->get_point_at(i));
             }
             return painter_path_;
         }
    }
    else if (this->item_shape_type_==smgis::Ponit)
    {
//        QMatrix mat;
//        mat.scale(1,1);
//        this->setMatrix(mat);
        painter_path_->addEllipse(point_item_->get_x_(),point_item_->get_y_(),10,10);
        return painter_path_;
    }

}
/********************************************************************/
/********************************************************************/
/********************************************************************/

QPainterPath SmGeoItem::shape() const
{
    QPainterPath p;

    if (this->item_shape_type_==smgis::Polygon)
    {


        if (polygon_item_->get_number_of_part_()==1)
        {
            p.moveTo(*polygon_item_->get_point_at(0));
            int a=polygon_item_->get_total_number_of_points_();
            for(int i=1;i<a;i++)
            {
                p.lineTo(*polygon_item_->get_point_at(i));
            }
            return p;
        }
        else
        {
            //this is multipart item
            unsigned int i=0,j=0,k=0,temp=0;
            while(i<(polygon_item_->get_number_of_part_()-1))
            {
                temp=polygon_item_->get_part_index_()[i+1]-polygon_item_->get_part_index_()[i];
                k=1;
                j=polygon_item_->get_part_index_()[i];
                p.moveTo(*polygon_item_->get_point_at(j));
                while(k<temp)
                {
                    p.lineTo(*polygon_item_->get_point_at(j+1));
                    ++k;
                    ++j;
                }
                ++i;
            }
            int a=polygon_item_->get_number_of_part_()-1;
            p.moveTo(*polygon_item_->get_point_at((polygon_item_->get_part_index_()[a])));
            int inx=polygon_item_->get_part_index_()[a]+1;
            int tota=polygon_item_->get_total_number_of_points_();
            for(int i=inx;i<tota;i++)
            {
                p.lineTo(*polygon_item_->get_point_at(i));
            }
            return p;
        }
    }
    else if (this->item_shape_type_==smgis::PolyLine)
    {
        if (polyline_item_->get_number_of_lines()==1)
        {
            p.moveTo(*polyline_item_->get_point_at(0));
            int a=polyline_item_->get_total_number_of_points_();
            for(int i=1;i<a;i++)
            {
                p.lineTo(*polyline_item_->get_point_at(i));
            }
            return p;
        }
        else
        {
            //this is multipart item
            unsigned int i=0,j=0,k=0,temp=0;
            while(i<(polyline_item_->get_number_of_lines()-1))
            {
                temp=polyline_item_->get_line_index_()[i+1]-polyline_item_->get_line_index_()[i];
                k=1;
                j=polyline_item_->get_line_index_()[i];
                p.moveTo(*polyline_item_->get_point_at(j));
                while(k<temp)
                {
                    p.lineTo(*polyline_item_->get_point_at(j+1));
                    ++k;
                    ++j;
                }
                ++i;
            }
            int a=polyline_item_->get_number_of_lines()-1;
            p.moveTo(*polyline_item_->get_point_at((polyline_item_->get_line_index_()[a])));
            int inx=polyline_item_->get_line_index_()[a]+1;
            int tota=polyline_item_->get_total_number_of_points_();
            for(int i=inx;i<tota;i++)
            {
                p.lineTo(*polyline_item_->get_point_at(i));
            }
            return p;
        }
    }
    else if (this->item_shape_type_==smgis::Ponit)
    {

         p.addRect(point_item_->get_x_(),point_item_->get_y_(),10,10);
        return p;
    }
}
/************************************************************************/
/************************************************************************/
/************************************************************************/

smgis::SmShapeType SmGeoItem::get_item_shape_type_(void)
{
    return item_shape_type_;
}

