# include "AnalysisZTagger.hh"

namespace analysis
{

  namespace standardmodel
{

AnalysisZ::AnalysisZ(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(ZId, LowerPtCut());
    pre_cuts().SetPtUpperCut(ZId, UpperPtCut());
    pre_cuts().SetMassUpperCut(ZId, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(ZId, detector_geometry.TrackerEtaMax);
}

void AnalysisZ::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        NewSignalFile(zz);
        break;
    case kBackground :
        NewBackgroundFile(tthad);
        NewBackgroundFile(hh);
        NewBackgroundFile(ww);
        NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

int AnalysisZ::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if(leptons.empty()) return 1;
    if(leptons.front().pt()<80) return 1;
   return 0;
}
std::string AnalysisZ::ProjectName() const
{
    return  "ZTagger-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-";
}

}

}
