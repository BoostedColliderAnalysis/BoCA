#include "ChargedHiggsLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

ChargedHiggsLeptonicTagger::ChargedHiggsLeptonicTagger()
{
    Note();
    DefineVariables();
}

int ChargedHiggsLeptonicTagger::Train(const Event& event, const PreCuts&, const Tag) const
{
    Info("Higgs Tags");
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    Info(triplets.size());
    /*
        std::vector<Triplet> triplets;
        for (const auto & triplet : triplets) {
            for (const auto & Jet : jets)  {
                if (triplet.SingletJet1() == Jet) continue;
                Triplet triplet(triplet, Jet);
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

        return SaveEntries(triplets);*/
    return 1;
}

std::vector<Triplet>  ChargedHiggsLeptonicTagger::Multiplets(const Event&, const PreCuts& , const TMVA::Reader&) const
{
    Info("Bdt");
//     Jets jets = bottom_reader_.Multiplets(event);
//     std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets(event);
//
//     std::vector<Triplet> triplets;
//     for (const auto & doublet : doublets) {
//         for (const auto & jet : jets)  {
//             if (doublet.SingletJet1() == jet) continue;
//             Triplet triplet(doublet, jet);
// //             triplet.SetTag(GetTag(triplet));
// //             std::vector<Quartet31> Prequartets;
// //             Prequartets = Getquartets(quartet, MissingEt);
// //             for (auto & quartet : Prequartets) {
//             triplet.SetBdt(Bdt(triplet, reader));
//             triplets.emplace_back(triplet);
// //             }
//         }
//     }
//     return ReduceResult(triplets);
    return std::vector<Triplet>{};
}

}

}
