//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `inet/visualizer/canvas/mobility/MobilityCanvasVisualizer.cc` of INET-4.4.1.

#include "../../inet/mobility/BeamVisualizer.h"

#include "inet/common/ModuleAccess.h"
#include "scs/mobility/SatelliteMobilityScs.h"
using namespace Satellite;
namespace inet {

namespace visualizer {

Define_Module(inet::visualizer::BeamVisualizer);

BeamVisualizer::MobilityCanvasVisualization::~MobilityCanvasVisualization()
{
    delete positionFigure;
    delete orientationFigure;
    delete velocityFigure;
    delete trailFigure;
}

BeamVisualizer::MobilityCanvasVisualization::MobilityCanvasVisualization(cOvalFigure *positionFigure, cPieSliceFigure *orientationFigure, cLineFigure *velocityFigure, TrailFigure *trailFigure, IMobility *mobility) :
    MobilityVisualization(mobility),
    positionFigure(positionFigure),
    orientationFigure(orientationFigure),
    velocityFigure(velocityFigure),
    trailFigure(trailFigure)
{
}

void BeamVisualizer::initialize(int stage)
{
    MobilityVisualizerBase::initialize(stage);
    if (!hasGUI()) return;
    if (stage == INITSTAGE_LOCAL) {
        zIndex = par("zIndex");
        canvasProjection = CanvasProjection::getCanvasProjection(visualizationTargetModule->getCanvas());
    }
}

void BeamVisualizer::refreshDisplay() const
{
    MobilityVisualizerBase::refreshDisplay();
    for (auto it : mobilityVisualizations) {
        bool satellite=false;
        auto mobilityVisualization = static_cast<MobilityCanvasVisualization *>(it.second);
        auto mobility = mobilityVisualization->mobility;

        if (dynamic_cast<inet::SatelliteMobilityScs *>(mobility)!=nullptr)
        {
            satellite=true;
        }
        auto position = canvasProjection->computeCanvasPoint(mobility->getCurrentPosition());
        auto orientation = mobility->getCurrentAngularPosition();
        auto velocity = canvasProjection->computeCanvasPoint(mobility->getCurrentVelocity());
        if (displayPositions && satellite) {
            double radius = positionCircleRadius ;/// getEnvir()->getZoomLevel(visualizationTargetModule);
            mobilityVisualization->positionFigure->setBounds(cFigure::Rectangle(position.x - radius, position.y - radius, 2 * radius, 2 * radius));
        }
        if (displayOrientations) {
            // NOTE: this negation cancels out the (incorrect) CCW angle handling of cPieSliceFigure (see bug https://dev.omnetpp.org/bugs/view.php?id=1030)
            auto angle = -orientation.toEulerAngles().alpha;
            mobilityVisualization->orientationFigure->setStartAngle(rad(angle - rad(M_PI) * orientationPieSize).get());
            mobilityVisualization->orientationFigure->setEndAngle(rad(angle + rad(M_PI) * orientationPieSize).get());
            double radius = orientationPieRadius / getEnvir()->getZoomLevel(visualizationTargetModule);
            mobilityVisualization->orientationFigure->setBounds(cFigure::Rectangle(position.x - radius, position.y - radius, 2 * radius, 2 * radius));
        }
        if (displayVelocities) {
            mobilityVisualization->velocityFigure->setStart(position);
            mobilityVisualization->velocityFigure->setEnd(position + velocity * velocityArrowScale);
            mobilityVisualization->velocityFigure->setVisible(velocity.getLength() != 0);
        }
        if (displayMovementTrails)
            extendMovementTrail(mobility, mobilityVisualization->trailFigure, position);
    }
    visualizationTargetModule->getCanvas()->setAnimationSpeed(mobilityVisualizations.empty() ? 0 : animationSpeed, this);
}

void BeamVisualizer::addMobilityVisualization(const IMobility *mobility, MobilityVisualization *mobilityVisualization)
{
    MobilityVisualizerBase::addMobilityVisualization(mobility, mobilityVisualization);
    auto mobilityCanvasVisualization = static_cast<MobilityCanvasVisualization *>(mobilityVisualization);
    auto canvas = visualizationTargetModule->getCanvas();
    if (displayPositions)
        canvas->addFigure(mobilityCanvasVisualization->positionFigure);
    if (displayOrientations)
        canvas->addFigure(mobilityCanvasVisualization->orientationFigure);
    if (displayVelocities)
        canvas->addFigure(mobilityCanvasVisualization->velocityFigure);
    if (displayMovementTrails)
        canvas->addFigure(mobilityCanvasVisualization->trailFigure);
}

void BeamVisualizer::removeMobilityVisualization(const MobilityVisualization *mobilityVisualization)
{
    auto canvas = visualizationTargetModule->getCanvas();
    auto mobilityCanvasVisualization = static_cast<const MobilityCanvasVisualization *>(mobilityVisualization);
    if (displayPositions)
        canvas->removeFigure(mobilityCanvasVisualization->positionFigure);
    if (displayOrientations)
        canvas->removeFigure(mobilityCanvasVisualization->orientationFigure);
    if (displayVelocities)
        canvas->removeFigure(mobilityCanvasVisualization->velocityFigure);
    if (displayMovementTrails)
        canvas->removeFigure(mobilityCanvasVisualization->trailFigure);
    MobilityVisualizerBase::removeMobilityVisualization(mobilityVisualization);
}

BeamVisualizer::MobilityVisualization *BeamVisualizer::createMobilityVisualization(IMobility *mobility)
{
    auto module = const_cast<cModule *>(check_and_cast<const cModule *>(mobility));
    cOvalFigure *positionFigure = nullptr;
    if (displayPositions) {
        positionFigure = new cOvalFigure("circle");
        positionFigure->setTags((std::string("position ") + tags).c_str());
        positionFigure->setTooltip("This circle represents the current position of the mobility model");
        positionFigure->setZIndex(zIndex);
        positionFigure->setLineColor(positionCircleLineColorSet.getColor(module->getId()));
        positionFigure->setLineWidth(positionCircleLineWidth);
        positionFigure->setFilled(false);
        positionFigure->setFillColor(positionCircleFillColorSet.getColor(module->getId()));
    }
    cPieSliceFigure *orientationFigure = nullptr;
    if (displayOrientations) {
        orientationFigure = new cPieSliceFigure("orientation");
        orientationFigure->setTags((std::string("orientation ") + tags).c_str());
        orientationFigure->setTooltip("This arc represents the current orientation of the mobility model");
        orientationFigure->setZIndex(zIndex);
        orientationFigure->setLineOpacity(orientationPieOpacity);
        orientationFigure->setLineColor(orientationLineColor);
        orientationFigure->setLineStyle(orientationLineStyle);
        orientationFigure->setLineWidth(orientationLineWidth);
        orientationFigure->setFilled(true);
        orientationFigure->setFillOpacity(orientationPieOpacity);
        orientationFigure->setFillColor(orientationFillColor);
    }
    cLineFigure *velocityFigure = nullptr;
    if (displayVelocities) {
        velocityFigure = new cLineFigure("velocity");
        velocityFigure->setTags((std::string("velocity ") + tags).c_str());
        velocityFigure->setTooltip("This arrow represents the current velocity of the mobility model");
        velocityFigure->setZIndex(zIndex);
        velocityFigure->setVisible(false);
        velocityFigure->setEndArrowhead(cFigure::ARROW_SIMPLE);
        velocityFigure->setLineColor(velocityLineColor);
        velocityFigure->setLineStyle(velocityLineStyle);
        velocityFigure->setLineWidth(velocityLineWidth);
    }
    TrailFigure *trailFigure = nullptr;
    if (displayMovementTrails) {
        trailFigure = new TrailFigure(trailLength, true, "movement trail");
        trailFigure->setTags((std::string("movement_trail recent_history ") + tags).c_str());
        trailFigure->setZIndex(zIndex);
    }
    return new MobilityCanvasVisualization(positionFigure, orientationFigure, velocityFigure, trailFigure, mobility);
}

void BeamVisualizer::extendMovementTrail(const IMobility *mobility, TrailFigure *trailFigure, cFigure::Point position) const
{
    cFigure::Point startPosition;
    cFigure::Point endPosition = position;
    if (trailFigure->getNumFigures() == 0)
        startPosition = position;
    else
        startPosition = static_cast<cLineFigure *>(trailFigure->getFigure(trailFigure->getNumFigures() - 1))->getEnd();
    double dx = startPosition.x - endPosition.x;
    double dy = startPosition.y - endPosition.y;

    double dx2 = dx * dx;
    int restart=0;

    // tak add to skip greater movement
    if ( dx2 >40000 )
    {
        dx2 = 0;
        dy=0;
        startPosition = position;
        restart=1;
    }
    // TODO 1?
    if (trailFigure->getNumFigures() == 0 || dx2 + dy * dy > 1 || restart>0) {
        cLineFigure *movementLine = new cLineFigure("movementTrail");
        movementLine->setTags((std::string("movement_trail recent_history ") + tags).c_str());
        movementLine->setTooltip("This line represents the recent movement trail of the mobility model");
        movementLine->setStart(startPosition);
        movementLine->setEnd(endPosition);
        auto module = const_cast<cModule *>(check_and_cast<const cModule *>(mobility));
        movementLine->setLineColor(movementTrailLineColorSet.getColor(module->getId()));
        movementLine->setLineStyle(movementTrailLineStyle);
        movementLine->setLineWidth(movementTrailLineWidth);
        movementLine->setZoomLineWidth(false);
        trailFigure->addFigure(movementLine);

        // tak 0304 i will move this function to another class in satellite project.
        // this is a trial to see if this can be draw circle tracking beam area.
        //
        cArcFigure *arc = new cArcFigure("arc");
        arc->setBounds(cFigure::Rectangle(startPosition.x,startPosition.y,1.3,1.3));
        arc->setStartAngle(0);
        arc->setEndAngle(2*M_PI);
        arc->setLineColor(cFigure::BLUE);
        arc->setEndArrowhead(cFigure::ARROW_BARBED);
        auto canvas = visualizationTargetModule->getCanvas();
        canvas->addFigure(arc);
    }
}

} // namespace visualizer

} // namespace inet

