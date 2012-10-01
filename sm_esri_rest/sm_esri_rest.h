/***************************************************************************
                           sm_esri_rest.h - SMGIS
                              -------------------
     begin                :  September 29 2012
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
#ifndef SM_ESRI_REST_H
#define SM_ESRI_REST_H
#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>


class SmEsriREST
{
public:
    SmEsriREST();

    /*********Setters & Getters**********/
    std::string get_rest_url_(void);
    std::string get_connection_name_(void);
    void set_connection_name_(std::string);
    void set_rest_url_(std::string);
    void set_map_name_(std::string);
    std::string get_map_name_();
    void set_image_width_(int);
    void set_image_height_(int);
    void set_image_scale_(double);
    void set_extent_xmin_(double);
    void set_extent_ymin_(double);
    void set_extent_xmax_(double);
    void set_extent_ymax_(double);
    void set_image_url_(std::string);
    std::string get_image_url_(void);
    double get_extent_xmin_(void)const;
    double get_extent_ymin_(void)const;
    double get_extent_xmax_(void)const;
    double get_extent_ymax_(void)const;
    int get_image_width_(void)const;
    int get_image_height_(void)const;
    double get_image_scale_(void)const;
    /************************************/

    int load_rest_map(void);

private:
//    SmViewPanel *graphic_handle_;
    std::string rest_url_;
    std::string connection_name_;
    std::string map_name_;
    int image_width_;
    std::string image_url_;
    int image_height_;
    double extent_xmin_;
    double extent_xmax_;
    double extent_ymin_;
    double extent_ymax;
    double image_scale_;
    QNetworkAccessManager * sm_qnam_;

};

#endif // SM_ESRI_REST_H
