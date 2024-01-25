// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scs.base;

import inet.mobility.contract.IMobility;
import os3_leosatellites.mobility.NoradScs;
import leosatellites.mobility.INorad;

// added red dropper
import inet.queueing.filter.RedDropper;
import inet.queueing.queue.PacketQueue;
import inet.node.inet.Router;
import inet.node.inet.MulticastRouter;

// Laser Satellite model that uses the NoradA implementation, which therefore allows the use of inter-satellite links.
//
//
module LaserSatellite extends SatelliteHostBase
{
    parameters:
        @node; //because of MobilityBase initialization
        @networkNode;
        string satelliteName = default(""); // Parameter for satellite name

        // Transmit Power of satellite (7dBW as example for CospasSarsat system)
        double transmitPower @unit(dBW) @display("i=device/satellite;bgb=324,226") = default(7dBW); // Symbol
        @display("t=$satelliteName"); 
        		   
    gates:
        input in[];
        output out[];

    submodules:
        router1: MulticastRouter {
            parameters:
            gates:
                pppg[];

        }
        NoradModule:<default("NoradScs")> like INorad if typename != "" { // Module for transformation between omnet and libNorad
            parameters:
                @display("p=708.75,34.649998");         
                satIndex = parentIndex();
				satName = "sat";
				planes = 1;
				satPerPlane = 66;
        }


    connections allowunconnected:
        
                
}
