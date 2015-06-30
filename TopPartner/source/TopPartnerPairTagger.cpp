#include "TopPartnerPairTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerPairTagger::TopPartnerPairTagger()
{
    Note("Constructor");
    set_tagger_name("TopPartnerPairTagger");
    top_partner_hadronic_reader_.SetTagger(top_partner_hadronic_tagger_);
    top_partner_semi_reader_.SetTagger(top_partner_semi_tagger_);
    DefineVariables();
}

int TopPartnerPairTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Higgs Tags");
    std::vector< Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
    std::vector< Quintet> quintets_2 = top_partner_semi_reader_.Multiplets<TopPartnerSemiTagger>(event);
    std::vector< Decuplet55 > decuplets;
    for (const auto quintet_1 :  quintets_1) {
        for (const auto quintet_2 : quintets_2) {
            Decuplet55 decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }

    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet55> TopPartnerPairTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  std::vector< Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets<TopPartnerHadronicTagger>(event);
  std::vector< Quintet> quintets_2 = top_partner_semi_reader_.Multiplets<TopPartnerSemiTagger>(event);
    std::vector< Decuplet55 > decuplets;
    for (const auto quintet_1 :  quintets_1) {
      for (const auto quintet_2 : quintets_2) {
            Decuplet55 decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetBdt(Bdt(decuplet,reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}

}
