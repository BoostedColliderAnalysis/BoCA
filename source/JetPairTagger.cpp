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

int JetPairTagger::Train(const Event &event, PreCuts &, const Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    if (jets.empty()) return 0;
    Debug(jets.size());

    Jets Bottoms = Particle_2Bottom(event, tag);
    Debug(Bottoms.size());

    Jets BottomJets;
    if (tag == Tag::signal) { // THIS SHOULD BE ENABLED AGAIN
        for (const auto & Bottom : Bottoms) {
            jets = SortedByMinDeltaRTo(jets, Bottom);
            if (jets.front().delta_R(Bottom) > DetectorGeometry::JetConeSize()) continue;
            BottomJets.emplace_back(jets.front());
        }
    }
    else if (tag == Tag::background) BottomJets = jets; // THIS SHOULD BE ENABLED AGAIN

    std::vector<Doublet> doublets;
    for (auto jet1 = BottomJets.begin(); jet1 != BottomJets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != BottomJets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);
            doublets.emplace_back(doublet);
        }

    Debug(doublets.size());

    if (tag == Tag::signal && doublets.size() > 1) {
        Error("Number of Jet Pairs", doublets.size());
        doublets = SortByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());
    }

    return SaveEntries(doublets);

}

Jets JetPairTagger::Particle_2Bottom(const Event &event, const Tag tag) const
{
    Jets particles = event.Partons().GenParticles();
    Jets final_particles;
    if (tag == Tag::signal) {
        final_particles = RemoveIfWrongAbsFamily(particles, Id::bottom, Id::gluon);
        Jets Bottom_NotFromEven = RemoveIfAbsGrandFamily(particles, Id::bottom, Id::heavy_higgs);
        Jets Bottom_NotFromHiggs = RemoveIfAbsGrandFamily(Bottom_NotFromEven, Id::bottom, Id::CP_odd_higgs);
        final_particles.insert(final_particles.begin(), Bottom_NotFromHiggs.begin(), Bottom_NotFromHiggs.end());
    }
//     if (tag == Tag::signal && final_particles.size() > 2) Error("Where is the quark pair?", final_particles.at(0).user_info<JetInfo>().constituents().front().family().grand_mother().id());
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
