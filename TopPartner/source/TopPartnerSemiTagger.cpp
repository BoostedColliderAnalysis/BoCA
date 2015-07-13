#include "TopPartnerSemiTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerSemiTagger::TopPartnerSemiTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerSemiTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector< Triplet> triplets = top_reader_.Multiplets(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets(event);
    std::vector< Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    return SaveEntries(quintets);
}

std::vector<Quintet> TopPartnerSemiTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector< Triplet> triplets = top_reader_.Multiplets(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets(event);
    std::vector< Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetBdt(Bdt(quintet,reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
