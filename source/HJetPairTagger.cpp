# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger()
{
//     DebugLevel = hanalysis::HObject::HDetailed;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HJetPairTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.tagger_name());
    BottomTagger = NewBottomTagger;
    DefineVariables();
}

void hanalysis::HJetPairTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("JetPair");

    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.Jet1Mass, "Jet1Mass");
    AddObservable(Branch.Jet1Pt, "Jet1Pt");
    AddObservable(Branch.Jet1Rap, "Jet1Rap");
    AddObservable(Branch.Jet1Phi, "Jet1Phi");
    AddObservable(Branch.Jet1Bdt, "Jet1Bdt");  // THIS SHOULD BE ENABLED AGAIN

    AddObservable(Branch.Jet2Mass, "Jet2Mass");
    AddObservable(Branch.Jet2Pt, "Jet2Pt");
    AddObservable(Branch.Jet2Rap, "Jet2Rap");
    AddObservable(Branch.Jet2Phi, "Jet2Phi");
    AddObservable(Branch.Jet2Bdt, "Jet2Bdt");  // THIS SHOULD BE ENABLED AGAIN


    AddObservable(Branch.BdtRatio11, "BdtRatio11");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio12, "BdtRatio12");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio13, "BdtRatio13");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio14, "BdtRatio14");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio21, "BdtRatio21");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio22, "BdtRatio22");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio23, "BdtRatio23");  // THIS SHOULD BE ENABLED AGAIN
    AddObservable(Branch.BdtRatio24, "BdtRatio24");  // THIS SHOULD BE ENABLED AGAIN



    AddObservable(Branch.Bdt, "Bdt");  // THIS SHOULD BE ENABLED AGAIN
    AddSpectator(Branch.Tag, "Tag");

}

HEventJetPairBranch hanalysis::HJetPairTagger::GetBranch(const HDoublet &Doublet) const
{

    Print(HInformation, "FillPairTagger", Doublet.Bdt());

    HEventJetPairBranch JetPairBranch;

    JetPairBranch.Mass = Doublet.Jet().m();
    JetPairBranch.Pt = Doublet.Jet().pt();
    JetPairBranch.Rap = Doublet.Jet().rap();
    JetPairBranch.Phi = Doublet.Jet().phi();
    JetPairBranch.Ht = Doublet.Ht();

    JetPairBranch.DeltaM = Doublet.DeltaM();
    JetPairBranch.DeltaPt = Doublet.DeltaPt();
    JetPairBranch.DeltaR = Doublet.DeltaR();
    JetPairBranch.DeltaRap = Doublet.DeltaRap();
    JetPairBranch.DeltaPhi = Doublet.DeltaPhi();

    JetPairBranch.Jet1Pt = Doublet.Singlet1().pt();
    JetPairBranch.Jet1Rap = std::abs(Doublet.Singlet1().rap());
    JetPairBranch.Jet1Phi = Doublet.Singlet1().phi();
    JetPairBranch.Jet1Mass = Doublet.Singlet1().m();
    JetPairBranch.Jet1Bdt = Doublet.Singlet1().user_info<HJetInfo>().Bdt();

    JetPairBranch.Jet2Pt = Doublet.Singlet2().pt();
    JetPairBranch.Jet2Rap = std::abs(Doublet.Singlet2().rap());
    JetPairBranch.Jet2Phi = Doublet.Singlet2().phi();
    JetPairBranch.Jet2Mass = Doublet.Singlet2().m();
    JetPairBranch.Jet2Bdt = Doublet.Singlet2().user_info<HJetInfo>().Bdt();

    JetPairBranch.BdtRatio11 = Doublet.BdtRatio1(1);
    JetPairBranch.BdtRatio12 = Doublet.BdtRatio1(2);
    JetPairBranch.BdtRatio13 = Doublet.BdtRatio1(3);
    JetPairBranch.BdtRatio14 = Doublet.BdtRatio1(4);

    JetPairBranch.BdtRatio21 = Doublet.BdtRatio2(1);
    JetPairBranch.BdtRatio22 = Doublet.BdtRatio2(2);
    JetPairBranch.BdtRatio23 = Doublet.BdtRatio2(3);
    JetPairBranch.BdtRatio24 = Doublet.BdtRatio2(4);

    JetPairBranch.Bdt = Doublet.Bdt();
    JetPairBranch.Tag = Doublet.Tag();
    return JetPairBranch;
}

std::vector<HEventJetPairBranch> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const HParticleId MotherId)
{
    Print(HInformation, "Get Jet Pair Tags", GetParticleName(MotherId));
    HJets Jets = GetJets(Event);
    Print(HDebug, "Number of Jets", Jets.size());
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);


    HJets BdtJets = Jets;

    std::vector<HEventJetPairBranch> JetPairBranches;
    if (Jets.empty()) return JetPairBranches;
    Print(HDebug, "Number BDT Jets", Jets.size());

    HJets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) Particles = RemoveIfWrongAbsFamily(Particles, BottomId, MotherId);
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsStepMother(Particles, TopId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongParticle(Particles, GluonId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsMother(Particles, ZId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
    if (
        Tag == kSignal &&  // THIS SHOULD BE ENABLED AGAIN
        Particles.size() != 2) Print(HError, "Where is the quark pair?", Particles.size());
    HJets BottomJets;
    Print(HDebug, "Number of Bottoms", Particles.size());

    if (Tag == kSignal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Particle : Particles) {
            Jets = SortByDeltaRTo(Jets, Particle);
            if (Jets.front().delta_R(Particle) > DetectorGeometry.JetConeSize) continue;

            BottomJets.push_back(Jets.front());
            if (Jets.size() > 1) Jets.erase(Jets.begin());
        }
    } else if (Tag == kBackground) BottomJets = Jets; // THIS SHOULD BE ENABLED AGAIN
//     if (Tag == kSignal && BottomJets.size() != 2) Print(HError, "Number of Matching Jets", BottomJets.size());

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = BottomJets.begin(); Jet1 != BottomJets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != BottomJets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));

            for (const auto & Jet : BdtJets) if (Jet != *Jet1 && Jet != *Jet2) Doublet.AddRestJet(Jet);
            if (Doublet.RestJets().size() != BdtJets.size() - 2) Print(HError, "to many jets in the rest jet vector");

            Doublets.push_back(Doublet);
        }

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    if (Tag == kSignal && Doublets.size() > 1) {
        Print(HError, "Number of Jet Pairs", Doublets.size());
        Doublets = SortByMaxDeltaRap(Doublets);
        if (Doublets.size() > 1) Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) JetPairBranches.push_back(GetBranch(Doublet));

    return JetPairBranches;

}

hanalysis::HObject::Tag hanalysis::HJetPairTagger::GetTag(const HDoublet &)
{
    return kSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &JetPairReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
            for (const auto & Jet : Jets) if (Jet != *Jet1 && Jet != *Jet2) Doublet.AddRestJet(Jet);
            if (Doublet.RestJets().size() != Jets.size() - 2) Print(HError, "to many jets in the rest jet vector");
//             if (std::abs(Doublet.DeltaRap()) < DetectorGeometry.JetConeSize) continue;
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(JetPairReader.Bdt());
            Doublets.push_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}

