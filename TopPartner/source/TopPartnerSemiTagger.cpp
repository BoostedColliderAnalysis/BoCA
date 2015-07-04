#include "TopPartnerSemiTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerSemiTagger::TopPartnerSemiTagger()
{
    Note();
    set_tagger_name("TopPartnerSemi");
    top_reader_.SetTagger(top_tagger_);
    z_hadronic_reader_.SetTagger(z_hadronic_tagger);
    DefineVariables();
}

int TopPartnerSemiTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Higgs Tags");
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopSemiTagger>(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets<ZHadronicTagger>(event);
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

std::vector<Quintet> TopPartnerSemiTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopSemiTagger>(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets<ZHadronicTagger>(event);
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
