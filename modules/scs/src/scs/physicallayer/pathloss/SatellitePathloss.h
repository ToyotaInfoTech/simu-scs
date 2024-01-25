//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef PHYSICALLAYER_PROPAGATION_SATELLITEPATHLOSS_H_
#define PHYSICALLAYER_PROPAGATION_SATELLITEPATHLOSS_H_

#include "inet/physicallayer/wireless/common/base/packetlevel/PathLossBase.h"
//#include "base/Calculation.h"
namespace inet {


namespace physicallayer {

class INET_API SatellitePathloss : public PathLossBase
{
  protected:
    double alpha;
    double systemLoss;
    cXMLElement*  plConfig;
    //Calculation* calculation;
    //std::ofstream outfile;               // File where results are written/saved

    //
    double sigmaSf;
    double CL;
    double scintillation;
    double atmospheric;
    double cluster;
    double shadow;
    double building;
    double fading;

  protected:
    virtual void initialize(int stage) override;
    virtual double computeFreeSpacePathLoss(m waveLength, double distance, double alpha, double systemLoss) const;

  public:
    SatellitePathloss();
    virtual ~SatellitePathloss();

    //virtual std::ostream& printToStream(std::ostream& stream, int level) const override;
    virtual std::ostream& printToStream(std::ostream& stream, int level) const ;
    virtual double computePathLoss(mps propagationSpeed, Hz frequency, m distance) const override;
    virtual double computePathLoss(const ITransmission *transmission, const IArrival *arrival) const override;
    virtual m computeRange(mps propagationSpeed, Hz frequency, double loss) const override;

};

}
}

#endif /* PHYSICALLAYER_PROPAGATION_SATELLITEPATHLOSS_H_ */
