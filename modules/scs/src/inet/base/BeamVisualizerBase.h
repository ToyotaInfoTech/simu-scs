//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/src/inet/visualizer/base/MobilityVisualizerBase.h` of INET-4.4.1. 


#ifndef __BEAMVISUALIZERBASE_H
#define __BEAMVISUALIZERBASE_H

#include "inet/mobility/contract/IMobility.h"
#include "inet/visualizer/base/VisualizerBase.h"
#include "inet/visualizer/util/ColorSet.h"
#include "inet/visualizer/util/ModuleFilter.h"

using namespace omnetpp;
namespace inet {
namespace visualizer {

class INET_API BeamVisualizerBase : public VisualizerBase, public cListener
{
  protected:
    class  INET_API BeamVisualization {
      public:
        int i;

      public:
        BeamVisualization(int i);
        virtual ~BeamVisualization() {}
    };

  protected:

    bool displayBeam = true;
    double animationSpeed = 0;
    ModuleFilter moduleFilter;
    double positionCircleRadius = NaN;
    double positionCircleLineWidth = NaN;
    ColorSet positionCircleLineColorSet;
    ColorSet positionCircleFillColorSet;

    std::map<int, BeamVisualization *> BeamVisualizations;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleParameterChange(const char *name) override;
    virtual void preDelete(cComponent *root) override;

    virtual void subscribe();
    virtual void unsubscribe();


  public:
    virtual BeamVisualization *createBeamVisualization(int i) = 0;
    virtual BeamVisualization *getBeamVisualization(const int i) const;
    virtual void addBeamVisualization(const int i, BeamVisualization *beamVisualization);
    virtual void removeBeamVisualization(const BeamVisualization *beamVisualization);
    virtual void removeAllBeamVisualizations();

};

}
}

#endif

