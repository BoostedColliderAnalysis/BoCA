# include "HTopLeptonTagger.hh"

HTopLeptonTagger::HTopLeptonTagger()
{
//         DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void HTopLeptonTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger)
{
    Print(HNotification, "SetTagger");
    DefineVariables();
    BottomTagger = NewBottomTagger;
}

void HTopLeptonTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    SetTaggerName("TopSemi");
    TopWindow = 50;
    ClearVectors();


//     AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaM, "DeltaM");
//     AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.BBdt, "BBdt");
    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    AddObservable(Branch.VertexMass, "VertexMass");
    AddObservable(Branch.MaxDisplacement, "MaxDisplacement");
    AddObservable(Branch.MeanDisplacement, "MeanDisplacement");
    AddObservable(Branch.SumDisplacement, "SumDisplacement");
    AddObservable(Branch.Multipliticity, "Multipliticity");
    AddObservable(Branch.VertexDeltaR, "VertexDeltaR");
    AddObservable(Branch.VertexSpread, "VertexSpread");
    AddObservable(Branch.EnergyFraction, "EnergyFraction");
    AddObservable(Branch.DeltaR, "DeltaR");
    AddObservable(Branch.Spread, "Spread");

    AddObservable(Branch.JetMass, "JetMass");
    AddObservable(Branch.LeptonPt, "LeptonPt");

    Print(HNotification, "Variables defined");

}

HTopLeptonBranch HTopLeptonTagger::GetBranch(const hanalysis::HDoublet &Doublet) const
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    HTopLeptonBranch TopSemiBranch;
    TopSemiBranch.Mass = Doublet.Jet().m();
    TopSemiBranch.Rap = Doublet.Jet().rap();
    TopSemiBranch.Phi = Doublet.Jet().phi();
    TopSemiBranch.Pt = Doublet.Jet().pt();
    TopSemiBranch.Ht = Doublet.Ht();

    TopSemiBranch.DeltaPt = Doublet.DeltaPt();
    TopSemiBranch.DeltaM = Doublet.DeltaM();
    TopSemiBranch.DeltaR = Doublet.DeltaR();
    TopSemiBranch.DeltaRap = Doublet.DeltaRap();
    TopSemiBranch.DeltaPhi = Doublet.DeltaPhi();

    TopSemiBranch.BBdt = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().Bdt();
    TopSemiBranch.Bdt = Doublet.Bdt();
    TopSemiBranch.Tag = Doublet.Tag();

    TopSemiBranch.VertexMass = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().VertexMass();
    TopSemiBranch.JetMass = Doublet.Singlet1().m();
    TopSemiBranch.LeptonPt = Doublet.Singlet2().pt();
//     TopSemiBranch.Pt = Jet.pt();
//     TopSemiBranch.Rap = Jet.rap();
//     TopSemiBranch.Phi = Jet.phi();
    float MaxDisp = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) TopSemiBranch.MaxDisplacement = std::log(MaxDisp);
    else TopSemiBranch.MaxDisplacement = -3;
    float MeanDisp = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) TopSemiBranch.MeanDisplacement = std::log(MeanDisp);
    else TopSemiBranch.MeanDisplacement = -3;
    float SumDisp = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) TopSemiBranch.SumDisplacement = std::log(SumDisp);
    else TopSemiBranch.SumDisplacement = -3;
    TopSemiBranch.Multipliticity = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().VertexNumber();
//     TopSemiBranch.DeltaR = GetDeltaR(Doublet.Singlet1());
    TopSemiBranch.Spread = GetSpread(Doublet.Singlet1());
    TopSemiBranch.VertexDeltaR = GetDeltaR(Doublet.Singlet1().user_info<hanalysis::HJetInfo>().VertexJet());
    TopSemiBranch.VertexSpread = GetSpread(Doublet.Singlet1().user_info<hanalysis::HJetInfo>().VertexJet());
    TopSemiBranch.EnergyFraction = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().VertexEnergy() / Doublet.Singlet1().e();
//     TopSemiBranch.BBdt = Doublet.Singlet1().user_info<hanalysis::HJetInfo>().Bdt();

    return TopSemiBranch;
}

std::vector< HTopLeptonBranch > HTopLeptonTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Get Top Tags");
    const int TopNumber = 2;
    EventNumber += TopNumber;

    HJets Jets = GetJets(Event);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = fastjet::sorted_by_pt(BottomTagger.GetJetBdt(Jets, BottomReader));

    HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
    Print(HInformation, "Lepton Number", Leptons.size());
//     switch (Tag) {
//     case  kSignal:
//         if (Leptons.size() > TopNumber) Leptons.erase(Leptons.begin() + TopNumber, Leptons.end());
//         break;
//     case HBackground :
        for (const auto & Jet : Jets) {
            const int LeptonPt = 1;
            Leptons.emplace_back(fastjet::PseudoJet(Jet.px(), Jet.py(), Jet.pz(), Jet.e()) / Jet.pt() * LeptonPt);
        }
//         break;
//     }

    std::vector<hanalysis::HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        ++LeptonNumber;
        for (const auto & Jet : Jets) {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            hanalysis::HDoublet Doublet(Jet, Lepton);
            Doublet.SetTag(tag);
            Doublets.emplace_back(Doublet);
            ++LeptonJetNumber;
        }
//         if (Tag == kSignal) break;
    }
    Print(HInformation, "Number of Doublets?", Doublets.size());

    std::vector<hanalysis::HDoublet> FinalDoublets;
    std::vector<HTopLeptonBranch> TopLeptonBranches;
    if (Doublets.empty()) return TopLeptonBranches;

    HJets TopParticles = Event.GetParticles()->Generator();
    TopParticles = RemoveIfWrongAbsParticle(TopParticles, TopId);
    if (TopParticles.size() != TopNumber) {
        if(tag == kSignal) Print(HError, "Top Quarks", TopParticles.size());
        if (tag == kBackground) FinalDoublets = Doublets;
    } else {
        if (TopParticles.at(0).delta_R(TopParticles.at(1)) < detector_geometry().JetConeSize) Print(HError, "Top Quarks Too close", TopParticles.size());
        for (const auto & TopParticle : TopParticles) {
            ++TopQuarkNumber;
            for (const auto & Doublet : Doublets) {
                if (tag == kSignal && Doublet.Jet().delta_R(TopParticle) < detector_geometry().JetConeSize) FinalDoublets.emplace_back(Doublet);
//                 Print(HError, "Distance", Doublet.Jet().delta_R(TopParticle));
                if (tag == kBackground && Doublet.Jet().delta_R(TopParticle) > detector_geometry().JetConeSize) FinalDoublets.emplace_back(Doublets.front());
            }
        }
    }


    if (tag == kSignal && FinalDoublets.size() > TopNumber) {
        Print(HError, "Where is the Top Jet?", FinalDoublets.size());
        std::sort(FinalDoublets.begin(), FinalDoublets.end(), SortByMass(TopMass));
        FinalDoublets.erase(FinalDoublets.begin() + TopNumber, FinalDoublets.end());
    }
    Print(HInformation, "Number Triplets", FinalDoublets.size());

    for (const auto & Triplet : FinalDoublets) {
        TopLeptonBranches.emplace_back(GetBranch(Triplet));
        ++TopJetNumberNumber;
    }

//     Print(HError, "Lepton Fraction", float(LeptonNumber) / EventNumber);
//     Print(HError, "Lepton Jet Fraction", float(LeptonJetNumber) / EventNumber);
//     Print(HError, "Quark Fraction", float(TopQuarkNumber) / EventNumber);
//     Print(HError, "Top Fraction", float(TopJetNumberNumber) / EventNumber);

    return TopLeptonBranches;
}



std::vector<hanalysis::HDoublet>  HTopLeptonTagger::GetBdt(const HJets &Jets, const HJets &Leptons, const hanalysis::Reader &Reader)
{

    Print(HInformation, "Get Bdt");

    std::vector<hanalysis::HDoublet> Doublets;
    for (const auto & Jet : Jets) {
        for (const auto & Lepton : Leptons) {
            if (Jet.delta_R(Lepton) > detector_geometry().JetConeSize) continue;
            hanalysis::HDoublet Doublet(Jet, Lepton);
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(Reader.Bdt());
            Doublets.emplace_back(Doublet);
        }
    }
    for (const auto & Jet : Jets) {
        if (Doublets.size() >= 2) break;
        const int LeptonPt = 1;
        fastjet::PseudoJet Lepton = fastjet::PseudoJet(Jet.px(), Jet.py(), Jet.pz(), Jet.e()) / Jet.pt() * LeptonPt;
        Print(HInformation, "Lepton pt", Lepton.pt(), Lepton.delta_R(Jet));
        hanalysis::HDoublet Doublet(Jet, Lepton);
        Branch = GetBranch(Doublet);
        Doublet.SetBdt(Reader.Bdt());
//         Print(HError,"Bdt",Doublet.Bdt(),Doublet.Singlet1().user_info<hanalysis::HJetInfo>().Bdt());
        Doublets.emplace_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());

    return Doublets;
}

float HTopLeptonTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
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

float HTopLeptonTagger::GetSpread(const fastjet::PseudoJet &Jet) const
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


