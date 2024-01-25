// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package scs.physicallayer.pathloss;

//
// This pathloss model computes the pathloss based on 3gpp TR38.811 v1.0.0
// the traveled distance is being calculated by Satellite NoradA model.
// arrival time was calculated by the distance divide by light speed.
// FSPL + LBEL(=0) + PL+SChitilation
//

import inet.physicallayer.wireless.common.contract.packetlevel.IPathLoss;

module SatellitePathloss like  IPathLoss
{
    parameters:
        double alpha = default(2);
        double systemLoss @unit(dB) = default(0dB);
        xml    plConfig;
        double sigmaSf = default(2.7);
        double CL = default(26.2);
        double scintillation = default(0.6);
        double atmospheric = default(0.6);
        double cluster = default(0.0);
        double shadow = default(0.0);
        double building = default(0.0);
        double fading = default(0.0);
        
        @class(inet::physicallayer::SatellitePathloss);
        @display("i=block/control");  
   
}


