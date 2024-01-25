// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "SBinder.h"
#include <cctype>
#include <algorithm>
#include "inet/common/InitStages.h"
#include "leosatellites/mobility/GroundStationMobility.h"
#include "leosatellites/mobility/SatelliteMobility.h"
#include "scs/base/SatelliteHost.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskRadio.h"
//#include "../../../../subproj/veins_inet/VeinsInetMobility.h"

using namespace omnetpp;
namespace Satellite {
Define_Module(SBinder);

void SBinder::initialize(int stage)
{
    if (stage == 0) {
        // TODO - Generated method body
        numOfSats=par("numOfSats"); // Number of satellites
        numOfMCCs=par("numOfMCCs"); // Number of Mission Control Centers
        numOfCars=par("numOfCars"); // Number of UE Cars
        numOfServiceLinkChannels=par("numOfServiceLinkChannels"); // Number of Channels
        numBeamInterfaces = par("numBeamInterfaces");
        numSubChannels = par("numSubChannels");
    }
}

void SBinder::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}


void SBinder::registerChannel()
{
    //SatelliteHost* mob = check_and_cast< SatelliteHost* >(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("satellite",0));
    //int numBeamInterfaces= mob->getParameters().numBeamInterfaces;
    //int numSubChannels = mob->getParameters().numSubChannels;

    // Feeder link MCC always dedicate beam index 0
#if 1
    for (int i = 0; i < numOfMCCs; i++) {
        referencetoMCCChannel[i] = 0;
    }
    for (int i = 0; i < numOfCars; i++) {
        // physicallayer::ApskRadio* mob = check_and_cast< physicallayer::ApskRadio* >(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("GS",i)->getSubmodule("wlan",0)->getSubmodule("radio"));
        // if (mob != nullptr)
        // {
            int channelNum = 0;  //mob->getParameters().channelNumber;
            referencetoCarChannel[i]=channelNum;
        // }

    }

    registerChannelSatellites();
    registerChannelUE();
    registerChannelMCC();

#endif
    int beamNumber=0;
    for (int i = 0; i < numSubChannels*numBeamInterfaces; i++) {
       std::map<int , int > k;
       for (int j=0; j<numSubChannels; j++) {
           k[j]=beamNumber;
           channelIndex[i]=k;
       }
       beamNumber++;
     }
}

void SBinder::registerChannelUE()
{
#if 1
    for (int i = 0; i < numOfCars; i++) {
        char name[128];
        std::sprintf(name, "InetCar[%d].mobility", i);
        cModule *mob = cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("GS",i)->getSubmodule("mobility");

        if (mob != nullptr)
             referencetoCar[i]= (cModule*)mob;
        else {
            std::sprintf(name, "Error in SBinder.registerChannelUE(): Could not find module \"%s\".", name);
            error(name);
            EV << "\nError SBinder registerChannelUE(): " << name << "\n";
        }
    }
#endif
}


 /**
  * Registers a Satellite to a given channel
  */
void SBinder::registerChannelSatellites()
{
    for (int i = 0; i < numOfSats; i++) {
        char name[128];
        std::sprintf(name, "satellite[%d].mobility", i);

        SatelliteMobility* mob = check_and_cast< SatelliteMobility* >(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("satellite",i)->getSubmodule("mobility"));
         if (mob != nullptr)
             referencetoSatellite[i]=(cModule*)mob;
        else {
            std::sprintf(name, "Error in SBinder.registerChannelSatellites(): Could not find module \"%s\".", name);
            error(name);
            EV << "\nError SBinder registerChannelSatellites(): " << name << "\n";
        }
    }
}

/**
 * Registers a MCC to a given channel
 */
void SBinder::registerChannelMCC()
{
   for (int i = 0; i < numOfMCCs; i++) {
       char name[128];
       std::sprintf(name, "MCC[%d].mobility", i);

       GroundStationMobility* mob = dynamic_cast< GroundStationMobility* >(cSimulation::getActiveSimulation()->getSystemModule()->getSubmodule("MCC",i)->getSubmodule("mobility"));

        if (mob != nullptr)
            referencetoMCC[i]=(cModule*)mob;
       else {
           std::sprintf(name, "Error in SBinder.registerChannelMCC(): Could not find module \"%s\".", name);
           error(name);
           EV << "\nError SBinder registerChannelMCC(): " << name << "\n";
       }
   }
}

Coord SBinder::getBeamPosition(int beamIndex)
{
    Coord Pos;
    Pos.x=0;
    Pos.y=0;

    if (beamIndex==0)
    {
        if (GroundStationMobility* mob =dynamic_cast< GroundStationMobility* >(referencetoMCC[0]))
        {
            Pos.x = mob->getLUTPositionX();
            Pos.y = mob->getLUTPositionY();
        }
        else
        {
            Pos.x = 35.18698;
            Pos.y = 136.90033;
        }

    }
    else
    {
        if (auto iter = referencetoCarChannel.find(beamIndex); iter!=end(referencetoCarChannel))
        {
            int carIndex = referencetoCarChannel.at(beamIndex);
            if (carIndex<numOfCars) {
                if (GroundStationMobility *mob = dynamic_cast<GroundStationMobility*>(referencetoCar[carIndex]))
                {
                    Pos.x = mob->getLUTPositionX();
                    Pos.y = mob->getLUTPositionY();
                }
            }

        }
    }

    return Pos;
}

}

