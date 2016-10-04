/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/InfoRecombiner.hh"
#include "boca/physics/Range.hh"
#include "boca/io/Source.hh"
#include "boca/plotting/Font.hh"

namespace boca
{

/**
 * @brief JetType indicates which type of jet is going to be used
 *
 */
enum class JetType
{
    jet, ///< usual Delphse Jet
    gen_jet, ///<  Delphes GenJet
    e_flow_jet ///< Jet formed from the eflow Variables according to the parameter set in Settings
};

std::string Name(JetType jet_type);

/**
 * @brief Detector type indicates which kind of detector geometry is going to be used
 *
 */
enum class Collider
{
    lhc, ///< default LHC detector
    future ///<  default detector for a 100TeV collider
};

std::string Name(Collider collider);

/**
 * @brief Detector and Collider specific constants
 *
 */
class Settings
{

public:

    static fastjet::JetDefinition JetDefinition();

    static fastjet::JetDefinition JetDefinition(Angle const& jet_cone);

    static fastjet::JetDefinition SubJetDefinition();

    static Momentum JetMinPt();

    static Momentum MinCellPt();

    static Momentum LeptonMinPt();

    static Momentum HardLeptonMomentum();

    static Momentum ForwardJetPt();

    static Mass VertexMassMin();

    static Angle JetConeSize();

    static Angle OverlapConeSize();

    static Angle MinCellResolution();

    static Angle TrackerEtaMax();

    static Angle IsolationConeSize();

    static Length TrackerDistanceMin();

    static Length TrackerDistanceMax();

    static Range<Length> TrackerRange();

    static boca::Luminosity Luminosity();

    static boca::JetType JetType();

    static void SetCollider(boca::Collider collider);

    static boca::Collider Collider();

    static InfoRecombiner& Recombiner();

    static double IsolationFraction();

    static double Experimental();

    static boca::Font Font();

    static boca::Source Source();

    static bool Isolation();

    static bool SubStructure();

private:

    static boca::Collider collider_;

    static InfoRecombiner info_recombiner_;

};

}
