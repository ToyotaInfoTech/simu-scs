// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "scs_utils/converter/PositionConverter.h"

#include <cctype>
#include <algorithm>


using namespace omnetpp;
namespace Satellite {
Define_Module(PositionConverter);

PositionConverter::PositionConverter() {
    // TODO Auto-generated constructor stub

}

PositionConverter::~PositionConverter() {
    // TODO Auto-generated destructor stub
}

void PositionConverter::initialize(int stage)
{
    if (stage==0)
    {
         offsetX = par("offsetX");   // when use with veins OSM map on left and offsetX indicate world map offset to the left.
         offset_x = par("offset_x");  // x offset from map to map2
         offset_y = par("offset_y");  // y offset from map to map2
         mapx = par("mapx");      // world original map size
         mapy = par("mapy");      // world original map size
         mapx2 = par("mapx2");
         mapy2 = par("mapy2");
         emapx = par("emapx");
         emapy = par("emapy");

         scalex = emapx / mapx2 ;
         scaley = emapy / mapy2;

    }
}

float PositionConverter::currentXposition(double longitude)
{
    float currentx = scalex * (mapx * (longitude/360) + mapx/2);

    // scale window offset
    currentx = currentx - scalex * offset_x;

    // wrap around
    if (emapx==mapx){
        currentx = static_cast<int>(currentx) % static_cast<int>(mapx);
    }
    else
    if (currentx>emapx)
    {
        currentx=emapx;
    }
    else if (currentx<0)
    {
        currentx=0;
    }

    // 2 display offset
    currentx = currentx + offsetX;
    currentX = currentx;

    return currentx;
}

float PositionConverter::currentYposition(double latitude)
{
    float currenty = scaley * (-1 * mapy * (latitude / 180) + mapy / 2);

    currenty = currenty - scaley * offset_y;

    currentY = currenty;

    return currenty;
}
}
