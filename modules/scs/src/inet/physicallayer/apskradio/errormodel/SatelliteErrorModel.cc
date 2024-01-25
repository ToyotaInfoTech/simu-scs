//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/errormodel/ApskErrorModel.cc`. 

#include "inet/physicallayer/apskradio/errormodel/SatelliteErrorModel.h"

#include "inet/physicallayer/wireless/common/base/packetlevel/ApskModulationBase.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/FlatTransmissionBase.h"

namespace inet{

namespace physicallayer{

Define_Module(inet::physicallayer::SatelliteErrorModel);

void SatelliteErrorModel::initialize()
{
    // TODO - Generated method body
}

//void SatelliteErrorModel::handleMessage(cMessage *msg)
//{
    // TODO - Generated method body
//}

std::ostream& SatelliteErrorModel::printToStream(std::ostream& stream, int level, int evFlags) const
{
    return stream << "ApskErrorModel";
}

double SatelliteErrorModel::computePacketErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method("computePacketErrorRate");
    double bitErrorRate = computeBitErrorRate(snir, part);
    if (bitErrorRate == 0.0)
        return 0.0;
    else if (bitErrorRate == 1.0)
        return 1.0;
    else {
        const FlatTransmissionBase *flatTransmission = check_and_cast<const FlatTransmissionBase *>(snir->getReception()->getTransmission());
        double headerSuccessRate = pow(1.0 - bitErrorRate, b(flatTransmission->getHeaderLength()).get());
        double dataSuccessRate = pow(1.0 - bitErrorRate, b(flatTransmission->getDataLength()).get());
        //recordScalar("Header success rate ", headerSuccessRate);
        //recordScalar("Data success rate ", dataSuccessRate);
        switch (part) {
            case IRadioSignal::SIGNAL_PART_WHOLE:
                return 1.0 - headerSuccessRate * dataSuccessRate;
            case IRadioSignal::SIGNAL_PART_PREAMBLE:
                return 0;
            case IRadioSignal::SIGNAL_PART_HEADER:
                return 1.0 - headerSuccessRate;
            case IRadioSignal::SIGNAL_PART_DATA:
                return 1.0 - dataSuccessRate;
            default:
                throw cRuntimeError("Unknown signal part: '%s'", IRadioSignal::getSignalPartName(part));
        }
    }
}

double SatelliteErrorModel::computeBitErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method("computeBitErrorRate");
    const FlatTransmissionBase *flatTransmission = check_and_cast<const FlatTransmissionBase *>(snir->getReception()->getTransmission());
    const ApskModulationBase *modulation = check_and_cast<const ApskModulationBase *>(flatTransmission->getModulation());
    double sinr = getScalarSnir(snir);
    //sinr = 13;
    Hz bandwidth = flatTransmission->getBandwidth();
    bps bitrate = flatTransmission->getBitrate();
    double EbN0 = sinr * bandwidth.get() / bitrate.get();

    unsigned int codeWordSize = modulation->getCodeWordSize();
    unsigned int constellationSize = modulation->getConstellationSize();

    double ber = 4.0 / codeWordSize * (1 - 1 / sqrt(constellationSize)) * 0.5 * erfc(1 / sqrt(2) * sqrt(3.0 * codeWordSize / (constellationSize - 1) * EbN0));
    //recordScalar("BER ", ber);

    ASSERT(0.0 <= ber && ber <= 1.0);

    return ber;
}

double SatelliteErrorModel::computeSymbolErrorRate(const ISnir *snir, IRadioSignal::SignalPart part) const
{
    Enter_Method("computeSymbolErrorRate");
    const FlatTransmissionBase *flatTransmission = check_and_cast<const FlatTransmissionBase *>(snir->getReception()->getTransmission());
    const ApskModulationBase *modulation = check_and_cast<const ApskModulationBase *>(flatTransmission->getModulation());

    return modulation->calculateSER(getScalarSnir(snir), flatTransmission->getBandwidth(), flatTransmission->getBitrate());
}

}
}

