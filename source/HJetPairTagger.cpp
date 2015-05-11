# include "HJetPairTagger.hh"

hanalysis::HJetPairTagger::HJetPairTagger()
{
//     DebugLevel = hanalysis::HObject::kDetailed;
    Print(kNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HJetPairTagger::SetTagger(const BottomTagger &NewBottomTagger)
{
    Print(kNotification, "Set Tagger", NewBottomTagger.tagger_name());
    bottom_tagger_ = NewBottomTagger;
    DefineVariables();
}

void hanalysis::HJetPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
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

HEventJetPairBranch hanalysis::HJetPairTagger::GetBranch(const Doublet &doublet) const
{

    Print(kInformation, "FillPairTagger", doublet.Bdt());

    HEventJetPairBranch JetPairBranch;

    JetPairBranch.Mass = doublet.Jet().m();
    JetPairBranch.Pt = doublet.Jet().pt();
    JetPairBranch.Rap = doublet.Jet().rap();
    JetPairBranch.Phi = doublet.Jet().phi();
    JetPairBranch.Ht = doublet.Ht();

    JetPairBranch.DeltaM = doublet.DeltaM();
    JetPairBranch.DeltaPt = doublet.DeltaPt();
    JetPairBranch.DeltaR = doublet.DeltaR();
    JetPairBranch.DeltaRap = doublet.DeltaRap();
    JetPairBranch.DeltaPhi = doublet.DeltaPhi();

    JetPairBranch.Jet1Pt = doublet.Singlet1().pt();
    JetPairBranch.Jet1Rap = std::abs(doublet.Singlet1().rap());
    JetPairBranch.Jet1Phi = doublet.Singlet1().phi();
    JetPairBranch.Jet1Mass = doublet.Singlet1().m();
    JetPairBranch.Jet1Bdt = doublet.Singlet1().user_info<JetInfo>().Bdt();

    JetPairBranch.Jet2Pt = doublet.Singlet2().pt();
    JetPairBranch.Jet2Rap = std::abs(doublet.Singlet2().rap());
    JetPairBranch.Jet2Phi = doublet.Singlet2().phi();
    JetPairBranch.Jet2Mass = doublet.Singlet2().m();
    JetPairBranch.Jet2Bdt = doublet.Singlet2().user_info<JetInfo>().Bdt();

    JetPairBranch.BdtRatio11 = doublet.BdtRatio1(1);
    JetPairBranch.BdtRatio12 = doublet.BdtRatio1(2);
    JetPairBranch.BdtRatio13 = doublet.BdtRatio1(3);
    JetPairBranch.BdtRatio14 = doublet.BdtRatio1(4);

    JetPairBranch.BdtRatio21 = doublet.BdtRatio2(1);
    JetPairBranch.BdtRatio22 = doublet.BdtRatio2(2);
    JetPairBranch.BdtRatio23 = doublet.BdtRatio2(3);
    JetPairBranch.BdtRatio24 = doublet.BdtRatio2(4);

    JetPairBranch.Bdt = doublet.Bdt();
    JetPairBranch.Tag = doublet.Tag();
    return JetPairBranch;
}

std::vector<HEventJetPairBranch> hanalysis::HJetPairTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag, const HParticleId MotherId)
{
    Print(kInformation, "Get Jet Pair Tags", GetParticleName(MotherId));
    Jets jets = GetJets(Event);
    Print(kDebug, "Number of Jets", jets.size());
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this


    Jets BdtJets = jets;

    std::vector<HEventJetPairBranch> JetPairBranches;
    if (jets.empty()) return JetPairBranches;
    Print(kDebug, "Number BDT Jets", jets.size());

    Jets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) Particles = RemoveIfWrongAbsFamily(Particles, BottomId, MotherId);
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsStepMother(Particles, TopId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongParticle(Particles, GluonId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsMother(Particles, ZId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
    if (
        Tag == kSignal &&  // THIS SHOULD BE ENABLED AGAIN
        Particles.size() != 2) Print(kError, "Where is the quark pair?", Particles.size());
    Jets BottomJets;
    Print(kDebug, "Number of Bottoms", Particles.size());

    if (Tag == kSignal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Particle : Particles) {
            jets = SortedByMinDeltaRTo(jets, Particle);
            if (jets.front().delta_R(Particle) > detector_geometry().JetConeSize) continue;

            BottomJets.emplace_back(jets.front());
            if (jets.size() > 1) jets.erase(jets.begin());
        }
    } else if (Tag == kBackground) BottomJets = jets; // THIS SHOULD BE ENABLED AGAIN
//     if (Tag == kSignal && BottomJets.size() != 2) Print(kError, "Number of Matching Jets", BottomJets.size());

    std::vector<Doublet> doublets;
    for (auto Jet1 = BottomJets.begin(); Jet1 != BottomJets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != BottomJets.end(); ++Jet2) {
            Doublet doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) doublet.SetSinglets((*Jet1), (*Jet2));
            else doublet.SetSinglets((*Jet2), (*Jet1));

            for (const auto & Jet : BdtJets) if (Jet != *Jet1 && Jet != *Jet2) doublet.AddRestJet(Jet);
            if (doublet.RestJets().size() != BdtJets.size() - 2) Print(kError, "to many jets in the rest jet vector");

            doublets.emplace_back(doublet);
        }

    Print(kDebug, "Number of Jet Pairs", doublets.size());

    if (Tag == kSignal && doublets.size() > 1) {
        Print(kError, "Number of Jet Pairs", doublets.size());
        doublets = SortByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());
    }

    for (const auto & doublet : doublets) JetPairBranches.emplace_back(GetBranch(doublet));

    return JetPairBranches;

}

hanalysis::HObject::Tag hanalysis::HJetPairTagger::GetTag(const Doublet &)
{
    return kSignal;
}

std::vector<hanalysis::Doublet>  hanalysis::HJetPairTagger::GetBdt(const Jets &jets, const hanalysis::Reader &JetPairReader)
{
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) doublet.SetSinglets((*Jet1), (*Jet2));
            else doublet.SetSinglets((*Jet2), (*Jet1));
            for (const auto & Jet : jets)  if (Jet != *Jet1 && Jet != *Jet2) doublet.AddRestJet(Jet);
            if (doublet.RestJets().size() != jets.size() - 2) Print(kError, "to many jets in the rest jet vector");
//             if (std::abs(doublet.DeltaRap()) < detector_geometry().JetConeSize) continue;
            Branch = GetBranch(doublet);
            doublet.SetBdt(JetPairReader.Bdt());
            doublets.emplace_back(doublet);
        }
    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

