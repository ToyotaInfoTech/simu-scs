//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/physicallayer/wireless/apsk/packetlevel/ScalarRadioMedium.ned`. 

package inet_scs.physicallayer.apskradio;

//
// This radio medium model uses scalar transmission power in the analog
// representation. It must be used in conjunction with the
// ~Ieee80211ScalarRadio model.
//
// @see ~Ieee80211ScalarRadio, ~Ieee80211ScalarTransmitter,
// ~Ieee80211ScalarReceiver, ~ScalarAnalogModel.
//
module SatelliteScalarRadioMedium extends SatelliteRadioMedium
{
    parameters:
        analogModel.typename = default("ScalarAnalogModel");
        backgroundNoise.typename = default("IsotropicScalarBackgroundNoise");
       
}

