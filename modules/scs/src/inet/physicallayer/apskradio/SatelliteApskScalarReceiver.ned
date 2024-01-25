//
// Copyright (C) 2013 OpenSim Ltd
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
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarReceiver.ned`. 

package inet_scs.physicallayer.apskradio;

import inet.physicallayer.wireless.common.base.packetlevel.NarrowbandReceiverBase;


//
// This receiver model receives a transmission succesfully if the minimum of the
// signal to noise and interference ratio over the duration of the reception is
// sufficiently high. It uses the error model to compute the error rate based on
// this value and the used modulation.
//
// @see ~ApskScalarTransmitter, ~ApskScalarRadio, ~ApskScalarRadioMedium,
// ~ScalarAnalogModel.
//
module SatelliteApskScalarReceiver extends NarrowbandReceiverBase
{
    parameters:
        modulation = default("BPSK");
        errorModel.typename = default("SatelliteBERModel");
        @class(inet::physicallayer::SatelliteApskScalarReceiver);
}

