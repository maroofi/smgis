/***************************************************************************
                       sm_layer_color_dialog.h - SMGIS
                              -------------------
     begin                :  August 14 2012
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
#ifndef SM_LAYER_COLOR_DIALOG_H
#define SM_LAYER_COLOR_DIALOG_H
#include <QApplication>
#include <QDialog>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QGridLayout>
#include <QPalette>
#include <QColorDialog>
#include <iostream>
#include <QString>
class SmLayerColorDialog:public QDialog
{
    Q_OBJECT
 public:

    ~SmLayerColorDialog();
    SmLayerColorDialog(const QColor&,QWidget * parent=0);
   QColor get_layer_color(void);
   QSlider * get_transparent_slider_(void);
 private:

   QColor  last_color_;

    QSlider * slider;

    QLabel * lbl_color;
private slots:
   void btn_choose_color_clicked();

   void val_changed(int );
};

#endif // SM_LAYER_COLOR_DIALOG_H
