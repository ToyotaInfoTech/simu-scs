//
// Copyright (C) 2004 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/networklayer/configurator/ipv4/L3NetworkConfiguratorBase.h` of INET-4.4.1.

#ifndef INET_SATELLITENETWORKCONFIGURATORSCS_H_
#define INET_SATELLITENETWORKCONFIGURATORSCS_H_

#include "leosatellites/networklayer/configurator/ipv4/SatelliteNetworkConfigurator.h"

namespace inet {

class INET_API SatelliteNetworkConfiguratorScs : public SatelliteNetworkConfigurator {
    protected:
        virtual double computeWirelessLinkWeight(Link *link, const char *metric, cXMLElement *parameters) override;
        virtual double computeWiredLinkWeight(Link *link, const char *metric, cXMLElement *parameters) override;
};
} // inet
#endif /* INET_SATELLITENETWORKCONFIGURATORSCS_H_ */
