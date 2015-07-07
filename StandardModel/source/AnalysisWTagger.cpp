#include "AnalysisWTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

AnalysisW::AnalysisW(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Note();
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::W, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::W, 200);
    //     pre_cuts().SetTrackerMaxEta(Id::top, DetectorGeometry().TrackerEtaMax);
}

void AnalysisW::SetFiles(const Tag tag)
{
    Note("Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
      NewFile(tag ,Process::ww);
        break;
    case Tag::background :
      NewFile(tag ,Process::tt_lep);
      NewFile(tag ,Process::tt_had);
      NewFile(tag ,Process::hh);
      NewFile(tag ,Process::zz);
      NewFile(tag ,Process::bb);
      NewFile(tag ,Process::cc);
      NewFile(tag ,Process::qq);
      NewFile(tag ,Process::gg);
        break;
    }
}

int AnalysisW::PassPreCut(const Event &event)
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
  return  "WTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(Process::tt) + "";
}

}

}
