# include "AnalysisBottomTagger.hh"

namespace analysis
{

  namespace standardmodel
{

AnalysisBottom::AnalysisBottom(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(BottomId, LowerPtCut());
    pre_cuts().SetPtUpperCut(BottomId, UpperPtCut());
    DetectorGeometry detector_geometry;
    pre_cuts().SetTrackerMaxEta(BottomId, detector_geometry.TrackerEtaMax);
    pre_cuts().SetSubJets(false);
}

void AnalysisBottom::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    switch (tag) {
    case kSignal :
        NewSignalFile(bb);
//     NewSignalFile(tt);
//     NewBackgroundFile(bb);
        break;
    case kBackground :
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
    Print(kInformation, "pass pre cut");
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
