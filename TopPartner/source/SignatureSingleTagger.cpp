#include "SignatureSingleTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

SignatureSingleTagger::SignatureSingleTagger()
{
    Note();
    DefineVariables();
}

int SignatureSingleTagger::Train(const Event& event, PreCuts& pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector<Septet> septets = top_partner_higgs_pair_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets(event);
    std::vector<Decuplet73> decuplets;
    for (const auto& septet :  septets) {
        for (const auto& triplet : triplets) {
            Decuplet73 decuplet(septet, triplet);
            if (decuplet.Overlap())
                continue;
            decuplet.SetTag(tag);
            decuplets.emplace_back(decuplet);
        }
    }
    return SaveEntries(decuplets);
}

std::vector<Decuplet73> SignatureSingleTagger::Multiplets(const Event& event, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    std::vector<Septet> septets = top_partner_higgs_pair_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets(event);
    std::vector<Decuplet73> decuplets;
    for (const auto& septet :  septets) {
        for (const auto& triplet : triplets) {
            Decuplet73 decuplet(septet, triplet);
            if (decuplet.Overlap())
                continue;
            decuplet.SetBdt(Bdt(decuplet, reader));
            decuplets.emplace_back(decuplet);
        }
    }
    return ReduceResult(decuplets);
}

}

}
