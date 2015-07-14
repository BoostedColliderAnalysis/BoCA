#include "TopPartnerHiggsPairTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerHiggsPairTagger::TopPartnerHiggsPairTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerHiggsPairTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info();
    std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
    std::vector< Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector< Septet > septets;
    for (const auto &quintet :  quintets) {
        for (const auto &doublet : doublets) {
            Septet septet(quintet, doublet);
            if (septet.Overlap()) continue;
            septet.SetTag(tag);
            septets.emplace_back(septet);
        }

    }
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
  std::vector< Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
  std::vector< Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector< Septet > septets;
    for (const auto &quintet :  quintets) {
      for (const auto &doublet : doublets) {
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
