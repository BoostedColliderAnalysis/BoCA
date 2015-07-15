#pragma once

#include "fastjet/JetDefinition.hh"

namespace analysis
{

enum class JetType
{
    jet, gen_jet, e_flow_jet
};

enum class DetectorType
{
  CMS, Spp
};

class DetectorGeometry
{
public:
    float JetMinPt() const;
    float JetConeSize() const;
    float MinCellPt() const;
    float MinCellResolution() const;
    float TrackerEtaMax() const;
//     float JetRadiusParameter() const;
    fastjet::JetDefinition JetDefinition() const;
    fastjet::JetDefinition SubJetDefinition() const;
    float TrackerDistanceMin() const;
    float TrackerDistanceMax() const;
    float VertexMassMin() const;
    float LeptonMinPt() const;
    JetType jet_type() const;
private:
    DetectorType detector_type() const;
};

}
