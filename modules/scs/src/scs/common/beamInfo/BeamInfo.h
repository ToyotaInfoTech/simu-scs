// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __Satellite_BEAMINFO_H_
#define __Satellite_BEAMINFO_H_

#include <omnetpp.h>

#include "inet/common/geometry/common/Coord.h"

using namespace omnetpp;
using namespace inet;
namespace Satellite {

class BeamInfo : public cSimpleModule
{
  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    int BeamIndex=0;

    int BeamPositionIndex;

    int assignedMaxBeamNum;

    std::map<int, Coord> beamOffsetRate;

    float unitScale_x;
    float unitScale_y;

    std::map<int, Coord> beamCenter;

    int numBeams = 19;

    float radian=0;

    bool bInitialized;

  public:
    BeamInfo();
    virtual ~BeamInfo();

    virtual void addBeam();

    virtual void updatePosition();

    virtual void FindBeamDirection();

    double beamAreaMinX;
    double beamAreaMinY;
    double beamAreaMaxX;
    double beamAreaMaxY;

     // speed for CircleMobility and ConstSpeedSpeedMobility
     double speed ;

     // position update interval for CircleMobility and ConstSpeedMobility
     double positionUpdateInterval ;

     // number of sub-CHANNEL per RB, DL
     int numSubChannels ;

     // number of TDMA channels
     int numTDMA ;

     double latitude;

     double longitude;

     double beamCenterLatitude;

     double beamCenterLongitude;

     double latitudeUE;
     double longitudeUE;

     int  satelliteIndex;

     int numBeamInterfaces;

     Coord Center=Coord(0,0);

     virtual int getNumBeams() {return numBeams; };

     virtual Coord getBeamCenter(int i);

     virtual float getBeamRadian() { return radian; };

     virtual void SetCenter(Coord X) { Center = X; };

};
}
#endif
