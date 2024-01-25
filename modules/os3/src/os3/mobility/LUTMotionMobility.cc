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
// This program was developed based on `src/os3/mobility/LUTMotionMobility.cc`
// of os3 (https://github.com/inet-framework/os3). 

#include "LUTMotionMobility.h"
#include "scs_utils/converter/PositionConverter.h"
#include <cmath>

using namespace Satellite;

Define_Module(LUTMotionMobility);

void LUTMotionMobility::initialize(int stage)
{
    StationaryMobility::initialize(stage);

    EV << "initializing LUTMotionMobility stage " << stage << endl;
    WATCH(lastPosition);
    if (stage == 0) {
        offsetX = par("offsetX");

        mapx = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 0));


        mapx = mapx-offsetX;


        mapy = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 1));
        latitude = par("latitude");
        longitude = par("longitude");

        updateFromDisplayString = par("updateFromDisplayString");
    }
    if (stage == 1) {
        setInitialPosition();
    }

}

double LUTMotionMobility::getLUTPositionX() const
{
    return longitude;
}
double LUTMotionMobility::getLUTPositionY() const
{
    return latitude;
}

Coord& LUTMotionMobility::getCurrentPosition()
{
    //return Coord(lastPosition.x, lastPosition.y);
    return lastPosition;
}

//
// this mobility model does not deal with speed, but it must be implemented
// because it is a pure virtual function declared in IMobility
//
Coord LUTMotionMobility::getCurrentSpeed()
{
    return Coord(0,0,0);
}

void LUTMotionMobility::setInitialPosition()
{
#if 0
   lastPosition.y = (((-mapy * latitude) / 180) + (mapy / 2)) ;
   lastPosition.x = (mapx * longitude / 360 + (mapx / 2)) ;

   lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapx) + offsetX;
#endif

   PositionConverter * PC = dynamic_cast<PositionConverter *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("Pos"));

   if (PC!=nullptr) {
       lastPosition.x = PC->currentXposition(longitude);
       lastPosition.y = PC->currentYposition(latitude);
   }
   else {
       lastPosition.y = (((-mapy * latitude) / 180) + (mapy / 2)) ;
       lastPosition.x = (mapx * longitude / 360 + (mapx / 2)) ;
       lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapx) + offsetX;

   }

   EV << "latitude " << latitude << "longitude " << longitude << " X" << lastPosition.x << " Y" << lastPosition.y << endl;

   getDisplayString().setTagArg("p", 0, static_cast<long>(lastPosition.x));
   getDisplayString().setTagArg("p", 1, static_cast<long>(lastPosition.y));
}

double LUTMotionMobility::getLUTAltitude() const
{
    // for now tentatively altitude 0
    return 0;
}

