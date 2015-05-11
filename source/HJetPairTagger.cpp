# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger()
{
//     DebugLevel = hanalysis::HObject::HDetailed;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HJetPairTagger::SetTagger(const BottomTagger &NewBottomTagger)
{
    Print(HNotification, "Set Tagger", NewBottomTagger.tagger_name());
    bottom_tagger_ = NewBottomTagger;
    DefineVariables();
}

void hanalysis::HJetPairTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    set_tagger_name("JetPair");

    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.Jet1Mass, "Jet1Mass");
    AddVariable(Branch.Jet1Pt, "Jet1Pt");
    AddVariable(Branch.Jet1Rap, "Jet1Rap");
    AddVariable(Branch.Jet1Phi, "Jet1Phi");
    AddVariable(Branch.Jet1Bdt, "Jet1Bdt");  // THIS SHOULD BE ENABLED AGAIN

    AddVariable(Branch.Jet2Mass, "Jet2Mass");
    AddVariable(Branch.Jet2Pt, "Jet2Pt");
    AddVariable(Branch.Jet2Rap, "Jet2Rap");
    AddVariable(Branch.Jet2Phi, "Jet2Phi");
    AddVariable(Branch.Jet2Bdt, "Jet2Bdt");  // THIS SHOULD BE ENABLED AGAIN


    AddVariable(Branch.BdtRatio11, "BdtRatio11");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio12, "BdtRatio12");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio13, "BdtRatio13");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio14, "BdtRatio14");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio21, "BdtRatio21");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio22, "BdtRatio22");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio23, "BdtRatio23");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(Branch.BdtRatio24, "BdtRatio24");  // THIS SHOULD BE ENABLED AGAIN



    AddVariable(Branch.Bdt, "Bdt");  // THIS SHOULD BE ENABLED AGAIN
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
    Jets jets = GetJets(Event);
    Print(HDebug, "Number of Jets", jets.size());
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this


    Jets BdtJets = jets;

    std::vector<HEventJetPairBranch> JetPairBranches;
    if (jets.empty()) return JetPairBranches;
    Print(HDebug, "Number BDT Jets", jets.size());

    Jets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) Particles = RemoveIfWrongAbsFamily(Particles, BottomId, MotherId);
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsStepMother(Particles, TopId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongParticle(Particles, GluonId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsMother(Particles, ZId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
    if (
        Tag == kSignal &&  // THIS SHOULD BE ENABLED AGAIN
        Particles.size() != 2) Print(HError, "Where is the quark pair?", Particles.size());
    Jets BottomJets;
    Print(HDebug, "Number of Bottoms", Particles.size());

    if (Tag == kSignal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Particle : Particles) {
            jets = SortedByMinDeltaRTo(jets, Particle);
            if (jets.front().delta_R(Particle) > detector_geometry().JetConeSize) continue;

            BottomJets.emplace_back(jets.front());
            if (jets.size() > 1) jets.erase(jets.begin());
        }
    } else if (Tag == kBackground) BottomJets = jets; // THIS SHOULD BE ENABLED AGAIN
//     if (Tag == kSignal && BottomJets.size() != 2) Print(HError, "Number of Matching Jets", BottomJets.size());

    std::vector<HDoublet> Doublets;
    for (auto Jet1 = BottomJets.begin(); Jet1 != BottomJets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != BottomJets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));

            for (const auto & Jet : BdtJets) if (Jet != *Jet1 && Jet != *Jet2) Doublet.AddRestJet(Jet);
            if (Doublet.RestJets().size() != BdtJets.size() - 2) Print(HError, "to many jets in the rest jet vector");

            Doublets.emplace_back(Doublet);
        }

    Print(HDebug, "Number of Jet Pairs", Doublets.size());

    if (Tag == kSignal && Doublets.size() > 1) {
        Print(HError, "Number of Jet Pairs", Doublets.size());
        Doublets = SortByMaxDeltaRap(Doublets);
        if (Doublets.size() > 1) Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) JetPairBranches.emplace_back(GetBranch(Doublet));

    return JetPairBranches;

}

hanalysis::HObject::Tag hanalysis::HJetPairTagger::GetTag(const HDoublet &)
{
    return kSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HJetPairTagger::GetBdt(const Jets &jets, const hanalysis::Reader &JetPairReader)
{
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            HDoublet Doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) Doublet.SetSinglets((*Jet1), (*Jet2));
            else Doublet.SetSinglets((*Jet2), (*Jet1));
            for (const auto & Jet : jets)  if (Jet != *Jet1 && Jet != *Jet2) Doublet.AddRestJet(Jet);
            if (Doublet.RestJets().size() != jets.size() - 2) Print(HError, "to many jets in the rest jet vector");
//             if (std::abs(Doublet.DeltaRap()) < detector_geometry().JetConeSize) continue;
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(JetPairReader.Bdt());
            Doublets.emplace_back(Doublet);
        }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}

