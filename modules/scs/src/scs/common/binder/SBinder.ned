// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scs.common.binder;

simple SBinder
{
        parameters:

        @display("i=block/cogwheel");
        @class(Satellite::SBinder);
        
        int numOfSats; // Number of satellites
        int numOfMCCs; // Number of Mission Control Centers
        int numOfCars; // Number of UE Cars
        int numOfServiceLinkChannels; // Number of Channels
        int numBeamInterfaces;
        int numSubChannels;
}
