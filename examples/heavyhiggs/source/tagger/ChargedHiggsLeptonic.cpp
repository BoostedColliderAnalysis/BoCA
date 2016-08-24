#include "include/tagger/ChargedHiggsLeptonic.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs {

namespace tagger {

int ChargedHiggsLeptonic::Train(boca::Event const& event, PreCuts const&, const Tag)
{
    INFO0;
   auto jets = bottom_reader_.Jets(event);
    auto triplets = top_leptonic_reader_.Multiplets(event);
    INFO(triplets.size());
    /*
        auto triplets = std::vector<Triplet>{};
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

std::vector<Triplet>  ChargedHiggsLeptonic::Multiplets(boca::Event const&, PreCuts const& , TMVA::Reader const&)
{
    INFO0;
//    std::vector<Jet> jets = bottom_reader_.Jets(event);
//     std::vector<Doublet> doublets = top_leptonic_reader_.Multiplets(event);
//
//     auto triplets = std::vector<Triplet>{};
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
