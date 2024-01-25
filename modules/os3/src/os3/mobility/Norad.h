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
// This program was developed based on `src/os3/mobility/Norad.h`
// of os3 (https://github.com/inet-framework/os3). 

#ifndef __OS3_Norad_H__
#define __OS3_Norad_H__

#include <omnetpp.h>

#include <string>
#include <ctime>

#include "os3/libnorad/cEci.h"
#include "os3/libnorad/cJulian.h"
#include "os3/libnorad/ccoord.h"

class cTle;
class cOrbit;
using namespace omnetpp;
//-----------------------------------------------------
// Class: Norad
//
// Provides the functionality for satellite positioning
// this class provides the functionality needed to get the positions for satellites according
// to current tables from web information by providing known data
//-----------------------------------------------------
class Norad : public cSimpleModule
{
public:
    Norad();

    // sets the internal calendar by translating the current gregorian time
    // currentTime: time at which the simulation takes place
    void setJulian(std::tm* currentTime);

    // Updates the end time of current linear movement for calculation of current position
    // targetTime: End time of current linear movement
    void updateTime(const simtime_t& targetTime);

    // This method gets the current simulation time, cares for the file download (happens only once)
    // of the TLE files from the web and reads the values for the satellites according to the
    // omnet.ini-file. The information is provided by the respective mobility class.
    // targetTime: End time of current linear movement
    virtual void initializeMobility(const simtime_t& targetTime);

    // returns the longitude
    double getLongitude();

    // returns the latitude
    double getLatitude();

    // returns the elevation to a reference point
    double getElevation(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999);

    // returns the azimuth
    double getAzimuth(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999);

    // returns the altitude
    double getAltitude();

    void finish();

    // returns the distance to the satellite from a reference point (distance in km)
    double getDistance(const double& refLatitude, const double& refLongitude, const double& refAltitude = -9999);

    cEci eci;

protected:
    virtual void handleMessage(cMessage* msg);

private:

    cJulian currentJulian;
    double gap;

    cTle* tle;
    cOrbit* orbit;
    cCoordGeo geoCoord;
    std::string line0;
    std::string line1;
    std::string line2;
    std::string line3;
};

#endif
