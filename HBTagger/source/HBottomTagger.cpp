# include "HBottomTaggerSimple.hh"

# include "HEvent.hh"
# include "HReader.hh"

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
//     AddObservable(Branch.Pt, "Pt");
//     AddSpectator(Branch.Rap, "Rap");
//     AddSpectator(Branch.Phi, "Phi");
    AddObservable(branch_.MaxDisplacement, "MaxDisplacement");
    AddObservable(branch_.MeanDisplacement, "MeanDisplacement");
    AddObservable(branch_.SumDisplacement, "SumDisplacement");
    AddObservable(branch_.Multipliticity, "Multipliticity");
    AddObservable(branch_.DeltaR, "DeltaR");
    AddObservable(branch_.Spread, "Spread");
    AddObservable(branch_.VertexDeltaR, "VertexDeltaR");
    AddObservable(branch_.VertexSpread, "VertexSpread");
    AddObservable(branch_.EnergyFraction, "EnergyFraction");
//     AddSpectator(Branch.BTag, "BTag");
//
    AddObservable(branch_.Mass, "Mass");
//     AddSpectator(Branch.Tag, "Tag");
//     AddSpectator(Branch.Bdt, "Bdt");
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
    if (MaxDisp > 0) BottomBranch.MaxDisplacement = std::log(MaxDisp);
    else BottomBranch.MaxDisplacement = -3;
    float MeanDisp = Jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) BottomBranch.MeanDisplacement = std::log(MeanDisp);
    else BottomBranch.MeanDisplacement = -3;
    float SumDisp = Jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) BottomBranch.SumDisplacement = std::log(SumDisp);
    else BottomBranch.SumDisplacement = -3;
    BottomBranch.Multipliticity = Jet.user_info<hanalysis::HJetInfo>().VertexNumber();
    BottomBranch.DeltaR = GetDeltaR(Jet);
    BottomBranch.Spread = GetSpread(Jet);
    BottomBranch.VertexDeltaR = GetDeltaR(Jet.user_info<hanalysis::HJetInfo>().VertexJet());
    BottomBranch.VertexSpread = GetSpread(Jet.user_info<hanalysis::HJetInfo>().VertexJet());
    BottomBranch.EnergyFraction = Jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / Jet.e();
    BottomBranch.BTag = Jet.user_info<hanalysis::HJetInfo>().BTag();
    BottomBranch.Tag = Jet.user_info<hanalysis::HJetInfo>().Tag();
    BottomBranch.Bdt = Jet.user_info<hanalysis::HJetInfo>().Bdt();

    return BottomBranch;

}

int hbtagger::HBottomTaggerSimple::GetBranches(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Get Bottom Tag", tag);

    HJets jets = GetJets(event);
    Print(HInformation, "Number Jets", jets.size());

    HJets particles = event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsPairId(BottomId, TopId)), Particles.end());
    particles.erase(std::remove_if(particles.begin(), particles.end(), WrongAbsId(BottomId)), particles.end());
    Print(HInformation, "Particle size", particles.size());

    if (jets.empty()) return 0;
    HJets final_jets = CleanJets(jets, particles, tag);

    Print(HDebug, "Number B Jets", jets.size());

    SaveEntries(final_jets);

    return final_jets.size();

}

HJets hbtagger::HBottomTaggerSimple::CleanJets(HJets &Jets, const HJets &Particles, const Tag Tag)
{
    Print(HInformation, "Clean Jets");

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Jets.front().delta_R(Particle) < DetectorGeometry.JetConeSize) static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    HJets NewCleanJets;
    for (const auto & Jet : Jets) {
        if (!Jet.has_user_info<hanalysis::HJetInfo>()) {
            Print(HError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(Jet.rap()) > DetectorGeometry.TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
//         static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         Jet.user_info<hanalysis::HJetInfo>().PrintAllInfos(HDebug);
//         if (Tag == kSignal && Jet.user_info<hanalysis::HJetInfo>().MaximalFraction() < .8) {
//             continue;
//         }
//         if (Tag == kSignal && Jet.user_info<hanalysis::HJetInfo>().MeanDisplacement() < .1) {
//             continue;
//         }
        if (Tag == kSignal && Jet.user_info<hanalysis::HJetInfo>().SumDisplacement() == 0) {
            continue;
        }
//         if (Tag == HBackground && Jet.user_info<hanalysis::HJetInfo>().Fraction(BottomId) > .2) {
//             continue;
//         }
// for (const auto &Particle : Particles) if (Tag == HBackground && Jet.delta_R(Particle) < std::min(GetDeltaR(Jet), float(0.4))) continue;
//         static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        Print(HDebug, "Jet Tag", Jet.user_info<hanalysis::HJetInfo>().Tag());
//         if (Jet.user_info<hanalysis::HJetInfo>().Tag() != Tag) continue;
        NewCleanJets.push_back(Jet);
    }
    return NewCleanJets;
}

hanalysis::HObject::Tag hbtagger::HBottomTaggerSimple::GetTag(const fastjet::PseudoJet &) const
{

    return kSignal;
}


int hbtagger::HBottomTaggerSimple::GetJetBdt(hanalysis::HEvent &event)
{
  HJets jets = GetJets(event);
    HJets final_jets;
    Print(HInformation, "Get Jet Bdt");
    for (const auto jet : jets) {
        if (std::abs(jet.rap()) > DetectorGeometry.TrackerEtaMax) continue;
        if (!jet.has_user_info<hanalysis::HJetInfo>()) {
            Print(HError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
        if (jet.m() <= 0) {
            Print(HInformation, "Empty Piece");
            continue;
        }
        branch_ = GetBranch(jet);
//         static_cast<hanalysis::HJetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(reader().Bdt()); // FIXME reenable this !!!!
        final_jets.push_back(jet);
    }

    SaveEntries(final_jets);

    return final_jets.size();
}


float hbtagger::HBottomTaggerSimple::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float hbtagger::HBottomTaggerSimple::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}
