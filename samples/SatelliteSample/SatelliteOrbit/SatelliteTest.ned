// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
package SatelliteOrbit;

import scs.base.LaserSatellite;
import scs.base.GroundStation;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarRadioMedium;
import inet_leosatellites.networklayer.configurator.ipv4.SatelliteNetworkConfiguratorScs;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.visualizer.contract.IIntegratedVisualizer;
import scs.common.binder.SBinder;
import scs_utils.converter.PositionConverter;
//
network SatelliteTest
{
    parameters:
        int numOfSats; // Number of satellites
        int numOfMCCs; // Number of Mission Control Centers
        int numOfCars;
        int numOfServiceLinkChannels;
        int numServer = default(0);

        int numUe = default(0);
        //@display("bgi=os3/japan1080x1080,s;bgb=1080,1080");
        @display("bgi=os3/background_earth,s;bgb=2160,1080");
        
    submodules:

        configurator: SatelliteNetworkConfiguratorScs {
            @display("p=0,0;i=onedot");
        }
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer {
            @display("p=0,0;i=onedot");
        }

        sbinder: SBinder {
            @display("p=0,0;i=onedot");
            
        }
           
        satellite[numOfSats]: LaserSatellite {   //LaserSatellite for using NoradA, Satellite for Ground-Relays using TLE
            parameters:
                @display("p=797.72003,93.24;i=os3/satellit_blue");
        }
        MCC[numOfMCCs]: GroundStation {
            parameters:
                @display("p=1284.64,88.06;r=10;i=device/receiverdish");
        }
        radioMediumFL: <default("SatelliteScalarRadioMedium")> like IRadioMedium {
            parameters:
                //numChannels = 2;
            @display("p=0,0;i=onedot");
        }
        radioMediumSV[numOfServiceLinkChannels]: <default("SatelliteScalarRadioMedium")> like IRadioMedium {
            parameters:
                //numChannels = 2;
            @display("p=0,0;i=onedot");
        }
        
        GS[numOfCars]: GroundStation {
            @display("p=1807.8201,1100;i=onedot");

        }

        Pos: PositionConverter {
              parameters:
                //numChannels = 2;
                @display("p=40,0;i=onedot");
        }
    connections allowunconnected:

}
