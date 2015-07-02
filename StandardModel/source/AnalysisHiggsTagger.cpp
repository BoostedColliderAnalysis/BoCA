#include "AnalysisHiggsTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

AnalysisHiggs::AnalysisHiggs(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Note();
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::higgs, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::higgs, UpperPtCut());
    pre_cuts().SetPtLowerCut(Id::bottom, LowerPtCut() / 5);
    pre_cuts().SetPtUpperCut(Id::bottom, UpperPtCut() / 5);
    pre_cuts().SetMassUpperCut(Id::higgs, 250);
    pre_cuts().SetTrackerMaxEta(Id::higgs, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry().TrackerEtaMax);
}
std::string AnalysisHiggs::ProjectName() const
{
    return  "HiggsTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-bb";
}

void AnalysisHiggs::SetFiles(const Tag tag)
{
    Note("Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        NewSignalFile(hh_bb);
        if (tagger().name() == "Bottom") NewSignalFile(bb);
        if (tagger().name() == "Bottom") NewSignalFile(tt_had);
        if (tagger().name() == "Bottom") NewSignalFile(tt_lep);
        break;
    case Tag::background :
        if (tagger().name() != "Bottom") NewBackgroundFile(tt_had);
        if (tagger().name() != "Bottom") NewBackgroundFile(tt_lep);
        NewBackgroundFile(zz);
        NewBackgroundFile(ww);
        if (tagger().name() != "Bottom") NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

int AnalysisHiggs::PassPreCut(Event &event)
{
    Info("pass pre cut");

    Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
    if (jets.empty()) return 0;
    if (jets.front().pt() < LowerPtCut()) return 0;

    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;

    return 0;
}

}

}
