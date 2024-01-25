//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/src/inet/visualizer/base/MobilityVisualizerBase.ned` of INET-4.4.1.

package inet_scs.base;

import inet.visualizer.base.VisualizerBase;
//
// This is a base module for mobility visualizer simple modules. It subscribes
// for the mobilityStateChanged signal at the module determined by the
// visualizationSubjectModule parameter. The actual visualization of mobility is done in
// derived modules.
//
// @see ~MobilityCanvasVisualizer, ~MobilityOsgVisualizer, ~IMobilityVisualizer, ~VisualizerBase
//
simple BeamVisualizerBase extends VisualizerBase
{
    parameters:
        string networkNodeVisualizerModule = default("^.networkNodeVisualizer"); // the network node visualizer module, refers to a sibling submodule by default

        bool displayBeam = default(true); // display mobility, enabled by default
        string moduleFilter @mutable = default("**.mobility"); // which mobilities are considered, matches all mobilities by default
  	    double animationSpeed = default(0);
        double positionCircleRadius = default(4); // radius of the circle
        double positionCircleLineWidth = default(1); // line width of the circle
        string positionCircleLineColor @enum("light", "dark") = default("dark"); // position circle line color is a list of colors, a set of dark colors by default
        string positionCircleFillColor @enum("light", "dark") = default("dark"); // position circle fill color is a list of colors, a set of dark colors by default

        @class(inet::visualizer::BeamVisualizerBase);
}

