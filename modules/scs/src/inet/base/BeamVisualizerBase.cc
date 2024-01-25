//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/src/inet/visualizer/base/MobilityVisualizerBase.cc` of INET-4.1.1. 


#include "../../inet/base/BeamVisualizerBase.h"

#include "inet/common/ModuleAccess.h"

namespace inet {

namespace visualizer {

BeamVisualizerBase::BeamVisualization::BeamVisualization(int i) :
    i(i)
{
}


void BeamVisualizerBase::initialize(int stage)
{
    VisualizerBase::initialize(stage);
    if (!hasGUI()) return;
    if (stage == INITSTAGE_LOCAL) {
        displayBeam = par("displayBeam");
        animationSpeed = par("animationSpeed");
        moduleFilter.setPattern(par("moduleFilter"));
        positionCircleRadius = par("positionCircleRadius");
        positionCircleLineWidth = par("positionCircleLineWidth");
        positionCircleLineColorSet.parseColors(par("positionCircleLineColor"));
        positionCircleFillColorSet.parseColors(par("positionCircleFillColor"));
        subscribe();
    }
}
void BeamVisualizerBase::handleParameterChange(const char *name)
{
    if (!hasGUI()) return;
    if (name != nullptr) {
        if (!strcmp(name, "moduleFilter"))
            moduleFilter.setPattern(par("moduleFilter"));
    }
}
void BeamVisualizerBase::preDelete(cComponent *root)
{
    unsubscribe();
    removeAllBeamVisualizations();
}

void BeamVisualizerBase::subscribe()
{
    visualizationSubjectModule->subscribe(IMobility::mobilityStateChangedSignal, this);
    visualizationSubjectModule->subscribe(PRE_MODEL_CHANGE, this);
}
void BeamVisualizerBase::unsubscribe()
{
    auto visualizationSubjectModule = findModuleFromPar<cModule>(par("visualizationSubjectModule"), this);
    if (visualizationSubjectModule != nullptr) {
        visualizationSubjectModule->unsubscribe(IMobility::mobilityStateChangedSignal, this);
        visualizationSubjectModule->unsubscribe(PRE_MODEL_CHANGE, this);
    }
}

BeamVisualizerBase::BeamVisualization *BeamVisualizerBase::getBeamVisualization(const int i) const
{
    auto it = BeamVisualizations.find(i);
    return (it == BeamVisualizations.end()) ? nullptr : it->second;
}

void BeamVisualizerBase::addBeamVisualization(const int i, BeamVisualization *beamVisualization)
{
    BeamVisualizations[i] = beamVisualization;
}

void BeamVisualizerBase::removeBeamVisualization(const BeamVisualization *beamVisualization)
{
    BeamVisualizations.erase(beamVisualization->i);
}

void BeamVisualizerBase::removeAllBeamVisualizations()
{
    std::vector<const BeamVisualization *> removedBeamVisualizations;
    for (auto it : BeamVisualizations)
        removedBeamVisualizations.push_back(it.second);
    for (auto beamVisualization : removedBeamVisualizations) {
        removeBeamVisualization(beamVisualization);
        delete beamVisualization;
    }
}

}
}

