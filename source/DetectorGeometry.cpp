/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace boca {

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
    Default("Detector Type","");
  }
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
    case DetectorType::CMS : return 20. * GeV;
    case DetectorType::Spp : return 40. * GeV;
    Default("Detector Type", 20. * GeV);
    }
}

Angle DetectorGeometry::JetConeSize()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.4 * rad;
    case DetectorType::Spp : return 0.5 * rad;
    Default("Detector Type", 0.5 * rad);
    }
}

Momentum DetectorGeometry::MinCellPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .5 * GeV;
    case DetectorType::Spp : return .5 * GeV;
    Default("Detector Type", .5 * GeV);
    }
}

Angle DetectorGeometry::MinCellResolution()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .1 * rad;
    case DetectorType::Spp : return .1 * rad;
    Default("Detector Type", .1 * rad);
    }
}

Angle DetectorGeometry::TrackerEtaMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 2.5 * rad;
    case DetectorType::Spp : return 3.5 * rad;
    Default("Detector Type", 2.5 * rad);
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
    case DetectorType::CMS : return 0.1 * mm;
    case DetectorType::Spp : return 0.1 * mm;
    Default("Detector Type", 0.1 * mm);
    }
}

Length DetectorGeometry::TrackerDistanceMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 1. * m;
    case DetectorType::Spp : return 1. * m;
    Default("Detector Type", 1. * m);
    }
}

Mass DetectorGeometry::VertexMassMin()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.1 * GeV;
    case DetectorType::Spp : return 0.1 * GeV;
    Default("Detector Type", 0.1 * GeV);
    }
}

Momentum DetectorGeometry::LeptonMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 10. * GeV;
    case DetectorType::Spp : return 20. * GeV;
    Default("Detector Type", 10. * GeV);
    }
}

Luminosity DetectorGeometry::Luminosity()
{
  switch (detector_type()) {
    case DetectorType::CMS : return 300. / fb;
    case DetectorType::Spp : return 3000. / fb;
    Default("Detector Type", 300.  / fb );
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
