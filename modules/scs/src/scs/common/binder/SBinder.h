// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __Satellite_SBINDER_H_
#define __Satellite_SBINDER_H_

#include <omnetpp.h>
#include "inet/common/geometry/common/Coord.h"

using namespace omnetpp;
using namespace inet;
namespace Satellite {
/**
 * TODO - Generated class
 */
class SBinder : public cSimpleModule
{
  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

    int numOfSats; // Number of satellites
    int numOfMCCs; // Number of Mission Control Centers
    int numOfCars; // Number of UE Cars
    int numOfServiceLinkChannels; // Number of Channels
    int numBeamInterfaces;
    int numSubChannels;
    int initialized;

  private:

      std::map<int , int > k;
      std::map<int , cModule*>  referencetoCar;
      std::map<int , cModule*>  referencetoMCC;
      std::map<int,  cModule*>  referencetoSatellite;
      std::map<int , int>       referencetoCarChannel;
      std::map<int , int>       referencetoMCCChannel;

      std::map<int, int>        satelliteIndex;

      std::map<int, std::map<int, int>>   channelIndex;

  public:
      SBinder()
      { numOfSats=0;
        numOfMCCs=0;
        numOfCars = 0;
        numOfServiceLinkChannels = 0;
        numBeamInterfaces = 0;
        numSubChannels = 0;
        initialized = 0;
      }

      virtual ~SBinder(){

      }

     void registerChannel();

     /**
      * Registers a UE to a given channel
      */
     void registerChannelUE();

     void registerChannelSatellites();

     void registerChannelMCC();

     Coord getBeamPosition(int index);

};
}
#endif
