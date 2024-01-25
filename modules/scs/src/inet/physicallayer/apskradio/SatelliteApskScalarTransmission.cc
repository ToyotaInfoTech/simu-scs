//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarTransmission.cc`. 

#include "../../../inet/physicallayer/apskradio/SatelliteApskScalarTransmission.h"

#include "../../../inet/physicallayer/apskradio/SatelliteApskScalarTransmitter.h"
#include "os3/libnorad/cSite.h"
#include "os3/libnorad/cEci.h"
#include "os3/libnorad/cJulian.h"
#include "os3/libnorad/ccoord.h"
#include "leosatellites/libnorad/cEcef.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskScalarTransmission.h"
namespace inet {

namespace physicallayer {


cEci  SatelliteStartPosition;


SatelliteApskScalarTransmission::SatelliteApskScalarTransmission(const IRadio *transmitter, const Packet *packet, const simtime_t startTime, const simtime_t endTime, const simtime_t preambleDuration, const simtime_t headerDuration, const simtime_t dataDuration, const Coord startPosition, const Coord endPosition, const Quaternion startOrientation, const Quaternion endOrientation, const IModulation *modulation, b headerLength, b payloadLength, Hz centerFrequency, Hz bandwidth, bps bitrate, W power, cCoordGeo longLatStartPosition, cCoordGeo longLatEndPosition) :
    ApskScalarTransmission(transmitter, packet, startTime, endTime, preambleDuration, headerDuration, dataDuration, startPosition, endPosition, startOrientation, endOrientation, modulation, headerLength, payloadLength, centerFrequency, bandwidth, bitrate, power)
{
    this->longLatStartPosition = longLatStartPosition;
    this->longLatEndPosition = longLatEndPosition;
    this->centerFrequency = centerFrequency;
    this->bandwidth = bandwidth;
    this->power = power;
    this->startPosition = startPosition;

    if (const SatelliteApskScalarTransmitter *SatelliteTransmitter = dynamic_cast<const SatelliteApskScalarTransmitter *>(transmitter->getTransmitter()))
    {
        SatelliteStartPosition = SatelliteTransmitter->getSatellitePosition();

    } else {
        EV << "\n==================================== cast failed in transmission ===================";
    }
}


const double SatelliteApskScalarTransmission::getDistance(const double& refLatitude, const double& refLongitude, const double& refAltitude)
{
    double distance;

    cJulian date;
    //cEci eci(this->longLatStartPosition, date);
    cEcef transmissionEcef = cEcef();

    cEci eci;
    cSite siteEquator(refLatitude, refLongitude, refAltitude);
    cCoordTopo topoLook = siteEquator.getLookAngle(eci);
    distance = topoLook.m_Range;
    return distance;

}

cEci SatelliteApskScalarTransmission::getSatellitePosition() const {
    return SatelliteStartPosition;
}


} // namespace physicallayer

} // namespace inet

