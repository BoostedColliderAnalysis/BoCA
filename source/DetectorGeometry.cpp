#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace analysis
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

DetectorType DetectorGeometry::detector_type() const
{
//     return DetectorType::CMS;
    return DetectorType::Spp;
}

float DetectorGeometry::JetMinPt() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 20;
    case DetectorType::Spp:
        return 40;
    }
}
float DetectorGeometry::JetConeSize() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.5;
    case DetectorType::Spp:
        return 0.5;
    }
}
float DetectorGeometry::MinCellPt() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return .5;
    case DetectorType::Spp:
        return .5;
    }
}
float DetectorGeometry::MinCellResolution() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return .1;
    case DetectorType::Spp:
        return.1 ;
    }
}
float DetectorGeometry::TrackerEtaMax() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 2.5;
    case DetectorType::Spp:
        return 3.5;
    }
}
// float DetectorGeometry::JetRadiusParameter() const
// {
//     switch (detector_type()) {
//     case DetectorType::CMS:
//         return ;
//     case DetectorType::Spp:
//         return ;
//     }
// }
fastjet::JetDefinition DetectorGeometry::JetDefinition() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize());
    case DetectorType::Spp:
        return fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize());
    }
}
fastjet::JetDefinition DetectorGeometry::SubJetDefinition() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize());
    case DetectorType::Spp:
        return fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize());
    }
}
float DetectorGeometry::TrackerDistanceMin() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.1;
    case DetectorType::Spp:
        return 0.1;
    }
}
float DetectorGeometry::TrackerDistanceMax() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 1000;
    case DetectorType::Spp:
        return 1000;
    }
}
float DetectorGeometry::VertexMassMin() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 0.1;
    case DetectorType::Spp:
        return 0.1;
    }
}
float DetectorGeometry::LeptonMinPt() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return 10;
    case DetectorType::Spp:
        return 20;
    }
}
JetType DetectorGeometry::jet_type() const
{
    switch (detector_type()) {
    case DetectorType::CMS:
        return JetType::jet;
    case DetectorType::Spp:
        return JetType::jet;
//         return JetType::e_flow_jet;
    }
}

}
