# include "AnalysisWTagger.hh"

namespace analysis
{

  namespace standardmodel
{

  AnalysisW::AnalysisW(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(WId, LowerPtCut());
    pre_cuts().SetPtUpperCut(WId, UpperPtCut());
    pre_cuts().SetMassUpperCut(WId, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(TopId, detector_geometry.TrackerEtaMax);
}

void AnalysisW::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        NewSignalFile(ww);
        break;
    case kBackground :
        NewBackgroundFile(ttlep);
        NewBackgroundFile(tthad);
        NewBackgroundFile(hh);
        NewBackgroundFile(zz);
        NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

int AnalysisW::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
//     Jets particles = event.Partons().GenParticles();
//     Jets w = fastjet::sorted_by_pt(copy_if_abs_particle(particles, WId));
//     remove_if_not_in_pt_window(w, PreCut(), UpperCut());
    return 1;
}
AnalysisW::Decay AnalysisW::WDecay() const
{
    return kHadronic;
    //         return kLeptonic;
    //         return kSemi;
}
std::string AnalysisW::ProjectName() const
{
    return  "WTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "";
}

}

}
