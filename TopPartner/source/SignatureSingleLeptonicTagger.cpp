#include "SignatureSingleLeptonicTagger.hh"
#include "Event.hh"
#include "Exeption.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

  int SignatureSingleLeptonicTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    std::vector<Decuplet532> decuplets = Decuplets(event, pre_cuts, [&](Decuplet532 & decuplet) {
      decuplet.SetTag(tag);
      return decuplet;
    });
    Info(decuplets.size());
//     if(decuplets.size() > 1) std::sort(decuplets.begin(),decuplets.end());
//     if(!decuplets.empty()) Info(decuplets.front().VetoBdt());
    return SaveEntries(decuplets, 1);
}

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, pre_cuts, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

// std::vector<Decuplet532> SignatureSingleLeptonicTagger::Decuplets(boca::Event const& event, std::function< Decuplet532(Decuplet532&)> const& function) const
// {
//     return pairs(partner_reader_.Multiplets(event), veto_reader_.Multiplets(event), [&](Quintet const & quintet, Quintet const & veto) {
//         Decuplet532 decuplet(quintet, veto.Triplet(), veto.Doublet());
//         if (decuplet.Overlap()) throw Overlap();
//         decuplet.SetVetoBdt(veto.Bdt());
//         Error(decuplet.VetoBdt());
//         return function(decuplet);
//     });
// }

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Decuplets(Event const& event, PreCuts const& pre_cuts, std::function< Decuplet532(Decuplet532&)> const& function) const
{
  return triples(partner_reader_.Multiplets(event) , top_reader_.Multiplets(event), higgs_reader_.Multiplets(event), [&](Quintet const & quintet, Triplet const & triplet, Doublet const& doublet) {
    Decuplet532 decuplet(quintet, triplet, doublet);
    if (decuplet.Overlap()) throw Overlap();
    decuplet.SetVetoBdt(veto_reader_.Bdt(Quintet(triplet, boson_reader_.Multiplet(doublet, pre_cuts))));
//     Error(decuplet.VetoBdt());
    return function(decuplet);
  });
}

}

}
