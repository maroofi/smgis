/***************************************************************************
                       sm_layer_color_dialog.cpp - SMGIS
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
#include "sm_layer_color_dialog.h"

SmLayerColorDialog::SmLayerColorDialog(const QColor& layer_color_, QWidget *parent)
    :QDialog(parent)
{
    last_color_=layer_color_;
    QLabel * current_color=new QLabel("Current Color",this);
    QLabel * choose_color=new QLabel("Choose Color",this);
    QLabel * transparency=new QLabel("Transparency",this);
    slider=new QSlider(Qt::Horizontal,this);
    slider->setMaximum(0);
    slider->setMaximum(255);
    std::cout<<transparency<<std::endl;
    slider->setValue(255-layer_color_.alpha());
    QPushButton *btn_choose_color=new QPushButton("Choose Color",this);
    QPushButton * btn_ok=new QPushButton("Ok",this);
    QPushButton * btn_cancel=new QPushButton("Cancel",this);
    lbl_color=new QLabel(this);
    lbl_color->setText(layer_color_.name());
    lbl_color->setPalette(QPalette(layer_color_));
    lbl_color->setAutoFillBackground(true);
    QGridLayout * gl=new QGridLayout(this);
    this->setWindowTitle("Color");
    gl->addWidget(current_color,0,0);
    gl->addWidget(lbl_color,0,1);
    gl->addWidget(choose_color,1,0);
    gl->addWidget(btn_choose_color,1,1);
    gl->addWidget(transparency,2,0);
    gl->addWidget(slider,2,1);
    gl->addWidget(btn_ok,3,0);
    gl->addWidget(btn_cancel,3,1);
    this->setLayout(gl);
    this->connect(btn_ok,SIGNAL(clicked()),this,SLOT(accept()));
    this->connect(btn_cancel,SIGNAL(clicked()),this,SLOT(reject()));
    this->connect(btn_choose_color,SIGNAL(clicked()),
                  this,SLOT(btn_choose_color_clicked()));
    this->setModal(true);
    this->connect(slider,SIGNAL(valueChanged(int)),this,SLOT(val_changed(int)));

}

SmLayerColorDialog::~SmLayerColorDialog()
{
    delete slider;
    delete lbl_color;
}

QColor SmLayerColorDialog::get_layer_color()
{
    return last_color_;
}



void SmLayerColorDialog::btn_choose_color_clicked()
{
    last_color_ = QColorDialog::getColor(Qt::green, this, "Select Color",
                                   QColorDialog::DontUseNativeDialog);

    if (last_color_.isValid())
    {
        this->lbl_color->setText(last_color_.name());
        this->lbl_color->setPalette(QPalette(last_color_));
        this->lbl_color->setAutoFillBackground(true);
    }
}



void SmLayerColorDialog::val_changed(int val)
{
    last_color_.setAlpha(255-val);

}

QSlider* SmLayerColorDialog::get_transparent_slider_(void)
{
    return this->slider;
}
