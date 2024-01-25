//
// Copyright (c) Michael F. Henry
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
// This program was developed partly based on `src/os3/mobility/Norad.h`
// of os3 (https://github.com/inet-framework/os3). 

#ifndef OS3_MOBILITY_NORADSCS_H_
#define OS3_MOBILITY_NORADSCS_H_

#include <omnetpp.h>

#include <string>
#include <ctime>


#include "os3/libnorad/cJulian.h"
#include "os3/libnorad/ccoord.h"
#include "os3/libnorad/cEci.h"
#include "leosatellites/mobility/NoradA.h"
#include "os3/mobility/NoradScs.h"
#include "inet/common/geometry/common/Coord.h"
#include "os3/libnorad/cOrbitScs.h"
using namespace omnetpp;
using namespace inet;

class NoradScs : public NoradA
{
public:
    NoradScs();
    virtual void updateTime(const simtime_t& targetTime) override;
    virtual void initializeMobility(const simtime_t& targetTime) override;
    virtual const cEci  getSatellitePosition() const  {return satellitePosition; }

private:
    int gapOffset;
    cEci satellitePosition;
    std::string line0;
    std::string line1;
    std::string line2;
    std::string line3;
    int simcycle;
    // cOrbitScs *orbit;
};

#endif
