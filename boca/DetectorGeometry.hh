/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/InfoRecombiner.hh"
#include "boca/physics/Units.hh"
#include "boca/plotting/Font.hh"

namespace boca
{

/**
 * @brief JetType indicates which type of jet is going to be used
 *
 */
enum class JetType
{
    jet, //< usual Delphse Jet
    gen_jet, //<  Delphes GenJet
    e_flow_jet //< Jet formed from the eflow Variables according to the parameter set in DetectorGeometry
};

std::string Name(JetType jet_type);

/**
 * @brief Detector type indicates which kind of detector geometry is going to be used
 *
 */
enum class DetectorType
{
    CMS, //< default LHC detector
    Spp //<  default detector for a 100TeV collider
};

std::string Name(DetectorType detector_type);

/**
 * @brief Detector and Collider specific constants
 *
 */
class DetectorGeometry
{

public:

    static Momentum JetMinPt();

    static Angle JetConeSize();

    static Angle OverlapConeSize();

    static Momentum MinCellPt();

    static Angle MinCellResolution();

    static Angle TrackerEtaMax();

    static fastjet::JetDefinition JetDefinition();

    static fastjet::JetDefinition JetDefinition(Angle const& jet_cone);

    static fastjet::JetDefinition SubJetDefinition();

    static Length TrackerDistanceMin();

    static Length TrackerDistanceMax();

    static Mass VertexMassMin();

    static Momentum LeptonMinPt();

    static boca::Luminosity Luminosity();

    static boca::JetType JetType();

    static void SetDetectorType(boca::DetectorType detector_type);

    static boca::DetectorType DetectorType();

    static InfoRecombiner& Recombiner();

    static Angle IsolationConeSize();

    static Momentum HardLeptonMomentum();

    static double IsolationFraction();

    static Momentum ForwardJetPt();

    static double Experimental();

    static boca::Font Font();

private:

    static boca::DetectorType detector_type_;

    static InfoRecombiner info_recombiner_;

};

}
