#include "TopPartnerHiggsPairTagger.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerHiggsPairTagger::TopPartnerHiggsPairTagger()
{
//         DebugLevel = Severity::detailed;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopPartnerHiggsPairTagger");
    top_partner_hadronic_reader_.SetTagger(top_partner_hadronic_tagger_);
    higgs_reader_.SetTagger(higgs_tagger_);
    DefineVariables();
}

int TopPartnerHiggsPairTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tags");
    std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets<TopPartnerSemiTagger>(event);
    std::vector< Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Septet > septets;
    for (const auto quintet :  quintets) {
        for (const auto doublet : doublets) {
            Septet septet(quintet, doublet);
            if (septet.Overlap()) continue;
            septet.SetTag(tag);
            septets.emplace_back(septet);
        }

    }
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets<TopPartnerSemiTagger>(event);
  std::vector< Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Septet > septets;
    for (const auto quintet :  quintets) {
      for (const auto doublet : doublets) {
            Septet septet(quintet, doublet);
            if (septet.Overlap()) continue;
            septet.SetBdt(Bdt(septet,reader));
            septets.emplace_back(septet);
        }
    }
    return ReduceResult(septets);
}

}

}
