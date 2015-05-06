# include "HBottomTaggerSimple.hh"

# include "HEvent.hh"
# include "Reader.hh"

hbtagger::HBottomTaggerSimple::HBottomTaggerSimple()
{
//     DebugLevel = HDebug;
    Print(HInformation, "Constructor");
    SetTaggerName("Bottom");
    DefineVariables();
}

void hbtagger::HBottomTaggerSimple::DefineVariables()
{
    Print(HInformation , "Define Variables");

    ClearVectors();
    AddObservable(branch_.VertexMass, "VertexMass");
    //     AddObservable(branch_.Pt, "Pt");
    //     AddSpectator(branch_.Rap, "Rap");
    //     AddSpectator(branch_.Phi, "Phi");
    AddObservable(branch_.MaxDisplacement, "MaxDisplacement");
    AddObservable(branch_.MeanDisplacement, "MeanDisplacement");
    AddObservable(branch_.SumDisplacement, "SumDisplacement");
    AddObservable(branch_.Multipliticity, "Multipliticity");
    AddObservable(branch_.DeltaR, "DeltaR");
    AddObservable(branch_.Spread, "Spread");
    AddObservable(branch_.VertexDeltaR, "VertexDeltaR");
    AddObservable(branch_.VertexSpread, "VertexSpread");
    AddObservable(branch_.EnergyFraction, "EnergyFraction");
    //     AddSpectator(branch_.BTag, "BTag");
//
    AddObservable(branch_.Mass, "Mass");
    //     AddSpectator(branch_.Tag, "Tag");
    //     AddSpectator(branch_.Bdt, "Bdt");
}

HBottomBranch hbtagger::HBottomTaggerSimple::GetBranch(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Fill Branch");

    HBottomBranch BottomBranch;

    if (!Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HError, "BJet without user info");
        return BottomBranch;
    }

    BottomBranch.VertexMass = Jet.user_info<hanalysis::HJetInfo>().VertexMass();
    BottomBranch.Mass = Jet.m();
    BottomBranch.Pt = Jet.pt();
    BottomBranch.Rap = Jet.rap();
    BottomBranch.Phi = Jet.phi();
    float MaxDisp = Jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) BottomBranch.MaxDisplacement = std::log10(MaxDisp);
    else BottomBranch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) BottomBranch.MeanDisplacement = std::log10(MeanDisp);
    else BottomBranch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) BottomBranch.SumDisplacement = std::log10(SumDisp);
    else BottomBranch.SumDisplacement = -3;
    BottomBranch.Multipliticity = Jet.user_info<hanalysis::HJetInfo>().VertexNumber();
    BottomBranch.DeltaR = DeltaR(Jet);
    BottomBranch.Spread = Spread(Jet);
    BottomBranch.VertexDeltaR = DeltaR(Jet.user_info<hanalysis::HJetInfo>().VertexJet());
    BottomBranch.VertexSpread = Spread(Jet.user_info<hanalysis::HJetInfo>().VertexJet());
    BottomBranch.EnergyFraction = Jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / Jet.e();
    BottomBranch.BTag = Jet.user_info<hanalysis::HJetInfo>().BTag();
    BottomBranch.Tag = Jet.user_info<hanalysis::HJetInfo>().Tag();
    BottomBranch.Bdt = Jet.user_info<hanalysis::HJetInfo>().Bdt();
    return BottomBranch;
}



int hbtagger::HBottomTaggerSimple::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Get Bottom Tag", tag);
    HJets particles = event.GetParticles()->Generator();
    particles = RemoveIfWrongAbsParticle(particles, BottomId);
    Print(HInformation, "Particle size", particles.size());
    HJets jets = GetJets(event);
    Print(HInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;
    jets = CleanJets(jets, particles, tag);
    Print(HDebug, "Number B Jets", jets.size());
    SaveEntries(jets);
    return jets.size();
}

HJets hbtagger::HBottomTaggerSimple::CleanJets(HJets &jets, const HJets &particles, const Tag tag)
{
    Print(HInformation, "Clean Jets");
    for (const auto & particle : particles) {
      jets = SortedByMinDeltaRTo(jets, particle);
        if (jets.front().delta_R(particle) < detector_geometry().JetConeSize) static_cast<hanalysis::HJetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }
    HJets clean_jets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<hanalysis::HJetInfo>())continue;
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
        if (tag == kSignal && Jet.user_info<hanalysis::HJetInfo>().SumDisplacement() == 0) continue;
        Print(HDebug, "Jet Tag", Jet.user_info<hanalysis::HJetInfo>().Tag());
        clean_jets.emplace_back(Jet);
    }
    return clean_jets;
}

int hbtagger::HBottomTaggerSimple::GetBdt(hanalysis::HEvent &event, const TMVA::Reader &reader)
{
    HJets jets = event.GetJets()->GetJets();
    HJets final_jets;
    Print(HInformation, "Get Jet Bdt");
    for (const auto &jet : jets) {
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (!jet.has_user_info<hanalysis::HJetInfo>()) continue;
        if (jet.m() <= 0) continue;
        branch_ = GetBranch(jet);
        static_cast<hanalysis::HJetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(reader));
        final_jets.emplace_back(jet);
    }
    SaveEntries(final_jets);
    return final_jets.size();
}

float hbtagger::HBottomTaggerSimple::DeltaR(const fastjet::PseudoJet &jet) const
{
    Print(HInformation, "DeltaR");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100)continue;
        Print(HDebug, "Delta R", constituent_delta_r);
        if(constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float hbtagger::HBottomTaggerSimple::Spread(const fastjet::PseudoJet &jet) const
{
    Print(HInformation, "Spread");
    if (!jet.has_constituents()) return 0;
    float delta_r = DeltaR(jet);
    if (delta_r == 0) return 0;
    float spread = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        spread += constituent_delta_r * constituent.pt();
    }
    return spread / jet.pt() / delta_r;
}
