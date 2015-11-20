#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace analysis {

  std::string Name(DetectorType detector_type){
    switch(detector_type){
      case DetectorType::CMS : return "CMS";
      case DetectorType::Spp : return "Spp";
    }
  }
  
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


void DetectorGeometry::set_detector_type(const DetectorType detector_type)
{
  detector_type_ = detector_type;
}

DetectorType DetectorGeometry::detector_type()
{
  return detector_type_;
//     return DetectorType::CMS;
//     return DetectorType::Spp;
}

float DetectorGeometry::JetMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 20;
    case DetectorType::Spp:
        return 40;
    }
}
float DetectorGeometry::JetConeSize()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.5;
    case DetectorType::Spp:
        return 0.5;
    }
}
float DetectorGeometry::IsolationConeSize()
{
  switch (detector_type()) {
    case DetectorType::CMS:
      return 0.3;
    case DetectorType::Spp:
      return 0.3;
  }
}
float DetectorGeometry::HardLeptonMomentum()
{
  switch (detector_type()) {
    case DetectorType::CMS:
      return 50;
    case DetectorType::Spp:
      return 100;
  }
}
float DetectorGeometry::IsolationFraction()
{
  switch (detector_type()) {
    case DetectorType::CMS:
      return 1;
    case DetectorType::Spp:
      return 1;
  }
}
float DetectorGeometry::MinCellPt()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return .5;
    case DetectorType::Spp:
        return .5;
    }
}
float DetectorGeometry::MinCellResolution()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return .1;
    case DetectorType::Spp:
        return.1 ;
    }
}
float DetectorGeometry::TrackerEtaMax()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 2.5;
    case DetectorType::Spp:
        return 3.5;
    }
}

float DetectorGeometry::ForwardJetPt()
{
  switch (detector_type()) {
    case DetectorType::CMS:
      return 40;
    case DetectorType::Spp:
      return 40;
  }
}
// float DetectorGeometry::JetRadiusParameter()
// {
//     switch (detector_type()) {
//     case DetectorType::CMS:
//         return ;
//     case DetectorType::Spp:
//         return ;
//     }
// }
fastjet::JetDefinition DetectorGeometry::JetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS:
      return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize(), &info_recombiner_);
    case DetectorType::Spp:
      return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize(), &info_recombiner_);
    }
}
fastjet::JetDefinition DetectorGeometry::SubJetDefinition()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize(), &info_recombiner_);
    case DetectorType::Spp:
        return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize(), &info_recombiner_);
    }
}

float DetectorGeometry::TrackerDistanceMin()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.1;
    case DetectorType::Spp:
        return 0.1;
    }
}
float DetectorGeometry::TrackerDistanceMax()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 1000;
    case DetectorType::Spp:
        return 1000;
    }
}
float DetectorGeometry::VertexMassMin()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.1;
    case DetectorType::Spp:
        return 0.1;
    }
}
float DetectorGeometry::LeptonMinPt()
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 10;
    case DetectorType::Spp:
        return 20;
    }
}
/// in femtobarn
float DetectorGeometry::Luminosity()
{
  switch (detector_type()) {
    case DetectorType::CMS:
      return 3000;
    case DetectorType::Spp:
      return 3000;
  }
}
JetType DetectorGeometry::jet_type()
{
    switch (detector_type()) {
    case DetectorType::CMS:
//         return JetType::jet;
        return JetType::e_flow_jet;
    case DetectorType::Spp:
        return JetType::jet;
//         return JetType::e_flow_jet;
    }
}

}
