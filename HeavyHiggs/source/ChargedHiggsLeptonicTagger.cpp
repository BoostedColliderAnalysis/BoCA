#include "ChargedHiggsLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

ChargedHiggsLeptonicTagger::ChargedHiggsLeptonicTagger()
{
//     DebugLevel = Severity::debug;

    Note("Constructor");
    set_tagger_name("ChargedHiggsLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_leptonic_reader_.SetTagger(top_leptonic_tagger_);
    DefineVariables();
}

int ChargedHiggsLeptonicTagger::Train(Event &event, const Tag tag)
{
    Info("Higgs Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets<TopLeptonicTagger>(event);
    Info("Number of doublets", doublets.size());

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.SingletJet1() == Jet) continue;
            Triplet triplet(doublet, Jet);
//             triplet.SetTag(GetTag(triplet));
            if (triplet.Tag() != tag) continue;
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartet(quartet, MissingEt, Neutrinos, Tag);
//             for (auto & quartet : Prequartets) {
            triplets.emplace_back(triplet);
//             }
        }
    }
    Info("Numeber of triplets", triplets.size());


    if (tag == Tag::signal && triplets.size() > 1) {
        Error("Higgs Candidates", triplets.size());
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    return SaveEntries(triplets);
}

std::vector<Triplet>  ChargedHiggsLeptonicTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Info("Bdt");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets<TopLeptonicTagger>(event);

    std::vector<Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & jet : jets)  {
            if (doublet.SingletJet1() == jet) continue;
            Triplet triplet(doublet, jet);
//             triplet.SetTag(GetTag(triplet));
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartets(quartet, MissingEt);
//             for (auto & quartet : Prequartets) {
            triplet.SetBdt(Bdt(triplet, reader));
            triplets.emplace_back(triplet);
//             }
        }
    }
    return ReduceResult(triplets);
}

}

}
