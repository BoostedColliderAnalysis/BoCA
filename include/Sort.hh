/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>

#include "fastjet/PseudoJet.hh"

#include "LorentzVector.hh"
#include "Particles.hh"
#include "JetInfo.hh"

namespace boca
{

struct MinDeltaRTo {
    MinDeltaRTo(fastjet::PseudoJet const& jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet1, Multiplet const& multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    bool operator()(fastjet::PseudoJet const& jet1, fastjet::PseudoJet const& jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> multiplets, fastjet::PseudoJet const& jet)
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
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> multiplets, Mass mass)
{
    std::sort(multiplets.begin(), multiplets.end(), [mass](const Multiplet & multiplet_1, const Multiplet & multiplet_2) {
        return boost::units::abs(multiplet_1.Mass() - mass) < boost::units::abs(multiplet_2.Mass() - mass);
    });
    return multiplets;
}

struct SortByMassTo {
    SortByMassTo(Id id) {
        mass_ = MassOf(id);
    }
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return boost::units::abs(multiplet_1.Mass() - mass_) < boost::units::abs(multiplet_2.Mass() - mass_);
    }
    bool operator()(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
        return std::abs(jet_1.m() - mass_ / GeV) > std::abs(jet_2.m() - mass_ / GeV);
    }
    Mass mass_;
};

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> multiplets, Id id)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMassTo(id));
    return multiplets;
}

struct SortByMass {
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
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
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return multiplet_1.Pt() > multiplet_2.Pt();
    }
    bool operator()(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
        return jet_1.pt() > jet_2.pt();
    }
    bool operator()(LorentzVector const& lorentz_vector_1, LorentzVector const& lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }
//     bool operator()(Constituent const& constituent_1, Constituent const& constituent_2) {
//         return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
//     }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet> multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByPt());
    return multiplets;
}


/**
 * @brief sort vector of jets with largest bdt at the front
 *
 */
struct SortByBdt {
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return multiplet_1.Bdt() > multiplet_2.Bdt();
    }
    bool operator()(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2) {
        return jet_1.user_info<boca::JetInfo>().Bdt() > jet_2.user_info<boca::JetInfo>().Bdt();
    }
};

template <typename Multiplet>
std::vector<Multiplet> SortedByBdt(std::vector<Multiplet>  multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByBdt());
    return multiplets;
}


}
