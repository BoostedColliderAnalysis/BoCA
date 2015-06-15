# include "JetPairTagger.hh"

namespace analysis {

JetPairTagger::JetPairTagger()
{
//     DebugLevel = kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("JetPair");
    DefineVariables();
}

void JetPairTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Ht, "Ht");

    AddVariable(branch().DeltaM, "DeltaM");
    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaR, "DeltaR");

    AddVariable(branch().Jet1Mass, "Jet1Mass");
    AddVariable(branch().Jet1Pt, "Jet1Pt");
    AddVariable(branch().Jet1Rap, "Jet1Rap");
    AddVariable(branch().Jet1Phi, "Jet1Phi");
    AddVariable(branch().Jet1Bdt, "Jet1Bdt");  // THIS SHOULD BE ENABLED AGAIN

    AddVariable(branch().Jet2Mass, "Jet2Mass");
    AddVariable(branch().Jet2Pt, "Jet2Pt");
    AddVariable(branch().Jet2Rap, "Jet2Rap");
    AddVariable(branch().Jet2Phi, "Jet2Phi");
    AddVariable(branch().Jet2Bdt, "Jet2Bdt");  // THIS SHOULD BE ENABLED AGAIN


    AddVariable(branch().BdtRatio11, "BdtRatio11");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio12, "BdtRatio12");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio13, "BdtRatio13");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio14, "BdtRatio14");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio21, "BdtRatio21");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio22, "BdtRatio22");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio23, "BdtRatio23");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio24, "BdtRatio24");  // THIS SHOULD BE ENABLED AGAIN



    AddVariable(branch().Bdt, "Bdt");  // THIS SHOULD BE ENABLED AGAIN
    AddSpectator(branch().Tag, "Tag");

}

int JetPairTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
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
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);

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

    return SaveEntries(doublets);

}

std::vector<Doublet>  JetPairTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) doublet.SetMultiplets(*Jet1, *Jet2);
            else doublet.SetMultiplets(*Jet2, *Jet1);
//             for (const auto & Jet : jets)  if (Jet != *Jet1 && Jet != *Jet2) doublet.AddRestJet(Jet);
//             if (doublet.RestJets().size() != jets.size() - 2) Print(kError, "to many jets in the rest jet vector");
//             if (std::abs(doublet.DeltaRap()) < detector_geometry().JetConeSize) continue;
            doublet.SetBdt(Bdt(doublet,reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets);
}

}
