#include "TopPartnerLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
  Info();
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info("Higgs Tags");
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (auto const& doublet : doublets)
        for (auto const& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap())
                continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    return SaveEntries(quintets);
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (auto const& doublet : doublets)
        for (auto const& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetBdt(Bdt(quintet, reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
