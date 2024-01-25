//
// Copyright (C) 2020 OpenSim Ltd.
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
// 
// This program was developed based on INET Framework (https://inet.omnetpp.org/). 
// The original code can be found at `external/inet/node/base/NodeBase.cc`. 

#include "../../../inet/node/base/VeinsBase.h"

#include "inet/common/SubmoduleLayout.h"

namespace inet {

Define_Module(VeinsBase);

void VeinsBase::initialize(int stage)
{
    if (stage == INITSTAGE_LAST)
        layoutSubmodulesWithoutGates(this);
}

} // namespace inet

