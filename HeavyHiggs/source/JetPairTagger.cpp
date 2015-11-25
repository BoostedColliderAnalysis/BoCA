#include "JetPairTagger.hh"
#include "Event.hh"
#include "Sort.hh"
// #define DEBUG
#include "Debug.hh"

namespace analysis
{

JetPairTagger::JetPairTagger()
{
    Info();
    DefineVariables();
}

int JetPairTagger::Train(const Event &event, const PreCuts &, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    
//     jets = RemoveIfLargeRap(jets, DetectorGeometry::TrackerEtaMax());   
//     jets = RemoveIfSoft(jets, DetectorGeometry::ForwardJetPt());
    
    if (jets.size() < 2) return 0;
    Debug(jets.size());

    Jets higgs = heavyhiggs::HeavyHiggsSemiTagger::HiggsParticle(event, tag);
    Jets bottom_jets = TruthJetPair(event, jets, tag);
    
    Jets bottoms = PairBottomQuarks(event, tag);
    
//     static int jet_pt = 0;
//     static int bottom_rap = 0;    
//     if(bottoms.at(0).pt()> 20 && bottoms.at(1).pt() > 20){
//       jet_pt++;
//       if(std::abs(bottoms.at(0).rap()) > 2.5 && std::abs(bottoms.at(1).rap()) > 2.5)
//     {
//       bottom_rap++;
//       Error(bottom_rap, jet_pt);
//     }
// }
    std::vector<Doublet> doublets;
    for (auto jet1 = bottom_jets.begin(); jet1 != bottom_jets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != bottom_jets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);
            if (tag == Tag::background && higgs.size() > 0 && bottoms.size() == 2 && CheckIfBadBottom(doublet, bottoms)) continue;
            if (doublet.Overlap())continue;
            for(auto jet : jets) if(jet != *jet1 && jet != *jet2) doublet.AddRestJet(jet);            
//             Error(doublet.BdtRatio1(1));
            if (doublet.RestJets().size() != jets.size() - 2) Error("to many jets in the rest jet vector");
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
        
//     static int notusefulbottom = 0;
//     if (bottoms.size() == 2 && (bottoms.at(0).pt() < 50 || bottoms.at(1).pt() < 50)) {
//         notusefulbottom++;
//     }
    
    if (tag == Tag::signal && doublets.size() > 1) {
        doublets = SortedByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());  
    }
    return SaveEntries(doublets);
}

Jets JetPairTagger::PairBottomQuarks(const Event &event, Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets bottom_not_from_even = RemoveIfGrandFamily(particles, Id::bottom, Id::heavy_higgs);
    Jets bottom_not_from_higgs = RemoveIfGrandFamily(bottom_not_from_even, Id::bottom, Id::CP_odd_higgs);
    return bottom_not_from_higgs;
}

Jets JetPairTagger::TruthJetPair(Event const& event, Jets & jets, Tag tag) const {
  Jets bottoms = PairBottomQuarks(event, tag);
  Jets bottom_jets;
  switch (tag) {
    case Tag::signal :
      if (bottoms.size() != 2) Error(bottoms.size());
        for (const auto & bottom : bottoms) {
          jets = SortedByMinDeltaRTo(jets, bottom);
          if (Close(jets.at(1))(bottom)) continue;
          if (Close(jets.at(0))(bottom)) bottom_jets.emplace_back(jets.front());
        }      
      break;
    case Tag::background :
      bottom_jets = jets;
      break;
  }
  return bottom_jets;
}

std::vector<Doublet> JetPairTagger::TruthDoubletPairs(Event const& event, std::vector<Doublet> & doublets, Tag tag) const {
  Jets bottoms = PairBottomQuarks(event, tag);
  
  std::vector<Doublet> final_doublets;
  for (const auto& doublet : doublets) try{
    final_doublets.emplace_back(TruthDoubletPair(doublet, bottoms, tag));
  } catch (char const *) {};
  
  return final_doublets;
}

Doublet JetPairTagger::TruthDoubletPair(Doublet const& doublet, Jets const& bottoms, Tag tag) const {  
  switch (tag) {
    case Tag::signal :
      if (bottoms.size() != 2) {       
        Error(bottoms.size());
        break;
      }
      if ((Close(bottoms.at(0))(doublet.Singlet1().Jet()) && Close(bottoms.at(1))(doublet.Singlet2().Jet())) || (Close(bottoms.at(1))(doublet.Singlet1().Jet()) && Close(bottoms.at(0))(doublet.Singlet2().Jet()))) {
        return doublet;
      }
      break;
    case Tag::background : return doublet;
  }  
  throw "Problematic";
}

std::vector<Doublet> JetPairTagger::Multiplets(const Event &event, const analysis::PreCuts &, const TMVA::Reader &reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet>  doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1)
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet;
            if (std::abs((*jet_1).rap()) > std::abs((*jet_2).rap())) doublet.SetMultiplets(*jet_1, *jet_2);
            else doublet.SetMultiplets(*jet_2, *jet_1);
            if (doublet.Overlap())continue;
            for(auto jet : jets)  if(jet != *jet_1 && jet != *jet_2) doublet.AddRestJet(jet);            
            if (doublet.RestJets().size() != jets.size() - 2) Error("to many jets in the rest jet vector");
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets, 6);
}

bool JetPairTagger::CheckIfBadBottom(const analysis::Doublet &doublet, const Jets &jets)const
{
    if ((Close(jets.at(0))(doublet.Singlet1().Jet()) && Close(jets.at(1))(doublet.Singlet2().Jet())) || (Close(jets.at(1))(doublet.Singlet1().Jet()) && Close(jets.at(0))(doublet.Singlet2().Jet())))return true;
    else return false;

}

}
