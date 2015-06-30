#include "TopPartnerHadronicTagger.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
//         DebugLevel = Severity::detailed;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopPartnerHadronic");
    top_reader_.SetTagger(top_tagger_);
    z_hadronic_reader_.SetTagger(z_hadronic_tagger);
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(Event &event,  PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tags");
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            Quintet quintet(triplet, doublet);
            if (quintet.Overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
        Jets top_partner = copy_if_abs_particle(event.Partons().GenParticles(), Id::top_partner);
    Print(Severity::debug,"top partner",quintets.size(),top_partner.size());
    return SaveEntries(BestMatches(quintets, top_partner, tag), 2);
}

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector< Doublet> doublets = z_hadronic_reader_.Multiplets<HiggsTagger>(event);
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
