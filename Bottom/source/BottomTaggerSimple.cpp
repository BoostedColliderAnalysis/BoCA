# include "BottomTaggerSimple.hh"

# include "Event.hh"
# include "Reader.hh"

hbtagger::BottomTaggerSimple::BottomTaggerSimple()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Bottom");
    DefineVariables();
}

void hbtagger::BottomTaggerSimple::DefineVariables()
{
    Print(kInformation , "Define Variables");

    ClearVectors();
    AddVariable(branch_.VertexMass, "VertexMass");
    //     AddObservable(branch_.Pt, "Pt");
    //     AddSpectator(branch_.Rap, "Rap");
    //     AddSpectator(branch_.Phi, "Phi");
    AddVariable(branch_.MaxDisplacement, "MaxDisplacement");
    AddVariable(branch_.MeanDisplacement, "MeanDisplacement");
    AddVariable(branch_.SumDisplacement, "SumDisplacement");
    AddVariable(branch_.Multipliticity, "Multipliticity");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.Spread, "Spread");
    AddVariable(branch_.VertexDeltaR, "VertexDeltaR");
    AddVariable(branch_.VertexSpread, "VertexSpread");
    AddVariable(branch_.EnergyFraction, "EnergyFraction");
    //     AddSpectator(branch_.BTag, "BTag");
//
    AddVariable(branch_.Mass, "Mass");
    //     AddSpectator(branch_.Tag, "Tag");
    //     AddSpectator(branch_.Bdt, "Bdt");
}

BottomBranch hbtagger::BottomTaggerSimple::GetBranch(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Fill Branch");

    BottomBranch branch;

    if (!jet.has_user_info<analysis::JetInfo>()) {
        Print(kError, "BJet without user info");
        return branch;
    }

    branch.VertexMass = jet.user_info<analysis::JetInfo>().VertexMass();
    branch.Mass = jet.m();
    branch.Pt = jet.pt();
    branch.Rap = jet.rap();
    branch.Phi = jet.phi();
    float MaxDisp = jet.user_info<analysis::JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) branch.MaxDisplacement = std::log10(MaxDisp);
    else branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<analysis::JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) branch.MeanDisplacement = std::log10(MeanDisp);
    else branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<analysis::JetInfo>().SumDisplacement();
    if (SumDisp > 0) branch.SumDisplacement = std::log10(SumDisp);
    else branch.SumDisplacement = -3;
    branch.Multipliticity = jet.user_info<analysis::JetInfo>().VertexNumber();
    branch.DeltaR = DeltaR(jet);
    branch.Spread = Spread(jet);
    branch.VertexDeltaR = DeltaR(jet.user_info<analysis::JetInfo>().VertexJet());
    branch.VertexSpread = Spread(jet.user_info<analysis::JetInfo>().VertexJet());
    branch.EnergyFraction = jet.user_info<analysis::JetInfo>().VertexEnergy() / jet.e();
//     bottom_branch.BTag = Jet.user_info<analysis::JetInfo>().BTag();
    branch.Tag = jet.user_info<analysis::JetInfo>().Tag();
    branch.Bdt = jet.user_info<analysis::JetInfo>().Bdt();
    Print(kError, "Multiplicity", branch.Multipliticity);
    return branch;
}



int hbtagger::BottomTaggerSimple::Train(analysis::Event &event, const analysis::Object::Tag tag)
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

Jets hbtagger::BottomTaggerSimple::CleanJets(Jets &jets, const Jets &particles, const Tag tag)
{
    Print(kInformation, "Clean Jets");
    for (const auto & particle : particles) {
        jets = SortedByMinDeltaRTo(jets, particle);
        if (jets.front().delta_R(particle) < detector_geometry().JetConeSize) static_cast<analysis::JetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }
    Jets clean_jets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<analysis::JetInfo>())continue;
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
        if (tag == kSignal && Jet.user_info<analysis::JetInfo>().SumDisplacement() == 0) continue;
        Print(kDebug, "Jet Tag", Jet.user_info<analysis::JetInfo>().Tag());
        clean_jets.emplace_back(Jet);
    }
    return clean_jets;
}

int hbtagger::BottomTaggerSimple::GetBdt(analysis::Event &event, const TMVA::Reader &reader)
{
    Jets jets = GetJets(event);
    Jets final_jets;
    Print(kInformation, "Get Jet Bdt");
    for (const auto & jet : jets) {
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (!jet.has_user_info<analysis::JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        branch_ = GetBranch(jet);
        static_cast<analysis::JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(reader));
        final_jets.emplace_back(jet);
    }
    SaveEntries(final_jets);
    return final_jets.size();
}

float hbtagger::BottomTaggerSimple::DeltaR(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "DeltaR");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100)continue;
        Print(kDebug, "Delta R", constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float hbtagger::BottomTaggerSimple::Spread(const fastjet::PseudoJet &jet) const
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
