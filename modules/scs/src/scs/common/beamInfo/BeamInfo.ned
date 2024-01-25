// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scs.common.beamInfo;

simple BeamInfo
{
        parameters:
        @display("i=block/control");
        @class(Satellite::BeamInfo);  
         
        double latitude = default(9999);
        
        double longitude = default(9999);
        
        double beamCenterLatitude = default(9999);
        
        double beamCenterLongitude = default(9999);
        
        int  satelliteID = default (9999);
        
        int  numBeamInterfaces = default(1);
        
        int   numSubChannels= default(1);
        
}
