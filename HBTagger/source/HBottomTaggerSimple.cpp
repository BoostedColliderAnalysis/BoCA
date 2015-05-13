# include "HBottomTaggerSimple.hh"

# include "Event.hh"
# include "Reader.hh"

hbtagger::HBottomTaggerSimple::HBottomTaggerSimple()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    SetTaggerName("Bottom");
    DefineVariables();
}

void hbtagger::HBottomTaggerSimple::DefineVariables()
{
    Print(kInformation , "Define Variables");

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

BottomBranch hbtagger::HBottomTaggerSimple::GetBranch(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Fill Branch");

    BottomBranch bottom_branch;

    if (!Jet.has_user_info<hanalysis::JetInfo>()) {
        Print(kError, "BJet without user info");
        return bottom_branch;
    }

    bottom_branch.VertexMass = Jet.user_info<hanalysis::JetInfo>().VertexMass();
    bottom_branch.Mass = Jet.m();
    bottom_branch.Pt = Jet.pt();
    bottom_branch.Rap = Jet.rap();
    bottom_branch.Phi = Jet.phi();
    float MaxDisp = Jet.user_info<hanalysis::JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) bottom_branch.MaxDisplacement = std::log10(MaxDisp);
    else bottom_branch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<hanalysis::JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) bottom_branch.MeanDisplacement = std::log10(MeanDisp);
    else bottom_branch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<hanalysis::JetInfo>().SumDisplacement();
    if (SumDisp > 0) bottom_branch.SumDisplacement = std::log10(SumDisp);
    else bottom_branch.SumDisplacement = -3;
    bottom_branch.Multipliticity = Jet.user_info<hanalysis::JetInfo>().VertexNumber();
    bottom_branch.DeltaR = DeltaR(Jet);
    bottom_branch.Spread = Spread(Jet);
    bottom_branch.VertexDeltaR = DeltaR(Jet.user_info<hanalysis::JetInfo>().VertexJet());
    bottom_branch.VertexSpread = Spread(Jet.user_info<hanalysis::JetInfo>().VertexJet());
    bottom_branch.EnergyFraction = Jet.user_info<hanalysis::JetInfo>().VertexEnergy() / Jet.e();
    bottom_branch.BTag = Jet.user_info<hanalysis::JetInfo>().BTag();
    bottom_branch.Tag = Jet.user_info<hanalysis::JetInfo>().Tag();
    bottom_branch.Bdt = Jet.user_info<hanalysis::JetInfo>().Bdt();
    return bottom_branch;
}



int hbtagger::HBottomTaggerSimple::Train(hanalysis::Event &event, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get Bottom Tag", tag);
    Jets particles = event.Partons().Generator();
    particles = RemoveIfWrongAbsParticle(particles, BottomId);
    Print(kInformation, "Particle size", particles.size());
    Jets jets = GetJets(event);
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;
    jets = CleanJets(jets, particles, tag);
    Print(kDebug, "Number B Jets", jets.size());
    SaveEntries(jets);
    return jets.size();
}

Jets hbtagger::HBottomTaggerSimple::CleanJets(Jets &jets, const Jets &particles, const Tag tag)
{
    Print(kInformation, "Clean Jets");
    for (const auto & particle : particles) {
      jets = SortedByMinDeltaRTo(jets, particle);
        if (jets.front().delta_R(particle) < detector_geometry().JetConeSize) static_cast<hanalysis::JetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }
    Jets clean_jets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<hanalysis::JetInfo>())continue;
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
        if (tag == kSignal && Jet.user_info<hanalysis::JetInfo>().SumDisplacement() == 0) continue;
        Print(kDebug, "Jet Tag", Jet.user_info<hanalysis::JetInfo>().Tag());
        clean_jets.emplace_back(Jet);
    }
    return clean_jets;
}

int hbtagger::HBottomTaggerSimple::GetBdt(hanalysis::Event &event, const TMVA::Reader &reader)
{
    Jets jets = event.Hadrons().GetJets();
    Jets final_jets;
    Print(kInformation, "Get Jet Bdt");
    for (const auto &jet : jets) {
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (!jet.has_user_info<hanalysis::JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        branch_ = GetBranch(jet);
        static_cast<hanalysis::JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(reader));
        final_jets.emplace_back(jet);
    }
    SaveEntries(final_jets);
    return final_jets.size();
}

float hbtagger::HBottomTaggerSimple::DeltaR(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "DeltaR");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100)continue;
        Print(kDebug, "Delta R", constituent_delta_r);
        if(constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float hbtagger::HBottomTaggerSimple::Spread(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Spread");
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
