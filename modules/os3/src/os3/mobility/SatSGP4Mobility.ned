//
// Copyright (c) Michael F. Henry
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on `src/os3/mobility/SatSGP4Mobility.ned`
// of os3 (https://github.com/inet-framework/os3). 

package os3.mobility;


import inet.mobility.base.MobilityBase;

//
// Manages the SatSGP4 Mobility
//
simple SatSGP4Mobility extends MobilityBase
{
    parameters:
        bool faceForward=true;
        bool updateFromDisplayString=default(false);
        @class(SatSGP4Mobility);
        @display("i=block/cogwheel_s");
        double updateInterval @unit(s); // Time interval to update the hosts position
        
        //int offsetX=default(1920);
        int offsetX=default(0);
}
