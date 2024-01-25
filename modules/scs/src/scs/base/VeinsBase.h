// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef __INET_NODEBASE_H
#define __INET_NODEBASE_H

#include "inet/common/INETDefs.h"
using namespace inet;
namespace Satellite {
class INET_API VeinsBase : public cModule
{
  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
};
}

#endif

