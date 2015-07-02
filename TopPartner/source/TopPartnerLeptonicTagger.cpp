#include "TopPartnerLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
    Note();
    set_tagger_name("TopPartnerLeptonic");
    top_reader_.SetTagger(top_tagger_);
    z_hadronic_reader_.SetTagger(z_hadronic_tagger);
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("Higgs Tags");
    std::vector< Doublet> top_doublets = top_reader_.Multiplets<TopLeptonicTagger>(event);
    std::vector< Doublet> z_doublets = z_hadronic_reader_.Multiplets<HiggsTagger>(event);
//     Debug("top and higgs",top_doublets.size(),z_doublets.size());
    std::vector< Quartet22 > quartets;
    for (const auto & top_doublet : top_doublets)
        for (const auto & z_doublet : z_doublets) {
            Quartet22 quartet(top_doublet, z_doublet);
            if (quartet.Overlap()) continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }
    Jets top_partner = copy_if_abs_particle(event.Partons().GenParticles(), Id::top_partner);
//     Debug("top partner",quartets.size(),top_partner.size());
    return SaveEntries(BestMatches(quartets, top_partner, tag), 2);
}

std::vector<Quartet22> TopPartnerLeptonicTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector< Doublet> top_doublets = top_reader_.Multiplets<TopLeptonicTagger>(event);
    std::vector< Doublet> z_doublets = z_hadronic_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Quartet22 > quartets;
    for (const auto & top_doublet : top_doublets)
        for (const auto & z_doublet : z_doublets) {
            Quartet22 quartet(top_doublet, z_doublet);
            if (quartet.Overlap()) continue;
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}

}

}
