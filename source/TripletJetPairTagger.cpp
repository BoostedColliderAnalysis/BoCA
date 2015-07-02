#include "TripletJetPairTagger.hh"
#include "Predicate.hh"
#include "Debug.hh"

namespace analysis {

TripletJetPairTagger::TripletJetPairTagger()
{
    Note();
    set_tagger_name("TripletJetJetPair");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_hadronic_reader_.SetTagger(top_hadronic_tagger);
    DefineVariables();
}

int TripletJetPairTagger::Train(const Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag)
{
    Info("W Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
//     Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
//     std::vector<Doublet> doublets = WTagger.GetBdt(jets, WReader);
    //     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
//     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, top_hadronic_reader_, WTagger, WReader, bottom_tagger_, bottom_reader_);
    Debug("Number of Hadronic Tops", triplets.size());

//     for (const auto & Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }

//     for (const auto & Jet : jets) {
//         Jets Pieces = WTagger.GetSubJets(Jet, 3);
    //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader); // TODO reenable this
//         std::vector<Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, top_hadronic_reader_);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }

//     if (triplets.size() > 3) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());
//     }
//     std::vector<Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader);

    Jets TopParticles = event.Partons().GenParticles();
    TopParticles = RemoveIfWrongAbsFamily(TopParticles, Id::top, Id::gluon);
    if (TopParticles.size() != 1 && tag == Tag::signal) Error("Where is the Top?", TopParticles.size());

    std::vector<Triplet> Finaltriplets;
    switch(tag) {
    case Tag::signal :
      for (const auto & triplet : triplets) if (triplet.Jet().delta_R(TopParticles.front()) < DetectorGeometry().JetConeSize) Finaltriplets.emplace_back(triplet);
        break;
    case Tag::background :
        Finaltriplets = triplets;
        break;
    }
//     std::sort(triplets.begin(), triplets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) triplets.erase(triplets.begin() + 1, triplets.end());
//     if (Tag == HBackground && triplets.size() > 0) triplets.erase(triplets.begin());

    Jets BottomParticles = event.Partons().GenParticles();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, Id::bottom, Id::gluon);
    if (BottomParticles.size() != 1 && tag == Tag::signal) Error("Where is the Bottom?", BottomParticles.size());

    Jets FinalJets;
    switch (tag) {
    case  Tag::signal :
      for (const auto & Jet : jets) if (Jet.delta_R(BottomParticles.front()) < DetectorGeometry().JetConeSize) FinalJets.emplace_back(Jet);
        break;
    case Tag::background :
        FinalJets = jets;
        break;
    }

//     std::sort(jets.begin(), jets.end(), MinDeltaR(BottomParticles.front()));
//     if (Tag == Tag::signal && triplets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());


    std::vector<Quartet31> quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets) {
            Quartet31 quartet(triplet, Jet);
            if(quartet.Overlap()) continue;
//             if (quartet.DeltaR() < 2) continue;
//             quartet.SetTag(GetTag(quartet));
//             if (quartet.Tag() != Tag) continue;
            quartets.emplace_back(quartet);
        }

    Debug("Number of Jet Pairs", quartets.size());

    if (tag == Tag::signal && quartets.size() > 1) {
        quartets = SortByMaxDeltaRap(quartets);
//         std::sort(quartets.begin(), quartets.end(), SortedByDeltaRap());
        if (quartets.size() > 1)quartets.erase(quartets.begin() + 1, quartets.end());
    }

    return SaveEntries(quartets);

//     std::vector<TripletJetPairBranch> JetPairBranches;
//     for (const auto & quartet : quartets) JetPairBranches.emplace_back(GetBranch(quartet));

//     return JetPairBranches;

}

std::vector<Quartet31>  TripletJetPairTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Triplet> triplets = top_hadronic_reader_.Multiplets<TopHadronicTagger>(event);
    std::vector<Quartet31>  quartets;
    for (const auto & triplet : triplets)
        for (const auto & Jet : jets)  {
            Quartet31 quartet(triplet, Jet);
            if(quartet.Overlap()) continue;
            quartet.SetBdt(Bdt(quartet,reader));
            quartets.emplace_back(quartet);
        }
    std::sort(quartets.begin(), quartets.end());
    quartets.erase(quartets.begin() + std::min(max_combi(), int(quartets.size())), quartets.end());
    return quartets;
}

}
