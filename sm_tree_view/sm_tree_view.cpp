/***************************************************************************
                            sm_tree_view.cpp - SMGIS
                              -------------------
     begin                :  August 13 2012
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
#include "sm_tree_view.h"

SmTreeView::SmTreeView(QWidget *parent):QTreeView(parent)
{

    tree_model_=0;
    sm_layer_color_dialog_=0;
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(mySlot(QModelIndex)));
}


void SmTreeView::mySlot(QModelIndex i)
{
    //std::cout<<"hi clicked"<<std::endl;
   QModelIndex m;
   m=i.parent();
   if (m.isValid())
   {
       if (tree_model_)
       {
           QStandardItem* qsi= tree_model_->itemFromIndex(i);
           if (qsi)
           {


               QColor col(qsi->text().mid(4,7));
                sm_layer_color_dialog_=new SmLayerColorDialog(
                     col,this);
               std::cout<<qsi->text().mid(4,7).toStdString()<<std::endl;
               QStandardItem* qsi_parent=qsi->parent();


               int res= sm_layer_color_dialog_->exec();
                //std::cout<<" :"<<res<<std::endl;
                if (res==QDialog::Accepted)
                {
                                QColor cl=sm_layer_color_dialog_->get_layer_color();
                                int si= (graphic_handle_)->vector_of_layer_.size();

                                for(int j=0;j<si;++j)
                                {
                                    if(  ((graphic_handle_))->vector_of_layer_[j]->
                                            get_layer_name_()==(qsi_parent->text().toStdString()) )
                                    {
                                        (graphic_handle_)->vector_of_layer_[j]->
                                                layer_color_->operator=(cl);
                                        qsi->setText("RGB("+ cl.name() +")");
                                        qsi->setForeground(QBrush(cl));
                                        break;
                                    }
                                }

                }
                else if (res==QDialog::Rejected)
                {
                    std::cout<<"rejected anyway"<<std::endl;
                }
           }
       }
   }

   //this works...double-click on child makes it print "is valid"
   //but nothing happen if you click the parents.
   //you can change it to something happen if you add just a simple
   //else statement...it's fuckin piece of cake.
}

void SmTreeView::set_tree_model_(SmLayerView *tm)
{
    tree_model_=tm;
}

void SmTreeView::set_graphic_handle_(SmViewPanel *gh)
{
    graphic_handle_=gh;
}
