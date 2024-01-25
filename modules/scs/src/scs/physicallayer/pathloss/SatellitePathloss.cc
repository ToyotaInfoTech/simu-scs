//
// Copyright (C) 2023 TOYOTA MOTOR CORPORATION. ALL RIGHTS RESERVED.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "scs/physicallayer/pathloss/SatellitePathloss.h"
#include "inet/physicallayer/apskradio/SatelliteApskScalarTransmission.h"


const double EarthRadius = 6378.137764899274;  // In km

namespace inet {


namespace physicallayer {

Define_Module(SatellitePathloss);



SatellitePathloss::SatellitePathloss() :
        alpha(2.0),
        systemLoss(1.0),
        sigmaSf(2.7),
        CL(0.0),
        scintillation(0.6),
        atmospheric(10),
        cluster(0.0),
        shadow(0.0),
        building(0.0),
        fading(0.0)
{
    // TODO Auto-generated constructor stub

}

void SatellitePathloss::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        alpha = par("alpha");
        systemLoss = math::dB2fraction(par("systemLoss"));
    }

    plConfig = par("plConfig").xmlValue();

    // below xml has not implemented
    cXMLElementList sigmaSf = plConfig->getElementsByTagName("sigmaSf");

    //calculation = dynamic_cast<Calculation*>(getParentModule()->getSubmodule("radioMedium",0)->getSubmodule("pathLoss",0)->getSubmodule("cni_os3", 0)->getSubmodule("calculation", 0));
    //calculation->initialize();
}


SatellitePathloss::~SatellitePathloss() {
    // TODO Auto-generated destructor stub
    //outfile.close();
}

std::ostream& SatellitePathloss::printToStream(std::ostream& stream, int level) const
{
    //outfile << "SatellitePathLoss" << std::endl;

    stream << "SatellitePathLoss";
    if (level <= PRINT_LEVEL_TRACE)
        stream << ", alpha = " << alpha
               << ", systemLoss = " << systemLoss;
    return stream;
}

double SatellitePathloss::computeFreeSpacePathLoss(m waveLength, double distance, double alpha, double systemLoss) const
{
    //EV << "---------------->  satellite computeFreeSpacePathLoss is called \n";
    // factor = waveLength ^ 2 / (16 * PI ^ 2 * systemLoss * distance ^ alpha)
    // satellite FSPL factor is wavelength^2 / d^2
    return distance == 0.0 ? 1.0 : (waveLength * waveLength).get() / (pow(distance, alpha));

}

double SatellitePathloss::computePathLoss(mps propagationSpeed, Hz frequency, m distance) const
{
    m waveLength = propagationSpeed / frequency;
    //EV << "---------------->  satellite computePathLoss is called \n";
    return computeFreeSpacePathLoss(waveLength, distance.get(), alpha, systemLoss);
}

double SatellitePathloss::computePathLoss(const ITransmission *transmission, const IArrival *arrival) const
{
    const double transmitterGain = 13.0; // GPS transmitter gain
    const double receiverGain = 0.0;     // Average GPS antenna
    W      power(0);  // GPS transmitter power
    const double lambda = 0.1905;        // wavelength of GPS signal in m (f = 1575,42 MHz)
    const double dG = 0.5;               // Average ratio of antenna radiation from ground (omnidirectional gps antenna)
    const double tR = 150;               // in K, Receiver noise temperature
    Hz     bandwidth(0);
    const double propargationspeed = 299792458;
    const mps propargationSpeed(299792458);
    const simtime_t duration =  arrival->getEndPropagationTime();

    double distance = duration.dbl() * propargationspeed;
    EV << "DISTANCE from duration * C is " << distance/1000 << "Km\n" ;

    Hz centerFrequency(0);
   // double distance = 0; //m

        if (const SatelliteApskScalarTransmission *satApskTransmission = dynamic_cast<const SatelliteApskScalarTransmission*>(transmission)) {

            centerFrequency = satApskTransmission->getCenterFrequency();
            bandwidth = satApskTransmission->getBandWidth();
            power = satApskTransmission->getPower();

        }else {
            EV << "\nOTHER TRANSMITTER DETECTED";
        }

    //EV << "DISTANCE from duration * C %d" << distance ;
    m waveLength = propargationSpeed / centerFrequency;
    //double snr = calculation->calcSNRleo(transmitterGain, receiverGain, power.get(),lambda,  bandwidth.get(),dG, tR);

    // center frequenct in Ghz unit.
    double centerFrequencyGhz = centerFrequency.get() * pow(10,-9);

    double FSPL1 = 32.45 + 20*std::log10(centerFrequencyGhz)+20*std::log10(distance); // distance (m)
    double FSPL2 = sigmaSf + CL + scintillation + atmospheric + cluster + shadow + building + fading;
    double FSPL = FSPL1 + FSPL2;

    // return FSPL in decimal number
    //double FSPLD = pow (10, -1 * FSPL);
    double FSPLD = computeFreeSpacePathLoss(waveLength, distance, alpha, systemLoss);

    EV << "---------------->  FSPL : " << FSPL << " (db) duration " << duration.dbl() << "(s) power loss " << FSPLD << " \n";


    // still FSPLD is very small value so that signal not reachable.
    return FSPLD;
    // to simulate communication, returns no attenuated power. but indicated arithmetic result in print to log.
    //return 1.0;
    //return computeFreeSpacePathLoss(waveLength, distance, alpha, systemLoss);
}

m SatellitePathloss::computeRange(mps propagationSpeed, Hz frequency, double loss) const
{
    // distance = (waveLength ^ 2 / (16 * PI ^ 2 * systemLoss * loss)) ^ (1 / alpha)
    m waveLength = propagationSpeed / frequency;
    EV << "---------------->  satellite compute Rage is called \n";
   return m(pow((waveLength * waveLength).get() / (16.0 * M_PI * M_PI * systemLoss * loss), 1.0 / alpha));
}


}
}
