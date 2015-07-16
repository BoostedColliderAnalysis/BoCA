#include "JetPairTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

JetPairTagger::JetPairTagger()
{
    Note();
    DefineVariables();
}

void JetPairTagger::DefineVariables()
{
    Note("Define Variables");
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
    Tagger:: AddVariable(branch().BdtRatio21, "BdtRatio21");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio22, "BdtRatio22");  // THIS SHOULD BE ENABLED AGAIN
    Tagger:: AddVariable(branch().BdtRatio23, "BdtRatio23");  // THIS SHOULD BE ENABLED AGAIN
    AddVariable(branch().BdtRatio24, "BdtRatio24");  // THIS SHOULD BE ENABLED AGAIN



    AddVariable(branch().Bdt, "Bdt");  // THIS SHOULD BE ENABLED AGAIN
    AddSpectator(branch().Tag, "Tag");

}

int JetPairTagger::Train(const Event &event, PreCuts &, const Tag tag) const
{
    Info("Jet Pair Tags");
    Jets jets = bottom_reader_.Multiplets(event);
    Debug("Number of Jets", jets.size());

    Jets BdtJets = jets;

    if (jets.empty()) return 0;
    Debug("Number BDT Jets", jets.size());

    Jets BottomJets;
    Jets Bottoms = Particle_2Bottom(event, tag);

    Debug("Number of Bottoms", Bottoms.size());
    if (tag == Tag::signal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Bottom : Bottoms) {
            jets = SortedByMinDeltaRTo(jets, Bottom);
            if (jets.front().delta_R(Bottom) > DetectorGeometry::JetConeSize()) continue;
            BottomJets.emplace_back(jets.front());
            if (jets.size() > 1) jets.erase(jets.begin());
        }
    } else if (tag == Tag::background) BottomJets = jets; // THIS SHOULD BE ENABLED AGAIN

    std::vector<Doublet> doublets;
    for (auto jet1 = BottomJets.begin(); jet1 != BottomJets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != BottomJets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);
            doublets.emplace_back(doublet);
        }

    Debug("Number of Jet Pairs", doublets.size());

    if (tag == Tag::signal && doublets.size() > 1) {
        Error("Number of Jet Pairs", doublets.size());
        doublets = SortByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());
    }

    return SaveEntries(doublets);

}

Jets JetPairTagger::Particle_2Bottom(const Event &event, const Tag tag) const
{
    Jets Particles = event.Partons().GenParticles();
    Jets final_particles;
    Jets temp_Particles;
    if (tag == Tag::signal) {
        temp_Particles = RemoveIfAbsGrandFamily(Particles, Id::bottom, Id::heavy_higgs);
        temp_Particles = RemoveIfAbsGrandFamily(Particles, Id::bottom, Id::CP_odd_higgs);
        final_particles = RemoveIfWrongAbsFamily(Particles, Id::bottom, Id::gluon);
        final_particles.insert(final_particles.begin(), temp_Particles.begin(), temp_Particles.end());
    }
    if (
        tag == Tag::signal &&  // THIS SHOULD BE ENABLED AGAIN
        final_particles.size() != 2) Error("Where is the quark pair?", final_particles.size());
    return final_particles;
}
std::vector<Doublet>  JetPairTagger::Multiplets(const Event &event, analysis::PreCuts &, const TMVA::Reader &reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet;
            if (std::abs((*Jet1).rap()) > std::abs((*Jet2).rap())) doublet.SetMultiplets(*Jet1, *Jet2);
            else doublet.SetMultiplets(*Jet2, *Jet1);
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets);
}

}
