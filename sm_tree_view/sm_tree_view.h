/***************************************************************************
                            sm_tree_view.h - SMGIS
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
#ifndef SM_TREE_VIEW_H
#define SM_TREE_VIEW_H

#include <QTreeView>
#include <QMouseEvent>
#include <iostream>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include "../sm_view_panel/sm_view_panel.h"
#include "../sm_layer_view/sm_layer_view.h"
#include "../sm_layer_color_dialog/sm_layer_color_dialog.h"


class SmTreeView:public QTreeView
{

    Q_OBJECT
private:
    SmViewPanel * graphic_handle_;
    SmLayerView * tree_model_;
    SmLayerColorDialog * sm_layer_color_dialog_;
    QAction * remove_act_;
public:
    SmTreeView(QWidget* parent=0);
    void set_tree_model_(SmLayerView*);
    void set_graphic_handle_(SmViewPanel *);

private slots:
    void mySlot(QModelIndex);

protected:

};

#endif // SM_TREE_VIEW_H
