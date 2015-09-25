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
    }
}

float DetectorGeometry::JetConeSize()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.4;
    case DetectorType::Spp : return 0.5;
    }
}

Momentum DetectorGeometry::MinCellPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .5 * GeV;
    case DetectorType::Spp : return .5 * GeV;
    }
}

float DetectorGeometry::MinCellResolution()
{
    switch (detector_type()) {
    case DetectorType::CMS : return .1;
    case DetectorType::Spp : return .1 ;
    }
}

float DetectorGeometry::TrackerEtaMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 2.5;
    case DetectorType::Spp : return 3.5;
    }
}

fastjet::JetDefinition DetectorGeometry::JetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS : return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize(), &info_recombiner_);
    case DetectorType::Spp : return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize(), &info_recombiner_);
    }
}

fastjet::JetDefinition DetectorGeometry::SubJetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS : return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize(), &info_recombiner_);
    case DetectorType::Spp : return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize(), &info_recombiner_);
    }
}

float DetectorGeometry::TrackerDistanceMin()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.1;
    case DetectorType::Spp : return 0.1;
    }
}

float DetectorGeometry::TrackerDistanceMax()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 1000;
    case DetectorType::Spp : return 1000;
    }
}

Mass DetectorGeometry::VertexMassMin()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 0.1 * GeV;
    case DetectorType::Spp : return 0.1 * GeV;
    }
}

Momentum DetectorGeometry::LeptonMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS : return 10. * GeV;
    case DetectorType::Spp : return 20. * GeV;
    }
}

Luminosity DetectorGeometry::Luminosity()
{
  switch (detector_type()) {
    case DetectorType::CMS : return 300. / fb;
    case DetectorType::Spp : return 3000. / fb;
  }
}
JetType DetectorGeometry::jet_type()
{
    switch (detector_type()) {
    case DetectorType::CMS : return JetType::jet;
    case DetectorType::Spp : return JetType::jet;
//         return JetType::e_flow_jet;
    }
}

}
