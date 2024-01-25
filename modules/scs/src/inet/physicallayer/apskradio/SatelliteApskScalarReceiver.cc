//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarReceiver.cc`. 

#include "inet/physicallayer/apskradio/SatelliteApskScalarReceiver.h"

#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarNoise.h"
#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarReception.h"
#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarSnir.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskScalarReceiver.h"
#include "inet/physicallayer/wireless/apsk/packetlevel/ApskScalarTransmission.h"
#include "inet/physicallayer/wireless/common/radio/packetlevel/BandListening.h"

namespace inet {

namespace physicallayer {

Define_Module(SatelliteApskScalarReceiver);

SatelliteApskScalarReceiver::SatelliteApskScalarReceiver() :
    FlatReceiverBase()
{
}

std::ostream& SatelliteApskScalarReceiver::printToStream(std::ostream& stream, int level) const
{
    stream << "ApskScalarReceiver";
    return FlatReceiverBase::printToStream(stream, level);
}

bool SatelliteApskScalarReceiver::computeIsReceptionPossible(const IListening *listening, const ITransmission *transmission) const
{
    auto apskTransmission = dynamic_cast<const ApskScalarTransmission *>(transmission);
    return apskTransmission && NarrowbandReceiverBase::computeIsReceptionPossible(listening, transmission);
}

bool SatelliteApskScalarReceiver::computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const
{
    auto apksTransmission = dynamic_cast<const ApskScalarTransmission *>(reception->getTransmission());
    return apksTransmission && FlatReceiverBase::computeIsReceptionPossible(listening, reception, part);
}

} // namespace physicallayer

} // namespace inet


