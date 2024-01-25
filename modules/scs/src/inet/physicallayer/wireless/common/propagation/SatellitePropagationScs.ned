// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package inet_scs.physicallayer.wireless.common.propagation;

import leosatellites.physicallayer.propagation.SatellitePropagation;

module SatellitePropagationScs extends SatellitePropagation
{
    parameters:
        @class(inet::physicallayer::SatellitePropagationScs);
}
