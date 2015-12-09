/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "InfoRecombiner.hh"
#include "physics/Units.hh"

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

class DetectorGeometry
{

public:

    static Momentum JetMinPt();

    static Angle JetConeSize();

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

    static JetType jet_type();

    static void set_detector_type(DetectorType detector_type);

    static DetectorType detector_type();

    static InfoRecombiner& Recombiner();

private:

    static DetectorType detector_type_;

    static InfoRecombiner info_recombiner_;

};

}
