# include "TopPartnerLeptonicTagger.hh"

namespace analysis
{

namespace toppartner
{

TopPartnerLeptonicTagger::TopPartnerLeptonicTagger()
{
//         DebugLevel = Severity::detailed;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopPartnerSemi");
    top_reader_.SetTagger(top_tagger_);
    z_hadronic_reader_.SetTagger(z_hadronic_tagger);
    DefineVariables();
}

int TopPartnerLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Higgs Tags");
    std::vector< Doublet> top_doublets = top_reader_.Multiplets<TopLeptonicTagger>(event);
    std::vector< Doublet> z_doublets = z_hadronic_reader_.Multiplets<ZHadronicTagger>(event);
    std::vector< Quartet22 > quartets;
    for (const auto & top_doublet : top_doublets)
        for (const auto & z_doublet : z_doublets) {
            Quartet22 quartet(top_doublet, z_doublet);
            if (quartet.Overlap()) continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }
    return SaveEntries(quartets);
}

std::vector<Quartet22> TopPartnerLeptonicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector< Doublet> top_doublets = top_reader_.Multiplets<TopLeptonicTagger>(event);
    std::vector< Doublet> z_doublets = z_hadronic_reader_.Multiplets<ZHadronicTagger>(event);
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
