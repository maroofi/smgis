/***************************************************************************
                        sm_esri_shp_format.cpp - SMGIS
                              -------------------
     begin                :  July 15 2012
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

#include <iostream>
#include <fstream>
#include <string>
#include "sm_esri_shp_format.h"
SmEsriSHPFormat::SmEsriSHPFormat(SmViewPanel *qgv)
{
    this->graphic_handle_=qgv;
    this->header_buffer_=new char[100];
    inp_file_=new std::ifstream();
    file_length_=0;
    esri_shape_type_=smgis::Ponit;
}

int  SmEsriSHPFormat::set_shp_file_name(std::string fn)
{
    this->header_buffer_=new char[100];
    inp_file_=new std::ifstream();
    file_length_=0;
    esri_shape_type_=smgis::Ponit;
    shp_file_name_=fn;
    return 0;
}
SmEsriSHPFormat::SmEsriSHPFormat(const char *fn, SmViewPanel *qgv)
{
    this->graphic_handle_=qgv;
    this->header_buffer_=new char[100];
    inp_file_=new std::ifstream();
    file_length_=0;
    esri_shape_type_=smgis::Ponit;
    shp_file_name_=fn;
    read_shp_file();
}
SmEsriSHPFormat::SmEsriSHPFormat(std::string fn, SmViewPanel *qgv)
{
    this->graphic_handle_=qgv;
    this->header_buffer_=new char[100];
    inp_file_=new std::ifstream();
    file_length_=0;
    esri_shape_type_=smgis::Ponit;
    shp_file_name_=fn;
    read_shp_file();
}

int  SmEsriSHPFormat::read_shp_file(void)
{
    if (shp_file_name_=="")
        {
          // QMessageBox::information(NULL,"Shape file(.shp)","There is NO valid .shp file name");
           std::cout<<"There is NO valid .shp file name "<<std::endl;
            return -1;
        }

    inp_file_->open(shp_file_name_.c_str(),std::ios::in|std::ios::binary);
    if (!inp_file_->is_open())
    {
       // QMessageBox::information(0,"Shape file(.shp)","Can NOT open file"+shp_file_name_);
        return -1;
    }

    inp_file_->read(header_buffer_,100);
    int file_code=0;
    /*file code  should be 9994 and is big endian*/
    file_code=header_buffer_[0]<<24 | (header_buffer_[1]<<16 & 0x00ff0000)|
                (header_buffer_[2]<<8& 0x0000ff00)|(header_buffer_[3]&0xff);
    if (file_code !=9994)
    {
      // QMessageBox::information(this,"Shape file(.shp)","This is not a valid .shp file");
        return -1;
    }
    file_length_=header_buffer_[24]<<24 | (header_buffer_[25]<<16 & 0x00ff0000)|
                (header_buffer_[26]<<8 & 0x0000ff00)|(header_buffer_[27]& 0xff);
    file_length_*=2;
    /*version value is 1000 and little endian*/
    unsigned int file_version_=header_buffer_[28]<<24| (header_buffer_[29]<<16 & 0x00ff0000)|
                (header_buffer_[30]<<8 & 0x0000ff00)|(header_buffer_[31] & 0xff);
    big_endian_to_little(file_version_);

    unsigned int shpt=header_buffer_[32]<<24| (header_buffer_[33]<<16 &0x00ff0000)|
                (header_buffer_[34]<<8 & 0x0000ff00)|(header_buffer_[35]&0xff);
    big_endian_to_little(shpt);
    esri_shape_type_=this->specify_shp_type(shpt);
    std::cout<<"shape type is : "<<this->get_shape_type_string()<<std::endl;
    /*define bounding box*/
    inp_file_->seekg(36,std::ios::beg);
    inp_file_->read((char*)&bounding_box_[0],8);
    inp_file_->read((char*)&bounding_box_[1],8);
    inp_file_->read((char*)&bounding_box_[2],8);
    inp_file_->read((char*)&bounding_box_[3],8);
    //std::cout<<"Xmin is : "<<bounding_box_[0]<<std::endl;
    //std::cout<<"Ymin is : "<<bounding_box_[1]<<std::endl;
    //std::cout<<"Xmax is : "<<bounding_box_[2]<<std::endl;
    //std::cout<<"ymax is : "<<bounding_box_[3]<<std::endl;
    inp_file_->seekg(100,std::ios::beg);
    if(esri_shape_type_==smgis::Ponit)
        this->read_point_feature();
    else if (esri_shape_type_==smgis::PolyLine)
        this->read_polyline_feature();
    else if (esri_shape_type_==smgis::Polygon)
        this->read_polygon_feature();
    return 0;

}

int SmEsriSHPFormat::read_point_feature(void)
{
//    std::cout<<"here here here "<<std::endl;
    int record_number;
    char * buff=new char [4];
    int content_length;   //should multiply by 2(16 bit word)
    double double_data;     //for reading x and y
    int fl=this->file_length_;
    fl-=100;
    //std::cout<<"fl is "<<fl<<std::endl;
    SmGeoItem *smg=0;
    SmPoint *sm_point=0;
    SmLayerInfo * smlf= this->graphic_handle_->create_new_layer();
        if (!smlf){std::cout<<"Esri shp file line 133"<<std::endl;}
        smlf->set_bounding_box_(this->bounding_box_);
        smlf->set_layer_is_hidden_(false);
        smlf->set_layer_shape_type_(this->esri_shape_type_);
        graphic_handle_->get_scene_handle_()->setSceneRect(bounding_box_[0],
                                                           bounding_box_[1],
                                                           bounding_box_[2]-bounding_box_[0],
                                                           bounding_box_[3]-bounding_box_[1]);
        smlf->set_layer_number_(SmLayerInfo::get_assign_num_to_layer_());
        /*realy important to call this increament method here*/
        SmLayerInfo::set_increament_assign_num_to_layer();
        smlf->set_layer_name_(this->get_shp_file_name_());
        std::cout<<"scene rect is:"<<bounding_box_[0]<<" "<<
                   bounding_box_[1]<<" "<<bounding_box_[2]<<" "<<
                   bounding_box_[3]<<std::endl;
//        smlf->calculate_intervals(this->graphic_handle_->get_panel_width_(),
//                                  this->graphic_handle_->get_panel_height_());

    /*
    ** for every new layer you have to calculate interval here in esri and other place
    ** in mssql and mysql and other database....
    */

    while(fl>0)
    {
        inp_file_->read(buff,4);
        fl-=4;
        record_number=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                          (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);

        inp_file_->read(buff,4);
        fl-=4;
        content_length=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);
        content_length=content_length*2;

        inp_file_->read(buff,4);    /*4 byte shape type(check it later to make sure
                                          it is what it should be)*/

        if (buff[0]==0 && buff[1]==0 && buff[2]==0 && buff[3]==0)
            std::cout<<"has NULL Shape Type"<<std::endl;
        fl-=4;
        sm_point=new SmPoint();
        inp_file_->read((char*)&double_data,8);
        fl-=8;

        sm_point->set_x_(double_data);
        inp_file_->read((char *)&double_data,8);
        fl-=8;
        sm_point->set_y_(double_data);
//        std::cout<<sm_point->well_known_text()<<std::endl;
        smg=new SmGeoItem(record_number,*sm_point);
        if (!smg)
            std::cout<<"can not allocate memory for items"<<std::endl;
        smg->set_layer_info_(smlf);
        smg->set_item_shape_type_(smgis::Ponit);
        delete sm_point;
         this->graphic_handle_->add_item_to_scene(smg);
        delete smg;
    }

    return 0;
}

int SmEsriSHPFormat::read_polyline_feature(void)
{
    //int cntr_num_of_point=0;
    int record_number;
    int num_part=0;
    int num_point=0;
    char * buff=new char[4];
    int content_length;   //should multiply by 2(16 bit word)
    double double_data;     //for reading x and y
    int fl=this->file_length_;
    fl-=100;
    double* bb=new double[4];
    SmPolyline * sm_polyline=0;
    SmGeoItem * smg=0;
    SmPoint* sm_point=0;
    int item_counter=0;
    SmLayerInfo * smlf= this->graphic_handle_->create_new_layer();

       if (!smlf){std::cout<<"Esri shp file line 209"<<std::endl;}
       smlf->set_bounding_box_(this->bounding_box_);
       graphic_handle_->get_scene_handle_()->setSceneRect(bounding_box_[0],
                                                          bounding_box_[1],
                                                          bounding_box_[2]-bounding_box_[0],
                                                          bounding_box_[3]-bounding_box_[1]);
       std::cout<<"scene rect is:"<<bounding_box_[0]<<" "<<
                  bounding_box_[1]<<" "<<bounding_box_[2]<<" "<<
                  bounding_box_[3]<<std::endl;
       smlf->set_layer_number_(SmLayerInfo::get_assign_num_to_layer_());
       /*realy important to call this increament method here*/
       SmLayerInfo::set_increament_assign_num_to_layer();
         smlf->set_layer_name_(this->get_shp_file_name_());
       smlf->set_layer_is_hidden_(false);
       smlf->set_layer_shape_type_(this->esri_shape_type_);
//       smlf->calculate_intervals(this->graphic_handle_->get_panel_width_(),
//                                this->graphic_handle_->get_panel_height_());


    while(fl>0)
    {
        inp_file_->read(buff,4);
        fl-=4;
        record_number=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                          (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);

        //std::cout<<"Record Number is : "<<record_number<<std::endl;
        inp_file_->read(buff,4);
        fl-=4;
        content_length=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);
        content_length=content_length*2;
        //std::cout<<"Content Length is : "<<content_length<<std::endl;
        inp_file_->read(buff,4);    /*4 byte shape type(check it later to make sure
                                          it is what it should be)*/
        fl-=4;
        inp_file_->read((char*)&bb[0],8);
        inp_file_->read((char*)&bb[1],8);
        inp_file_->read((char*)&bb[2],8);
        inp_file_->read((char*)&bb[3],8);
        //std::cout<<"Xmin(Polyline) is : "<<bb[0]<<std::endl;
        //std::cout<<"Ymin(Polyline) is : "<<bb[1]<<std::endl;
        //std::cout<<"Xmax(Polyline) is : "<<bb[2]<<std::endl;
        //std::cout<<"ymax(Polyline) is : "<<bb[3]<<std::endl;
        fl=fl-32;
        inp_file_->read((char*)&num_part,4);
        inp_file_->read((char*)&num_point,4);
        fl-=8;
        //std::cout<<"number of part is: "<<num_part<<std::endl;
        //std::cout<<"number of point is :"<<num_point<<std::endl;
        //cntr_num_of_point+=num_point;
        sm_polyline=new SmPolyline(num_part,num_point);
        //std::cout<<num_point<<std::endl;

        sm_polyline->set_bounding_box_(bb);
        int part_index;
        int count_er=0;
        while(num_part>0)
        {
            inp_file_->read((char*)&part_index,4);
        //    std::cout<<" aaasassasasasasa:"<<part_index<<std::endl;
            fl-=4;
            num_part-=1;
            sm_polyline->set_line_index_(count_er,part_index);
            count_er+=1;
        }
       // std::cout<<"hi here 258"<<std::endl;
        count_er=0;
         sm_point=new SmPoint();
      //   std::cout<<"hi here 261"<<std::endl;


        while(num_point>0)
        {
            inp_file_->read((char*)&double_data,8);
            fl-=8;
            sm_point->set_x_(double_data);
            inp_file_->read((char*)&double_data,8);
            fl-=8;
            sm_point->set_y_(double_data);
            num_point-=1;
            sm_polyline->set_point_array_(count_er,sm_point);
            count_er+=1;

        }
       // std::cout<<"hi here 276"<<std::endl;
        smg=new SmGeoItem(record_number,*sm_polyline);
        //std::cout<<"size of smg is :"<<sizeof(*smg)<<std::endl;
        //smg->set_layer_info_(0);
       // std::cout<<"hi here 278"<<std::endl;
        if (!smg)
            std::cout<<"can not allocate memory for items"<<std::endl;
        //smg->set_layer_info_(smlf);
        //smg->set_item_shape_type_(smgis::PolyLine);
        smg->set_layer_info_(smlf);

        //std::cout<<"hi here 285"<<std::endl;
        if (!graphic_handle_)
            std::cout<<"graphics_handle_ is null or shit"<<std::endl;
        this->graphic_handle_->add_item_to_scene(smg);
        //this->graphic_handle_->get_scene_handle_()->addItem(smg);
        delete sm_point;
        delete sm_polyline;
        delete smg;
        item_counter++;
        //if (item_counter> 50000)
          //  break;
       // std::cout<<"hi here 291"<<std::endl;
    }
    delete[] buff;

    return 0;
}   //end of poly line feature
/*
** read polygon feature in .shp file and hand it to QgraphicsItem class in Qt!!!
*/
int SmEsriSHPFormat::read_polygon_feature(void)
{
//    int cntr_num_of_point=0;
    int record_number;
    int num_part=0;
    int num_point=0;
    char * buff=new char[4];
    if (!buff)
    {
        //QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
        return -1;
    }
    int content_length;   //should multiply by 2(16 bit word)
    double double_data;     //for reading x and y
    int fl=this->file_length_;
    fl-=100;
    double* bb=new double[4];
    if (!bb)
    {
       // QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
        return -1;
    }
    SmPolygon * sm_polygon=0;
    SmGeoItem * smg=0;
    SmPoint* sm_point=0;
    int item_counter=0;
    SmLayerInfo * smlf= this->graphic_handle_->create_new_layer();

    if (!smlf)
    {
        //QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
        return -1;
    }
       smlf->set_bounding_box_(this->bounding_box_);
       //
       graphic_handle_->get_scene_handle_()->setSceneRect((bounding_box_[0]),
                                                          (bounding_box_[1]),
                                                          bounding_box_[2]-bounding_box_[0],
                                                          bounding_box_[3]-bounding_box_[1]);


       std::cout<<"scene rect is:"<<bounding_box_[0]<<" "<<
                  bounding_box_[1]<<" "<<bounding_box_[2]<<" "<<
                  bounding_box_[3]<<std::endl;
       std::cout<<"scene width is :"<<graphic_handle_->get_scene_handle_()->width()<<std::endl;
       smlf->set_layer_number_(SmLayerInfo::get_assign_num_to_layer_());
       /*realy important to call this increament method here*/
       SmLayerInfo::set_increament_assign_num_to_layer();
       smlf->set_layer_name_(this->get_shp_file_name_());
       smlf->set_layer_is_hidden_(false);
       smlf->set_layer_shape_type_(this->esri_shape_type_);
//     smlf->calculate_intervals(this->graphic_handle_->get_panel_width_(),
//                                this->graphic_handle_->get_panel_height_());


       while(fl>0)
       {
           inp_file_->read(buff,4);
           fl-=4;
           record_number=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                             (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);

           //std::cout<<"Record Number is : "<<record_number<<std::endl;
           inp_file_->read(buff,4);
           fl-=4;
           content_length=buff[0]<<24 | (buff[1]<<16 & 0x00ff0000)|
                                   (buff[2]<<8 & 0x0000ff00)|(buff[3]& 0xff);
           content_length=content_length*2;
           //std::cout<<"Content Length is : "<<content_length<<std::endl;
           inp_file_->read(buff,4);    /*4 byte shape type(check it later to make sure
                                             it is what it should be)*/
           fl-=4;
           inp_file_->read((char*)&bb[0],8);
           inp_file_->read((char*)&bb[1],8);
           inp_file_->read((char*)&bb[2],8);
           inp_file_->read((char*)&bb[3],8);

           fl=fl-32;
           inp_file_->read((char*)&num_part,4);
           inp_file_->read((char*)&num_point,4);
           fl-=8;

           if (num_part>1)
               item_counter+=num_point;
           sm_polygon=new SmPolygon(num_part,num_point);
           if (!sm_polygon)
           {
               //QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
               return -1;
           }

           sm_polygon->set_bounding_box_(bb);
           int part_index;
           int count_er=0;
           while(num_part>0)
           {
               inp_file_->read((char*)&part_index,4);
               fl-=4;
               num_part-=1;
               sm_polygon->set_part_index_(count_er,part_index);
               count_er+=1;
           }
           count_er=0;
            sm_point=new SmPoint();

           while(num_point>0)
           {
               inp_file_->read((char*)&double_data,8);
               fl-=8;
               sm_point->set_x_(double_data);
               inp_file_->read((char*)&double_data,8);
               fl-=8;
               sm_point->set_y_(double_data);
               num_point-=1;
               sm_polygon->set_point_array_(count_er,sm_point);
               count_er+=1;

           }
           smg=new SmGeoItem(record_number,*sm_polygon);

           if (!smg)
           {
               //QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
               return -1;
           }
           smg->set_layer_info_(smlf);

           if (!graphic_handle_)
           {
              // QMessageBox::information(this,"Shape file(.shp)","Can NOT allocate memory...program will be closed");
               return -1;
           }
           this->graphic_handle_->add_item_to_scene(smg);
           delete sm_point;
           delete sm_polygon;
           delete smg;
       }
       delete[] buff;
       std::cout<<"number of multipart\'s points is : "<<item_counter<<std::endl;
       return 0;
}

smgis::SmShapeType SmEsriSHPFormat::specify_shp_type(int shpt)
{
    switch(shpt)
    {
        /*
        **at this stage only support for polygon,point and polyline
        */
        case smgis::Ponit:
            return smgis::Ponit;
        case smgis::PolyLine:
            return smgis::PolyLine;
        case smgis::Polygon:
            return smgis::Polygon;
        default:
            return smgis::NullShape;
    }
}

unsigned int SmEsriSHPFormat::get_file_length_(void)
{
    return this->file_length_;
}

std::string SmEsriSHPFormat::get_shp_file_name_(void)
{
    return this->shp_file_name_;

}
std::string SmEsriSHPFormat::get_shape_type_string(void)
{
    switch(this->esri_shape_type_)
    {
        case smgis::Ponit:
            return "Point";break;
        case smgis::Polygon:
            return "Polygon";break;
      case smgis::PolyLine:
          return "Polyline";break;
      case smgis::NullShape:
            return "NullShape";break;
         default:
            return "Unrecognized Shape";break;
    }
}
