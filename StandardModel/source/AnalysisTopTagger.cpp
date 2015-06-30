#include "AnalysisTopTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace standardmodel
{

TopAnalysis::TopAnalysis(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Note("Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::top, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::top, UpperPtCut());
    pre_cuts().SetMassUpperCut(Id::top, 400);
    pre_cuts().SetTrackerMaxEta(Id::top, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetPtLowerCut(Id::bottom, LowerPtCut() / 5);
    pre_cuts().SetPtLowerCut(Id::W, LowerPtCut() / 5);
}

std::string TopAnalysis::ProjectName() const
{
    return  "TopTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "-" + DecayName(TopDecay()) + "-sorted";
}

Decay TopAnalysis::TopDecay() const
{
            return Decay::hadronic;
//     return Decay::leptonic;
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
    Note("Set File Vector", Name(tag));
    switch (tag) {
    case Tag::signal :
        if (TopDecay() == Decay::hadronic || tagger().name() == "Bottom") NewSignalFile(tt_had);
        if (tagger().name() == "Bottom") NewSignalFile(hh);
        if (tagger().name() == "Bottom") NewSignalFile(bb);
        if (TopDecay() == Decay::leptonic || tagger().name() == "Bottom") NewSignalFile(tt_lep);
        if (tagger().name() == "WHadronic") NewSignalFile(ww);
        break;
    case Tag::background :
        if (TopDecay() == Decay::leptonic && tagger().name() != "Bottom") NewBackgroundFile(tt_had);
        if (tagger().name() != "Bottom") NewBackgroundFile(hh);
        if (tagger().name() != "Bottom") NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(gg);
        NewBackgroundFile(qq);
        if (TopDecay() == Decay::hadronic && tagger().name() != "Bottom") NewBackgroundFile(tt_lep);
        NewBackgroundFile(zz);
        if (tagger().name() != "WHadronic") NewBackgroundFile(ww);
        break;
    }

}

int TopAnalysis::PassPreCut(Event &event)
{
    Info("pass pre cut");
    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, Id::top));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) Error("just one top");
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;
    return 0;
}

}

}
