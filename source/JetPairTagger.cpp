#include "JetPairTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

JetPairTagger::JetPairTagger()
{
    Note();
    DefineVariables();
}

int JetPairTagger::Train(const Event& event, PreCuts&, const Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    if (jets.empty())
        return 0;
    Debug(jets.size());
    Jets bottoms = BottomPair(event, tag);
    Debug(bottoms.size());
    Jets bottom_jets;
    switch (tag) {
    case Tag::signal :
        for (const auto& bottom : bottoms) {
            jets = SortedByMinDeltaRTo(jets, bottom);
            if (Close(jets.at(0))(bottom)) continue;
            if (Close(jets.at(1))(bottom)) 
            {
              bottom_jets.emplace_back(jets.front());
            }
            else
            {
              if(jets.at(0).m()<jets.at(1).m()) bottom_jets.emplace_back(jets.at(0));
              else bottom_jets.emplace_back(jets.at(1));
            }
        }
        break;
    case Tag::background :
      bottom_jets = jets;
      break;
    }
    std::vector<Doublet> doublets;
    for (auto jet1 = bottom_jets.begin(); jet1 != bottom_jets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != bottom_jets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap()))
                doublet.SetMultiplets(*jet1, *jet2);
            else
                doublet.SetMultiplets(*jet2, *jet1);
            doublets.emplace_back(doublet);
        }
    Debug(doublets.size());
    if (tag == Tag::signal && doublets.size() > 1) {
        Error(doublets.size());
        doublets = SortByMaxDeltaRap(doublets);
        if (doublets.size() > 1)
            doublets.erase(doublets.begin() + 1, doublets.end());
    }
    return SaveEntries(doublets,1);
}

Jets JetPairTagger::BottomPair(const Event& event, const Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets bottom_not_from_even = RemoveIfGrandFamily(particles, Id::bottom, Id::heavy_higgs);
    Jets bottom_not_from_higgs = RemoveIfGrandFamily(bottom_not_from_even, Id::bottom, Id::CP_odd_higgs);
    return bottom_not_from_higgs;
}

std::vector<Doublet>  JetPairTagger::Multiplets(const Event& event, analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet>  doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1)
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet;
            if (std::abs((*jet_1).rap()) > std::abs((*jet_2).rap()))
                doublet.SetMultiplets(*jet_1, *jet_2);
            else
                doublet.SetMultiplets(*jet_2, *jet_1);
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets, 6);
}

}
