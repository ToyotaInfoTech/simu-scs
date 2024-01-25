// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "BeamInfo.h"
#include "BeamDef.h"
#include "leosatellites/mobility/NoradA.h"
#include "inet/common/InitStages.h"

#include "leosatellites/mobility/SatelliteMobility.h"
#if 1
#include "scs/common/binder/SBinder.h"
#include "scs_utils/converter/PositionConverter.h"
#endif
#include "inet/common/ModuleAccess.h"

namespace Satellite {
Define_Module(BeamInfo);

BeamInfo::BeamInfo()
{
    bInitialized = false;
}

BeamInfo::~BeamInfo()
{

}

void BeamInfo::initialize(int stage)
{
    // TODO - Generated method body

    if (stage == 0) {

     latitude= par("latitude");

     longitude= par("longitude");

     beamCenterLatitude= par("beamCenterLatitude");

     beamCenterLongitude= par("beamCenterLongitude");

     satelliteIndex = getParentModule()->getIndex();

     numBeamInterfaces = par("numBeamInterfaces");

     numSubChannels = par ("numSubChannels");

     beamOffsetRate[0]=Coord(-2,4);
     beamOffsetRate[1]=Coord(  0, 4);
     beamOffsetRate[2]= Coord(  2, 4);
     beamOffsetRate[3]= Coord( -3, 2);
     beamOffsetRate[4]= Coord( -1, 2);
     beamOffsetRate[5]= Coord(  1, 2);
     beamOffsetRate[6]= Coord(  3, 2);
     beamOffsetRate[7]= Coord( -4, 0);
     beamOffsetRate[8]= Coord( -2, 0);
     beamOffsetRate[9]= Coord(  0, 0);
     beamOffsetRate[10]= Coord( 2, 0);
     beamOffsetRate[11]= Coord( 4, 0);
     beamOffsetRate[12]= Coord( -3, -2);
     beamOffsetRate[13]= Coord( -1, -2);
     beamOffsetRate[14]= Coord(  1, -2);
     beamOffsetRate[15]= Coord(  3, -2);
     beamOffsetRate[16]= Coord( -2, -4);
     beamOffsetRate[17]= Coord(  0, -4);
     beamOffsetRate[18]= Coord(  2, -4);
    }

}

void BeamInfo::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void BeamInfo::addBeam()
{

}

void BeamInfo::updatePosition()
{

    Coord pos;
    pos = Center;
#if 1
    PositionConverter * PC = dynamic_cast<PositionConverter *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("Pos"));

    if (PC!=nullptr)
    {
        for (int i=0; i<numBeams; i++)
        {
            float x = pos.x + beamOffsetRate[i].x*PC->isScaleX()* 9;
            float y = pos.y + beamOffsetRate[i].y*PC->isScaleY()* 9;
            beamCenter[i]=Coord(x, y) ;
        }

        radian = 9 * PC->isScaleX() * cos(PI/4);

        if (bInitialized)
        {
            FindBeamDirection();
        }

    }
#endif
    // for each subchannels to find a user
    bInitialized = true;
}

Coord BeamInfo::getBeamCenter(int i)
{
    return beamCenter[i];
}

void  BeamInfo::FindBeamDirection()
{
#if 1
    SBinder * SB = dynamic_cast<SBinder *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("sbinder"));
    PositionConverter * PC = dynamic_cast<PositionConverter *>(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("Pos"));
#endif

    double initialDistance = 16200; //(90** + 90**)
    int posIndex=0;
#if 1
    if ((PC!=nullptr) && (SB!=nullptr) )
    {
        SB->registerChannel();

        for (int i=0; i<numBeams; i++)
        {
            Coord Pos = beamCenter[i];
            Coord BeamPosition = SB->getBeamPosition(i);
            Coord BeamMapOnCanvas;

            BeamMapOnCanvas.x = PC->currentXposition(BeamPosition.x);
            BeamMapOnCanvas.y = PC->currentXposition(BeamPosition.y);

            double distance2x = (Pos.x-BeamMapOnCanvas.x)*(Pos.x-BeamMapOnCanvas.x) + (Pos.y-BeamMapOnCanvas.y)*(Pos.y-BeamMapOnCanvas.y);

            if (distance2x<=initialDistance) {
                initialDistance = distance2x;
                posIndex = i;
            }
        }

        BeamPositionIndex = posIndex;

    }

    EV << "\nBeamPosition: SatelliteIndex: " << satelliteIndex << " beam index: " << BeamPositionIndex  << "\n";
#endif
}
}
