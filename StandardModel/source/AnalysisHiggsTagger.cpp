# include "AnalysisHiggsTagger.hh"

namespace analysis
{

  namespace standardmodel
{

  AnalysisHiggs::AnalysisHiggs(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(HiggsId, LowerPtCut());
    pre_cuts().SetPtUpperCut(HiggsId, UpperPtCut());
    pre_cuts().SetMassUpperCut(HiggsId, 250);
//     DetectorGeometry detector_geometry;
    //     pre_cuts().SetTrackerMaxEta(HiggsId, detector_geometry.TrackerEtaMax);
}
std::string AnalysisHiggs::ProjectName() const
{
    return  "HiggsTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-";
}

std::string AnalysisHiggs::ClassName() const{
  return "AnalysisHiggs";
}

void AnalysisHiggs::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        NewSignalFile(hh);
        break;
    case kBackground :
        NewBackgroundFile(tthad);
        NewBackgroundFile(zz);
        NewBackgroundFile(ww);
        NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

int AnalysisHiggs::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");

    Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
    if (jets.empty()) return 0;
    if (jets.front().pt() < LowerPtCut()) return 0;

//     Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
//     if (leptons.empty()) return 1;
//     if (leptons.front().pt() < 80) return 1;
//     return 0;

    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, HiggsId));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) return 0;
    if ((particles.at(0).pt() > LowerPtCut() && particles.at(0).pt() < UpperPtCut()) && (particles.at(1).pt() > LowerPtCut() &&  particles.at(1).pt() < UpperPtCut())) return 1;

    return 1;
}

}

}
