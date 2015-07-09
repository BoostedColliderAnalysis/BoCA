#include "TopPartnerLeptonicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
    Note();
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector< Doublet> top_doublets = top_reader_.Multiplets(event);
    std::vector< Doublet> z_doublets = higgs_hadronic_reader_.Multiplets(event);
//     Debug("top and higgs",top_doublets.size(),z_doublets.size());
    std::vector< Quartet22 > quartets;
    for (const auto & top_doublet : top_doublets)
        for (const auto & z_doublet : z_doublets) {
            Quartet22 quartet(top_doublet, z_doublet);
            if (quartet.Overlap()) continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }
    Jets top_partner = CopyIfAbsParticle(event.Partons().GenParticles(), Id::top_partner);
//     Debug("top partner",quartets.size(),top_partner.size());
    return SaveEntries(BestMatches(quartets, top_partner, tag), 2);
}

std::vector<Quartet22> TopPartnerLeptonicTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector< Doublet> top_doublets = top_reader_.Multiplets(event);
    std::vector< Doublet> z_doublets = higgs_hadronic_reader_.Multiplets(event);
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
