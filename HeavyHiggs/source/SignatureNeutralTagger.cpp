#include "SignatureNeutralTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

SignatureNeutralTagger::SignatureNeutralTagger()
{
  Info();
    DefineVariables();
}

int SignatureNeutralTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    Debug(doublets.size());
    doublets = jet_pair_reader_.Tagger().TruthDoubletPairs(event, doublets, tag);
    Debug(doublets.size());
    if(doublets.empty()) return 0;
    
    Jets higgs = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    Debug(sextets.size(), higgs.size());
    sextets = BestMatches(sextets, higgs, tag);
    Debug(sextets.size());
    std::vector<Octet62> octets;
    for (const auto& doublet : doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }    
    Debug(octets.size());  
    if (tag == Tag::signal && octets.size() > 1) {
        Info(octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }
    return SaveEntries(octets);
}

std::vector<Octet62> SignatureNeutralTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    std::vector<Octet62> octets;
    for (const auto& doublet : doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

std::vector<Octet62> SignatureNeutralTagger::CleanOctets(Event const& event, std::vector<Octet62> const& octets, Tag tag) const {  
  
  std::vector<Octet62> final_octets;
  Jets bottoms = jet_pair_reader_.Tagger().PairBottomQuarks(event, tag);
//   Check((tag==Tag::signal && bottoms.size()==2) || (tag==Tag::background && bottoms.size() == 2), bottoms.size());
  Jets higgses = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
//   Check((tag==Tag::signal && higgses.size()==1) || (tag==Tag::background && higgses.size() == 0), higgses.size());
//   Error(bottoms.size());
  for(auto const& octet : octets){    
    switch (tag) {
      case Tag::signal :
        for (const auto & higgs : higgses) if (!Close(higgs)(octet.Sextet())) continue;
        break;
      case Tag::background  :
//         Error("What are we doing here?");
        break;
    }    
    try{
      Doublet doublet = jet_pair_reader_.Tagger().TruthDoubletPair(octet.Doublet(), bottoms, tag);    
    } catch (char const *){ 
      continue;      
    }
    final_octets.emplace_back(octet);
  }  
  return final_octets;
}

}

}
