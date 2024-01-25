//
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

package scs.base;

import inet.node.inet.StandardHost;
import leosatellites.mobility.GroundStationMobility;


module GroundStation extends StandardHost
{
    parameters:
        string cityName = default("");
        string mobilityType = default("GroundStationMobility"); // Define mobility module
        @display("t=$cityName");
       // @class("GroundStation");
        @node;
        @networkNode;     
        numWlanInterfaces = default(1);
        wlan[*].typename = default("AckingWirelessInterface");
        wlan[*].radio.transmitter.typename = default("SatelliteApskScalarTransmitter");
        wlan[*].radio.receiver.typename = default("SatelliteApskScalarReceiver");
		wlan[*].radio.typename = default("ApskScalarRadio");
		//wlan[*].radio.typename = default("Ieee80211Radio");
		wlan[*].mobility.typename = mobilityType;
		wlan[*].radio.bandwidth = default(2MHz);
		wlan[*].radio.transmitter.preambleduration = default(1us);
		wlan[*].radio.channelNumber = default(0);
		wlan[*].radio.centerFrequency = default(28.5GHz);
        wlan[*].radio.bandwidth = default(500MHz);
        wlan[*].agent.defaultSsid = default("uplink");
        wlan[*].mgmt.typename = default("Ieee80211MgmtStaSimplified");
        wlan[*].radio.receiver.errorModel.typename = default("SatelliteErrorModel");
        wlan[*].radio.displayCommunicationRange = default(false);
 		wlan[*].radio.antenna.mobilityModule = default("^.^.^.mobility");
        forwarding = default(true);
   
        @signal[packetSent](type=inet::Packet);
        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[throughput](title="throughput"; unit=bps; source="throughput(packetReceived)"; record=vector);
        @statistic[packetSent](title="packets sent"; source=packetSent; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[rcvdPkLifetime](title="received packet lifetime"; source="dataAge(packetReceived)"; unit=s; record=stats,vector; interpolationmode=none);
 
    gates:

    submodules:
        

    connections allowunconnected: // Connections between compound gates and submodules

}