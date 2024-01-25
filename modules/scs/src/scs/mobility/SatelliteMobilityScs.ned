//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package scs.mobility;

import leosatellites.mobility.SatelliteMobility;

simple SatelliteMobilityScs extends SatelliteMobility
{
    parameters:
        @display("i=block/cogwheel_s");
        @class(inet::SatelliteMobilityScs);
        int targetyear=default(123);
        int targetmonth = default(2);
        int targetday = default(2);
        int targethour = default(12);
        int targetmin  = default(9);
        int targetsec  = default(10);
        int targetwday = default(4);
        int targetyday = default(60);
        int cycleTime = default(1200);
        int enableRepeatCycle = default(1);
}