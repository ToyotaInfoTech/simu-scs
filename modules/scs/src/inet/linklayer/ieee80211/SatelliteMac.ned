// Copyright (C) 2004 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/linklayer/ieee80211/mac/Mac.ned` of INET-4.4.1.

package inet_scs.linklayer.ieee80211;

import inet.linklayer.base.MacProtocolBase;
import inet.linklayer.ieee80211.IIeee80211Mac;
import inet.linklayer.ieee80211.mac.contract.IDcf;
import inet.linklayer.ieee80211.mac.contract.IDs;
import inet.linklayer.ieee80211.mac.contract.IHcf;
import inet.linklayer.ieee80211.mac.contract.IRx;
import inet.linklayer.ieee80211.mac.contract.ITx;
import inet.linklayer.ieee80211.mac.coordinationfunction.Dcf;
import inet.linklayer.ieee80211.mac.coordinationfunction.Hcf;
import inet.linklayer.contract.ILinkLayer;
import inet.linklayer.contract.IMacProtocol;
//
// This module implements a highly abstracted wireless network interface (NIC)
// that uses a trivial MAC protocol. It offers simplicity for scenarios where
// Layer 1 and 2 effects can be completely ignored, for example testing the
// basic functionality of a wireless ad-hoc routing protocol.
//
// The most important parameter this model accepts is the transmission range.
// When a radio transmits a frame, all other radios within transmission range
// will receive the frame correctly, and radios that are out of range will not be
// affected at all.
//
// This module requires an ~UnitDiskRadioMedium instance in the network.
//
module SatelliteMac extends MacProtocolBase like IIeee80211Mac
{
    parameters:
        string modeSet @enum("a", "b", "g(erp)", "g(mixed)", "n(mixed-2.4Ghz)", "p", "ac") = default("p");
        string mibModule;
        string fcsMode @enum("declared", "computed") = default("declared");
        string initialRadioMode @enum("off", "sleep", "receiver", "transmitter", "transceiver") = default("receiver");

        int mtu @unit(B) = default(2304B);
        bool qosStation = default(false);

        *.mibModule = default(absPath(this.mibModule));
        *.rxModule = "^.rx";
        *.txModule = "^.tx";

        @display("i=block/layer");
        @class(SatelliteMac);
        @signal[linkBroken](type=inet::Packet); // TODO this signal is only present for the statistic to pass the signal check, to be removed
        @signal[modesetChanged](type=inet::physicallayer::Ieee80211ModeSet);
        @statistic[packetSentToUpper](title="packets sent to upper layer"; record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetSentToLower](title="packets sent to lower layer"; record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetReceivedFromUpper](title="packets received from upper layer"; record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetReceivedFromLower](title="packets received from lower layer"; record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[linkBroken](title="link breaks"; record=count, vector?; interpolationmode=none);
        @statistic[packetDrop](title="packet drops"; source=packetDropped; record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropIncorrectlyReceived](title="packet drops: incorrectly received"; source=packetDropReasonIsIncorrectlyReceived(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropNotAddressedToUs](title="packet drops: not addressed to us"; source=packetDropReasonIsNotAddressedToUs(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropQueueOverflow](title="packet drops: queue overflow"; source=packetDropReasonIsQueueOverflow(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropRetryLimitReached](title="packet drops: retry limit reached"; source=packetDropReasonIsRetryLimitReached(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropDuplicateDetected](title="packet drops: duplicate detected"; source=packetDropReasonIsDuplicateDetected(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);
        @statistic[packetDropOther](title="packet drops: other"; source=packetDropReasonIsOther(packetDropped); record=count,sum(packetBytes),vector(packetBytes); interpolationmode=none);

        
    gates:
        input mgmtIn;
        output mgmtOut;
    submodules:

        ds: <default("Dss")> like IDs {
            parameters:
                @display("p=400,100");
        }
        rx: <default("Rxs")> like IRx {
            parameters:
                @display("p=100,200");
        }
        tx: <default("Txs")> like ITx {
            parameters:
                @display("p=250,200");
        }
}

