# include "AnalysisWTagger.hh"

namespace analysis
{

  namespace standardmodel
{

  AnalysisW::AnalysisW(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::Severity::Debug;
    Print(Severity::Notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::W, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::W, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(Id::Top, detector_geometry.TrackerEtaMax);
}

void AnalysisW::SetFiles(const Tag tag)
{
    Print(Severity::Notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::Signal :
        NewSignalFile(ww);
        break;
    case Tag::Background :
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
    Print(Severity::Information, "pass pre cut");
//     Jets particles = event.Partons().GenParticles();
//     Jets w = fastjet::sorted_by_pt(copy_if_abs_particle(particles, Id::W));
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
