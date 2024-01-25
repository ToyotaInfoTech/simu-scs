// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

//
//  Description:
//  This file contains LTE typedefs and constants.
//  At the end of the file there are some utility functions.
//

#ifndef _SATCOMMON_H_
#define _SATCOMMON_H_


#include <iostream>
#include <omnetpp.h>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <set>
#include <queue>
#include <map>
#include <list>
#include <algorithm>

using namespace Satellite;

class BeamInfo;

/**
 * TODO
 */
#define ELEM(x) {x,#x}

/// Transmission time interval
#define TTI 0.001

/// Current simulation time
#define NOW omnetpp::simTime()

/// Node Id bounds
#define ENB_MIN_ID 1
#define ENB_MAX_ID 1023
#define BGUE_ID 1024
#define UE_MIN_ID 1025
#define NR_UE_MIN_ID 2049
#define BGUE_MIN_ID 4097
#define UE_MAX_ID 65535


/// ChannelID
typedef unsigned int ChannelID;

/// SubChannelID
typedef unsigned int SubChannelID;

/// BeamID
typedef unsigned int BeamID;

/// UEID
typedef unsigned int UEID;

typedef std::vector<double> ChannelVector;

typedef std::vector<double> SubChannelVector;

typedef std::vector<double> BeamVector;

typedef std::vector<double> UEVector;

/**
 */
typedef std::map<BeamID, UEVector>  UEperBeam;

/*********************
 * Utility functions
 *********************/


#endif

