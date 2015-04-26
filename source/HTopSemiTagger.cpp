# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HTopSemiTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger)
{
    Print(HNotification, "SetTagger");
    DefineVariables();
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    SetTaggerName("TopSemi");
    TopWindow = (TopMass - WMass) / 2;
    ClearVectors();


//     Boost = true; // be carefull with this one

    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.WPt, "WPt");


    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");










    AddObservable(Branch.VertexMass, "VertexMass");
    AddObservable(Branch.MaxDisplacement, "MaxDisplacement");
    AddObservable(Branch.MeanDisplacement, "MeanDisplacement");
    AddObservable(Branch.SumDisplacement, "SumDisplacement");
    AddObservable(Branch.Multipliticity, "Multipliticity");
    AddObservable(Branch.Spread, "Spread");
    AddObservable(Branch.VertexDeltaR, "VertexDeltaR");
    AddObservable(Branch.VertexSpread, "VertexSpread");
    AddObservable(Branch.EnergyFraction, "EnergyFraction");









//     AddObservable(Branch.WBdt, "WBdt");
    AddObservable(Branch.BBdt, "BBdt");
    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

HTopSemiBranch hanalysis::HTopSemiTagger::GetBranch(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    HTopSemiBranch TopSemiBranch;
    TopSemiBranch.Mass = Triplet.Jet().m();
    TopSemiBranch.Rap = Triplet.Jet().rap();
    TopSemiBranch.Phi = Triplet.Jet().phi();
    TopSemiBranch.Pt = Triplet.Jet().pt();
    TopSemiBranch.Ht = Triplet.Ht();

    TopSemiBranch.BottomPt = Triplet.Singlet().pt();
    TopSemiBranch.WPt = Triplet.DoubletJet().pt();

    TopSemiBranch.DeltaPt = Triplet.DeltaPt();
    TopSemiBranch.DeltaM = Triplet.DeltaM();
    TopSemiBranch.DeltaHt = Triplet.DeltaHt();
    TopSemiBranch.DeltaR = Triplet.DeltaR();
    TopSemiBranch.DeltaRap = Triplet.DeltaRap();
    TopSemiBranch.DeltaPhi = Triplet.DeltaPhi();

    GetBottomInfo(TopSemiBranch, Triplet.Singlet());

    TopSemiBranch.BBdt = Triplet.Singlet().user_info<HJetInfo>().Bdt();
//     TopSemiBranch.WBdt = Triplet.Singlet().Bdt();
    TopSemiBranch.Bdt = Triplet.Bdt();
    TopSemiBranch.Tag = Triplet.Tag();

    return TopSemiBranch;
}




void hanalysis::HTopSemiTagger::GetBottomInfo(HTopSemiBranch &TopHadronicBranch, const fastjet::PseudoJet jet) const
{

    TopHadronicBranch.VertexMass = jet.user_info<hanalysis::HJetInfo>().VertexMass();
    float MaxDisp = jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) TopHadronicBranch.MaxDisplacement = std::log(MaxDisp);
    else TopHadronicBranch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) TopHadronicBranch.MeanDisplacement = std::log(MeanDisp);
    else TopHadronicBranch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) TopHadronicBranch.SumDisplacement = std::log(SumDisp);
    else TopHadronicBranch.SumDisplacement = -3;
    TopHadronicBranch.Multipliticity = jet.user_info<hanalysis::HJetInfo>().VertexNumber();
    //     TopHadronicBranch.DeltaR = GetDeltaR(jet);
    TopHadronicBranch.Spread = GetSpread(jet);
    TopHadronicBranch.VertexDeltaR = GetDeltaR(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    TopHadronicBranch.VertexSpread = GetSpread(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    TopHadronicBranch.EnergyFraction = jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / jet.e();
}










std::vector< HTopSemiBranch > hanalysis::HTopSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag, float pre_cut)
{
    Print(HInformation, "Get Top Tags");

    int WSemiId = WSemiTagger.GetWSemiId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());


    HJets Jets = GetJets(Event);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    Print(HInformation, "Number Doublets", Doublets.size());

        std::vector<HTriplet> Triplets;
    if (!Boost) {

        for (const auto & Jet : Jets) {
            for (const auto & Doublet : Doublets) {
                HTriplet Triplet(Doublet, Jet);
                if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // should be enabled again
                if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
                if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
                Triplet.SetTag(Tag);
                Triplets.push_back(Triplet);
            }
        }

    }

    for (const auto & Jet : Jets) {
        for (const auto & Lepton : Leptons) {
            HDoublet Doublet(Lepton);
            HTriplet Triplet(Doublet, Jet);
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // should be enabled again
            if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
            if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
            if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
            Triplet.SetTag(Tag);
            Triplets.push_back(Triplet);
        }
    }

    std::vector<HTopSemiBranch> TopSemiBranches;
    int SemiLeptonicTopNumber = 1; // Must be 1 for the analysis!!;
    if (Tag == HSignal &&
            Triplets.size() > SemiLeptonicTopNumber) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
        Triplets.erase(Triplets.begin() + SemiLeptonicTopNumber, Triplets.end());
    }
    Print(HInformation, "Number Triplets", Triplets.size());

    for (const auto & Triplet : Triplets) TopSemiBranches.push_back(GetBranch(Triplet));

    return TopSemiBranches;
}



std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &Reader)
{

    Print(HInformation, "Get Bdt");

        std::vector<HTriplet> Triplets;
    if (!Boost) {

        for (const auto & Jet : Jets) {
            for (const auto & Doublet : Doublets) {
                HTriplet Triplet(Doublet, Jet);
                if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
                Branch = GetBranch(Triplet);
                Triplet.SetBdt(Reader.Bdt());
                Triplets.push_back(Triplet);
            }
        }
    }

    for (const auto & Jet : Jets) {
        for (const auto & PreDoublet : Doublets) {
            HDoublet Doublet(PreDoublet.Singlet1());
            HTriplet Triplet(Doublet, Jet);
//             if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // reactivate this check
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(Reader.Bdt());
            Triplets.push_back(Triplet);
        }
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());

    return Triplets;
}













float hanalysis::HTopSemiTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
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

float hanalysis::HTopSemiTagger::GetSpread(const fastjet::PseudoJet &Jet) const
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









