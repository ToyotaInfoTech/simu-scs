// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#ifndef __SATELLITESTANDARDHOST_H_
#define __SATELLITESTANDARDHOST_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include <fstream>
#include <string>

using namespace omnetpp;
namespace Satellite {
struct parameters
{
    int numBeamInterfaces;
    int numSubChannels;
};
/**
 * TODO - Generated class
 */
class INET_API SatelliteHost : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    parameters userParameters;

    virtual void updatePosition();

    std::string  sTrackingFileName;
    std::ofstream trackingFile;

  public:
    const parameters& getParameters() const                          { return userParameters; };

    virtual void writeTime(int month, int day, int hour, int min, int sec);
    virtual void writePosition(double x, double y);
};
}
#endif
