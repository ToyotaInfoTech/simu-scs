//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package scs.base;

import inet.node.inet.StandardHost;
import scs.common.beamInfo.BeamInfo;
import inet_scs.mobility.BeamVisualizer;
//
// Models a host with (default) one wireless (802.11) card in infrastructure mode.
// This module is basically a ~StandardHost with an ~Ieee80211Interface with
// mgmt.typename = ~Ieee80211MgmtSta added.
// It should be used in conjunction with ~AccessPoint, or any other AP model
// which contains ~Ieee80211Interface with mgmt.typename = ~Ieee80211MgmtAp.
//
module SatelliteHost extends StandardHost
{
    parameters:
        @class(SatelliteHost);
        @display("i=device/pc2");
        @figure[submodules];
        forwarding = default(true);  
        ipv4.arp.proxyArpInterfaces = default(""); // proxy arp is disabled on hosts by default 

        multicastForwarding = true;
        bool initFromDisplayString=default(false);

        wlan[*].typename = default("AckingWirelessInterface");
        //wlan[*].typename = default("Ieee80211Interface");
        wlan[*].radio.transmitter.typename = default("SatelliteApskScalarTransmitter");
        wlan[*].radio.receiver.typename = default("SatelliteApskScalarReceiver");
		//wlan[*].radio.typename = default("ApskScalarRadio");
		wlan[*].radio.typename = default("Ieee80211Radio");
        wlan[*].mgmt.typename = default("Ieee80211MgmtAdhoc");
        wlan[*].radio.receiver.errorModel.typename = default("SatelliteErrorModel");   
        wlan[*].radio.displayCommunicationRange = false;
  		wlan[*].radio.antenna.mobilityModule = default("^.^.^.mobility");
  		
  		wlan[*].radio.bandwidth = default(2MHz);
        
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

