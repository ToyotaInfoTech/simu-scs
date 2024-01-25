// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "scs/base/SatelliteHost.h"
#if 1
#include "scs/common/beamInfo/BeamInfo.h"
#endif
using namespace omnetpp;

namespace Satellite {
Define_Module(SatelliteHost);

void SatelliteHost::initialize()
{
    // TODO - Generated method body

    //std::string satelliteName = getParentModule()->par("satelliteName").stringValue();
    std::string satelliteName = "STARLINK-3308";
    sTrackingFileName = satelliteName+".trace.txt";

    if (sTrackingFileName!="")
    {
        trackingFile.open(sTrackingFileName);
    }
}

void SatelliteHost::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (trackingFile)
    {
        trackingFile.close();
    }
}

void SatelliteHost::updatePosition()
{
#if 1
    BeamInfo * BM = dynamic_cast<BeamInfo *>(getSubmodule("bm"));
    BM->updatePosition();
#endif
}

void SatelliteHost::writeTime(int year, int month, int day, int hour, int min)
{
    if (trackingFile)
    {
        trackingFile << "year: " << year << "month: " << month << "day: " << day << "hour: " << hour << min << endl;
        EV_INFO << "year: " << year << "month: " << month << "day: " << day << "hour: " << hour << min << endl;
    }
}

void SatelliteHost::writePosition(double x, double y)
{
    if (trackingFile)
    {
        trackingFile << "longitude: " << x << "latitude: " << y <<  endl;
        EV_INFO << "longitude: " << x << "latitude: " << y <<  endl;
    }
}
}

