/***************************************************************************
                           sm_arcsde101_connection.cpp - SMGIS
                              -------------------
     begin                :  September 15 2012
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
#include "../sm_arcsde101_connection/sm_arcsde101_connection.h"

SmArcSDE101Connection::SmArcSDE101Connection(SmViewPanel * graphic_handle)
{
    graphic_handle_=graphic_handle;
    geo_type_=smgis::UNDEFINED;
    database_name_="";
    server_name_="";
    port_number_="";
    user_name_="";
    password_="";
    owner_name_="";
    db_=0;
    query_handle_=0;
}

SmArcSDE101Connection::SmArcSDE101Connection(std::string user, std::string pass, std::string server,
                       std::string dbase, std::string port_num,std::string owner)
{
    geo_type_=smgis::SQLGEOMETRY;
    password_=pass;
    user_name_=user;
    database_name_=dbase;
    port_number_=port_num;
    server_name_=server;
    owner_name_=owner;
    db_=0;
    query_handle_=0;
}


std::string SmArcSDE101Connection::get_database_name_(void)const
{
    return database_name_;
}

std::string SmArcSDE101Connection::get_owner_name_(void)const
{
    return owner_name_;
}

std::string SmArcSDE101Connection::get_password_(void)const
{
    return password_;
}

std::string SmArcSDE101Connection::get_port_number_(void)const
{
    return port_number_;
}

std::string SmArcSDE101Connection::get_server_name_(void)const
{
    return server_name_;
}

std::string SmArcSDE101Connection::get_user_name_(void)const
{
    return user_name_;
}

void SmArcSDE101Connection::set_database_name_(std::string dbase)
{
    database_name_=dbase;
}
void SmArcSDE101Connection::set_owner_name_(std::string own)
{
    owner_name_=own;
}

void SmArcSDE101Connection::set_password_(std::string pass)
{
    password_=pass;
}

void SmArcSDE101Connection::set_port_number_(std::string port_num)
{
    port_number_=port_num;
}
void SmArcSDE101Connection::set_server_name_(std::string server)
{
    server_name_=server;
}
void SmArcSDE101Connection::set_user_name_(std::string user)
{
    user_name_=user;
}

void SmArcSDE101Connection::set_db_(QSqlDatabase *db)
{
    this->db_=db;
    query_handle_=new QSqlQuery("",*db_);
}
void SmArcSDE101Connection::set_query_handle_(QSqlQuery *query_handle)
{
    this->query_handle_=query_handle;
}

void SmArcSDE101Connection::set_geo_type(void)
{
    QString str_query;
    str_query="SELECT keyword , parameter_name , config_string from " +
            QString(this->get_database_name_().c_str())+ "."+
            QString(this->get_owner_name_().c_str())+"." +"SDE_dbtune";
   if (query_handle_->exec(str_query)==false)
   {
       QSqlError err=query_handle_->lastError();
//       QMessageBox::information(dialog,"Query Error",err.text());
   }
   else
   {
       QString keyword1;
       QString parameter_name1;
       QString config_string1;
       while(query_handle_->next())
       {
           keyword1=query_handle_->value(0).toString();
           parameter_name1=query_handle_->value(1).toString();
           config_string1=query_handle_->value(2).toString();
           if (keyword1=="DEFAULTS")
           {
               if (parameter_name1=="GEOMETRY_STORAGE")
               {
                   if (config_string1=="GEOMETRY") //sql native geometry data
                   {
                       this->geo_type_=smgis::SQLGEOMETRY;
                   }
                   else if (config_string1=="GEOGRAPHY")
                   {
                        this->geo_type_=smgis::SQLGEOGRAPHI;
                   }
                   else if (config_string1=="SDEBINARY")
                   {
                        this->geo_type_=smgis::SDEBINARY;
                   }
               }
           }
       }
   }
}

QSqlQuery* SmArcSDE101Connection::get_query_handle_(void)const
{
    return query_handle_;
}

void SmArcSDE101Connection::load_feature_table(std::string table_name)
{

    if (table_name=="")
        return;
    if (geo_type_==smgis::UNDEFINED)
        set_geo_type();
    if (geo_type_==smgis::SDEBINARY)
    {
        load_feature_table93(table_name);
        return;
    }
    char * d_array=new char[8];
    SmGeoItem *smg=0;
    SmPoint *sm_point=0;
    SmPolyline * sm_polyline=0;
    QString shape_column;
    int layer_id;
    QString str_query="select layer_id,spatial_column from ";
    str_query+="[";
    str_query +=QString(database_name_.c_str());
    str_query+="].[";
    str_query+=owner_name_.c_str();
    str_query+="].[SDE_layers] where ";
    str_query+="table_name=";
    str_query+="\'";
    str_query+=table_name.c_str();
    str_query+="\';";



    if ( query_handle_->exec(str_query)==false)
    {
        std::cout<<"error in query"<<std::endl;
        return;
    }
    else
    {
        double bb[4];
        SmLayerInfo * smlf= graphic_handle_->create_new_layer();
        query_handle_->next();
        layer_id=query_handle_->value(0).toInt();
        smlf->set_db_layer_id_(layer_id);
        smlf->set_layer_is_hidden_(false);
        smlf->set_layer_number_(SmLayerInfo::get_assign_num_to_layer_());
        /*realy important to call this increament method here*/
        SmLayerInfo::set_increament_assign_num_to_layer();
        smlf->set_layer_name_(table_name);
        shape_column=query_handle_->value(1).toString();
        str_query="SELECT minx,miny,maxx,maxy FROM ";
        str_query+="[";
        str_query+=QString(database_name_.c_str());
        str_query+="].[";
        str_query+=QString(owner_name_.c_str());
        str_query+="].[SDE_layers";
        str_query+="] where table_name=";
        str_query+="\'";
        str_query+=QString(table_name.c_str());
        str_query+="\';";
        if (query_handle_->exec(str_query)==false)
        {
            std::cout<<"bounding box query error"<<std::endl;
            return;
        }
        else
        {
            int i=0;
            while(query_handle_->next())
            {
                while(i<4)
                {
                    bb[i]=query_handle_->value(i).toDouble();
                    std::cout<<query_handle_->value(i).toDouble()<<std::endl;
                    ++i;
                }
            }
        }
        smlf->set_bounding_box_(bb);
//        std::cout<<smlf->get_x_min()<<" , "<<
//                   smlf->get_y_min()<<" , "<<
//                   smlf->get_x_max()<<" , "<<
//                   smlf->get_y_max()<<std::endl;
        graphic_handle_->get_scene_handle_()->setSceneRect(
                    bb[0],bb[1],bb[2]-bb[0],bb[3]-bb[1]);
        str_query="select objectid,";
        str_query+=shape_column;
        str_query+=".STAsBinary() from ";
        str_query+="[";
        str_query+=QString(database_name_.c_str());
        str_query+="].[";
        str_query+=QString(owner_name_.c_str());
        str_query+="].[";
        str_query+=QString(table_name.c_str());
        str_query+="];";
        if ( query_handle_->exec(str_query)==false)
        {
            std::cout<<"error executing query...."<<std::endl;
        }
        else
        {
            int objectid;
            double x_coor,y_coor;
            QByteArray wkb_byte;
            unsigned int wkb_type;
            unsigned int counter=0;
            while(query_handle_->next())
            {

                objectid=query_handle_->value(0).toInt();
                wkb_byte=(query_handle_->value(1).toByteArray());
                if (wkb_byte[0]==0) // Big Endian Coding(XDR)
                {
                    std::cout<<"NO SOPPORT FOR BIG ENDIAN YET!!!!"<<std::endl;

                }
                else   // Little Endian Coding(NDR)
                {
                    wkb_type=wkb_byte[1] | (wkb_byte[2]<<8)| (wkb_byte[3]<<16) |
                            (wkb_byte[4] <<24);
                    switch (wkb_type)
                    {
                    case 1:         //wkbPoint
                    {
//                        counter++;
                        smlf->set_layer_shape_type_(smgis::Ponit);
                        for(int i=0;i<8;++i)
                            d_array[i]=wkb_byte[i+5];
                        x_coor= *reinterpret_cast<double*>(d_array);
                        for (int i=0;i<8;++i)
                            d_array[i]=wkb_byte[i+13];
                        y_coor= *reinterpret_cast<double*>(d_array);
//                        std::cout<<x_coor<<" , "<<y_coor<<std::endl;
                        sm_point=new SmPoint();
                        sm_point->set_x_(x_coor);
                        sm_point->set_y_(y_coor);
                        smg=new SmGeoItem(objectid,*sm_point);
                        if (!smg)
                            std::cout<<"can not allocate memory for items"<<std::endl;
                        smg->set_layer_info_(smlf);
                        smg->set_item_shape_type_(smgis::Ponit);
                        delete sm_point;
                        graphic_handle_->add_item_to_scene(smg);
                        delete smg;
                        break;
                    }
                    case 2: //wkbLineString
                    {

                        smlf->set_layer_shape_type_(smgis::PolyLine);
                        int num_of_points=0;
                        num_of_points=wkb_byte[5] | (wkb_byte[6]<<8)| (wkb_byte[7]<<16) |
                                (wkb_byte[8] <<24);
//                        std::cout<<objectid<<"-->"<<num_of_points<<std::endl;
                        unsigned int dbl_cntr=0;
                        if(num_of_points<0)
                            break;
                        sm_polyline=new SmPolyline(1,num_of_points);
                        sm_point=new SmPoint();
                        int count_er=0;
                        bb[3]=smlf->get_x_min();
                        bb[2]=smlf->get_y_min();
                        bb[0]=smlf->get_x_max();
                        bb[1]=smlf->get_y_max();

                        for(int i=0;i<num_of_points;++i)
                        {
                            for(int j=0;j<8;++j)
                                d_array[j]=wkb_byte.at(j+9+dbl_cntr);
                            x_coor= *reinterpret_cast<double*>(d_array);
//                            x_coor=atof(d_array);
                            for(int j=0;j<8;++j)
                                d_array[j]=wkb_byte.at(j+17+dbl_cntr);
                            y_coor= *reinterpret_cast<double*>(d_array);
//                            y_coor=atof(d_array);
                            bb[3]=x_coor>bb[3]?x_coor:bb[3];
                            bb[2]=y_coor>bb[2]?y_coor:bb[2];
                            bb[0]=x_coor<bb[0]?x_coor:bb[0];
                            bb[1]=y_coor<bb[1]?y_coor:bb[1];
                            std::cout<<x_coor<<" , "<<y_coor<<std::endl;
                            dbl_cntr+=16;
                            sm_point->set_x_(x_coor);
                            sm_point->set_y_(y_coor);
                            sm_polyline->set_point_array_(count_er,sm_point);
                            count_er+=1;
                        }
                        sm_polyline->set_bounding_box_(bb);
                         smg=new SmGeoItem(objectid,*sm_polyline);
                         if (!smg)
                             std::cout<<"can not allocate memory for items"<<std::endl;
                         smg->set_layer_info_(smlf);
//                         std::cout<<sm_polyline->get_x_min()<<" , "<<
//                                    sm_polyline->get_y_min()<<" , "<<
//                                    sm_polyline->get_x_max()<<" , "<<
//                                    sm_polyline->get_y_max()<<" , "<<std::endl;
                         graphic_handle_->add_item_to_scene(smg);
                         delete sm_point;
                         delete sm_polyline;
                         delete smg;
                        break;
                    }
                    case 3:
                    {
                        //wkbPolygon
                        break;
                    }
                    case 4:
                    {
                        //wkbMiltiPoint
                        break;
                    }
                    case 5:
                    {
                        //wkbMultiLineString
                        break;
                    }
                    case 6:
                    {
                        //wkbMultiPolygon
                        break;
                    }
                    }
                }
            }
        }
    }
}



void SmArcSDE101Connection::load_feature_table93(std::string table_name)
{
    //here we read SDEBINARY binary represntation of geometry
    std::cout<<"SDEBINARY format from Arcsde NOT supported Yet"<<std::endl;

}
