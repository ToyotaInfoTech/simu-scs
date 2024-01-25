//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef MOBILITY_SATELLITEMOBILITYSCS_H_
#define MOBILITY_SATELLITEMOBILITYSCS_H_


#include "leosatellites/mobility/SatelliteMobility.h"
#include "inet/base/BeamVisualizerBase.h"
#include "leosatellites/mobility/NoradA.h"
#include "scs/common/beamInfo/BeamInfo.h"

namespace inet {

class SatelliteMobilityScs : public SatelliteMobility
{
public:
    SatelliteMobilityScs();
    void initialize(int stage) override;
    virtual void initializePosition() override;
    int thisIndex;
    virtual int getThisIndex() const {return thisIndex; };
    virtual const cEci  getSatellitePosition() const  {return satellitePosition; }
    Coord targetPosition;
    virtual void ttprint(std::tm ttime);

protected:
    Satellite::BeamInfo* BeamCircleInfo;
    int  offsetX;
    cEci satellitePosition;
    int targetyear, targetmonth, targetday, targethour, targetmin, targetsec, targetwday, targetyday;
    simtime_t intervalTimer, cycleTimeSet;
    int cycleTime, enableRepeatCycle;
    virtual void setTargetPosition();
    virtual void move() override;
    std::tm targetTime;
    simtime_t startTime;
};
}
#endif
