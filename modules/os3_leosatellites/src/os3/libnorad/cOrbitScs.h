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
// This program was developed partly based on `src/os3/libnorad/cOrbit.cc`
// of os3 (https://github.com/inet-framework/os3). 

#ifndef OS3_LIBNORAD_cOrbitScs_H__
#define OS3_LIBNORAD_cOrbitScs_H__

#include "os3/libnorad/cTLE.h"
#include "os3/libnorad/cJulian.h"
#include "leosatellites/libnorad/cOrbitA.h"
#include "leosatellites/libnorad/cNoradBaseA.h"

class cOrbitScs : public cOrbitA
{
public:
   cOrbitScs(const cTle &tle);

private:
   cTle        m_tle;
   double radGet(cTle::eField fld) const
      { return m_tle.getField(fld, cTle::U_RAD); }
   double degGet(cTle::eField fld) const
      { return m_tle.getField(fld, cTle::U_DEG); }

   // cJulian     m_jdEpoch;
   // cNoradBaseA* m_pNoradModel;

   // std::string satName;
   // int index;
   // int epochYear;
   // double epochDay;
   // double meanMotion;
   // double eccentricity;
   // double inclination;
   // double meanAnomaly;
   // double raan;
   // double argPerigee;
   // double bstar;
   // double drag;

   // Caching variables; note units are not necessarily the same as tle units
   // mutable double m_secPeriod;

   // Caching variables recovered from the input TLE elements
   // double m_aeAxisSemiMinorRec;  // semi-minor axis, in AE units
   // double m_aeAxisSemiMajorRec;  // semi-major axis, in AE units
   // double m_mnMotionRec;         // radians per minute
   // double m_kmPerigeeRec;        // perigee, in km
   // double m_kmApogeeRec;         // apogee, in km

};

#endif
