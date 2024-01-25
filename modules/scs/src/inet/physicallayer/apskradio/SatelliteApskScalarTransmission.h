//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarTransmission.h`. 

#ifndef OS3_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMISSION_H_
#define OS3_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMISSION_H_

#include "os3/libnorad/ccoord.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskScalarTransmission.h"
#include "os3/libnorad/cEci.h"

namespace inet {

namespace physicallayer {

//-----------------------------------------------------
// Class: SatelliteApskScalarTransmission
//
// To make sure that the propagation and path loss classes get the correct distance between two nodes (Satellite/Ground Station)
// this class was created. In contrast to the generic unit disk transmission class, the longitude, latitude and altitude of a
// specific transmitter is passed, allowing them to be mapped to a coordinate system, calculating the real distance between two nodes
// rather than the visual representation. This model uses the APSK scalar model and is not used by the simulation model.
// It was implemented to provide the flexibility of using a more detailed model if required.
// Written by Aiden Valentine
//-----------------------------------------------------
class SatelliteApskScalarTransmission : public ApskScalarTransmission
{
    protected:
        cCoordGeo longLatStartPosition;
        cCoordGeo longLatEndPosition;
        Hz        centerFrequency;
        W         power;
        Hz        bandwidth;
        Coord     startPosition;

    public:

        SatelliteApskScalarTransmission(const IRadio *transmitter, const Packet *packet, const simtime_t startTime, const simtime_t endTime, const simtime_t preambleDuration, const simtime_t headerDuration, const simtime_t dataDuration, const Coord startPosition, const Coord endPosition, const Quaternion startOrientation, const Quaternion endOrientation, const IModulation *modulation, b headerLength, b payloadLength, Hz centerFrequency, Hz bandwidth, bps bitrate, W power, cCoordGeo longLatStartPosition, cCoordGeo longLatEndPosition);
        virtual cCoordGeo getStartLongLatPosition() const { return longLatStartPosition; }
        virtual cCoordGeo getEndLongLatPosition() const { return longLatEndPosition; }
        virtual Hz        getCenterFrequency() const { return centerFrequency; }
        virtual Hz        getBandWidth() const { return bandwidth; }
        virtual W         getPower() const { return power; }
        virtual cEci      getSatellitePosition() const;

        const double      getDistance(const double& refLatitude, const double& refLongitude, const double& refAltitude);

};

} // namespace physicallayer

} // namespace inet

#endif /* OS3_PHYSICALLAYER_APSKRADIO_SATELLITEAPSKSCALARTRANSMISSION_H_ */
