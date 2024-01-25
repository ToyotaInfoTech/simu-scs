// 
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package scs_utils.converter;

simple PositionConverter
{
        parameters:

        @display("i=onedot");
        @class(Satellite::PositionConverter);
        
        int offsetX = default(0);   // when use with veins OSM map on left and offsetX indicate world map offset to the left.
        int offset_x = default(1782);  // x offset from map to map2
        int offset_y = default(189);  // y offset from map to map2
        int mapx = default(2160);      // world original map size
        int mapy = default(1080);      // world original map size
        int mapx2 = default(255);
        int mapy2 = default(255);
        int emapx = default(1080);
        int emapy = default(1080);
        
}