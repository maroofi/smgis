/***************************************************************************
                            sm_general.h - SMGIS
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

#ifndef PANEL_WIDTH
#define PANEL_WIDTH 800
#endif

#ifndef PANEL_HEIGHT
#define PANEL_HEIGHT 600
#endif

#ifndef SM_GENERAL_H
#define SM_GENERAL_H

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>

/*
**
**Where does this term "endian" come from?
**Jonathan Swift was a satirist (he poked fun at society
**through his writings). His most famous book is
**"Gulliver's Travels", and he talks about how certain
**people prefer to eat their hard boiled eggs from the
**little end first (thus, little endian), while others
**prefer to eat from the big end (thus, big endians)
**and how this lead to various wars.
**
*/

inline int big_endian_to_little(unsigned int & little)
{
    if(sizeof(little) !=4)
    {
        std::cout<<"This is not a 4 byte Integer..."<<std::endl;
        return -1;
    }
    unsigned int temp=0;
    temp=((little & 0x000000ff)<<24)|((little & 0x0000ff00)<<8)|
            ((little & 0x00ff0000)>>8)|((little & 0xff000000)>>24);
    little=temp;
    return 0;

    /*
    ** In big endian, you store the most significant
    **      byte in the smallest address.
    */
}
inline int little_endian_to_big(unsigned int & big)
{
    /*
    **In little endian, you store the least significant
    **    byte in the smallest address.
    */
    if (sizeof(big)!=4)
    {
        std::cout<<"This is NOT 4 byte Integer"<<std::endl;
        return -1;
    }
    unsigned int temp=0;
    temp=((big & 0x000000ff)<<24)| ((big & 0x0000ff00)<<8)|
            ((big& 0x00ff0000)>>8)|((big&0xff000000)>>24);
            big=temp;
            return 0;
}

inline unsigned int calculate_double_to_pixel(const double & val,const double &min_bound,const double& interval)
{
    /*should we use floor here???*/
    return (unsigned int)(((val-min_bound)/interval));
}

#endif
