#pragma once

#include "fastjet/JetDefinition.hh"

namespace analysis {

enum class JetType {
    jet, gen_jet, e_flow_jet
};

enum class DetectorType {
    CMS, Spp
};

class DetectorGeometry {
public:
    static float JetMinPt();
    static float JetConeSize();
    static float MinCellPt();
    static float MinCellResolution();
    static float TrackerEtaMax();
//     static float JetRadiusParameter();
    static fastjet::JetDefinition JetDefinition();
    static fastjet::JetDefinition SubJetDefinition();
    static float TrackerDistanceMin();
    static float TrackerDistanceMax();
    static float VertexMassMin();
    static float LeptonMinPt();
    static JetType jet_type();
private:
    static DetectorType detector_type();
};

}
