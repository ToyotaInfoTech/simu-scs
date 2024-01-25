//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/physicallayer/wireless/common/medium/RadioMedium.ned`. 


package inet_scs.physicallayer.apskradio;

//import leosatellites.physicallayer.apskradio.SpaceRadioMedium;
//import inet.physicallayer.wireless.common.medium.SpaceRadioMedium;
import inet.physicallayer.wireless.common.medium.RadioMedium;
//
// This radio medium model is part of thee IEEE 802.11 physical layer model. It
// must be used in conjunction with the ~Ieee80211Radio model or other derived
// models.
//
// This model provides sensible default values for the radio medium parameters
// to be used in IEEE 802.11 simulations.
//
// @see ~Ieee80211ScalarRadioMedium, ~Ieee80211DimensionalRadioMedium.
//
module SatelliteRadioMedium extends RadioMedium
{
    parameters:
        mediumLimitCache.centerFrequency = default(28.5GHz);
        mediumLimitCache.minReceptionPower = default(-85dBm);
        mediumLimitCache.minInterferencePower = default(-110dBm);
        analogModel.typename = default("ScalarAnalogModel");
        backgroundNoise.typename = default("IsotropicScalarBackgroundNoise");  
		//backgroundNoise.power = -110dBm;      
        propagation.typename = "SatellitePropagationScs";
		listeningFilter = false;
		propagation.propagationSpeed = 299792458mps ;
		analogModel.typename = "ScalarAnalogModel";
		pathLoss.typename = "SatellitePathloss";

}

