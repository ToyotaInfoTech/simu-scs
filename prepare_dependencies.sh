#!/bin/bash

# Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
# SPDX-License-Identifier: LGPL-3.0-or-later

LEOSATELLITES_ROOT=external/leosatellites/src/leosatellites

if [ -d ${LEOSATELLITES_ROOT}/libnorad ]; then
  rm ${LEOSATELLITES_ROOT}/libnorad/*
else
  mkdir -p ${LEOSATELLITES_ROOT}/libnorad
fi
pushd ${LEOSATELLITES_ROOT}/libnorad
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cEcef.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cEcef.h
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cNoradBaseA.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cNoradBaseA.h
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cNoradSGP4A.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cNoradSGP4A.h
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cOrbitA.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/libnorad/cOrbitA.h
popd

if [ -d ${LEOSATELLITES_ROOT}/mobility ]; then
  rm ${LEOSATELLITES_ROOT}/mobility/*
else
  mkdir -p ${LEOSATELLITES_ROOT}/mobility
fi
pushd ${LEOSATELLITES_ROOT}/mobility
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/GroundStationMobility.h
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/GroundStationMobility.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/GroundStationMobility.ned
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/INorad.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/INorad.h
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/INorad.ned
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/NoradA.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/NoradA.h
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/NoradA.ned
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/SatelliteMobility.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/SatelliteMobility.h
wget https://github.com/Avian688/leosatellites/raw/master/src/mobility/SatelliteMobility.ned
popd

if [ -d ${LEOSATELLITES_ROOT}/networklayer/configurator/ipv4 ]; then
  rm ${LEOSATELLITES_ROOT}/networklayer/configurator/ipv4/*
else
  mkdir -p ${LEOSATELLITES_ROOT}/networklayer/configurator/ipv4
fi
pushd ${LEOSATELLITES_ROOT}/networklayer/configurator/ipv4
wget https://github.com/Avian688/leosatellites/raw/master/src/networklayer/configurator/ipv4/MatcherOS3.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/networklayer/configurator/ipv4/MatcherOS3.h
wget https://github.com/Avian688/leosatellites/raw/master/src/networklayer/configurator/ipv4/SatelliteNetworkConfigurator.cc
wget https://github.com/Avian688/leosatellites/raw/master/src/networklayer/configurator/ipv4/SatelliteNetworkConfigurator.h
wget https://github.com/Avian688/leosatellites/raw/master/src/networklayer/configurator/ipv4/SatelliteNetworkConfigurator.ned
popd

if [ -d ${LEOSATELLITES_ROOT}/physicallayer ]; then
  rm ${LEOSATELLITES_ROOT}/physicallayer/propagation/*
  rm ${LEOSATELLITES_ROOT}/physicallayer/unitdisk/*
  rm ${LEOSATELLITES_ROOT}/physicallayer/apskradio/*
else
  mkdir -p ${LEOSATELLITES_ROOT}/physicallayer/propagation
  mkdir -p ${LEOSATELLITES_ROOT}/physicallayer/unitdisk
  mkdir -p ${LEOSATELLITES_ROOT}/physicallayer/apskradio
fi
pushd ${LEOSATELLITES_ROOT}/physicallayer
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/propagation/SatellitePropagation.cc -P propagation
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/propagation/SatellitePropagation.h -P propagation
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/propagation/SatellitePropagation.ned -P propagation
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/unitdisk/SatelliteUnitDiskTransmission.cc -P unitdisk
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/unitdisk/SatelliteUnitDiskTransmission.h -P unitdisk
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/apskradio/SatelliteApskScalarTransmission.cc -P apskradio
wget https://github.com/Avian688/leosatellites/raw/master/src/physicallayer/apskradio/SatelliteApskScalarTransmission.h -P apskradio
popd

pushd ${LEOSATELLITES_ROOT}
wget https://github.com/Avian688/leosatellites/raw/master/src/package.ned -O package.ned
popd

patch -u -t -p1 -d ${LEOSATELLITES_ROOT} < patches/leosatellites.patch

OS3_LIBNORAD_ROOT=modules/os3/src/os3/libnorad

if [ -d ${OS3_LIBNORAD_ROOT} ]; then
  rm ${OS3_LIBNORAD_ROOT}/*
else
  mkdir -p ${OS3_LIBNORAD_ROOT}
fi
pushd ${OS3_LIBNORAD_ROOT}
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/ccoord.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/ccoord.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cEci.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cEci.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cJulian.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cJulian.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradBase.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradBase.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradSDP4.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradSDP4.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradSGP4.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cNoradSGP4.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cOrbit.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cOrbit.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cSite.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cSite.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cTLE.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cTLE.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cVector.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/cVector.h
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/globals.cc
wget https://raw.githubusercontent.com/inet-framework/os3/master/src/os3/libnorad/globals.h
popd

patch -u -t -p1 -d ${OS3_LIBNORAD_ROOT} < patches/os3_libnorad.patch

OS3_IMAGE_ROOT=samples/images/os3

if [ -d ${OS3_IMAGE_ROOT} ]; then
  rm ${OS3_IMAGE_ROOT}/*
else
  mkdir -p ${OS3_IMAGE_ROOT}
fi
pushd ${OS3_IMAGE_ROOT}
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/Erde.GIF
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/Erde.jpg
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/Erde1.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/Galileo_Satellit_klein.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/background_earth.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/background_earth_CospasSarsat.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/binocular.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellit_blue.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellit_green.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellit_l_rot.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellit_orange.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellit_yellow.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/satellite_red.gif
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/sw.gif
popd

if [ -d ${OS3_IMAGE_ROOT}/weatherIcons ]; then
  rm ${OS3_IMAGE_ROOT}/weatherIcons/*
else
  mkdir -p ${OS3_IMAGE_ROOT}/weatherIcons
fi
pushd ${OS3_IMAGE_ROOT}/weatherIcons
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0001_sunny.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0002_sunny_intervals.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0003_white_cloud.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0004_black_low_cloud.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0006_mist.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0007_fog.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0008_clear_sky_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0009_light_rain_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0010_heavy_rain_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0011_light_snow_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0012_heavy_snow_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0013_sleet_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0016_thundery_showers.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0017_cloudy_with_light_rain.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0018_cloudy_with_heavy_rain.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0019_cloudy_with_light_snow.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0020_cloudy_with_heavy_snow.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0021_cloudy_with_sleet.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0024_thunderstorms.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0025_light_rain_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0026_heavy_rain_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0027_light_snow_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0028_heavy_snow_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0029_sleet_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0032_thundery_showers_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0033_cloudy_with_light_rain_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0034_cloudy_with_heavy_rain_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0035_cloudy_with_light_snow_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0036_cloudy_with_heavy_snow_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0037_cloudy_with_sleet_night.png
wget https://raw.githubusercontent.com/inet-framework/os3/master/images/os3/weatherIcons/wsymbol_0040_thunderstorms_night.png
popd

patch -u -t -p1 external/simu5G/.project < patches/simu5G.patch
