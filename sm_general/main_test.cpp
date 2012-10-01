/***************************************************************************
                            main_test.cpp - SMGIS
                              -------------------
     begin                : Thursday July 10 2012
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
#include <string>
#include <iostream>
#include "sm_general.h"
int main ()
{
    unsigned int a=0x90ab12cd;
    std::cout<<"a is : "<<a<<std::endl;
    big_endian_to_little(a);
    std::cout<<a<<std::endl;
    little_endian_to_big(a);
    std::cout<<a<<std::endl;
    return 0;
}
