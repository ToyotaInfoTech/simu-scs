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
// This program was developed partly based on `src/os3/mobility/Norad.cc`
// of os3 (https://github.com/inet-framework/os3). 

#include "../../os3/mobility/NoradScs.h"

#include "leosatellites/mobility/NoradA.h"

#include <ctime>
#include <cmath>
#include <fstream>

#include "os3/libnorad/cTLE.h"
#include "os3/libnorad/cOrbitScs.h"
#include "os3/libnorad/cSite.h"

using namespace omnetpp;
Define_Module(NoradScs);

NoradScs::NoradScs() : NoradA()
{
    line0 = "";
    line1 = "";
    line2 = "";
}

void NoradScs::updateTime(const simtime_t& targetTime)
{
    orbit->getPosition((gap + targetTime.dbl()) / 60, &eci);
    geoCoord = eci.toGeo();
    cVector p = eci.getPos();
    satellitePosition = eci;
}


void NoradScs::initializeMobility(const simtime_t& targetTime)
{

    std::string satNameA = par("satName");
    int epochY = par("epochYear");
    double epochD = par("epochDay");
    double ecc = par("eccentricity");
    double incl = par("inclination");
    double meanAnom = par("meanAnomaly");
    double bstarA = par("bstar");
    double dragA = par("drag");
    int phaseOffset = par("phaseOffset");
    planes = par("planes");
    satPerPlane = par("satPerPlane");
    elevationAngle = par("elevationAngle");
    double altitude = par("altitude");

    int satIndex = getParentModule()->getIndex();
    double mMotion = par("meanMotion");
    int gapOffset = par("gapOffset");
    int simcycle = par("simcycle");
    std::string filename = par("TLEfile").stringValue();

    std::string satelliteName = getParentModule()->par("satelliteName").stringValue();

    if (orbit!=nullptr) {
        delete orbit;
    }

    if (filename!="") {
        std::fstream tleFile;
        tleFile.open(filename.c_str());
        char line[100]     = "";
        char line1tmp[100] = "";
        char line2tmp[100] = "";
        std::string line_str;

        if (satelliteName == "") {
            int index = satIndex;

            int i = 0;
            do {
                tleFile.getline(line, 100);
                if (!tleFile.good()) {
                    EV << "Error in Norad::initializeMobility(): Cannot read further satellites from TLE file!" << std::endl;
                    endSimulation();
                }
            } while (i++ < index * 3 && tleFile.good());
            line_str.append(line);

        } else {
            do {
                line_str = "";
                tleFile.getline(line, 100);
                line_str.append(line);
            } while (tleFile.good()
                    && line_str.find(satelliteName.c_str()) == std::string::npos);
        }
        tleFile.getline(line1tmp, 100);
        tleFile.getline(line2tmp, 100);

        // Pretty up the satellites name
        line_str = line_str.substr(0, line_str.find("  "));
        line0 = line_str;
        line1.append(line1tmp);
        line2.append(line2tmp);
        cTle tle(line0, line1, line2);
        orbit = new cOrbitScs(tle);

        // Set name from TLE file for icon name
        line3 = orbit->SatName(false);
    }
    else {
        EV << "Error in NoradScs::initializeMobility(): TLE file is not specified." << std::endl;
        endSimulation();
    }

    gap = orbit->TPlusEpoch(currentJulian);        
    gap += gapOffset;
    updateTime(targetTime);
}
