# include "HTopLeptonTagger.hh"

HTopLeptonTagger::HTopLeptonTagger()
{
//         DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void HTopLeptonTagger::SetTagger(const hanalysis::BottomTagger &NewBottomTagger)
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
    ClearVectors();


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

HTopLeptonBranch HTopLeptonTagger::GetBranch(const hanalysis::Doublet &doublet) const
{
    Print(kInformation, "Fill Top Tagger", doublet.Bdt());

    HTopLeptonBranch TopSemiBranch;
    TopSemiBranch.Mass = doublet.Jet().m();
    TopSemiBranch.Rap = doublet.Jet().rap();
    TopSemiBranch.Phi = doublet.Jet().phi();
    TopSemiBranch.Pt = doublet.Jet().pt();
    TopSemiBranch.Ht = doublet.Ht();

    TopSemiBranch.DeltaPt = doublet.DeltaPt();
    TopSemiBranch.DeltaM = doublet.DeltaM();
    TopSemiBranch.DeltaR = doublet.DeltaR();
    TopSemiBranch.DeltaRap = doublet.DeltaRap();
    TopSemiBranch.DeltaPhi = doublet.DeltaPhi();

    TopSemiBranch.BBdt = doublet.Singlet1().user_info<hanalysis::JetInfo>().Bdt();
    TopSemiBranch.Bdt = doublet.Bdt();
    TopSemiBranch.Tag = doublet.Tag();

    TopSemiBranch.VertexMass = doublet.Singlet1().user_info<hanalysis::JetInfo>().VertexMass();
    TopSemiBranch.JetMass = doublet.Singlet1().m();
    TopSemiBranch.LeptonPt = doublet.Singlet2().pt();
//     TopSemiBranch.Pt = Jet.pt();
//     TopSemiBranch.Rap = Jet.rap();
//     TopSemiBranch.Phi = Jet.phi();
    float MaxDisp = doublet.Singlet1().user_info<hanalysis::JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) TopSemiBranch.MaxDisplacement = std::log(MaxDisp);
    else TopSemiBranch.MaxDisplacement = -3;
    float MeanDisp = doublet.Singlet1().user_info<hanalysis::JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) TopSemiBranch.MeanDisplacement = std::log(MeanDisp);
    else TopSemiBranch.MeanDisplacement = -3;
    float SumDisp = doublet.Singlet1().user_info<hanalysis::JetInfo>().SumDisplacement();
    if (SumDisp > 0) TopSemiBranch.SumDisplacement = std::log(SumDisp);
    else TopSemiBranch.SumDisplacement = -3;
    TopSemiBranch.Multipliticity = doublet.Singlet1().user_info<hanalysis::JetInfo>().VertexNumber();
//     TopSemiBranch.DeltaR = GetDeltaR(doublet.Singlet1());
    TopSemiBranch.Spread = GetSpread(doublet.Singlet1());
    TopSemiBranch.VertexDeltaR = GetDeltaR(doublet.Singlet1().user_info<hanalysis::JetInfo>().VertexJet());
    TopSemiBranch.VertexSpread = GetSpread(doublet.Singlet1().user_info<hanalysis::JetInfo>().VertexJet());
    TopSemiBranch.EnergyFraction = doublet.Singlet1().user_info<hanalysis::JetInfo>().VertexEnergy() / doublet.Singlet1().e();
//     TopSemiBranch.BBdt = doublet.Singlet1().user_info<hanalysis::JetInfo>().Bdt();

    return TopSemiBranch;
}

std::vector< HTopLeptonBranch > HTopLeptonTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get Top Tags");
    const int TopNumber = 2;
    EventNumber += TopNumber;

    Jets jets = GetJets(Event);
    Print(kInformation, "Jet Number", jets.size());
    //     jets = fastjet::sorted_by_pt(bottom_tagger_.GetJetBdt(jets, BottomReader)); // TODO reenable this

    Jets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
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

    std::vector<hanalysis::Doublet> doublets;
    for (const auto & Lepton : Leptons) {
        ++LeptonNumber;
        for (const auto & Jet : jets)  {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            hanalysis::Doublet doublet(Jet, Lepton);
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
            ++LeptonJetNumber;
        }
//         if (Tag == kSignal) break;
    }
    Print(kInformation, "Number of doublets?", doublets.size());

    std::vector<hanalysis::Doublet> Finaldoublets;
    std::vector<HTopLeptonBranch> TopLeptonBranches;
    if (doublets.empty()) return TopLeptonBranches;

    Jets TopParticles = Event.GetParticles()->Generator();
    TopParticles = RemoveIfWrongAbsParticle(TopParticles, TopId);
    if (TopParticles.size() != TopNumber) {
        if(tag == kSignal) Print(kError, "Top Quarks", TopParticles.size());
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
        std::sort(Finaldoublets.begin(), Finaldoublets.end(), SortByMass(TopMass));
        Finaldoublets.erase(Finaldoublets.begin() + TopNumber, Finaldoublets.end());
    }
    Print(kInformation, "Number triplets", Finaldoublets.size());

    for (const auto & triplet : Finaldoublets) {
        TopLeptonBranches.emplace_back(GetBranch(triplet));
        ++TopJetNumberNumber;
    }

//     Print(kError, "Lepton Fraction", float(LeptonNumber) / EventNumber);
//     Print(kError, "Lepton Jet Fraction", float(LeptonJetNumber) / EventNumber);
//     Print(kError, "Quark Fraction", float(TopQuarkNumber) / EventNumber);
//     Print(kError, "Top Fraction", float(TopJetNumberNumber) / EventNumber);

    return TopLeptonBranches;
}



std::vector<hanalysis::Doublet>  HTopLeptonTagger::GetBdt(const Jets &jets, const Jets &Leptons, const hanalysis::Reader &Reader)
{

    Print(kInformation, "Get Bdt");

    std::vector<hanalysis::Doublet> doublets;
    for (const auto & Jet : jets)  {
        for (const auto & Lepton : Leptons) {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            hanalysis::Doublet doublet(Jet, Lepton);
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
        hanalysis::Doublet doublet(Jet, Lepton);
        Branch = GetBranch(doublet);
        doublet.SetBdt(Reader.Bdt());
//         Print(kError,"Bdt",doublet.Bdt(),doublet.Singlet1().user_info<hanalysis::JetInfo>().Bdt());
        doublets.emplace_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());

    return doublets;
}

float HTopLeptonTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Delta R");

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
    Print(kInformation, "Get Centrality");
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


