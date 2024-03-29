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
// This program was developed based on `src/os3/mobility/Norad.cc`
// of os3 (https://github.com/inet-framework/os3). 

#include "../../os3/mobility/Norad.h"

#include <ctime>
#include <fstream>

#include "os3/libnorad/cTLE.h"
#include "os3/libnorad/cOrbit.h"
#include "os3/libnorad/cSite.h"

Define_Module(Norad);

Norad::Norad()
{
    gap = 0.0;
    tle = nullptr;
    orbit = nullptr;
}

void Norad::finish()
{
    delete orbit;
    delete tle;
}

void Norad::initializeMobility(const simtime_t& targetTime)
{
    std::string filename = par("TLEfile").stringValue();
    //std::cout << "Norad initialize mobility." << std::endl;

    // read file with TLE data
    std::fstream tleFile;
    tleFile.open(filename.c_str());

    // Length 100 should be enough since lines are usually 70+'\n' char long
    char line[100]     = "";
    char line1tmp[100] = "";
    char line2tmp[100] = "";
    //std::cout << "Norad initialization." << filename.c_str() << std::endl;
    std::string satelliteName = getParentModule()->par("satelliteName").stringValue();
    //std::string satelliteName = cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("satellite",)->par("satelliteName").stringValue();
    std::string line_str;
    if (satelliteName == "") {
        int index = getParentModule()->getIndex();
        int i = 0;
        //std::cout << "Norad index." << index << std::endl;
        do {
            tleFile.getline(line, 100);
            if (!tleFile.good()) {
                std::cout << "Error in Norad::initializeMobility(): Cannot read further satellites from TLE file!" << i << std::endl;
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
    orbit = new cOrbit(tle);

    // Gap is needed to eliminate different start times
    gap = orbit->TPlusEpoch(currentJulian);

    updateTime(targetTime);

    // Set name from TLE file for icon name
    line3 = orbit->SatName(false);
    /*if (line3.find(" (") != std::string::npos) {
        line3.at(line3.find(" (")) = '\n';
    }*/

    //std::size_t found = line3.find("(PRN ");
    //std::string satName = "PRN-";
    std::size_t found = line3.find("(STARLINK-");
    std::string satName = "STARLINK-";
    satName.push_back(line3.at(found+10));
    satName.push_back(line3.at(found+11));
    satName.push_back(line3.at(found+12));
    satName.push_back(line3.at(found+13));   
    satName += "\nsatellite";
    //getParentModule()->setName(satName.c_str());
}

void Norad::updateTime(const simtime_t& targetTime)
{
    orbit->getPosition((gap + targetTime.dbl()) / 60, &eci);
    geoCoord = eci.toGeo();
}

double Norad::getLongitude()
{
    return rad2deg(geoCoord.m_Lon);
}

double Norad::getLatitude()
{
    return rad2deg(geoCoord.m_Lat);
}

double Norad::getElevation(const double& refLatitude, const double& refLongitude, const double& refAltitude)
{
    cSite siteEquator(refLatitude, refLongitude, refAltitude);
    cCoordTopo topoLook = siteEquator.getLookAngle(eci);
    if (topoLook.m_El == 0.0) {
        error("Error in Norad::getElevation(): Corrupted database.");
    }
    return rad2deg(topoLook.m_El);
}

double Norad::getAzimuth(const double& refLatitude, const double& refLongitude, const double& refAltitude)
{
    cSite siteEquator(refLatitude, refLongitude, refAltitude);
    cCoordTopo topoLook = siteEquator.getLookAngle(eci);
    if (topoLook.m_El == 0.0) {
        error("Error in Norad::getAzimuth(): Corrupted database.");
    }
    return rad2deg(topoLook.m_Az);
}

double Norad::getAltitude()
{
    geoCoord = eci.toGeo();
    return geoCoord.m_Alt;
}

double Norad::getDistance(const double& refLatitude, const double& refLongitude, const double& refAltitude)
{
    cSite siteEquator(refLatitude, refLongitude, refAltitude);
    cCoordTopo topoLook = siteEquator.getLookAngle(eci);
    double distance = topoLook.m_Range;
    return distance;
}

void Norad::handleMessage(cMessage* msg)
{
    error("Error in Norad::handleMessage(): This module is not able to handle messages.");
}

void Norad::setJulian(std::tm* currentTime)
{
    currentJulian = cJulian(currentTime->tm_year + 1900,
                            currentTime->tm_mon + 1,
                            currentTime->tm_mday,
                            currentTime->tm_hour,
                            currentTime->tm_min, 0);
}
