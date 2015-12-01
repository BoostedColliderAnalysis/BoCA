#include "SignatureSingleLeptonicTagger.hh"
#include "Event.hh"
#include "Exception.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int SignatureSingleLeptonicTagger::Train(Event const& event, PreCuts const& , Tag tag) const
{
    Info0;
    std::vector<Decuplet532> decuplets = Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    });
    INFO(decuplets.size());
    return SaveEntries(decuplets, tag);
}

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function) const
{
  Info0;
  std::vector<Triplet> triplets = top_reader_.Multiplets(event);
  std::vector<Quintet> quintets = partner_reader_.Multiplets(event);
  std::vector<Decuplet532> decuplets;
  for (auto const & doublet : higgs_reader_.Multiplets(event)) {
    for (auto const & triplet : triplets) {
      Quintet veto(triplet, doublet);
      if (veto.Overlap()) continue;
      float veto_bdt = veto_reader_.Bdt(veto);
      for (auto const & quintet : quintets) {
        Decuplet532 decuplet(quintet, triplet, doublet);
        if (decuplet.Overlap()) continue;
        decuplet.SetVetoBdt(veto_bdt);
        decuplets.emplace_back(function(decuplet));
      }
    }
  }
  Debug(decuplets.size());
  return decuplets;
}

std::string SignatureSingleLeptonicTagger::NiceName() const
{
    return "T_{l}t_{h}h";
}

std::string SignatureSingleLeptonicTagger::Name() const
{
    return "SignatureSingleLeptonic";
}

}

}
