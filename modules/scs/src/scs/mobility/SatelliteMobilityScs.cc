//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "SatelliteMobilityScs.h"
#include "os3/libnorad/cJulian.h"

#include <ctime>
#include <cmath>

#include "leosatellites/mobility/INorad.h"
#include "leosatellites/mobility/NoradA.h"
#include "os3/mobility/NoradScs.h"
#include "scs/base/SatelliteHost.h"
#include "scs/common/beamInfo/BeamInfo.h"
#include "scs_utils/converter/PositionConverter.h"

namespace inet {

Define_Module(SatelliteMobilityScs);

SatelliteMobilityScs::SatelliteMobilityScs() : SatelliteMobility()
{
   targetPosition = Coord::ZERO;

}

void SatelliteMobilityScs::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);

    if (stage == 1) {
        noradModule->initializeMobility(0);

    }
    else if (stage == 0) {
        noradModule = check_and_cast< INorad* >(getParentModule()->getSubmodule("NoradModule"));
        BeamCircleInfo = check_and_cast<Satellite::BeamInfo*>(getParentModule()->getSubmodule("bm"));
        offsetX = par("offsetX");

        if (noradModule == nullptr) {
            error("Error in SatSGP4Mobility::initializeMobility(): Cannot find module Norad.");
        }

        targetyear = par("targetyear");
        targetmonth = par("targetmonth");
        targetday = par("targetday");
        targethour = par("targethour");
        targetsec = par("targetsec");
        targetmin = par("targetmin");
        targetwday = par("targetwday");
        targetyday = par("targetyday");
        enableRepeatCycle = par("enableRepeatCycle");
        cycleTime = par("cycleTime");
        targetTime.tm_hour = targethour;
        targetTime.tm_mday = targetday;
        targetTime.tm_min = targetmin;
        targetTime.tm_mon = targetmonth;
        targetTime.tm_year = targetyear;
        targetTime.tm_gmtoff = 7;
        targetTime.tm_isdst = 0;
        targetTime.tm_sec = targetsec;
        targetTime.tm_wday = targetwday;
        targetTime.tm_yday = targetyday;
        intervalTimer = 0;
        cycleTimeSet = cycleTime;
        std::time_t yesterday;
        time(&yesterday);
        tm * tt = std::localtime(&yesterday);
        targetTime.tm_gmtoff = tt->tm_gmtoff;
        targetTime.tm_zone = tt->tm_zone;
        startTime = simTime();
        noradModule->INorad::setJulian(&targetTime);
        mapX = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 0));
        mapX = mapX-offsetX;
        mapY = std::atoi(getParentModule()->getParentModule()->getDisplayString().getTagArg("bgb", 1));
        EV << "initializing SatSGP4Mobility stage " << stage << endl;
        WATCH(lastPosition);
        thisIndex = getParentModule()->getIndex();
    }
}

void SatelliteMobilityScs::initializePosition()
{
    nextChange = simTime();
    if(NoradScs* noradAModule = dynamic_cast<NoradScs*>(noradModule)){
        satellitePosition = noradAModule->getSatellitePosition();
    }

    MobilityBase::initializePosition();
    if (!stationary) {
        setTargetPosition();
        EV_INFO << "current target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();
    }
    lastUpdate = simTime();
    scheduleUpdate();
}



void SatelliteMobilityScs::setTargetPosition()
{
    nextChange += updateInterval.dbl();
    intervalTimer += updateInterval.dbl();
    Satellite::PositionConverter * PC = dynamic_cast<Satellite::PositionConverter *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("Pos"));

    if ((intervalTimer>cycleTimeSet) && enableRepeatCycle>0){
        initialize(1);
        intervalTimer = 0;
    }

    noradModule->updateTime(intervalTimer);
    if (PC!=nullptr) {
        lastPosition.x = PC->currentXposition(noradModule->getLongitude());
        lastPosition.y = PC->currentYposition(noradModule->getLatitude());
    }
    else {
        lastPosition.x = mapX * noradModule->getLongitude() / 360 + (mapX / 2);
        lastPosition.x = static_cast<int>(lastPosition.x) % static_cast<int>(mapX) + offsetX;

        float lat = noradModule->getLatitude();

        lastPosition.y = ((-mapY * lat) / 180) + (mapY / 2);
    }

    targetPosition.x = lastPosition.x;
    targetPosition.y = lastPosition.y;

    if(NoradScs *noradAModule = dynamic_cast<NoradScs*>(noradModule)){
        satellitePosition = noradAModule->getSatellitePosition();
    }

    if (BeamCircleInfo!=nullptr)
    {
        BeamCircleInfo->SetCenter(targetPosition);
        BeamCircleInfo->updatePosition();
    }
}

void SatelliteMobilityScs::move()
{
    if(NoradScs *noradAModule = dynamic_cast<NoradScs*>(noradModule)){
        satellitePosition = noradAModule->getSatellitePosition();
    }

    EV_INFO << "longitude: " << getLongitude() << "latitude: " << getLatitude() <<  endl;

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
        Satellite::BeamInfo* host=dynamic_cast<Satellite::BeamInfo*>(getParentModule()->getSubmodule("bm"));
        host->updatePosition();
    }

    raiseErrorIfOutside();

}

void SatelliteMobilityScs::ttprint(std::tm ttime)
{
    int year = ttime.tm_year + 1900;
    int month = ttime.tm_mon + 1;
    int day = ttime.tm_mday;
    int hour = ttime.tm_hour;
    int min = ttime.tm_min;

    EV_INFO << "year: " << year << "month: " << month << "day: " << day << "hour: " << hour << min << endl;
}

}
