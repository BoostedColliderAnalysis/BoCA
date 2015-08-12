#include "TopPartnerHiggsPairTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerHiggsPairTagger::TopPartnerHiggsPairTagger()
{
  Info();
    DefineVariables();
}

int TopPartnerHiggsPairTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Septet> septets;
    for (auto const& quintet :  quintets) {
        for (auto const& doublet : doublets) {
            Septet septet(quintet, doublet);
            if (septet.Overlap())
                continue;
            septet.SetTag(tag);
            septets.emplace_back(septet);
        }
    }
    return SaveEntries(septets);
}

std::vector<Septet> TopPartnerHiggsPairTagger::Multiplets(Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Quintet> quintets = top_partner_hadronic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Septet> septets;
    for (auto const& quintet :  quintets) {
        for (auto const& doublet : doublets) {
            Septet septet(quintet, doublet);
            if (septet.Overlap())
                continue;
            septet.SetBdt(Bdt(septet, reader));
            septets.emplace_back(septet);
        }
    }
    return ReduceResult(septets);
}

}

}
