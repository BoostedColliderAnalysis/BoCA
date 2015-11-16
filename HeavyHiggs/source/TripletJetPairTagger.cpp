/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TripletJetPairTagger.hh"
#include "Sort.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

int TripletJetPairTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info("W Tags");
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets(event);
//     Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.SaveBdt(jets, WReader);
    //     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(doublets, jets, TopHadronicReader);
//     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(jets, top_hadronic_reader_, WTagger, WReader, bottom_tagger_, bottom_reader_);
    Debug("Number of Hadronic Tops", triplets.size());
//     for (auto const& Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.SaveBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.SaveBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     for (auto const& Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 3);
    //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.SaveBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.SaveBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     if (triplets.size() > 3) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
//     }
//     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(jets, TopHadronicReader);
    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = CopyIfFamily(TopParticles, Id::top, Id::gluon);
    if (TopParticles.size() != 1 && tag == Tag::signal)
        Error("Where is the Top?", TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal :
        for (auto const& triplet : triplets) if (Close(TopParticles.front())(triplet.Jet()))
                Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && triplets.size() > 0) triplets.erase(triplets.begin());
    Jets BottomParticles = event.Partons().GenParticles();
    BottomParticles = CopyIfFamily(BottomParticles, Id::bottom, Id::gluon);
    if (BottomParticles.size() != 1 && tag == Tag::signal)
        Error("Where is the Bottom?", BottomParticles.size());
    Jets FinalJets;
    switch (tag) {
    case  Tag::signal :
        for (auto const& Jet : jets) if (Close(BottomParticles.front())(Jet))
                FinalJets.emplace_back(Jet);
        break;
    case Tag::background :
        FinalJets = jets;
        break;
    }
//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());
    std::vector<Quartet31> quartets;
    for (auto const& triplet : triplets)
        for (auto const& Jet : jets) {
            Quartet31 quartet(triplet, Jet);
            if (quartet.Overlap())
                continue;
//             if (quartet.DeltaR() < 2) continue;
//             quartet.SetTag(GetTag(quartet));
//             if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }
    Debug("Number of Jet Pairs", quartets.size());
    if (tag == Tag::signal && quartets.size() > 1) {
        quartets = SortedByMaxDeltaRap(quartets);
//         std::sort(quartets.begin(), quartets.end(), SortedByDeltaRap());
        if (quartets.size() > 1)
            quartets.erase(quartets.begin() + 1, quartets.end());
    }
    return SaveEntries(quartets);
//     std::vector<TripletJetPairBranch> JetPairBranches;
//     for (auto const& quartet : quartets) JetPairBranches.emplace_back(GetBranch(quartet));
//     return JetPairBranches;
}

std::vector<Quartet31>  TripletJetPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Jets jets = bottom_reader_.Jets(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets(event);
    std::vector<Quartet31>  quartets;
    for (auto const& triplet : triplets)
        for (auto const& Jet : jets)  {
            Quartet31 quartet(triplet, Jet);
            if (quartet.Overlap())
                continue;
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return ReduceResult(quartets);
}
std::string TripletJetPairTagger::Name() const
{
    return "TripletJetJetPair";
}

}
