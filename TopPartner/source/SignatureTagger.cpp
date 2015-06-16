# include "../include/SignatureTagger.hh"

namespace analysis
{

namespace toppartner {

SignatureTagger::SignatureTagger()
{
//         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_partner_pair_reader_.set_tagger(top_partner_pair_tagger_);
    higgs_pair_reader_.set_tagger(higgs_pair_tagger);
    DefineVariables();
}

int SignatureTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< Decuplet55> decuplets = top_partner_pair_reader_.Multiplets<TopPartnerPairTagger>(event);
    std::vector< Quartet22> quartets = higgs_pair_reader_.Multiplets<HiggsPairTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (const auto decuplet : decuplets) {
        for (const auto quartet : quartets) {
            Quattuordecuplet quattuordecuplet(decuplet, quartet);
            if (quattuordecuplet.Overlap()) continue;
            quattuordecuplet.SetTag(tag);
            quattuordecuplets.emplace_back(quattuordecuplet);
        }
    }
    return SaveEntries(quattuordecuplets);
}

std::vector< Quattuordecuplet > SignatureTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    std::vector< Decuplet55> decuplets = top_partner_pair_reader_.Multiplets<TopPartnerPairTagger>(event);
    std::vector< Quartet22> quartets = higgs_pair_reader_.Multiplets<HiggsPairTagger>(event);
    std::vector< Quattuordecuplet > quattuordecuplets;
    for (const auto decuplet : decuplets) {
        for (const auto quartet : quartets) {
            Quattuordecuplet quattuordecuplet(decuplet, quartet);
            if (quattuordecuplet.Overlap()) continue;
            if (quattuordecuplet.Overlap()) continue;
            quattuordecuplet.SetBdt(Bdt(quattuordecuplet,reader));
            quattuordecuplets.emplace_back(quattuordecuplet);
        }
    }
    return ReduceResult(quattuordecuplets);
}

}

}
