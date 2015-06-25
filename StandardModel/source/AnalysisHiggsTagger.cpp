# include "AnalysisHiggsTagger.hh"

namespace analysis
{

namespace standardmodel
{

AnalysisHiggs::AnalysisHiggs(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::Severity::Debug;
    Print(Severity::Notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::Higgs, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::Higgs, UpperPtCut());
    pre_cuts().SetPtLowerCut(Id::Bottom, LowerPtCut() / 5);
    pre_cuts().SetPtUpperCut(Id::Bottom, UpperPtCut() / 5);
    pre_cuts().SetMassUpperCut(Id::Higgs, 250);
    pre_cuts().SetTrackerMaxEta(Id::Higgs, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetTrackerMaxEta(Id::Bottom, DetectorGeometry().TrackerEtaMax);
}
std::string AnalysisHiggs::ProjectName() const
{
    return  "HiggsTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-";
}

std::string AnalysisHiggs::ClassName() const
{
    return "AnalysisHiggs";
}

void AnalysisHiggs::SetFiles(const Tag tag)
{
    Print(Severity::Notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::Signal :
        NewSignalFile(hh);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(bb);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(tthad);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(ttlep);
        break;
    case Tag::Background :
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(tthad);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(ttlep);
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
    Print(Severity::Information, "pass pre cut");

    Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
    if (jets.empty()) return 0;
    if (jets.front().pt() < LowerPtCut()) return 0;

    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;

    return 0;
}

}

}
