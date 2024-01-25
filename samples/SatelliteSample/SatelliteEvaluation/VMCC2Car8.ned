// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package SatelliteEvaluation;

import scs.base.LaserSatellite;
import scs.base.GroundStation;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarRadioMedium;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.common.geometry.common.SimpleGeographicCoordinateSystem;
import inet.common.geometry.common.OsgGeographicCoordinateSystem;
import inet.environment.objectcache.GridObjectCache;
import inet_scs.physicallayer.apskradio.SatelliteScalarRadioMedium;
import inet.physicallayer*.wireless.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.node.wireless.AccessPoint;
import inet.node.ethernet.Eth10G;
import scs.common.binder.SBinder;
import scs_utils.converter.PositionConverter;

//
network VMCC2Car8
{
    parameters:
        int numOfSats; // Number of satellites
        int numOfMCCs; // Number of Mission Control Centers
        int numOfCars;
        int numOfServiceLinkChannels;

        //@display("bgi=os3/background_earthX2X2,s;bgb=4140,1080");   
        @display("bgi=veinsAndJapan1080,s;bgb=2160,1080");
        
    submodules:
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer {
            @display("p=1041.18,93.24");
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
                @display("p=611.24,88.06;i=misc/sun");
        }
        radioMediumSV[numOfServiceLinkChannels]: <default("SatelliteScalarRadioMedium")> like IRadioMedium {
            parameters:
                //numChannels = 2;
                @display("p=1559.18,88.06;i=misc/sun");
        }
        GS[numOfCars]: GroundStation {
                        @display("p=1807.8201,93.24;i=car_vs");

        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=367.78,93.24");
        }


        sbinder: SBinder {
            @display("p=88.06,93.24;is=s");
            
        }
        Pos: PositionConverter {
              parameters:
                //numChannels = 2;
                @display("p=40,0;i=onedot");
        }
    connections allowunconnected:


}
