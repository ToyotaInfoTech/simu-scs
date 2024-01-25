// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "scs/application/RefreshCounterNode.h"

namespace inet {

RefreshCounterNode::RefreshCounterNode() {
    // TODO Auto-generated constructor stub

}

RefreshCounterNode::~RefreshCounterNode() {
    // TODO Auto-generated destructor stub
}

void RefreshCounterNode::CountUp(long interval)
{
    Count +=interval;
}
void RefreshCounterNode::Reset()
{
    Count = 0.0;
}

long RefreshCounterNode::isCount()
{
    return Count;
}

}
