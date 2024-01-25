//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/physicallayer/wireless/common/propagation/ConstantSpeedPropagation.h` of INET-4.4.1. 

#include "SatellitePropagationScs.h"
#include "inet/physicallayer/apskradio/SatelliteApskScalarTransmission.h"
#include "os3/mobility/SatSGP4Mobility.h"
#include "os3/mobility/LUTMotionMobility.h"
#include "leosatellites/mobility/GroundStationMobility.h"
#include "scs/mobility/SatelliteMobilityScs.h"
#include "leosatellites/mobility/NoradA.h"
#include "os3/libnorad/ccoord.h"
#include "os3/libnorad/cEci.h"
#include "os3/libnorad/cSite.h"
#include "leosatellites/libnorad/cEcef.h"
#include "inet/physicallayer/wireless/common/signal/Arrival.h"
#include <math.h>

// using namespace Satellite;

#ifdef USEVEINSINET
namespace veins {
}
using namespace veins;
#endif

namespace inet {

namespace physicallayer {

Define_Module(SatellitePropagationScs);

SatellitePropagationScs::SatellitePropagationScs() : SatellitePropagation()
{
}

const IArrival *SatellitePropagationScs::computeArrival(const ITransmission *transmission, IMobility *mobility) const
{
    arrivalComputationCount++;
    const simtime_t startTime = transmission->getStartTime();
    const simtime_t endTime = transmission->getEndTime();

    const Coord startPosition(transmission->getStartPosition());   //antenna position when the transmitter has started the transmission
    const Coord endPosition (transmission->getEndPosition());

    cEcef transmissionEcef = cEcef();
    cEcef receiverEcef = cEcef();

    int   TransmitterID = transmission->getTransmitterId();

    double distance = 0; //m
        if (const SatelliteApskScalarTransmission *satApskTransmission = dynamic_cast<const SatelliteApskScalarTransmission*>(transmission)) {

            const auto GParent = (satApskTransmission->getName());

            if (const inet::SatelliteMobilityScs *receiverSatMobility = dynamic_cast<const inet::SatelliteMobilityScs*>(mobility)) {

                std::string satelliteName = receiverSatMobility->getParentModule()->par("satelliteName").stringValue();

                const auto Parent = (receiverSatMobility->getParentModule());

                if (Parent) {
                    const int satNum2 = Parent->getIndex();
                    distance = receiverSatMobility->getDistance(satApskTransmission->getStartLongLatPosition().m_Lat, satApskTransmission->getStartLongLatPosition().m_Lon, satApskTransmission->getStartLongLatPosition().m_Alt);

                    if(distance<=2000)
                    {
                        EV << "\nDISTANCE: " << distance << "km" << "(satellite Propagation) " << satelliteName << "(" << satNum2 << ")" << "ground" << GParent << "Transmitter id " << TransmitterID << "..\n";                    //EV << "\nDISTANCE: lat" << satApskTransmission->getStartLongLatPosition().m_Lat << " do " << satApskTransmission->getStartLongLatPosition().m_Lon << "do" <<  receiverSatMobility->getLatitude() << " do " <<  receiverSatMobility->getLongitude() << " do" << distance/1000 << "Ground Station \n";
                    }
                    distance *=1000;
                }

            } else if (const GroundStationMobility *receiverLutMobility = dynamic_cast<const GroundStationMobility*>(mobility))
            {
                // satelliteposition

                const SatelliteApskScalarTransmission* SatTransmission = dynamic_cast<const SatelliteApskScalarTransmission*>(transmission);

                if (SatTransmission) {

                    cSite siteEquator(receiverLutMobility->getLUTPositionY(),receiverLutMobility->getLUTPositionX(),receiverLutMobility->getLUTAltitude());
                    cCoordTopo topoLook = siteEquator.getLookAngle(SatTransmission->getSatellitePosition());
                    distance = topoLook.m_Range;
                    EV << "\nDISTANCE: " << distance << "km" << "(ground station propagation)" << "to satellite name " << GParent << "Transmitter id " << TransmitterID << "\n";
                    distance *= 1000;

                }
                else {
                    EV << "\n================cast transmission failed ====================================";
                }


            }
                else {
                  distance = 700000;
                  EV << "\nOTHER receiver DETECTED";
              }

        }
        else {
            EV << "\nOTHER TRANSMITTER DETECTED";
        }

    const Coord startArrivalPosition = ignoreMovementDuringPropagation ? mobility->getCurrentPosition() : computeArrivalPosition(startTime, startPosition, mobility);

    const simtime_t startPropagationTime =  distance / propagationSpeed.get();
    const simtime_t startArrivalTime = startTime + startPropagationTime;
    const Quaternion startArrivalOrientation = mobility->getCurrentAngularPosition();

    if (ignoreMovementDuringReception) {
        const Coord endArrivalPosition = startArrivalPosition;
        const simtime_t endPropagationTime = startPropagationTime;
        const simtime_t endArrivalTime = endTime + startPropagationTime;
        const simtime_t preambleDuration = transmission->getPreambleDuration();
        const simtime_t headerDuration = transmission->getHeaderDuration();
        const simtime_t dataDuration = transmission->getDataDuration();
        const Quaternion endArrivalOrientation = mobility->getCurrentAngularPosition();
        return new Arrival(startPropagationTime, endPropagationTime, startArrivalTime, endArrivalTime, preambleDuration, headerDuration, dataDuration, startArrivalPosition, endArrivalPosition, startArrivalOrientation, endArrivalOrientation);
    }
    else {
        const Coord endArrivalPosition = computeArrivalPosition(endTime, endPosition, mobility);
        const simtime_t endPropagationTime = endPosition.distance(endArrivalPosition) / propagationSpeed.get();
        const simtime_t endArrivalTime = endTime + endPropagationTime;
        const simtime_t preambleDuration = transmission->getPreambleDuration();
        const simtime_t headerDuration = transmission->getHeaderDuration();
        const simtime_t dataDuration = transmission->getDataDuration();
        const Quaternion endArrivalOrientation = mobility->getCurrentAngularPosition();
        return new Arrival(startPropagationTime, endPropagationTime, startArrivalTime, endArrivalTime, preambleDuration, headerDuration, dataDuration, startArrivalPosition, endArrivalPosition, startArrivalOrientation, endArrivalOrientation);
    }
}

} // namespace physicallayer

} // namespace inet

