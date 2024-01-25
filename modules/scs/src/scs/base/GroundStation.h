// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef __BASE_GROUNDSTATION_H_
#define __BASE_GROUNDSTATION_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"


using namespace omnetpp;
namespace Satellite {
class GroundStation : public cSimpleModule
{
public:
    GroundStation();
    virtual ~GroundStation();
};
}
#endif /* org.scs.Satellite_BASE_GROUNDSTATION_H_ */
