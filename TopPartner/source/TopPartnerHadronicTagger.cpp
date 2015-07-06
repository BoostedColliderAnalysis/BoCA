#include "TopPartnerHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
    Note();
    set_tagger_name("TopPartnerHadronic");
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(const Event &event,  PreCuts &pre_cuts, const Tag tag) const
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
        Jets top_partner = copy_if_abs_particle(event.Partons().GenParticles(), Id::top_partner);
//     Debug("top partner",quintets.size(),top_partner.size());
    return SaveEntries(BestMatches(quintets, top_partner, tag), 2);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const const
{
    std::vector< Triplet> triplets = top_reader_.Multiplets(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets(event);
    std::vector< Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetBdt(Bdt(quintet, reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}

}

}
