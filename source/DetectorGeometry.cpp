/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "DetectorGeometry.hh"
#include "Debug.hh"

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

DetectorType DetectorGeometry::detector_type_ = DetectorType::Spp;

InfoRecombiner DetectorGeometry::info_recombiner_ = InfoRecombiner();


std::string Name(DetectorType detector_type)
{
    switch (detector_type) {
    case DetectorType::CMS : return "LHC";
    case DetectorType::Spp : return "100TeV";
        Default("Detector Type", "");
    }
}

InfoRecombiner& DetectorGeometry::Recombiner()
{
    return info_recombiner_;
}

void DetectorGeometry::set_detector_type(DetectorType detector_type)
{
    detector_type_ = detector_type;
}

DetectorType DetectorGeometry::detector_type()
{
    return detector_type_;
}

Momentum DetectorGeometry::JetMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 20_GeV;
    case DetectorType::Spp : return 40_GeV;
        Default("Detector Type", 20_GeV);
    }
}

Angle DetectorGeometry::JetConeSize()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.4_rad;
    case DetectorType::Spp : return 0.5_rad;
        Default("Detector Type", 0.5_rad);
    }
}

Momentum DetectorGeometry::MinCellPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .5_GeV;
    case DetectorType::Spp : return .5_GeV;
        Default("Detector Type", .5_GeV);
    }
}

Angle DetectorGeometry::MinCellResolution()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .1_rad;
    case DetectorType::Spp : return .1_rad;
        Default("Detector Type", .1_rad);
    }
}

Angle DetectorGeometry::TrackerEtaMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 2.5_rad;
    case DetectorType::Spp : return 3.5_rad;
        Default("Detector Type", 2.5_rad);
    }
}

fastjet::JetDefinition DetectorGeometry::JetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS : return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize() / rad, &info_recombiner_);
    case DetectorType::Spp : return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize() / rad, &info_recombiner_);
        Default("Detector Type", {});
    }
}

fastjet::JetDefinition DetectorGeometry::JetDefinition(Angle const& jet_cone)
{
//     Error(info_recombiner_.description());
    return fastjet::JetDefinition(fastjet::cambridge_aachen_algorithm, jet_cone / rad, &info_recombiner_);
}


fastjet::JetDefinition DetectorGeometry::SubJetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS : return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize() / rad, &info_recombiner_);
    case DetectorType::Spp : return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize() / rad, &info_recombiner_);
        Default("Detector Type", {});
    }
}

Length DetectorGeometry::TrackerDistanceMin()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.1_mm;
    case DetectorType::Spp : return 0.1_mm;
        Default("Detector Type", 0.1_mm);
    }
}

Length DetectorGeometry::TrackerDistanceMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 1_m;
    case DetectorType::Spp : return 1_m;
        Default("Detector Type", 1_m);
    }
}

Mass DetectorGeometry::VertexMassMin()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.1_GeV;
    case DetectorType::Spp : return 0.1_GeV;
        Default("Detector Type", 0.1_GeV);
    }
}

Momentum DetectorGeometry::LeptonMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 10_GeV;
    case DetectorType::Spp : return 20_GeV;
        Default("Detector Type", 10_GeV);
    }
}

Luminosity DetectorGeometry::Luminosity()
{
    switch (detector_type()) {
    case DetectorType::CMS :
        return 3000. / fb;
        return 300. / fb;
    case DetectorType::Spp : return 3000. / fb;
        Default("Detector Type", 300.  / fb);
    }
}
JetType DetectorGeometry::jet_type()
{
    switch (detector_type()) {
    case DetectorType::CMS : return JetType::jet;
    case DetectorType::Spp : return JetType::jet;
        //         return JetType::e_flow_jet;
        Default("Detector Type", JetType::jet);
    }
}

}
