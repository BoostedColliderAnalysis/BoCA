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
    pre_cuts().SetPtLowerCut(BottomId, LowerPtCut() / 5);
    pre_cuts().SetPtUpperCut(BottomId, UpperPtCut() / 5);
    pre_cuts().SetMassUpperCut(HiggsId, 250);
    pre_cuts().SetTrackerMaxEta(HiggsId, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetTrackerMaxEta(BottomId, DetectorGeometry().TrackerEtaMax);
}
std::string AnalysisHiggs::ProjectName() const
{
    return  "HiggsTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-";
}

std::string AnalysisHiggs::ClassName() const
{
    return "AnalysisHiggs";
}

void AnalysisHiggs::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        NewSignalFile(hh);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(bb);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(tthad);
        break;
    case kBackground :
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(tthad);
        NewBackgroundFile(zz);
        NewBackgroundFile(ww);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(bb);
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

    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;

    return 0;
}

}

}
