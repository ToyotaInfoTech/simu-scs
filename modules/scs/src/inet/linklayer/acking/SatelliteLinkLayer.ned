//
// Copyright (C) 2004 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/linklayer/acking/LinkLayer.ned` of INET-4.4.1.

package inet_scs.linklayer.acking;

import inet.queueing.contract.IPacketQueue;
import inet.linklayer.contract.IWirelessInterface;
import inet.networklayer.common.NetworkInterface;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadio;
import inet.common.MessageDispatcher;
import inet.linklayer.acking.AckingWirelessInterface;
import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarRadio;
import inet.common.MessageDispatcher;
import inet.linklayer.ieee80211.mgmt.IIeee80211Agent;
import inet.linklayer.ieee80211.mgmt.IIeee80211Mgmt;
import inet.linklayer.ieee80211.mib.Ieee80211Mib;
import inet_scs.linklayer.ieee80211.SatelliteMac;
import inet.linklayer.ieee80211.IIeee80211Mac;
import inet.linklayer.common.IIeee8021dQosClassifier;
import inet.linklayer.ieee80211.llc.IIeee80211Llc;

//
// TODO auto-generated type
//
module SatelliteLinkLayer  extends NetworkInterface like IWirelessInterface
{    parameters:
        string interfaceTableModule;
        string energySourceModule = default("");
        double bitrate @unit(bps);
        
        *.interfaceTableModule = default(absPath(this.interfaceTableModule));
        *.energySourceModule = default(absPath(this.energySourceModule));
        **.bitrate = this.bitrate;

       // string opMode @enum("a","b","g(erp)","g(mixed)","n(mixed-2.4Ghz)","p","ac") = default("g(mixed)");
        string address @mutable = default("auto"); // MAC address as hex string (12 hex digits), or
                                                   // "auto". "auto" values will be replaced by
                                                   // a generated MAC address in init stage 0.
        string protocol = default("");

        //**.opMode = this.opMode;

       // mac.modeSet = default(this.opMode);
       // mac.*.rateSelection.dataFrameBitrate = default(this.bitrate);
        *.macModule = default(absPath(".mac"));
        *.mibModule = default(absPath(".mib"));

        
    gates:
        input upperLayerIn;
        output upperLayerOut;
        input radioIn @labels(WirelessSignal);
    submodules:
        queue: <default("DropTailQueue")> like IPacketQueue {
            parameters:
                @display("p=200,100;q=l2queue");
        }
        mib: Ieee80211Mib {
            parameters:
                @display("p=100,300;is=s");
        }
        llc: <default("Ieee80211LlcLpd")> like IIeee80211Llc {
            parameters:
                @display("p=300,200");
        }
        classifier: <default("OmittedIeee8021dQosClassifier")> like IIeee8021dQosClassifier {
            parameters:
                @display("p=500,100");
        }
        agent: <default("Ieee80211AgentSta")> like IIeee80211Agent if typename != "" {
            parameters:
                @display("p=700,300");
        }
        mgmt: <default("Ieee80211MgmtSta")> like IIeee80211Mgmt {
            parameters:
                @display("p=500,300");
        }
        mac: <default("Ieee80211Mac")> like IIeee80211Mac { 
        //mac: SatelliteMac { 
            parameters:
                @display("p=300,100");
        }
        radio: <default("UnitDiskRadio")> like IRadio {
            parameters:
                @display("p=300,200");
        }
    connections:
        llc.lowerLayerOut --> { @display("m=n"); } --> queue.in;

        radioIn --> { @display("m=s"); } --> radio.radioIn;
        radio.upperLayerIn <-- mac.lowerLayerOut;
        radio.upperLayerOut --> mac.lowerLayerIn;
               
        // added june/16
        mac.mgmtOut --> mgmt.macIn;
        mac.mgmtIn <-- mgmt.macOut;

        mgmt.agentOut --> agent.mgmtIn if exists(agent);
        mgmt.agentIn <-- agent.mgmtOut if exists(agent);

        llc.upperLayerOut --> { @display("m=n"); } --> upperLayerOut;
        llc.upperLayerIn <-- { @display("m=n"); } <-- classifier.out;

        queue.out --> mac.upperLayerIn;
        llc.lowerLayerIn <-- mac.upperLayerOut;

        classifier.in <-- { @display("m=n"); } <-- upperLayerIn;
}
