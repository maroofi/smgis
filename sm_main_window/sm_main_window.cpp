/***************************************************************************
                            sm_main_window.cpp - SMGIS
                              -------------------
     begin                : Thursday July 15 2012
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
#include "sm_main_window.h"
#include <QApplication>
#include <QHeaderView>
#include <QMouseEvent>

SmMainWindow::SmMainWindow(SmViewPanel* smvp):QMainWindow(),graphic_handle_(smvp)
{

   statusBar();
    create_toolbar();
   create_menu();
    create_dock_widget();
    statusBar()->showMessage("ready");
}

void SmMainWindow::fnc_zoom_in(void)
{

    //QMessageBox::information(this,"smgis","zoom in tool");
    QCursor* qc=new QCursor( QPixmap("../sm_icons/sm_zoomin.png"));
    this->graphic_handle_->setCursor(*qc);

    graphic_handle_->sm_gadget_=smgis::ZoomIn;
}

void SmMainWindow::fnc_zoom_out(void)
{
   // QMessageBox::information(this,"smgis","zoom out tool");
    QCursor* qc=new QCursor( QPixmap("../sm_icons/sm_zoomout.png"));
    this->graphic_handle_->setCursor(*qc);

    graphic_handle_->sm_gadget_=smgis::ZoomOut;
}

void SmMainWindow::fnc_full_extent(void)
{
    // QMessageBox::information(this,"smgis","full extent tool");
 //    QCursor* qc=new QCursor( QPixmap("../sm_icons/sm_full_extent_cursor.png"));
 //    this->graphic_handle_->setCursor(*qc);
     this->graphic_handle_->setCursor(Qt::ArrowCursor);
    graphic_handle_->sm_gadget_=smgis::Cursor;

     graphic_handle_->sm_gadget_=smgis::FullExtent;
     qreal max_scene=(graphic_handle_->get_scene_handle_()->width()>
             graphic_handle_->get_scene_handle_()->height())?
                 graphic_handle_->get_scene_handle_()->width():
                 graphic_handle_->get_scene_handle_()->height();

     qreal min_view;
     min_view=(graphic_handle_->viewport()->width()>
               graphic_handle_->viewport()->height())?
                 graphic_handle_->viewport()->height():
                 graphic_handle_->viewport()->width();
     qreal sca=min_view/max_scene;
     QMatrix mat;
     mat.scale(sca,-sca);
     graphic_handle_->setMatrix(mat);
     //graphic_handle_->scale(1/sca,1/sca);
    return;
}

void SmMainWindow::fnc_cursor(void)
{
    //QMessageBox::information(this,"smgis","cursor tool");
    this->graphic_handle_->setCursor(Qt::ArrowCursor);
    graphic_handle_->sm_gadget_=smgis::Cursor;
}

void SmMainWindow::fnc_hand(void)
{
    //QMessageBox::information(this,"smgis","hand tool");
    //this->graphic_handle_->setCursor(Qt::OpenHandCursor);
    this->graphic_handle_->setCursor(Qt::OpenHandCursor);
    graphic_handle_->sm_gadget_=smgis::Pan;
}

void SmMainWindow::fnc_identify(void)
{
    //QMessageBox::information(this,"smgis","identify tool");
    QCursor* qc=new QCursor( QPixmap("../sm_icons/sm_identify1.png"));
    this->graphic_handle_->setCursor(*qc);

    graphic_handle_->sm_gadget_=smgis::Identify;
}

void SmMainWindow::fnc_database(void)
{
    SmDatabaseConnection* smdc=new SmDatabaseConnection(this->graphic_handle_);
    if (smdc->establish_connection()==0)  //0 means true
    {

        sm_layer_view_->add_layer((graphic_handle_->vector_of_layer_[graphic_handle_->
                                  vector_of_layer_.size()-1])->get_layer_name_(),"Point");
    }
}


void SmMainWindow::fnc_exit(void)
{

    graphic_handle_->sm_gadget_=smgis::Exit;
    qApp->quit();
}

void SmMainWindow::set_graphic_handle_(SmViewPanel *smvp)
{
    this->graphic_handle_=smvp;
}

void SmMainWindow::fnc_rest(void)
{
    SmRESTDialog * dlg=new SmRESTDialog();
    dlg->exec();
}

void SmMainWindow::fnc_shp(void)
{
   QString file_name = QFileDialog::getOpenFileName(this,
         tr("Open Shape File"), tr("*.shp"));
   if (file_name==NULL)
       return;
   else
   {
       //this should be fixed!!!
       SmEsriSHPFormat* esri=new SmEsriSHPFormat(file_name.toStdString(),graphic_handle_);
        sm_layer_view_->add_layer(esri->get_shp_file_name_(),esri->get_shape_type_string());

   }

}

 void SmMainWindow::sm_make_center()
{
  int x, y;
  int screenWidth;
  int screenHeight;

//  int WIDTH = PANEL_WIDTH;
//  int HEIGHT = PANEL_HEIGHT;


  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();

  x = screenWidth-5*screenWidth/100 ;
  y = screenHeight-5/screenHeight/100 ;

  this->setGeometry(5*screenWidth/100, 5*screenHeight/100, x, y);
}

QTreeView* SmMainWindow::get_tree_view_(void)
{
    return tree_view_;
}

SmViewPanel* SmMainWindow::get_graphic_handle_(void)
{
    if (graphic_handle_!=0)
    {
        return graphic_handle_;
    }
}

void SmMainWindow::fnc_jpg(void)
{
    this->graphic_handle_->setCursor(Qt::ArrowCursor);
    graphic_handle_->sm_gadget_=smgis::Cursor;
        QFileDialog::Options options;
            options |= QFileDialog::DontUseNativeDialog;
        QString selectedFilter;
        QString file_name = QFileDialog::getSaveFileName(this,
                                    tr("QFileDialog::getSaveFileName()"),
                                    tr("Export_PNG.png"),
                                    tr("Image Files (*.png)"),
                                    &selectedFilter,
                                    options);
        if (!file_name.isEmpty())
        {
                 QPixmap pixMap = QPixmap::grabWidget(graphic_handle_);
                 pixMap.save(file_name);
        }
}

QDockWidget * SmMainWindow::get_layer_list_dock_(void)
{
    return layer_list_dock_;
}


  void SmMainWindow::create_toolbar(void)
{
    QToolBar *toolbar = addToolBar("Main Toolbar");
    QPixmap pix_shp("../sm_icons/sm_shp.png");
     toolbar_shp=toolbar->addAction(QIcon(pix_shp),"Load Shape File");
    this->connect(toolbar_shp,SIGNAL(triggered()),this ,SLOT(fnc_shp()));
    QPixmap pix_sde("../sm_icons/sm_sde.png");
    toolbar_sde=toolbar->addAction(QIcon(pix_sde),"Arcsde Database on MSSQL");
    this->connect(toolbar_sde,SIGNAL(triggered()),this ,SLOT(fnc_database()));
    QPixmap pix_mssql("../sm_icons/sm_database.png");
    toolbar_mssql=toolbar->addAction(QIcon(pix_mssql),"Load MSSQL Layer");
    this->connect(toolbar_mssql,SIGNAL(triggered()),this ,SLOT(fnc_database()));
    QPixmap pix_postgis("../sm_icons/sm_database1.png");
   toolbar_postgis=toolbar->addAction(QIcon(pix_postgis),"Load Postgis Layer");
    this->connect(toolbar_postgis,SIGNAL(triggered()),this ,SLOT(fnc_database()));

    QPixmap pix_rest("../sm_icons/sm_rest.png");
    toolbar_rest=toolbar->addAction(QIcon(pix_rest),"Esri REST Service");
    this->connect(toolbar_rest,SIGNAL(triggered()),this ,SLOT(fnc_rest()));


     toolbar->addSeparator();
    QPixmap pix_zoom_in("../sm_icons/sm_zoom_in.png");
    toolbar_zoom_in=toolbar->addAction(QIcon(pix_zoom_in),"Zoom In");
    this->connect(toolbar_zoom_in,SIGNAL(triggered()),this ,SLOT(fnc_zoom_in()));
    QPixmap pix_zoom_out("../sm_icons/sm_zoom_out.png");
     toolbar_zoom_out=toolbar->addAction(QIcon(pix_zoom_out),"Zoom Out");
    this->connect(toolbar_zoom_out,SIGNAL(triggered()),this ,SLOT(fnc_zoom_out()));
    QPixmap pix_full_extent("../sm_icons/sm_full_extent.png");
     toolbar_full_extent=toolbar->addAction(QIcon(pix_full_extent),"Full Extent");
    this->connect(toolbar_full_extent,SIGNAL(triggered()),this ,SLOT(fnc_full_extent()));
     toolbar->addSeparator();
     QPixmap pix_cursor("../sm_icons/sm_cursor.png");
      toolbar_cursor=toolbar->addAction(QIcon(pix_cursor),"Cursor");
     this->connect(toolbar_cursor,SIGNAL(triggered()),this ,SLOT(fnc_cursor()));
     QPixmap pix_hand("../sm_icons/sm_hand.png");
      toolbar_hand=toolbar->addAction(QIcon(pix_hand),"Pan");
     this->connect(toolbar_hand,SIGNAL(triggered()),this ,SLOT(fnc_hand()));
     QPixmap pix_identify("../sm_icons/sm_info.png");
     toolbar_identify=toolbar->addAction(QIcon(pix_identify),"Identify");
     this->connect(toolbar_identify,SIGNAL(triggered()),this ,SLOT(fnc_identify()));
     QPixmap pix_jpg("../sm_icons/sm_jpg.png");
      toolbar_jpg=toolbar->addAction(QIcon(pix_jpg),"Export JPEG");
     this->connect(toolbar_jpg,SIGNAL(triggered()),this ,SLOT(fnc_jpg()));
     toolbar->addSeparator();
     QPixmap pix_exit("../sm_icons/sm_exit.png");
     toolbar_exit=toolbar->addAction(QIcon(pix_exit),"Exit Program");
     this->connect(toolbar_exit,SIGNAL(triggered()),this ,SLOT(fnc_exit()));
}

  void SmMainWindow::create_dock_widget(void)
{
    layer_list_dock_ = new QDockWidget(tr("Layers"), this);
    layer_list_dock_->setAllowedAreas(Qt::AllDockWidgetAreas);
    tree_view_=new SmTreeView(layer_list_dock_);
    sm_layer_view_=new SmLayerView(graphic_handle_);
    if (!sm_layer_view_)
    {
//        QMessageBox::information(this,"badAllocation","Can NOT allocate memory...");
        return;
    }
    tree_view_->setModel(sm_layer_view_);
    tree_view_->set_tree_model_(sm_layer_view_);
    tree_view_->set_graphic_handle_(graphic_handle_);


   layer_list_dock_->setWidget(tree_view_);
   this->addDockWidget(Qt::LeftDockWidgetArea,layer_list_dock_);

   view_menu_->addAction(layer_list_dock_->toggleViewAction());
}

 void SmMainWindow::create_menu(void)
{
    file_menu_= menuBar()->addMenu(tr("&File"));
   // file_menu_->addAction(newAct);
    edit_menu_=menuBar()->addMenu(tr("Edit"));
   view_menu_=menuBar()->addMenu(tr("View"));
   layer_menu_=menuBar()->addMenu(tr("Layer"));
    help_menu_=menuBar()->addMenu(tr("Help"));
     about_sub_menu_=new QAction(tr("&About"), this);
     help_menu_->addAction(about_sub_menu_);
     QPixmap pix_shp("../sm_icons/sm_shp.png");
     load_shape_file_sub_menu_=new QAction(QIcon(pix_shp),tr("Load Shape File"),this);
     file_menu_->addAction(load_shape_file_sub_menu_);
}

 void SmMainWindow::keyPressEvent(QKeyEvent *event)
 {
     if (event->key()==Qt::Key_Control)
     {
         graphic_handle_->sm_gadget_=smgis::Pan;
         graphic_handle_->setCursor(Qt::OpenHandCursor);
     }
 }

 void SmMainWindow::keyReleaseEvent(QKeyEvent *event)
 {
     graphic_handle_->setCursor(Qt::ArrowCursor);
     graphic_handle_->sm_gadget_=smgis::Cursor;
 }
