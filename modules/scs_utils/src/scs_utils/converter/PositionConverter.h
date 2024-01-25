// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef _COMMON_CONVERTER_POSITIONCONVERTER_H_
#define _COMMON_CONVERTER_POSITIONCONVERTER_H_

#include <omnetpp.h>
#include "inet/common/geometry/common/Coord.h"

using namespace omnetpp;
using namespace inet;
namespace Satellite {
class PositionConverter : public cSimpleModule
{
protected:
    virtual void initialize(int stage) override;
    double scalex;
    double scaley;

    float currentX;
    float currentY;

    int offsetX ;   // when use with veins OSM map on left and offsetX indicate world map offset to the left.
    int offset_x ;  // x offset from map to map2
    int offset_y ;  // y offset from map to map2
    int mapx ;      // world original map size
    int mapy ;      // world original map size
    int mapx2 ;
    int mapy2 ;
    int emapx ;
    int emapy ;

public:
    PositionConverter();
    virtual ~PositionConverter();

    virtual float currentXposition(double longitude);
    virtual float currentYposition(double latitude);

    virtual double isScaleX() { return scalex;};
    virtual double isScaleY() { return scaley;};
};
}
#endif
