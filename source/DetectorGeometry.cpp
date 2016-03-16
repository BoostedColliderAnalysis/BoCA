/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "DetectorGeometry.hh"
#include "DEBUG.hh"

namespace boca
{

/**
 * @brief Constructor
 *
 *
 * choose HDetectorType according to LHC or 100TeV
 *
 * LHC: DetectorType::CMS
 * 100TeV: DetectorType::Spp
 *
 */

std::string Name(JetType jet_type)
{
    switch (jet_type) {
    case JetType::jet : return "Jet";
    case JetType::gen_jet : return "GenJet";
    case JetType::e_flow_jet : return "EFlowJet";
        DEFAULT("Jet Type", "");
    }
}

DetectorType DetectorGeometry::detector_type_ = boca::DetectorType::Spp;

InfoRecombiner DetectorGeometry::info_recombiner_ = InfoRecombiner();

std::string Name(DetectorType detector_type)
{
    switch (detector_type) {
    case DetectorType::CMS : return "LHC";
    case DetectorType::Spp : return "100TeV";
        DEFAULT(Name(detector_type), "");
    }
}

InfoRecombiner& DetectorGeometry::Recombiner()
{
    return info_recombiner_;
}

void DetectorGeometry::SetDetectorType(boca::DetectorType detector_type)
{
    detector_type_ = detector_type;
}

boca::DetectorType DetectorGeometry::DetectorType()
{
    return detector_type_;
}

Momentum DetectorGeometry::JetMinPt()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return 20_GeV;
    case boca::DetectorType::Spp : return 40_GeV;
        DEFAULT(Name(DetectorType()), 20_GeV);
    }
}

Angle DetectorGeometry::JetConeSize()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return 0.4_rad;
    case boca::DetectorType::Spp : return 0.4_rad;
        DEFAULT(Name(DetectorType()), 0.5_rad);
    }
}

Angle DetectorGeometry::OverlapConeSize()
{
    return 0.2_rad;
}

Momentum DetectorGeometry::MinCellPt()
{
    return .5_GeV;
}

Angle DetectorGeometry::MinCellResolution()
{
    return .1_rad;
}

Angle DetectorGeometry::TrackerEtaMax()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return 2.5_rad;
    case boca::DetectorType::Spp : return 3.5_rad;
        DEFAULT(Name(DetectorType()), 2.5_rad);
    }
}

fastjet::JetDefinition DetectorGeometry::JetDefinition()
{
    return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize() / rad, &Recombiner());
}

fastjet::JetDefinition DetectorGeometry::JetDefinition(Angle const& jet_cone)
{
    return fastjet::JetDefinition(fastjet::cambridge_aachen_algorithm, jet_cone / rad, &Recombiner());
}


fastjet::JetDefinition DetectorGeometry::SubJetDefinition()
{
    return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize() / rad, &Recombiner());
}

Length DetectorGeometry::TrackerDistanceMin()
{
    return 0.1_mm;
}

Length DetectorGeometry::TrackerDistanceMax()
{
    return 1_m;
}

Mass DetectorGeometry::VertexMassMin()
{
    return 0.1_GeV;
}

Momentum DetectorGeometry::LeptonMinPt()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return 10_GeV;
    case boca::DetectorType::Spp : return 20_GeV;
        DEFAULT(Name(DetectorType()), 10_GeV);
    }
}

Luminosity DetectorGeometry::Luminosity()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS :
        return 3000. / fb;
        return 300. / fb;
    case boca::DetectorType::Spp :
        return 30000. / fb;
        return 3000. / fb;
        DEFAULT(Name(DetectorType()), 3000.  / fb);
    }
}

boca::JetType DetectorGeometry::JetType()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return boca::JetType::jet;
    case boca::DetectorType::Spp : return boca::JetType::jet;
        //         return JetType::e_flow_jet;
        DEFAULT(Name(DetectorType()), boca::JetType::jet);
    }
}

Angle DetectorGeometry::IsolationConeSize()
{
    return 0.3_rad;
}

Momentum DetectorGeometry::HardLeptonMomentum()
{
    switch (DetectorType()) {
    case boca::DetectorType::CMS : return 50_GeV;
    case boca::DetectorType::Spp : return 100_GeV;
        DEFAULT(Name(DetectorType()), 50_GeV);
    }
}

double DetectorGeometry::IsolationFraction()
{
    return 1;
}

Momentum DetectorGeometry::ForwardJetPt()
{
    return 40_GeV;
}

}
