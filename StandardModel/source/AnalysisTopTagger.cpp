# include "AnalysisTopTagger.hh"

namespace analysis
{

namespace standardmodel
{

TopAnalysis::TopAnalysis(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::Severity::Debug;
    Print(Severity::Notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::Top, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::Top, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::Top, 400);
    pre_cuts().SetTrackerMaxEta(Id::Top, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetPtLowerCut(Id::Bottom, LowerPtCut() / 5);
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut() / 5);
}

std::string TopAnalysis::ClassName() const
{
    return "AnalysisTop";
}

std::string TopAnalysis::ProjectName() const
{
    return  "TopTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "-test2";
}

TopAnalysis::Decay TopAnalysis::TopDecay() const
{
    return kHadronic;
//         return kLeptonic;
//         return kSemi;
}

void TopAnalysis::SetFiles(const Tag tag)
{
    Print(Severity::Notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::Signal :
        if (TopDecay() == kHadronic || tagger().tagger_name() == "Bottom") NewSignalFile(tthad);
        if (TopDecay() == kLeptonic || tagger().tagger_name() == "Bottom") NewSignalFile(ttlep);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(hh);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(bb);
        if (tagger().tagger_name() == "WHadronic") NewSignalFile(ww);
        break;
    case Tag::Background :
        if (TopDecay() == kHadronic && tagger().tagger_name() != "Bottom") NewBackgroundFile(ttlep);
        if (TopDecay() == kLeptonic && tagger().tagger_name() != "Bottom") NewBackgroundFile(tthad);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(hh);
        NewBackgroundFile(zz);
        if (tagger().tagger_name() != "WHadronic") NewBackgroundFile(ww);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

int TopAnalysis::PassPreCut(Event &event)
{
    Print(Severity::Information, "pass pre cut");
    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, Id::Top));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) Print(Severity::Error, "just one top");
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;
    return 0;
}

}

}
