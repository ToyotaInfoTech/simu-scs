//
// Copyright (C) 2013 OpenSim Ltd
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskRadio.ned`. 

package inet_scs.physicallayer.apskradio;


import inet.physicallayer.wireless.common.base.packetlevel.FlatRadioBase;


//
// This radio model is part of the IEEE 802.11 physical layer model. It supports
// multiple channels, different operation modes, and preamble modes. It must be
// used in conjunction with the ~SatelliteApskRadioMedium model or other derived
// models.
//
// This model provides sensible default values for the radio parameters to be
// used in IEEE 802.11 simulations. It also supports switching channels via
// ~ConfigureRadioCommand, or with direct C++ function calls.
//
// @see ~SatelliteApskScalarRadio, ~SatelliteApskDimensionalRadio.
//
//# TODO check this Table 18-14—Receiver performance requirements


module SatelliteRadio extends FlatRadioBase
{
       parameters:
        string signalAnalogRepresentation @enum("scalar", "dimensional") = default("scalar");
        string bandName @enum("28.5 GHz", "13.5 GHz", "11.7GHz") = default("13.5 GHz"); // band name
        int channelNumber = default(2);   
        string crcMode @enum("declared","computed") = default("declared");         
        transmitter.typename = default(signalAnalogRepresentation == "scalar" ? "SatelliteApskScalarTransmitter" : signalAnalogRepresentation == "dimensional" ? "SatelliteApskDimensionalTransmitter" : "");
        receiver.typename = default(signalAnalogRepresentation == "scalar" ? "SatelliteApskScalarReceiver" : signalAnalogRepresentation == "dimensional" ? "SatelliteApskDimensionalReceiver" : "");
        centerFrequency @unit(Hz) = default(21GHz);                 // the center frequency of the band is automatically set by the radio
        bandwidth @unit(Hz) = default(nan MHz);

   		
        @class(inet::physicallayer::SatelliteRadio);
        @signal[radioChannelChanged](type=long);
        @statistic[radioChannel](title="Radio channel"; source=radioChannelChanged; record=histogram,vector; interpolationmode=sample-hold);
    
}

