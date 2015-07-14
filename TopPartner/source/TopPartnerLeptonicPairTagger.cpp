#include "TopPartnerLeptonicPairTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerLeptonicPairTagger::TopPartnerLeptonicPairTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerLeptonicPairTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info();
    std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
    std::vector< Quartet22> quartets = top_partner_leptonic_reader_.Multiplets(event);
    std::vector< Nonet > nonets;
    for (const auto & quintet :  quintets) {
        for (const auto & quartet : quartets) {
            Nonet nonet(quintet, quartet);
            if (nonet.Overlap()) continue;
            nonet.SetTag(tag);
            nonets.emplace_back(nonet);
        }
    }
    std::sort(nonets.begin(),nonets.end());
    return SaveEntries(nonets,1);
}

std::vector<Nonet> TopPartnerLeptonicPairTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
  Info();
  std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
  std::vector< Quartet22> quartets = top_partner_leptonic_reader_.Multiplets(event);
    std::vector< Nonet > nonets;
    for (const auto & quintet :  quintets) {
      for (const auto & quartet : quartets) {
            Nonet nonet(quintet, quartet);
            if (nonet.Overlap()) continue;
            nonet.SetBdt(Bdt(nonet,reader));
            nonets.emplace_back(nonet);
        }
    }
    return ReduceResult(nonets);
}

}

}
