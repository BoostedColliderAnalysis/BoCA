# include "TopPartnerHadronicTagger.hh"

namespace analysis
{

namespace toppartner {

TopPartnerHadronicTagger::TopPartnerHadronicTagger()
{
//         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_reader_.set_tagger(top_tagger_);
    z_hadronic_reader_.set_tagger(z_hadronic_tagger);
    DefineVariables();
}

int TopPartnerHadronicTagger::Train(Event &event,  PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopHadronicTagger>(event);
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

std::vector<Quintet> TopPartnerHadronicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    std::vector< Triplet> triplets = top_reader_.Multiplets<TopHadronicTagger>(event);
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
