//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package inet_leosatellites.networklayer.configurator.ipv4;
import leosatellites.networklayer.configurator.ipv4.SatelliteNetworkConfigurator;

simple SatelliteNetworkConfiguratorScs extends SatelliteNetworkConfigurator
{
    parameters:
        @class(inet::SatelliteNetworkConfiguratorScs);
        @display("i=block/cogwheel");
		addStaticRoutes = true;
		optimizeRoutes = false;
}