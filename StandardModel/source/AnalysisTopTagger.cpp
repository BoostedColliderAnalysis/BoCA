# include "AnalysisTopTagger.hh"

namespace analysis
{

namespace standardmodel
{

TopAnalysis::TopAnalysis(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
//   DebugLevel = Severity::debug;
    Print(Severity::notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::top, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::top, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::top, 400);
    pre_cuts().SetTrackerMaxEta(Id::top, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetPtLowerCut(Id::bottom, LowerPtCut() / 5);
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut() / 5);
}

std::string TopAnalysis::ClassName() const
{
    return "AnalysisTop";
}

std::string TopAnalysis::ProjectName() const
{
    return  "TopTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "-" + DecayName(TopDecay()) + "";
}

Decay TopAnalysis::TopDecay() const
{
    //         return Decay::hadronic;
    return Decay::leptonic;
    //         return Decay::semi;

}

std::string TopAnalysis::DecayName(const Decay decay) const
{
    switch (decay) {
    case Decay::hadronic :
        return "hadronic";
    case Decay::leptonic :
        return "leptonic";
    case Decay::semi :
        return "semi";
    }
}

void TopAnalysis::SetFiles(const Tag tag)
{
    Print(Severity::notification, "Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        if (TopDecay() == Decay::hadronic || tagger().tagger_name() == "Bottom") NewSignalFile(tthad);
        if (TopDecay() == Decay::leptonic || tagger().tagger_name() == "Bottom") NewSignalFile(ttlep);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(hh);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(bb);
        if (tagger().tagger_name() == "WHadronic") NewSignalFile(ww);
        break;
    case Tag::background :
        if (TopDecay() == Decay::hadronic && tagger().tagger_name() != "Bottom") NewBackgroundFile(ttlep);
        if (TopDecay() == Decay::leptonic && tagger().tagger_name() != "Bottom") NewBackgroundFile(tthad);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(hh);
  //      NewBackgroundFile(zz);
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
    Print(Severity::information, "pass pre cut");
    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, Id::top));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) Print(Severity::error, "just one top");
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;
    return 0;
}

}

}
