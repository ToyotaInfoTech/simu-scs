// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package os3_leosatellites.mobility;

import leosatellites.mobility.NoradA;


simple NoradScs extends NoradA
{
parameters:

    double meanMotion = default(15.15306312100295);
	int gapOffset = default(0);
	string TLEfile = default("");          // filename of TLE data file
	int simcycle = default(120); // sec
    @class(NoradScs);
}