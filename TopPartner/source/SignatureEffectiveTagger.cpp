#include "SignatureEffectiveTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

SignatureEffectiveTagger::SignatureEffectiveTagger()
{
  Info();
    DefineVariables();
}

int SignatureEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    std::vector<Quattuordecuplet> quattuordecuplets = pairs(top_partner_pair_reader_.Multiplets(event), higgs_pair_reader_.Multiplets(event), [tag](Decuplet55 const& decuplet, Quartet22 const& quartet) {
        Quattuordecuplet quattuordecuplet(decuplet, quartet);
        if (quattuordecuplet.Overlap()) throw "overlap";
        quattuordecuplet.SetTag(tag);
        return quattuordecuplet;
    });
    return SaveEntries(quattuordecuplets);
}

std::vector<Quattuordecuplet> SignatureEffectiveTagger::Multiplets(Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Decuplet55> decuplets = top_partner_pair_reader_.Multiplets(event);
    std::vector<Quartet22> quartets = higgs_pair_reader_.Multiplets(event);
    std::vector<Quattuordecuplet> quattuordecuplets;
    for (auto const& decuplet : decuplets) {
        for (auto const& quartet : quartets) {
            Quattuordecuplet quattuordecuplet(decuplet, quartet);
            if (quattuordecuplet.Overlap()) continue;
            quattuordecuplet.SetBdt(Bdt(quattuordecuplet, reader));
            quattuordecuplets.emplace_back(quattuordecuplet);
        }
    }
    return ReduceResult(quattuordecuplets);
}

}

}



