#include "boca/SignatureSingleLeptonicTagger.hh"
#include "boca/Event.hh"
#include "boca/generic/Exception.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int SignatureSingleLeptonicTagger::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    auto decuplets = Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    });
    INFO(decuplets.size());
    return SaveEntries(decuplets, tag);
}

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<Decuplet532> SignatureSingleLeptonicTagger::Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function)
{
  INFO0;
  auto triplets = top_reader_.Multiplets(event);
  auto quintets = partner_reader_.Multiplets(event);
  std::vector<Decuplet532> decuplets;
  for (auto const & doublet : higgs_reader_.Multiplets(event)) {
    for (auto const & triplet : triplets) {
      Quintet veto(triplet, doublet);
      if (veto.Overlap()) continue;
      veto.SetBdt(veto_reader_.Bdt(veto));
      for (auto const & quintet : quintets) {
        Decuplet532 decuplet(quintet, triplet, doublet);
        if (decuplet.Overlap()) continue;
        decuplet.SetVetoBdt(veto.Bdt());
        decuplets.emplace_back(function(decuplet));
      }
    }
  }
  DEBUG(decuplets.size());
  return decuplets;
}

latex::String SignatureSingleLeptonicTagger::LatexName() const
{
    return "T_{l}t_{h}h";
}

std::string SignatureSingleLeptonicTagger::Name() const
{
    return "SignatureSingleLeptonic";
}

}

}
