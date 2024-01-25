//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/visualizer/canvas/mobility/MobilityCanvasVisualizer.ned` of INET-4.4.1.


package inet_scs.mobility;

import inet.visualizer.base.MobilityVisualizerBase;
import inet.visualizer.contract.IMobilityVisualizer;

//
// This module visualizes multiple mobilities on a 2D canvas. It moves visual
// representations according to their mobility model. It also displays recent
// movement as a polyline, current velocity vector and current orientation.
//
// @see ~MobilityOsgVisualizer, ~MobilityVisualizer, ~MobilityVisualizerBase, ~MobilityVisualizer
//
simple BeamVisualizer extends MobilityVisualizerBase like IMobilityVisualizer
{
    parameters:
        double zIndex = default(0); // determines the drawing order of figures relative to other visualizers
        @class(inet::visualizer::BeamVisualizer);
}

