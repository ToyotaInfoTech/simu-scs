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
// This program was developed based on `src/os3/libnorad/cOrbit.cc`
// of os3 (https://github.com/inet-framework/os3). 

#include "cOrbitScs.h"

#include <cmath>
#include <ctime>
#include <cassert>

#include "os3/libnorad/cVector.h"
#include "os3/libnorad/cEci.h"
#include "os3/libnorad/ccoord.h"
#include "os3/libnorad/cJulian.h"
#include "os3/libnorad/cNoradSGP4.h"
#include "os3/libnorad/cNoradSDP4.h"
#include "leosatellites/libnorad/cOrbitA.h"
#include "leosatellites/libnorad/cNoradSGP4A.h"
#include "os3/libnorad/cTLE.h"

cOrbitScs::cOrbitScs(const cTle &tle) : cOrbitA("", 2023, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 1, 1),
   m_tle(tle)
   // m_pNoradModel(NULL)
{
   m_tle.Initialize();

   epochYear = static_cast<int>(m_tle.getField(cTle::FLD_EPOCHYEAR));
   epochDay = m_tle.getField(cTle::FLD_EPOCHDAY);

   if (epochYear < 57)
      epochYear += 2000;
   else
      epochYear += 1900;

   m_jdEpoch = cJulian(epochYear, epochDay);

   m_secPeriod = -1.0;

   // parameters
   inclination = radGet(cTle::FLD_I);
   eccentricity = m_tle.getField(cTle::FLD_E);
   raan = radGet(cTle::FLD_RAAN);
   argPerigee = radGet(cTle::FLD_ARGPER);
   bstar = m_tle.getField(cTle::FLD_BSTAR);
   drag = m_tle.getField(cTle::FLD_MMOTIONDT);
   meanMotion = m_tle.getField(cTle::FLD_MMOTION);
   meanAnomaly = radGet(cTle::FLD_M);

   // Recover the original mean motion and semimajor axis from the
   // input elements.
   const double mm     = mnMotion();
   const double rpmin  = mm * 2 * PI / MIN_PER_DAY;   // rads per minute

   const double a1     = std::pow(XKE / rpmin, TWOTHRD);
   const double e      = Eccentricity();
   const double i      = Inclination();
   const double temp   = (1.5 * CK2 * (3.0 * sqr(cos(i)) - 1.0) / std::pow(1.0 - e * e, 1.5));
   const double delta1 = temp / (a1 * a1);
   const double a0     = a1 *
                      (1.0 - delta1 *
                      ((1.0 / 3.0) + delta1 *
                      (1.0 + 134.0 / 81.0 * delta1)));

   const double delta0 = temp / (a0 * a0);

   m_mnMotionRec        = rpmin / (1.0 + delta0);
   m_aeAxisSemiMinorRec = a0 / (1.0 - delta0);
   m_aeAxisSemiMajorRec = m_aeAxisSemiMinorRec / sqrt(1.0 - (e * e));
   m_kmPerigeeRec       = XKMPER_WGS72 * (m_aeAxisSemiMajorRec * (1.0 - e) - AE);
   m_kmApogeeRec        = XKMPER_WGS72 * (m_aeAxisSemiMajorRec * (1.0 + e) - AE);
   m_pNoradModel = new cNoradSGP4A(*this);
   std::string str = m_tle.getName();
   std::string strId;
   m_tle.getField(cTle::FLD_NORADNUM, cTle::U_NATIVE, &strId);
   str = str + " #" + strId;
   satName = str;
}

