# include "JetPairTagger.hh"

analysis::JetPairTagger::JetPairTagger()
{
//     DebugLevel = kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("JetPair");
    DefineVariables();
}

void analysis::JetPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.Jet1Mass, "Jet1Mass");
    AddVariable(branch_.Jet1Pt, "Jet1Pt");
    AddVariable(branch_.Jet1Rap, "Jet1Rap");
    AddVariable(branch_.Jet1Phi, "Jet1Phi");
    AddVariable(branch_.Jet1Bdt, "Jet1Bdt");  // THIS SHOULD BE ENABLED AGAIN

    AddVariable(branch_.Jet2Mass, "Jet2Mass");
    AddVariable(branch_.Jet2Pt, "Jet2Pt");
    AddVariable(branch_.Jet2Rap, "Jet2Rap");
    AddVariable(branch_.Jet2Phi, "Jet2Phi");
    AddVariable(branch_.Jet2Bdt, "Jet2Bdt");  // THIS SHOULD BE ENABLED AGAIN


    AddVariable(branch_.BdtRatio11, "BdtRatio11");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio12, "BdtRatio12");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio13, "BdtRatio13");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio14, "BdtRatio14");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio21, "BdtRatio21");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio22, "BdtRatio22");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio23, "BdtRatio23");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch_.BdtRatio24, "BdtRatio24");  // THIS SHOULD BE ENABLED AGAIN



    AddVariable(branch_.Bdt, "Bdt");  // THIS SHOULD BE ENABLED AGAIN
    AddSpectator(branch_.Tag, "Tag");

}

int analysis::JetPairTagger::Train(analysis::Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Jet Pair Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kDebug, "Number of Jets", jets.size());

    Jets BdtJets = jets;

    if (jets.empty()) return 0;
    Print(kDebug, "Number BDT Jets", jets.size());

    Jets Particles = event.Partons().GenParticles();
    ParticleId MotherId = GluonId;
    if (tag == kSignal) Particles = RemoveIfWrongAbsFamily(Particles, BottomId, MotherId);
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsStepMother(Particles, TopId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongParticle(Particles, GluonId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     if (Tag == HBackground) Particles = RemoveIfWrongAbsMother(Particles, ZId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
    if (
        tag == kSignal &&  // THIS SHOULD BE ENABLED AGAIN
        Particles.size() != 2) Print(kError, "Where is the quark pair?", Particles.size());
    Jets BottomJets;
    Print(kDebug, "Number of Bottoms", Particles.size());

    if (tag == kSignal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Particle : Particles) {
            jets = SortedByMinDeltaRTo(jets, Particle);
            if (jets.front().delta_R(Particle) > detector_geometry().JetConeSize) continue;

            BottomJets.emplace_back(jets.front());
            if (jets.size() > 1) jets.erase(jets.begin());
        }
    } else if (tag == kBackground) BottomJets = jets; // THIS SHOULD BE ENABLED AGAIN
//     if (Tag == kSignal && BottomJets.size() != 2) Print(kError, "Number of Matching Jets", BottomJets.size());

    std::vector<Doublet> doublets;
    for (auto jet1 = BottomJets.begin(); jet1 != BottomJets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != BottomJets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetSinglets((*jet1), (*jet2));
            else doublet.SetSinglets(*jet2, *jet1);

//             for (const auto & Jet : BdtJets) if (Jet != *Jet1 && Jet != *Jet2) doublet.AddRestJet(Jet);
//             if (doublet.RestJets().size() != BdtJets.size() - 2) Print(kError, "to many jets in the rest jet vector");

            doublets.emplace_back(doublet);
        }

    Print(kDebug, "Number of Jet Pairs", doublets.size());

    if (tag == kSignal && doublets.size() > 1) {
        Print(kError, "Number of Jet Pairs", doublets.size());
        doublets = SortByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());
    }

    return SaveEntries<JetPairBranch>(doublets);

}

std::vector<analysis::Doublet>  analysis::JetPairTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) doublet.SetSinglets((*Jet1), (*Jet2));
            else doublet.SetSinglets((*Jet2), (*Jet1));
//             for (const auto & Jet : jets)  if (Jet != *Jet1 && Jet != *Jet2) doublet.AddRestJet(Jet);
//             if (doublet.RestJets().size() != jets.size() - 2) Print(kError, "to many jets in the rest jet vector");
//             if (std::abs(doublet.DeltaRap()) < detector_geometry().JetConeSize) continue;
            branch_ = branch<JetPairBranch>(doublet);
            doublet.SetBdt(Bdt(reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets);
}

