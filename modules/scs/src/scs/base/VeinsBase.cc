// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#include "VeinsBase.h"

#include "inet/common/SubmoduleLayout.h"
#include "inet/common/InitStages.h"
namespace Satellite {

Define_Module(VeinsBase);

void VeinsBase::initialize(int stage)
{
    if (stage == INITSTAGE_LAST)
        layoutSubmodulesWithoutGates(this);
}

}
