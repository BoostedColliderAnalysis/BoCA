#include "TopPartnerPairTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerPairTagger::TopPartnerPairTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerPairTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector< Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets(event);
    std::vector< Quintet> quintets_2 = top_partner_semi_reader_.Multiplets(event);
    std::vector< Decuplet55 > decuplets;
    for (const auto &quintet_1 :  quintets_1) {
        for (const auto &quintet_2 : quintets_2) {
            Decuplet55 decuplet(quintet_1, quintet_2);
            if (decuplet.Overlap()) continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }

    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet55> TopPartnerPairTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
  std::vector< Quintet> quintets_1 = top_partner_hadronic_reader_.Multiplets(event);
  std::vector< Quintet> quintets_2 = top_partner_semi_reader_.Multiplets(event);
    std::vector< Decuplet55 > decuplets;
    for (const auto &quintet_1 :  quintets_1) {
      for (const auto &quintet_2 : quintets_2) {
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
