/***************************************************************************
                            sm_layer_view.h - SMGIS
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
#ifndef SM_LAYER_VIEW_H
#define SM_LAYER_VIEW_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QApplication>
#include <QIcon>
#include <QModelIndex>
#include <QMessageBox>
#include <iostream>
#include "../sm_layer_info/sm_layer_info.h"
#include "../sm_view_panel/sm_view_panel.h"
class SmLayerView:public QStandardItemModel
{
    Q_OBJECT
private:
    SmViewPanel * graphic_handle;
    unsigned int num_of_row_;
public:
    SmLayerView(SmViewPanel*);
    void add_layer(std::string, std::string);

private slots:
    void myslot(QStandardItem* item);

protected:


};
#endif // SM_LAYER_VIEW_H
