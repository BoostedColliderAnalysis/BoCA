#include "TopPartnerLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(const Event& event, const PreCuts& pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (const auto& doublet : doublets)
        for (const auto& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap())
                continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    return SaveEntries(quintets);
}

std::vector<Quintet> TopPartnerLeptonicTagger::Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    std::vector<Doublet> doublets = higgs_hadronic_reader_.Multiplets(event);
    std::vector<Quintet> quintets;
    for (const auto& doublet : doublets)
        for (const auto& triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap())
                continue;
            quintet.SetBdt(Bdt(quintet, reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
