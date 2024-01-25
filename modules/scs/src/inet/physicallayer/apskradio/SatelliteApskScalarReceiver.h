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
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarReceiver.h`. 

#ifndef __INET_APSKSCALARRECEIVER_H
#define __INET_APSKSCALARRECEIVER_H

#include "inet/physicallayer/wireless/common/base/packetlevel/FlatReceiverBase.h"
#include "inet/physicallayer/wireless/common/contract/packetlevel/IModulation.h"
#include "os3/libnorad/ccoord.h"

namespace inet {

namespace physicallayer {

class INET_API SatelliteApskScalarReceiver : public FlatReceiverBase
{
  protected:
    virtual bool computeIsReceptionPossible(const IListening *listening, const ITransmission *transmission) const override;
    virtual bool computeIsReceptionPossible(const IListening *listening, const IReception *reception, IRadioSignal::SignalPart part) const override;
    cCoordGeo longLatEndPosition;

  public:
    SatelliteApskScalarReceiver();

    //virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual std::ostream& printToStream(std::ostream& stream, int level) const;
    virtual cCoordGeo getEndLongLatPosition() const { return longLatEndPosition; }

};

} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_APSKSCALARRECEIVER_H

