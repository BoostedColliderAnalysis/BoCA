/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "JetPairTagger.hh"
#include "HeavyHiggsSemiTagger.hh"
#include "Event.hh"
#include "Sort.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

// int JetPairTagger::Train(Event const& event, PreCuts const& , Tag tag) const
// {
//     INFO0;
//     std::vector<Jet> jets = bottom_reader_.Jets(event);
//     if (jets.empty()) return 0;
//     DEBUG(jets.size());
//     std::vector<Particle> bottoms = TruthJetPair(event, tag);
//     std::vector<Particle> higgs = HeavyHiggsSemiTagger::HiggsParticle(event, jets, tag);
//     DEBUG(bottoms.size());
//     std::vector<Jet> bottom_jets;
//     std::vector<Jet> bad_bottom_jets;
//     switch (tag) {
//     case Tag::signal :
//         for (auto const & bottom : bottoms) {
//             jets = SortedByMinDeltaRTo(jets, bottom);
//             if (Close(jets.at(1))(bottom))continue;
//             if (Close(jets.at(0))(bottom))bottom_jets.emplace_back(jets.front());
//         }
//         break;
//     case Tag::background :
//         bottom_jets = jets;
//         break;
//     }
// //    std::vector<Jet> bottom_jets = BestMatches(jets,bottoms,tag);
//     std::vector<Doublet> doublets;
//     for (auto jet1 = bottom_jets.begin(); jet1 != bottom_jets.end(); ++jet1)
//         for (auto jet2 = jet1 + 1; jet2 != bottom_jets.end(); ++jet2) {
//             Doublet doublet;
//             if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
//             else doublet.SetMultiplets(*jet2, *jet1);
//
//             if (bottoms.size() == 2 && !higgs.empty() && tag == Tag::background) {
//                 if (CheckIfBadBottom(doublet, bottoms)) continue;
//             }
//
//             if (doublet.Overlap())continue;
//             doublet.SetTag(tag);
//             doublets.emplace_back(doublet);
//         }
//     DEBUG(doublets.size());
//     if (tag == Tag::signal && doublets.size() > 1) {
//         ERROR(doublets.size());
//         doublets = SortedByMaxDeltaRap(doublets);
//         if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());  //FIXME  sorted by what?
//     }
//     return SaveEntries(doublets);
// }

std::vector<Particle>JetPairTagger::PairBottomQuarks(Event const& event, Tag tag) const
{
    if (tag == Tag::background) return std::vector<Particle> {};
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> bottom_not_from_even = RemoveIfGrandFamily(particles, Id::bottom, Id::heavy_higgs);
    std::vector<Particle> bottom_not_from_higgs = RemoveIfGrandFamily(bottom_not_from_even, Id::bottom, Id::CP_odd_higgs);
    return bottom_not_from_higgs;
}

// std::vector<Doublet> JetPairTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
// {
//     std::vector<Jet> jets = bottom_reader_.Jets(event);
//     std::vector<Doublet>  doublets;
//     for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1)
//         for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
//             Doublet doublet;
//             if (std::abs((*jet_1).rap()) > std::abs((*jet_2).rap()))
//                 doublet.SetMultiplets(*jet_1, *jet_2);
//             else
//                 doublet.SetMultiplets(*jet_2, *jet_1);
//             if (doublet.Overlap())continue;
//             doublet.SetBdt(Bdt(doublet, reader));
//             doublets.emplace_back(doublet);
//         }
//     return ReduceResult(doublets, 6);
// }

bool JetPairTagger::CheckIfBadBottom(boca::Doublet const& doublet, std::vector<Particle> const& jets)const
{
    if ((Close(jets.at(0))(doublet.Singlet1().Jet()) && Close(jets.at(1))(doublet.Singlet2().Jet())) || (Close(jets.at(1))(doublet.Singlet1().Jet()) && Close(jets.at(0))(doublet.Singlet2().Jet())))return true;
    else return false;

}

std::vector<Particle> JetPairTagger::HiggsParticle(Event const& event, Tag tag) const
{
    if (tag == Tag::background) return std::vector<Particle> {};
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    std::vector<Particle> odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return Join(even, odd);
}

std::string JetPairTagger::Name() const
{
    return "JetPair";
}


int JetPairTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    INFO0;
    std::vector<Jet> jets = bottom_reader_.Multiplets(event);
    if (jets.size() < 2) return 0;
    DEBUG(jets.size());
    std::vector<Particle> higgs = HeavyHiggsSemiTagger::HiggsParticle(event, tag);
    std::vector<Jet> bottom_jets = TruthJetPair(event, jets, tag);

    std::vector<Particle> bottoms = PairBottomQuarks(event, tag);
    std::vector<Doublet> doublets;
    for (auto jet1 = bottom_jets.begin(); jet1 != bottom_jets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != bottom_jets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);
            if (tag == Tag::background && !higgs.empty() && bottoms.size() == 2 && CheckIfBadBottom(doublet, bottoms)) continue;
            if (doublet.Overlap())continue;
//             for (auto jet : jets) if (jet != *jet1 && jet != *jet2) doublet.AddRestJet(jet); // FIXME reactivate this
            if (doublet.Jets().size() != jets.size() - 2) ERROR("to many jets in the rest jet vector");
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }

    if (tag == Tag::signal && doublets.size() > 1) {
        doublets = SortedByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());
    }
    return SaveEntries(doublets);
}

std::vector<Jet> JetPairTagger::TruthJetPair(Event const& event, std::vector<Jet>& jets, Tag tag) const
{
    std::vector<Particle> bottoms = PairBottomQuarks(event, tag);
    std::vector<Jet> bottom_jets;
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() != 2) ERROR(bottoms.size());
        for (const auto & bottom : bottoms) {
            jets = SortedByMinDeltaRTo(jets, bottom);
            if (Close(jets.at(1))(bottom)) continue;
            if (Close(jets.at(0))(bottom)) bottom_jets.emplace_back(jets.front());
        }
        break;
    case Tag::background :
        bottom_jets = jets;
        break;
    }
    return bottom_jets;
}

std::vector<Doublet> JetPairTagger::TruthDoubletPairs(Event const& event, std::vector<Doublet>& doublets, Tag tag) const
{
    std::vector<Particle> bottoms = PairBottomQuarks(event, tag);

    std::vector<Doublet> final_doublets;
    for (const auto & doublet : doublets) try {
            final_doublets.emplace_back(TruthDoubletPair(doublet, bottoms, tag));
        } catch (char const*) {};

    return final_doublets;
}

Doublet JetPairTagger::TruthDoubletPair(Doublet const& doublet, std::vector<Particle> const& bottoms, Tag tag) const
{
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() != 2) {
            ERROR(bottoms.size());
            break;
        }
        if ((Close(bottoms.at(0))(doublet.Singlet1().Jet()) && Close(bottoms.at(1))(doublet.Singlet2().Jet())) || (Close(bottoms.at(1))(doublet.Singlet1().Jet()) && Close(bottoms.at(0))(doublet.Singlet2().Jet()))) {
            return doublet;
        }
        break;
    case Tag::background : return doublet;
    }
    throw "Problematic";
}

std::vector<Doublet> JetPairTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    std::vector<Jet> jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet>  doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1)
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet;
            if (std::abs((*jet_1).rap()) > std::abs((*jet_2).rap())) doublet.SetMultiplets(*jet_1, *jet_2);
            else doublet.SetMultiplets(*jet_2, *jet_1);
            if (doublet.Overlap())continue;
//             for (auto jet : jets)  if (jet != *jet_1 && jet != *jet_2) doublet.AddRestJet(jet); // FIXME reactivate this
            if (doublet.Jets().size() != jets.size() - 2) ERROR("to many jets in the rest jet vector");
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets, 6);
}

}

}
