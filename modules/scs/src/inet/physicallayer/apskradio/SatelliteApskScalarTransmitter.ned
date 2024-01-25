//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/pyisicallayer/wireless/apsk/packetlevel/ApskScalarTransmitter.ned`. 

package inet_scs.physicallayer.apskradio;

import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarTransmitter;

//-----------------------------------------------------
// This model creates a SatelliteScalarTransmission which stores the longitude, latitude and altitude of a given transmitter.
// These values are used within the path loss and propagation calculations so that the visual x, y and z values can be
// decoupled from their actual positions.
// Written by Aiden Valentine
//-----------------------------------------------------

module SatelliteApskScalarTransmitter extends ApskScalarTransmitter
{
    parameters:
        double SatelliteAltitude = default(1684);
        //double SatelliteAltitude = default();
        @class(inet::physicallayer::SatelliteApskScalarTransmitter);
        @display("i=block/wtx");
        headerLength = default(23B);

}