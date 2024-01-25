//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package SCSV5GFusion;

import scs.base.LaserSatellite;
import scs.base.GroundStation;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarRadioMedium;
import inet_leosatellites.networklayer.configurator.ipv4.SatelliteNetworkConfiguratorScs;
import inet.visualizer.contract.IIntegratedVisualizer;

import inet.node.inet.Router;
import inet.node.ethernet.Eth10G;
import inet.node.inet.StandardHost;
import scs.common.binder.SBinder;

// 5G
import inet.networklayer.ipv4.RoutingTableRecorder;
import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.nodes.PgwStandard;
import simu5g.common.binder.Binder;
import simu5g.nodes.eNodeB;
import simu5g.nodes.Ue;
import simu5g.nodes.Upf;
import simu5g.nodes.NR.gNodeB;
import scs_utils.converter.PositionConverter;

//veins
import scs_optional.veins_inet_scs.VeinsInetManager;
import scs_optional.node.UECar;
import scs_optional.veins_inet_scs.InetCar;
import scs_optional.veins_scs.visualizer.RoadsINETCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
//
network SV5GFusion4
{
    parameters:
        int numOfSats; // Number of satellites
        int numOfMCCs; // Number of Mission Control Centers
        int numOfCars;
        int numOfServiceLinkChannels;
        int numOfUECar = default(1);

        int numUe = default(1);
        int numUeD2DTx = default(0);
        int numUeD2DRx = default(0);
        @display("bgi=veinsAndJapan1080,s;bgb=2160,1080");
   
    submodules:
        channelControl: LteChannelControl {
            @display("p=0,0;i=onedot");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=0,0;i=onedot");
        }
        configurator: SatelliteNetworkConfiguratorScs {
            @display("p=0,0;i=onedot");

        }
        binder: Binder {
            @display("p=0,0;i=onedot");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=0,0;i=onedot");
        }
        
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer {
            @display("p=0,0;i=onedot");
        }
        
        // enable below 3 modules
        manager: VeinsInetManager {
            @display("p=0,0;i=onedot");
        }
        roadsCanvasVisualizer: RoadsINETCanvasVisualizer {
                        @display("p=0,0;i=onedot");
        }
        node[0]: UECar;

        sbinder: SBinder {
            @display("p=0,0;i=onedot");
            
        }
           
        satellite[numOfSats]: LaserSatellite {   //LaserSatellite for using NoradA, Satellite for Ground-Relays using TLE
            parameters:
                @display("p=797.72003,93.24;i=onedot");
        }
        MCC[numOfMCCs]: GroundStation {
            parameters:
                @display("p=1284.64,88.06;r=10;i=onedot");
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

        // 5G
        // Feeder link side network.
        routerFL: Router {
            @display("p=1100,1100;i=onedot");
        }

        upf: Upf {
            @display("p=800,1100");
        }
  
        router2: Router {
            @display("p=400,1100;i=device/smallrouter");
        }    
        server: StandardHost {
            @display("p=200,1100;is=n;i=device/server");
        }     
        
        // Service link side network
        router: Router {
            @display("p=1600,1100;i=device/smallrouter");
        }
        pgw: PgwStandard {
            @display("p=1800,1100;is=s");
        }
        eNB: eNodeB {
            @display("p=2000,1100;is=s");
        }
        Pos: PositionConverter {
              parameters:
                //numChannels = 2;
                @display("p=40,0;i=onedot");
        }
    connections allowunconnected:
    //connections :
       // Feeder link network
        MCC[0].pppg++  <--> Eth10G <--> routerFL.pppg++;
        routerFL.pppg++ <--> Eth10G <--> upf.pppg++;
        upf.pppg++ <--> Eth10G <--> router2.pppg++; 
        router2.pppg++ <--> Eth10G <--> server.pppg++;   
        
       // service link network
        GS[0].pppg++  <--> Eth10G <--> router.pppg++;
        router.pppg++ <--> Eth10G <--> pgw.filterGate;
        pgw.pppg++ <--> Eth10G <--> eNB.ppp;


}
