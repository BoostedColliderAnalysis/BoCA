/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Types.hh"
#include "boca/Settings.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

/**
 * @brief Constructor
 *
 *
 * choose HCollider according to LHC or 100TeV
 *
 * LHC: Collider::lhc
 * 100TeV: Collider::future
 *
 */

std::string Name(JetType jet_type)
{
    switch (jet_type) {
    case JetType::jet : return "Jet";
    case JetType::gen_jet : return "GenJet";
    case JetType::e_flow_jet : return "EFlowJet";
        DEFAULT(to_int(jet_type), "");
    }
}

Collider Settings::collider_ = boca::Collider::future;

InfoRecombiner Settings::info_recombiner_ = InfoRecombiner();

std::string Name(Collider collider)
{
    switch (collider) {
    case Collider::lhc : return "LHC";
    case Collider::future : return "100TeV";
        DEFAULT(to_int(collider), "");
    }
}

InfoRecombiner& Settings::Recombiner()
{
    return info_recombiner_;
}

void Settings::SetCollider(boca::Collider collider)
{
    collider_ = collider;
}

boca::Collider Settings::Collider()
{
    return collider_;
}

Momentum Settings::JetMinPt()
{
    switch (Collider()) {
    case boca::Collider::lhc : return 20_GeV;
    case boca::Collider::future : return 40_GeV;
        DEFAULT(Name(Collider()), 20_GeV);
    }
}

Angle Settings::JetConeSize()
{
    switch (Collider()) {
    case boca::Collider::lhc : return 400_mrad;
    case boca::Collider::future : return 400_mrad;
        DEFAULT(Name(Collider()), 500_mrad);
    }
}

Angle Settings::OverlapConeSize()
{
    return 200_mrad;
}

Momentum Settings::MinCellPt()
{
    return 500_MeV;
}

Angle Settings::MinCellResolution()
{
    return 100_mrad;
}

Angle Settings::TrackerEtaMax()
{
    switch (Collider()) {
    case boca::Collider::lhc : return 2.5_rad;
    case boca::Collider::future : return 3.5_rad;
        DEFAULT(Name(Collider()), 2.5_rad);
    }
}

fastjet::JetDefinition Settings::JetDefinition()
{
    return {fastjet::antikt_algorithm, JetConeSize() / rad, &Recombiner()};
}

fastjet::JetDefinition Settings::JetDefinition(Angle const& jet_cone)
{
    return {fastjet::cambridge_aachen_algorithm, jet_cone / rad, &Recombiner()};
}

fastjet::JetDefinition Settings::SubJetDefinition()
{
    return {fastjet::kt_algorithm, JetConeSize() / rad, &Recombiner()};
}

Length Settings::TrackerDistanceMin()
{
    return 100_um;
}

Length Settings::TrackerDistanceMax()
{
    return 1_m;
}

Range< Length > Settings::TrackerRange()
{
    return {TrackerDistanceMin(), TrackerDistanceMax()};
}


Mass Settings::VertexMassMin()
{
    return 100_MeV;
}

Momentum Settings::LeptonMinPt()
{
    switch (Collider()) {
    case boca::Collider::lhc : return 10_GeV;
    case boca::Collider::future : return 20_GeV;
        DEFAULT(Name(Collider()), 10_GeV);
    }
}

Luminosity Settings::Luminosity()
{
    switch (Collider()) {
    case boca::Collider::lhc :
        return 3000. / fb;
        return 300. / fb;
    case boca::Collider::future :
        return 30000. / fb;
        return 3000. / fb;
        DEFAULT(Name(Collider()), 3000.  / fb);
    }
}

boca::JetType Settings::JetType()
{
    switch (Collider()) {
    case boca::Collider::lhc : return boca::JetType::jet;
    case boca::Collider::future : return boca::JetType::jet;
        //         return JetType::e_flow_jet;
        DEFAULT(Name(Collider()), boca::JetType::jet);
    }
}

Angle Settings::IsolationConeSize()
{
    return 300_mrad;
}

Momentum Settings::HardLeptonMomentum()
{
    switch (Collider()) {
    case boca::Collider::lhc : return 50_GeV;
    case boca::Collider::future : return 100_GeV;
        DEFAULT(Name(Collider()), 50_GeV);
    }
}

double Settings::IsolationFraction()
{
    return 300_mU; // aka 30%
}

Momentum Settings::ForwardJetPt()
{
    return 40_GeV;
}

double Settings::Experimental()
{
    // minimal alowed s over b value
    return 10_mU; // aka 1%
    return 100_mU; // aka 10%
}

boca::Font Settings::Font()
{
    return boca::Font::times;
    return boca::Font::helvetica;
}

boca::Source Settings::Source()
{
    return boca::Source::delphes;
    return boca::Source::snowmass;
    return boca::Source::pgs;
    return boca::Source::parton;
}

bool Settings::Isolation()
{
    return true;
    return false;
}

bool Settings::SubStructure()
{
    return true;
    return false;
}


}
