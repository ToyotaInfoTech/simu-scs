// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scs.base;

import inet_scs.node.base.SatApplicationLayerNodeBase;
import inet.node.base.ApplicationLayerNodeBase;
import scs.common.beamInfo.BeamInfo;
import inet_scs.mobility.BeamVisualizer;

// 
// User Equipment Module
//
module SatelliteHostBase extends SatApplicationLayerNodeBase
{
    parameters:
        @display("i=device/pc2");
        @figure[submodules];
        forwarding = default(true);  // disable routing by default
        ipv4.arp.proxyArpInterfaces = default(""); // proxy arp is disabled on hosts by default
        //*.routingTableModule = default(".ipv4.routingTable");
        multicastForwarding = true;
        bool initFromDisplayString=default(false);

        cnl[*].typename = default("AckingWirelessInterface");
        cnl[*].radio.transmitter.typename = default("SatelliteApskScalarTransmitter");
        cnl[*].radio.receiver.typename = default("SatelliteApskScalarReceiver");
		cnl[*].radio.typename = default("ApskScalarRadio");
        cnl[*].mgmt.typename = default("Ieee80211MgmtStaSimplified");
        cnl[*].radio.receiver.errorModel.typename = default("SatelliteErrorModel");   
        cnl[*].radio.displayCommunicationRange = false;
  		cnl[*].radio.antenna.mobilityModule = default("^.^.^.mobility");
        
        string errorModelType = default("SatelliteErrorModel");
		*.radio.receiver.errorModel.typename = errorModelType;
		*.routingTableModule = default("^.ipv4.routingTable");
		numWlanInterfaces = default(1);
		
	    submodules:	
        bm: BeamInfo {
            parameters:
            @display("p=100, 700");
        }    
        bv: BeamVisualizer {
             parameters:
            @display("p=100, 700");
        }
         
}