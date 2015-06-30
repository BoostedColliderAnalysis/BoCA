#include "AnalysisWTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

AnalysisW::AnalysisW(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Severity::debug;
    Note("Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::W, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::W, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(Id::top, detector_geometry.TrackerEtaMax);
}

void AnalysisW::SetFiles(const Tag tag)
{
    Note("Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        NewSignalFile(ww);
        break;
    case Tag::background :
        NewBackgroundFile(tt_lep);
        NewBackgroundFile(tt_had);
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
    Info("pass pre cut");
//     Jets particles = event.Partons().GenParticles();
//     Jets w = fastjet::sorted_by_pt(copy_if_abs_particle(particles, Id::W));
//     remove_if_not_in_pt_window(w, PreCut(), UpperCut());
    return 1;
}
Decay AnalysisW::WDecay() const
{
    return Decay::hadronic;
    //         return Decay::semi;
}
std::string AnalysisW::ProjectName() const
{
    return  "WTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "";
}

}

}
