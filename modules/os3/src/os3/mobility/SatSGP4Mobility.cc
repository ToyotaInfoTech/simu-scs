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
// This program was developed based on `src/os3/mobility/SatSGP4Mobility.cc`
// of os3 (https://github.com/inet-framework/os3). 

#include "os3/mobility/SatSGP4Mobility.h"

#include <ctime>
#include <cmath>

#include "os3/mobility/Norad.h"
#include "scs_utils/converter/PositionConverter.h"

using namespace Satellite;

Define_Module(SatSGP4Mobility);

SatSGP4Mobility::SatSGP4Mobility()
{
   noradModule = nullptr;
   mapX = 0;
   mapY = 0;
   transmitPower = 0.0;
   targetPosition = Coord::ZERO;
}

void SatSGP4Mobility::initialize(int stage)
{
    if (stage == 1) {
        noradModule->initializeMobility(nextChange);
    }

    MovingMobilityBase::initialize(stage);

    //noradModule = check_and_cast< Norad* >(getParentModule()->getSubmodule("NoradModule"));
    if (stage == 0) {

        // Tak added.
        offsetX = par("offsetX");

        //std::cout << "SatSGP4Mobility norad" << std::endl;
        noradModule = check_and_cast< Norad* >(getParentModule()->getSubmodule("NoradModule"));
        if (noradModule == nullptr) {
            error("Error in SatSGP4Mobility::initializeMobility(): Cannot find module Norad.");
        }

        std::time_t timestamp = std::time(nullptr);       // get current time as an integral value holding the num of secs
                                                      // since 00:00, Jan 1 1970 UTC
        std::tm* currentTime = std::gmtime(&timestamp);   // convert timestamp into structure holding a calendar date and time

        ///
        noradModule->setJulian(currentTime);

        mapX = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 0));
        mapY = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 1));

        mapX = mapX-offsetX;

        transmitPower = getParentModule()->par("transmitPower");

        EV << "initializing SatSGP4Mobility stage " << stage << " X" << lastPosition.x << " Y" << lastPosition.y << endl;
        WATCH(lastPosition);
    }

    //updateVisualRepresentation();
    refreshDisplay();
}

void SatSGP4Mobility::initializePosition()
{
    MobilityBase::initializePosition();
    if (!stationary) {
        setTargetPosition();
        EV_INFO << "current target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();
    }
    lastUpdate = simTime();
    scheduleUpdate();

}

double SatSGP4Mobility::getAltitude() const
{
    return noradModule->getAltitude();
}

double SatSGP4Mobility::getElevation(const double& refLatitude, const double& refLongitude,
                                     const double& refAltitude) const
{
    return noradModule->getElevation(refLatitude, refLongitude, refAltitude);
}

double SatSGP4Mobility::getAzimuth(const double& refLatitude, const double& refLongitude,
                                   const double& refAltitude) const
{
    return noradModule->getAzimuth(refLatitude, refLongitude, refAltitude);
}

double SatSGP4Mobility::getDistance(const double& refLatitude, const double& refLongitude,
                                    const double& refAltitude) const
{
    return noradModule->getDistance(refLatitude, refLongitude, refAltitude);
}

double SatSGP4Mobility::getLongitude() const
{
    return noradModule->getLongitude();
}

double SatSGP4Mobility::getLatitude() const
{
    return noradModule->getLatitude();
}

void SatSGP4Mobility::setTargetPosition()
{
    nextChange += updateInterval.dbl();
    noradModule->updateTime(nextChange);
#if 0
    lastPosition.x = mapX * noradModule->getLongitude() / 360 + (mapX / 2);
    //lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapX);
    lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapX)+ offsetX;
    lastPosition.y = ((-mapY * noradModule->getLatitude()) / 180) + (mapY / 2);
#endif
    PositionConverter * PC = dynamic_cast<PositionConverter *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("Pos"));

    if (PC!=nullptr) {
        lastPosition.x = PC->currentXposition(noradModule->getLongitude());
        lastPosition.y = PC->currentYposition(noradModule->getLatitude());
    }
    else {
        lastPosition.x = mapX * noradModule->getLongitude() / 360 + (mapX / 2);
        //lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapX);
        lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapX)+ offsetX;
        lastPosition.y = ((-mapY * noradModule->getLatitude()) / 180) + (mapY / 2);

    }

    targetPosition.x = lastPosition.x;
    targetPosition.y = lastPosition.y;


    EV << "X " << targetPosition.x << "Y " << targetPosition.y << endl;
}

void SatSGP4Mobility::move()
{
    //LineSegmentsMobilityBase::move();

    simtime_t now = simTime();
    if (now == nextChange) {
        lastPosition = targetPosition;
        EV_INFO << "reached current target position = " << lastPosition << endl;
        setTargetPosition();
        EV_INFO << "new target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();
    }
    else if (now > lastUpdate) {
        ASSERT(nextChange == -1 || now < nextChange);
        lastPosition += lastVelocity * (now - lastUpdate).dbl();
    }

    raiseErrorIfOutside();
}

void SatSGP4Mobility::fixIfHostGetsOutside()
{
    raiseErrorIfOutside();
}
