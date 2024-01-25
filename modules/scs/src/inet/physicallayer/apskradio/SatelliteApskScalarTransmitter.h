//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarTransmitter.h`. 

#ifndef INET_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMITTER_H_
#define INET_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMITTER_H_

#include "inet/physicallayer/wireless/apsk/packetlevel/ApskScalarTransmitter.h"
#include "os3/libnorad/cEci.h"

namespace inet {
namespace physicallayer {

class SatelliteApskScalarTransmitter : public ApskScalarTransmitter {
    public:
            virtual const ITransmission *createTransmission(const IRadio *radio, const Packet *packet, const simtime_t startTime) const override;
            SatelliteApskScalarTransmitter();
            virtual cEci  getSatellitePosition() const;
    private:
            double SatelliteAltitude;
            void initialize(int stage) override;
};

}
}
#endif /* INET_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMITTER_H_ */
