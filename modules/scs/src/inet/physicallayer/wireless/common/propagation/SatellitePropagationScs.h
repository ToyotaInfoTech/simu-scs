//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/physicallayer/wireless/common/propagation/ConstantSpeedPropagation.h` of INET-4.4.1. 

#ifndef __INET_SATELLITEPROPAGATIONSCS_H
#define __INET_SATELLITEPROPAGATIONSCS_H

#include "leosatellites/physicallayer/propagation/SatellitePropagation.h"

namespace inet {

namespace physicallayer {

class SatellitePropagationScs : public SatellitePropagation
{
  public:
    SatellitePropagationScs();
    virtual const IArrival *computeArrival(const ITransmission *transmission, IMobility *mobility) const override;
};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_SatellitePropagationScs_H

