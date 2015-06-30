#include "AnalysisBottomTagger.hh"

namespace analysis
{

  namespace standardmodel
{

AnalysisBottom::AnalysisBottom(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Print(Severity::notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::bottom, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::bottom, UpperPtCut());
    DetectorGeometry detector_geometry;
    pre_cuts().SetTrackerMaxEta(Id::bottom, detector_geometry.TrackerEtaMax);
    pre_cuts().SetSubJets(false);
}

void AnalysisBottom::SetFiles(const Tag tag)
{
    Print(Severity::notification, "Set File Vector", Name(tag));

    switch (tag) {
    case Tag::signal :
        NewSignalFile(bb);
//     NewSignalFile(tt);
//     NewBackgroundFile(bb);
        break;
    case Tag::background :
        NewBackgroundFile(cc);
//     NewBackgroundFile(tt);
//     NewBackgroundFile(ttcc);
//     NewBackgroundFile(ttjj);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
        NewBackgroundFile(ww);
        break;
    }

}

std::string AnalysisBottom::ProductionChannelName(const ProductionChannel production_channel) const
{
    switch (production_channel) {
    case Associated :
        return "llbb_";
    case DYP :
        return "pp_z_";
    case VBF :
        return "VBF_";
    default:
        return "";
    }
}

int AnalysisBottom::PassPreCut(Event &event)
{
    Print(Severity::information, "pass pre cut");
    Jets jets = event.Hadrons().Jets();
    jets = remove_if_not_in_pt_window(jets, LowerPtCut(), UpperPtCut());
    return jets.size();
}
std::string AnalysisBottom::ProjectName() const
{
    return  ProductionChannelName(production_channel()) + ColliderName(collider_type()) + "_" + std::to_string(MadGraphCut()) + "GeV";
}
AnalysisBottom::ProductionChannel AnalysisBottom::production_channel() const
{
    return DYP;
    //         return VBF;
//         return Associated;
}

}

}
