///
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/errormodel/ApskErrorModel.h`. 

#ifndef ___SATELLITEERRORMODEL_H_
#define ___SATELLITEERRORMODEL_H_

#include <omnetpp.h>

using namespace omnetpp;


#include "inet/physicallayer/wireless/common/base/packetlevel/ErrorModelBase.h"

using namespace omnetpp;

namespace inet {
namespace physicallayer{



/**
 * TODO - Generated class
 */
class INET_API SatelliteErrorModel : public ErrorModelBase
{
  protected:
    virtual void initialize() override;
    //virtual void handleMessage(cMessage *msg) override;

  public:

    virtual std::ostream& printToStream(std::ostream& stream, int level, int evFlags = 0) const override;

    virtual double computePacketErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

    virtual double computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;

    virtual double computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const override;


};

}
}
#endif
