# include "AnalysisZTagger.hh"

namespace analysis
{

  namespace standardmodel
{

AnalysisZ::AnalysisZ(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Severity::debug;
    Print(Severity::notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::Z, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::Z, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::Z, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(Id::Z, detector_geometry.TrackerEtaMax);
}

void AnalysisZ::SetFiles(const Tag tag)
{
    Print(Severity::notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        NewSignalFile(zz);
        break;
    case Tag::background :
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
    Print(Severity::information, "pass pre cut");
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
