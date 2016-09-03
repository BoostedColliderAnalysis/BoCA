/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Sort.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Particles.hh"

#include "heavyhiggs/tagger/TripletJetPair.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

using namespace boca;

namespace tagger
{

int TripletJetPair::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO("W Tags");
    auto jets = bottom_reader_.Jets(event);
    auto triplets = top_hadronic_reader_.Multiplets(event);
//    std::vector<Jet> jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.SaveBdt(jets, WReader);
    //     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(doublets, jets, TopHadronicReader);
//     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(jets, top_hadronic_reader_, WTagger, WReader, bottom_tagger_, bottom_reader_);
    DEBUG("Number of Hadronic Tops", triplets.size());
//     for (auto const& Jet : jets) {
//        std::vector<Jet> Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.SaveBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.SaveBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     for (auto const& Jet : jets) {
//        std::vector<Jet> Pieces = WTagger.GetSubJets(Jet, 3);
    //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.SaveBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.SaveBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     if (triplets.size() > 3) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + std::min(max_combi(), static_cast<int>(triplets.size())), triplets.end());
//     }
//     std::vector<Triplet> triplets = top_hadronic_tagger.SaveBdt(jets, TopHadronicReader);
    auto TopParticles = event.GenParticles();
    TopParticles = CopyIfFamily(TopParticles, Id::top, Id::gluon);
    if (TopParticles.size() != 1 && tag == Tag::signal)
        ERROR("Where is the Top?", TopParticles.size());
    std::vector<Triplet> Finaltriplets;
    switch (tag) {
    case Tag::signal :
        for (auto const & triplet : triplets) if (Close<Particle>(TopParticles.front())(triplet))
                Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && !triplets.empty()) triplets.erase(triplets.begin());
    auto BottomParticles = event.GenParticles();
    BottomParticles = CopyIfFamily(BottomParticles, Id::bottom, Id::gluon);
    if (BottomParticles.size() != 1 && tag == Tag::signal)
        ERROR("Where is the Bottom?", BottomParticles.size());
    std::vector<boca::Jet> FinalJets;
    switch (tag) {
    case  Tag::signal :
        for (auto const & Jet : jets) if (Close<Particle>(BottomParticles.front())(Jet))
                FinalJets.emplace_back(Jet);
        break;
    case Tag::background :
        FinalJets = jets;
        break;
    }
//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && !jets.empty()) jets.erase(jets.begin());
    std::vector<Quartet31> quartets;
    for (auto const & triplet : triplets)
        for (auto const & Jet : jets) {
            Quartet31 quartet(triplet, Jet);
            if (quartet.Overlap())
                continue;
//             if (quartet.DeltaR() < 2) continue;
//             quartet.SetTag(GetTag(quartet));
//             if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }
    DEBUG("Number of Jet Pairs", quartets.size());
    if (tag == Tag::signal && quartets.size() > 1) {
        quartets = SortedByMaxDeltaRap(quartets);
//         std::sort(quartets.begin(), quartets.end(), SortedByDeltaRap());
        if (quartets.size() > 1)
            quartets.erase(quartets.begin() + 1, quartets.end());
    }
    return SaveEntries(quartets);
//     std::vector<TripletJetPair> JetPaires;
//     for (auto const& quartet : quartets) JetPaires.emplace_back(Get(quartet));
//     return JetPaires;
}

std::vector<Quartet31>  TripletJetPair::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    auto jets = bottom_reader_.Jets(event);
    auto triplets = top_hadronic_reader_.Multiplets(event);
    std::vector<Quartet31>  quartets;
    for (auto const & triplet : triplets)
        for (auto const & Jet : jets)  {
            Quartet31 quartet(triplet, Jet);
            if (quartet.Overlap())
                continue;
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    return quartets;
}
std::string TripletJetPair::Name() const
{
    return "TripletJetJetPair";
}

}

}
