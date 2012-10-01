/***************************************************************************
                            sm_shape_general.h - SMGIS
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

#ifndef SM_SHAPE_GENERAL_H
#define SM_SHAPE_GENERAL_H
namespace smgis
{

enum Datum
{
    NAD83,WGS84,WGS72,GRS80,
    Australian1965,Krasovsky1940,
    NorthAmerican1927,International1924,
    Hayford1909,Clarke1880,Clarke1866,
    Airy1830,Bessel1841,Everest1830
};

enum WKBGeometryType
{
    WKBPoint=1,WKBLineString=2,
    WKBPolygon=3,WKBMultiPoint=4,
    WKBMultiLineString=5,WKBMultiPolygon=6,
    WKBGeometryCollection=7
};

enum GeometryType
{
    SQLGEOMETRY,SQLGEOGRAPHI,SDEBINARY,UNDEFINED
};

struct SmDatum
{
  double stER;
  double stFT;
  double stPR;
  double stOOF;
  smgis::Datum stDatum;
};

enum SmShapeType
    {
        NullShape=0,Ponit=1,
        PolyLine=3,Polygon=5,
        MultiPoint=8,PointZ=11,
        PolyLineZ=13,PolygonZ=15,
        MultiPointZ=18,PointM=21,
        PolyLineM=23,PolygonM=25,
        MultiPointM=28,MultiPatch=31
    };

enum SmGadget
    {
        ZoomIn,ZoomOut,
        Pan,Identify,Exit,
        FullExtent,Cursor
    };

}
#endif
