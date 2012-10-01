/***************************************************************************
                           sm_main_window.h - SMGIS
                              -------------------
     begin                :  July 30 2012
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
#ifndef SM_MAIN_WINDOW_H
#define SM_MAIN_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>
#include <QTreeView>
#include <QSplitter>
#include <QImage>
#include <QListWidget>
#include <QModelIndex>
#include <QDockWidget>
#include "../sm_view_panel/sm_view_panel.h"
#include "../sm_esri_shp_format/sm_esri_shp_format.h"
#include "../sm_layer_view/sm_layer_view.h"
#include "../sm_tree_view/sm_tree_view.h"
#include "../sm_database_connection/sm_database_connection.h"
#include "../sm_esri_rest/sm_esri_rest.h"
class SmMainWindow:public QMainWindow
{
    Q_OBJECT
private:
    void create_menu(void);
    void create_dock_widget(void);
    void create_toolbar(void);
    QDockWidget *layer_list_dock_;
    SmLayerView * sm_layer_view_;
    SmViewPanel * graphic_handle_;
     SmTreeView * tree_view_;
    QMenu * file_menu_;
    QMenu * edit_menu_;
    QMenu * view_menu_;
    QMenu * layer_menu_;
    QMenu * help_menu_;
    /********************************/
    QAction * about_sub_menu_;
    QAction * load_shape_file_sub_menu_;
    /******************************/
    QAction * toolbar_shp;
     QAction * toolbar_sde;
     QAction * toolbar_mssql;
    QAction * toolbar_postgis;
    QAction * toolbar_rest;
    QAction * toolbar_zoom_in;
    QAction * toolbar_zoom_out;
    QAction * toolbar_full_extent;
    QAction * toolbar_cursor;
    QAction * toolbar_hand;
     QAction * toolbar_identify;
     QAction * toolbar_jpg;
     QAction * toolbar_exit;
    /********************************/
public:
    SmViewPanel * get_graphic_handle_(void);
    void sm_make_center();
    void set_graphic_handle_(SmViewPanel*);
    SmMainWindow(SmViewPanel*);
    QDockWidget * get_layer_list_dock_(void);
    QSplitter* get_h_splitter_(void);
    QSplitter* get_v_splitter_(void);
    QTreeView* get_tree_view_(void);

    void visible_tree_view(bool);

private slots:
    void  fnc_rest(void);
    void  fnc_zoom_in(void);
    void  fnc_zoom_out(void);
    void fnc_full_extent(void);
    void fnc_cursor(void);
    void fnc_hand(void);
    void fnc_identify(void);
    void fnc_exit(void);
    void fnc_shp(void);
    void fnc_jpg(void);
    void fnc_database(void);
protected:

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};
#endif // SM_MAIN_WINDOW_H
