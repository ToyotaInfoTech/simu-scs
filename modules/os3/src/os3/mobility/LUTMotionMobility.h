//
// Copyright (c) Michael F. Henry
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on `src/os3/mobility/LUTMotionMobility.h`
// of os3 (https://github.com/inet-framework/os3). 

#ifndef __OS3_LUTMotionMobility_H__
#define __OS3_LUTMotionMobility_H__

#include <omnetpp.h>
#include "inet/mobility/base/MobilityBase.h"
#include "inet/mobility/static/StationaryMobility.h"    // inet
using namespace inet;
//-----------------------------------------------------
// Class: LUTMotionMobility
//
// Positions a ground station at a specific lat/long
//-----------------------------------------------------
class LUTMotionMobility : public StationaryMobility
{
public:
    // returns longitude
    double getLUTPositionX() const;

    // returns latitude
    double getLUTPositionY() const;

    virtual Coord& getCurrentPosition();
    virtual Coord getCurrentSpeed();

    double getLUTAltitude() const;

protected:
    virtual void initialize(int);

    virtual void setInitialPosition();

    //virtual void setTargetPosition();

    double latitude, longitude;   // Geographic coordinates
    int mapx, mapy;            // Coordinates on map
    bool updateFromDisplayString;

    // tak added
    int offsetX;
};

#endif
