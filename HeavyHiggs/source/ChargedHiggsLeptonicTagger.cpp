#include "ChargedHiggsLeptonicTagger.hh"
#include "generic/DEBUG.hh"

namespace boca {

namespace heavyhiggs {

int ChargedHiggsLeptonicTagger::Train(Event const& event, PreCuts const&, const Tag) const
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_leptonic_reader_.Multiplets(event);
    INFO(triplets.size());
    /*
        std::vector<Triplet> triplets;
        for (auto const& triplet : triplets) {
            for (auto const& Jet : jets)  {
                if (triplet.Singlet1() == Jet) continue;
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
        INFO("Numeber of triplets", triplets.size());


        if (tag == Tag::signal && triplets.size() > 1) {
            ERROR("Higgs Candidates", triplets.size());
            std::sort(triplets.begin(), triplets.end());
            triplets.erase(triplets.begin() + 1, triplets.end());
        }

        return SaveEntries(triplets);*/
    return 1;
}

std::vector<Triplet>  ChargedHiggsLeptonicTagger::Multiplets(Event const&, PreCuts const& , TMVA::Reader const&) const
{
    INFO0;
//    std::vector<Jet> jets = bottom_reader_.Jets(event);
//     std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets(event);
//
//     std::vector<Triplet> triplets;
//     for (auto const& doublet : doublets) {
//         for (auto const& jet : jets)  {
//             if (doublet.Singlet1() == jet) continue;
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
    return std::vector<Triplet>{};
}

}

}
