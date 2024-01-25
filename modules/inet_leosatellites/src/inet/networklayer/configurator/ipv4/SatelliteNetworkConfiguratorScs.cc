//
// Copyright (C) 2004 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/networklayer/configurator/ipv4/L3NetworkConfiguratorBase.cc` of INET-4.4.1.

#include "SatelliteNetworkConfiguratorScs.h"

#include <set>

Define_Module(inet::SatelliteNetworkConfiguratorScs);

namespace inet {

static double parseCostAttribute(const char *costAttribute)
{
    if (!strncmp(costAttribute, "inf", 3))
        return INFINITY;
    else {
        double cost = atof(costAttribute);
        if (cost <= 0)
            throw cRuntimeError("Cost cannot be less than or equal to zero");
        return cost;
    }
}

double SatelliteNetworkConfiguratorScs::computeWirelessLinkWeight(Link *link, const char *metric, cXMLElement *parameters)
{
    const char *costAttribute = parameters->getAttribute("cost");
    if (costAttribute != nullptr)
        return parseCostAttribute(costAttribute);
    else {
        if (!strcmp(metric, "hopCount"))
            return 1;
        else
            return minLinkWeight;
    }
}

double SatelliteNetworkConfiguratorScs::computeWiredLinkWeight(Link *link, const char *metric, cXMLElement *parameters)
{
    const char *costAttribute = parameters->getAttribute("cost");
    if (costAttribute != nullptr)
        return parseCostAttribute(costAttribute);
    else {
        Topology::Link *linkOut = static_cast<Topology::Link *>(static_cast<Topology::Link *>(link));
        if (!strcmp(metric, "hopCount"))
            return 1;
        else if (!strcmp(metric, "delay")) {
            cDatarateChannel *transmissionChannel = dynamic_cast<cDatarateChannel *>(linkOut->getLinkOutLocalGate()->findTransmissionChannel());
            if (transmissionChannel != nullptr)
                return transmissionChannel->getDelay().dbl();
            else
                return minLinkWeight;
        }
        else if (!strcmp(metric, "dataRate")) {
            cChannel *transmissionChannel = linkOut->getLinkOutLocalGate()->findTransmissionChannel();
            if (transmissionChannel != nullptr) {
                double dataRate = transmissionChannel->getNominalDatarate();
                return dataRate != 0 ? 1 / dataRate : minLinkWeight;
            }
            else
                return minLinkWeight;
        }
        else if (!strcmp(metric, "errorRate")) {
            cDatarateChannel *transmissionChannel = dynamic_cast<cDatarateChannel *>(linkOut->getLinkOutLocalGate()->findTransmissionChannel());
            if (transmissionChannel != nullptr) {
                inet::L3NetworkConfiguratorBase::InterfaceInfo *sourceInterfaceInfo = link->sourceInterfaceInfo;
                double bitErrorRate = transmissionChannel->getBitErrorRate();
                double packetErrorRate = 1.0 - pow(1.0 - bitErrorRate, sourceInterfaceInfo->networkInterface->getMtu());
                return minLinkWeight - log(1 - packetErrorRate);
            }
            else
                return minLinkWeight;
        }
        else if (!strcmp(metric, "propagationDelay")) {
                return minLinkWeight;
        }
        else
            throw cRuntimeError("Unknown metric");
    }
}
}
