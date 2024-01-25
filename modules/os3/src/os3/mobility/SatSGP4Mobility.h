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
// This program was developed based on `src/os3/mobility/SatSGP4Mobility.h`
// of os3 (https://github.com/inet-framework/os3). 

#ifndef __OS3_SatSGP4Mobility_H__
#define __OS3_SatSGP4Mobility_H__

#include "inet/mobility/base/MovingMobilityBase.h"

#include "Norad.h"


class Norad;

//-----------------------------------------------------
// Class: SatSGP4Mobility
//
// Realizes the SatSGP4 mobility module - provides methods to get and set
// the position of a satellite module and resets the satellite position when
// it gets outside the playground.
//-----------------------------------------------------
using namespace inet;
class SatSGP4Mobility : public MovingMobilityBase
{
public:
    SatSGP4Mobility();

    // returns x-position of satellite on playground (not longitude!)
    virtual double getPositionX() const                  { return lastPosition.x; };

    // returns y-position of satellite on playground (not latitude!)
    virtual double getPositionY() const                  { return lastPosition.y; };

    // returns the altitude of the satellite.
    virtual double getAltitude() const;

    // returns the elevation for the satellite in degrees
    virtual double getElevation(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999) const;

    // returns the azimuth from satellite to reference point in degrees
    virtual double getAzimuth(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999) const;

    // returns the Euclidean distance from satellite to reference point
    virtual double getDistance(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999) const;

    // returns satellite latitude
    virtual double getLatitude() const;

    // returns satellite longitude
    virtual double getLongitude() const;

    Coord targetPosition;

protected:
    Norad* noradModule;
    int mapX, mapY;
    double transmitPower;

    // initialize module
    // - creates a reference to the Norad moudule
    // - timestamps and initial position on playground are managed here.
    virtual void initialize(int stage) override;

    // sets the position of satellite
    // - sets the target position for the satellite
    // - the position is fetched from the Norad module with reference to the current timestamp
    virtual void setTargetPosition();

    // resets the position of the satellite
    // - wraps around the position of the satellite if it reaches the end of the playground
    virtual void fixIfHostGetsOutside();

    // implements basic satellite movement on map

    virtual void initializePosition() override;

    virtual void move() override;
    //virtual void move();

    // tak added.
    int  offsetX;

};

#endif
