#include "TopPartnerLeptonicPairTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerLeptonicPairTagger::TopPartnerLeptonicPairTagger()
{
    Note();
    set_tagger_name("TopPartnerLeptonicPairTagger");
    top_partner_hadronic_reader_.SetTagger(top_partner_hadronic_tagger_);
    top_partner_semi_reader_.SetTagger(top_partner_semi_tagger_);
    DefineVariables();
}

int TopPartnerLeptonicPairTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Higgs Tags");
    std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
    std::vector< Quartet22> quartets = top_partner_semi_reader_.Multiplets<TopPartnerLeptonicTagger>(event);
    std::vector< Nonet > nonets;
    for (const auto quintet :  quintets) {
        for (const auto quartet : quartets) {
            Nonet nonet(quintet, quartet);
            if (nonet.Overlap()) continue;
            nonet.SetTag(tag);
            nonets.emplace_back(nonet);
        }

    }
    std::sort(nonets.begin(),nonets.end());
    return SaveEntries(nonets,1);
}

std::vector<Nonet> TopPartnerLeptonicPairTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
  std::vector< Quartet22> quartets = top_partner_semi_reader_.Multiplets<TopPartnerLeptonicTagger>(event);
    std::vector< Nonet > nonets;
    for (const auto quintet :  quintets) {
      for (const auto quartet : quartets) {
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
