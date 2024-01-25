// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//
#ifndef _APPLICATION_REFRESHCOUNTERNODE_H_
#define _APPLICATION_REFRESHCOUNTERNODE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include "inet/applications/base/ApplicationBase.h"

namespace inet {

class RefreshCounterNode : public cModule {
public:
    RefreshCounterNode();
    virtual ~RefreshCounterNode();

    void CountUp(long interval);
    void Reset();

    long isCount();

private:
    long Count=0.0;
};

}

#endif /* org.scs.Satellite_APPLICATION_REFRESHCOUNTERNODE_H_ */
