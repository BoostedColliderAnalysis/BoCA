#include "../include/SignatureTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner {

SignatureTagger::SignatureTagger()
{
    Note();
    DefineVariables();
}

int SignatureTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector< Decuplet55> decuplets = top_partner_pair_reader_.Multiplets(event);
    std::vector< Quartet22> quartets = higgs_pair_reader_.Multiplets(event);
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

std::vector< Quattuordecuplet > SignatureTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    std::vector< Decuplet55> decuplets = top_partner_pair_reader_.Multiplets(event);
    std::vector< Quartet22> quartets = higgs_pair_reader_.Multiplets(event);
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
