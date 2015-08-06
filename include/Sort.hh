#pragma once

#include <vector>

#include "fastjet/PseudoJet.hh"

#include "LorentzVector.hh"

namespace analysis
{

struct MinDeltaRTo {
    MinDeltaRTo(const fastjet::PseudoJet& jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet1, const Multiplet& multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    bool operator()(const fastjet::PseudoJet& jet1, const fastjet::PseudoJet& jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> multiplets, const fastjet::PseudoJet& jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

template <class Multiplet>
std::vector<Multiplet> SortedByMaxDeltaRap(std::vector<Multiplet> multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), [](const Multiplet & multiplet_1, const Multiplet & multiplet_2) {
            return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    });
    return multiplets;
}

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> multiplets, float mass)
{
    std::sort(multiplets.begin(), multiplets.end(), [mass](const Multiplet & Multiplet1, const Multiplet & Multiplet2) {
        return std::abs(Multiplet1.Jet().m() - mass) < std::abs(Multiplet2.Jet().m() - mass);
    });
    return multiplets;
}

struct SortByMass {
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet_1, const Multiplet& multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) {
        return jet_1.m() > jet_2.m();
    }
};

template <class Multiplet>
std::vector<Multiplet> SortedByMass(std::vector<Multiplet> multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMass());
    return multiplets;
}


struct SortByPt {
    template <typename Multiplet>
    bool operator()(const Multiplet& multiplet_1, const Multiplet& multiplet_2) {
        return multiplet_1.Jet().pt() > multiplet_2.Jet().pt();
    }
    bool operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2) {
        return jet_1.pt() > jet_2.pt();
    }
    bool operator()(const LorentzVector& lorentz_vector_1, const LorentzVector& lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }
//     bool operator()(const Constituent& constituent_1, const Constituent& constituent_2) {
//         return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
//     }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet> multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByPt());
    return multiplets;
}

}
