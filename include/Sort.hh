/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>
#include <boost/range/algorithm/sort.hpp>

#include "Jet.hh"

#include "physics/Particles.hh"

namespace boca
{

struct MinDeltaRTo {
    MinDeltaRTo(Jet const& jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet1, Multiplet const& multiplet2) {
        return multiplet1.DeltaRTo(jet_) < multiplet2.DeltaRTo(jet_);
    }
    bool operator()(Jet const& jet1, Jet const& jet2) {
        return jet1.DeltaRTo(jet_)  < jet2.DeltaRTo(jet_);
    }
    Jet jet_;
};

template<typename Multiplet>
std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> multiplets, Jet const& jet)
{
    return boost::range::sort(multiplets, MinDeltaRTo(jet));
}

template <class Multiplet>
std::vector<Multiplet> SortedByMaxDeltaRap(std::vector<Multiplet> multiplets)
{
    return boost::range::sort(multiplets, [](const Multiplet & multiplet_1, const Multiplet & multiplet_2) {
        return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    });
}

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> multiplets, Mass mass)
{
    return boost::range::sort(multiplets, [mass](const Multiplet & multiplet_1, const Multiplet & multiplet_2) {
        return boost::units::abs(multiplet_1.Mass() - mass) < boost::units::abs(multiplet_2.Mass() - mass);
    });
}

struct SortByMassTo {
    SortByMassTo(Id id) {
        mass_ = MassOf(id);
    }
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return boost::units::abs(multiplet_1.Mass() - mass_) < boost::units::abs(multiplet_2.Mass() - mass_);
    }
    bool operator()(Jet const& jet_1, Jet const& jet_2) {
        return boost::units::abs(jet_1.Mass() - mass_) > boost::units::abs(jet_2.Mass() - mass_);
    }
    Mass mass_;
};

template <class Multiplet>
std::vector<Multiplet> SortedByMassTo(std::vector<Multiplet> multiplets, Id id)
{
    return boost::range::sort(multiplets, SortByMassTo(id));
}

struct SortByMass {
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return multiplet_1.Mass() > multiplet_2.Mass();
    }
    bool operator()(Jet const& jet_1, Jet const& jet_2) {
        return jet_1.Mass() > jet_2.Mass();
    }
};

template <class Multiplet>
std::vector<Multiplet> SortedByMass(std::vector<Multiplet> multiplets)
{
    return boost::range::sort(multiplets, SortByMass());
}


struct SortByPt {
    template <typename Multiplet>
    bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
        return multiplet_1.Pt() > multiplet_2.Pt();
    }
    bool operator()(Jet const& jet_1, Jet const& jet_2) {
        return jet_1.Pt() > jet_2.Pt();
    }
    bool operator()(LorentzVector<Momentum> const& lorentz_vector_1, LorentzVector<Momentum> const& lorentz_vector_2) {
        return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
    }
//     bool operator()(Constituent const& constituent_1, Constituent const& constituent_2) {
//         return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
//     }

};

template <class Multiplet>
std::vector<Multiplet> SortedByPt(std::vector<Multiplet> multiplets)
{
    return boost::range::sort(multiplets, SortByPt());
}


struct SortByRap {
  template <typename Multiplet>
  bool operator()(Multiplet const& multiplet_1, Multiplet const& multiplet_2) {
    return boost::units::abs(multiplet_1.Rap()) > boost::units::abs(multiplet_2.Rap());
  }
  bool operator()(Jet const& jet_1, Jet const& jet_2) {
    return boost::units::abs(jet_1.Rap()) > boost::units::abs(jet_2.Rap());
  }
  bool operator()(LorentzVector<Momentum> const& lorentz_vector_1, LorentzVector<Momentum> const& lorentz_vector_2) {
    return boost::units::abs(lorentz_vector_1.Rap()) > boost::units::abs(lorentz_vector_2.Rap());
  }
};

template <class Multiplet>
std::vector<Multiplet> SortedByRap(std::vector<Multiplet> multiplets)
{
  return boost::range::sort(multiplets, SortByRap());
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
    bool operator()(Jet const& jet_1, Jet const& jet_2) {
      return jet_1.Info().Bdt() > jet_2.Info().Bdt();
    }
};

template <typename Multiplet>
std::vector<Multiplet> SortedByBdt(std::vector<Multiplet>  multiplets)
{
    return boost::range::sort(multiplets, SortByBdt());
}


}
