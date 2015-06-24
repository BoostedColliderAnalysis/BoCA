# include "HTopLeptonTagger.hh"

namespace analysis
{

namespace top
{

HTopLeptonTagger::HTopLeptonTagger()
{
//         DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void HTopLeptonTagger::SetTagger(const BottomTagger &NewBottomTagger)
{
    Print(kNotification, "SetTagger");
    DefineVariables();
    bottom_tagger_ = NewBottomTagger;
}

void HTopLeptonTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");
    set_tagger_name("TopSemi");
    TopWindow = 50;
    ClearObservables();


//     AddObservable(Branch.Mass, "Mass");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaM, "DeltaM");
//     AddObservable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.BBdt, "BBdt");
    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    AddVariable(Branch.VertexMass, "VertexMass");
    AddVariable(Branch.MaxDisplacement, "MaxDisplacement");
    AddVariable(Branch.MeanDisplacement, "MeanDisplacement");
    AddVariable(Branch.SumDisplacement, "SumDisplacement");
    AddVariable(Branch.Multipliticity, "Multipliticity");
    AddVariable(Branch.VertexDeltaR, "VertexDeltaR");
    AddVariable(Branch.VertexSpread, "VertexSpread");
    AddVariable(Branch.EnergyFraction, "EnergyFraction");
    AddVariable(Branch.DeltaR, "DeltaR");
    AddVariable(Branch.Spread, "Spread");

    AddVariable(Branch.JetMass, "JetMass");
    AddVariable(Branch.LeptonPt, "LeptonPt");

    Print(kNotification, "Variables defined");

}

HTopLeptonBranch HTopLeptonTagger::GetBranch(const Doublet &doublet) const
{
    Print(kInformation, "Fill Top Tagger", doublet.Bdt());

    HTopLeptonBranch top_semi_branch;
    top_semi_branch.Mass = doublet.Jet().m();
    top_semi_branch.Rap = doublet.Jet().rap();
    top_semi_branch.Phi = doublet.Jet().phi();
    top_semi_branch.Pt = doublet.Jet().pt();
    top_semi_branch.Ht = doublet.Ht();

    top_semi_branch.DeltaPt = doublet.DeltaPt();
    top_semi_branch.DeltaM = doublet.DeltaM();
    top_semi_branch.DeltaR = doublet.DeltaR();
    top_semi_branch.DeltaRap = doublet.DeltaRap();
    top_semi_branch.DeltaPhi = doublet.DeltaPhi();

    top_semi_branch.BBdt = doublet.SingletJet1().user_info<JetInfo>().Bdt();
    top_semi_branch.Bdt = doublet.Bdt();
    top_semi_branch.Tag = doublet.Tag();

    top_semi_branch.VertexMass = doublet.SingletJet1().user_info<JetInfo>().VertexMass();
    top_semi_branch.JetMass = doublet.SingletJet1().m();
    top_semi_branch.LeptonPt = doublet.SingletJet2().pt();
//     top_semi_branch.Pt = Jet.pt();
//     top_semi_branch.Rap = Jet.rap();
//     top_semi_branch.Phi = Jet.phi();
    float MaxDisp = doublet.SingletJet1().user_info<JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) top_semi_branch.MaxDisplacement = std::log(MaxDisp);
    else top_semi_branch.MaxDisplacement = -3;
    float MeanDisp = doublet.SingletJet1().user_info<JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) top_semi_branch.MeanDisplacement = std::log(MeanDisp);
    else top_semi_branch.MeanDisplacement = -3;
    float SumDisp = doublet.SingletJet1().user_info<JetInfo>().SumDisplacement();
    if (SumDisp > 0) top_semi_branch.SumDisplacement = std::log(SumDisp);
    else top_semi_branch.SumDisplacement = -3;
    top_semi_branch.Multipliticity = doublet.SingletJet1().user_info<JetInfo>().VertexNumber();
//     top_semi_branch.DeltaR = GetDeltaR(doublet.Singlet1());
    top_semi_branch.Spread = GetSpread(doublet.SingletJet1());
    top_semi_branch.VertexDeltaR = GetDeltaR(doublet.SingletJet1().user_info<JetInfo>().VertexJet());
    top_semi_branch.VertexSpread = GetSpread(doublet.SingletJet1().user_info<JetInfo>().VertexJet());
    top_semi_branch.EnergyFraction = doublet.SingletJet1().user_info<JetInfo>().VertexEnergy() / doublet.SingletJet1().e();
//     top_semi_branch.BBdt = doublet.Singlet1().user_info<JetInfo>().Bdt();

    return top_semi_branch;
}

std::vector< HTopLeptonBranch > HTopLeptonTagger::GetBranches(Event &event, const Object::Tag tag)
{
    Print(kInformation, "Top Tags");
    const int TopNumber = 2;
    eventNumber += TopNumber;

    Jets jets = event.Hadrons().Jets();
    Print(kInformation, "Jet Number", jets.size());
    //     jets = fastjet::sorted_by_pt(bottom_tagger_.GetJetBdt(jets, BottomReader)); // TODO reenable this

    Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    Print(kInformation, "Lepton Number", Leptons.size());
//     switch (Tag) {
//     case  kSignal:
//         if (Leptons.size() > TopNumber) Leptons.erase(Leptons.begin() + TopNumber, Leptons.end());
//         break;
//     case HBackground :
    for (const auto & Jet : jets)  {
        const int LeptonPt = 1;
        Leptons.emplace_back(fastjet::PseudoJet(Jet.px(), Jet.py(), Jet.pz(), Jet.e()) / Jet.pt() * LeptonPt);
    }
//         break;
//     }

    std::vector<Doublet> doublets;
    for (const auto & Lepton : Leptons) {
        ++LeptonNumber;
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            Doublet doublet(Jet, Lepton);
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
            ++LeptonJetNumber;
        }
//         if (Tag == kSignal) break;
    }
    Print(kInformation, "Number of doublets?", doublets.size());

    std::vector<Doublet> Finaldoublets;
    std::vector<HTopLeptonBranch> TopLeptonBranches;
    if (doublets.empty()) return TopLeptonBranches;

    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = RemoveIfWrongAbsParticle(TopParticles, TopId);
    if (TopParticles.size() != TopNumber) {
        if (tag == kSignal) Print(kError, "Top Quarks", TopParticles.size());
        if (tag == kBackground) Finaldoublets = doublets;
    } else {
        if (TopParticles.at(0).delta_R(TopParticles.at(1)) < detector_geometry().JetConeSize) Print(kError, "Top Quarks Too close", TopParticles.size());
        for (const auto & TopParticle : TopParticles) {
            ++TopQuarkNumber;
            for (const auto & doublet : doublets) {
                if (tag == kSignal && doublet.Jet().delta_R(TopParticle) < detector_geometry().JetConeSize) Finaldoublets.emplace_back(doublet);
//                 Print(kError, "Distance", doublet.Jet().delta_R(TopParticle));
                if (tag == kBackground && doublet.Jet().delta_R(TopParticle) > detector_geometry().JetConeSize) Finaldoublets.emplace_back(doublets.front());
            }
        }
    }


    if (tag == kSignal && Finaldoublets.size() > TopNumber) {
        Print(kError, "Where is the Top Jet?", Finaldoublets.size());
        std::sort(Finaldoublets.begin(), Finaldoublets.end(), SortByMassTo(Mass(TopId)));
        Finaldoublets.erase(Finaldoublets.begin() + TopNumber, Finaldoublets.end());
    }
    Print(kInformation, "Number triplets", Finaldoublets.size());

    for (const auto & triplet : Finaldoublets) {
        TopLeptonBranches.emplace_back(GetBranch(triplet));
        ++TopJetNumberNumber;
    }

//     Print(kError, "Lepton Fraction", float(LeptonNumber) / eventNumber);
//     Print(kError, "Lepton Jet Fraction", float(LeptonJetNumber) / eventNumber);
//     Print(kError, "Quark Fraction", float(TopQuarkNumber) / eventNumber);
//     Print(kError, "Top Fraction", float(TopJetNumberNumber) / eventNumber);

    return TopLeptonBranches;
}



std::vector<Doublet>  HTopLeptonTagger::GetBdt(const Jets &jets, const Jets &Leptons, const Reader &Reader)
{

    Print(kInformation, "Bdt");

    std::vector<Doublet> doublets;
    for (const auto & Jet : jets)  {
        for (const auto & Lepton : Leptons) {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            Doublet doublet(Jet, Lepton);
            Branch = GetBranch(doublet);
            doublet.SetBdt(Reader.Bdt());
            doublets.emplace_back(doublet);
        }
    }
    for (const auto & Jet : jets)  {
        if (doublets.size() >= 2) break;
        const int LeptonPt = 1;
        fastjet::PseudoJet Lepton = fastjet::PseudoJet(Jet.px(), Jet.py(), Jet.pz(), Jet.e()) / Jet.pt() * LeptonPt;
        Print(kInformation, "Lepton pt", Lepton.pt(), Lepton.delta_R(Jet));
        Doublet doublet(Jet, Lepton);
        Branch = GetBranch(doublet);
        doublet.SetBdt(Reader.Bdt());
//         Print(kError,"Bdt",doublet.Bdt(),doublet.Singlet1().user_info<JetInfo>().Bdt());
        doublets.emplace_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());

    return doublets;
}

float HTopLeptonTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float HTopLeptonTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}

}

}
