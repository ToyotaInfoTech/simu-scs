//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarTransmitter.cc`. 

#include "../../../inet/physicallayer/apskradio/SatelliteApskScalarTransmitter.h"

#include "../../../inet/physicallayer/apskradio/SatelliteApskScalarTransmission.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskPhyHeader_m.h"
#include "inet/physicallayer/wireless/common/contract/packetlevel/RadioControlInfo_m.h"
#include "os3/mobility/LUTMotionMobility.h"
#include "os3/mobility/SatSGP4Mobility.h"
#include "inet/common/geometry/common/Coord.h"
#include "scs/mobility/SatelliteMobilityScs.h"
#include "leosatellites/mobility/GroundStationMobility.h"
#include "inet/common/InitStages.h"

using namespace Satellite;

namespace inet {

namespace physicallayer {

Define_Module(SatelliteApskScalarTransmitter);

SatelliteApskScalarTransmitter::SatelliteApskScalarTransmitter()
{
    SatelliteAltitude = 1684;
}

void SatelliteApskScalarTransmitter::initialize(int stage)
{
    FlatTransmitterBase::initialize(stage);
}

cEci SatellitePosition;

const ITransmission *SatelliteApskScalarTransmitter::createTransmission(const IRadio *transmitter, const Packet *packet, const simtime_t startTime) const
{
    auto phyHeader = packet->peekAtFront<ApskPhyHeader>();
    ASSERT(phyHeader->getChunkLength() == headerLength);
    auto dataLength = packet->getTotalLength() - phyHeader->getChunkLength();
    W transmissionPower = computeTransmissionPower(packet);
    Hz transmissionCenterFrequency = computeCenterFrequency(packet);
    Hz transmissionBandwidth = computeBandwidth(packet);
    bps transmissionBitrate = computeTransmissionDataBitrate(packet);
    const simtime_t headerDuration = b(headerLength).get() / bps(transmissionBitrate).get();
    const simtime_t dataDuration = b(dataLength).get() / bps(transmissionBitrate).get();
    const simtime_t duration = preambleDuration + headerDuration + dataDuration;
    const simtime_t endTime = startTime + duration;
    const cJulian dateTime = cJulian(2020,
            9 + 1,
            20,
            20,
            5, 0);;


    IMobility *mobility = transmitter->getAntenna()->getMobility();

    const Coord startPosition=Coord(mobility->getCurrentPosition());
    const Coord endPosition=Coord(mobility->getCurrentPosition());

    auto longLatStartPosition = cCoordGeo();
    auto longLatEndPosition = cCoordGeo();

    const Quaternion startOrientation = mobility->getCurrentAngularPosition();
    const Quaternion endOrientation = mobility->getCurrentAngularPosition();

    if (inet::SatelliteMobilityScs *sgp4Mobility = dynamic_cast<inet::SatelliteMobilityScs *>(mobility))
    { //The node is a satellite (550km altitude)

        longLatStartPosition = cCoordGeo(sgp4Mobility->getLatitude(), sgp4Mobility->getLongitude(), SatelliteAltitude);
        longLatEndPosition = cCoordGeo(sgp4Mobility->getLatitude(), sgp4Mobility->getLongitude(), SatelliteAltitude);
        SatellitePosition= sgp4Mobility->getSatellitePosition();
        //return new SatelliteApskScalarTransmission(transmitter, packet, startTime, endTime, preambleDuration, headerDuration, dataDuration, d, endPosition, startOrientation, endOrientation, modulation, headerLength, dataLength, transmissionCenterFrequency, transmissionBandwidth, transmissionBitrate, transmissionPower, longLatStartPosition, longLatEndPosition);

    } else if (GroundStationMobility *lutMobility = dynamic_cast<GroundStationMobility *>(mobility))
    {  //The node transmitter is a ground station
        longLatStartPosition = cCoordGeo(lutMobility->getLUTPositionY(), lutMobility->getLUTPositionX(), 0);
        longLatEndPosition = cCoordGeo(lutMobility->getLUTPositionY(), lutMobility->getLUTPositionX(), 0);
        cEci SP(longLatStartPosition, dateTime);
        SatellitePosition = SP;
        EV << "\nGroundstation LAT: " << lutMobility->getLUTPositionY() << " LON: " << lutMobility->getLUTPositionX() << " altitude  " << SatelliteAltitude ;
    } else
    {  //other
        longLatStartPosition = cCoordGeo(35.45279, 137.74062, 0);
        longLatEndPosition = cCoordGeo(35.45279, 137.74062, 0);
        cEci SP(longLatStartPosition, dateTime);
        SatellitePosition = SP;
        EV << "\nnoone? ";

    }

    const ITransmission* IT = new SatelliteApskScalarTransmission(transmitter, packet, startTime, endTime, preambleDuration, headerDuration, dataDuration,
                    startPosition, endPosition, startOrientation, endOrientation, modulation, headerLength, dataLength, transmissionCenterFrequency, transmissionBandwidth, transmissionBitrate, transmissionPower, longLatStartPosition, longLatEndPosition);
    int teansmitterID = IT->getTransmitterId();

    EV << " ID: " << teansmitterID << "\n";

    return IT;
}

cEci SatelliteApskScalarTransmitter::getSatellitePosition() const {
    return SatellitePosition;
}

} // namespace physicallayer

} // namespace inet

