/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "boca/generic/Vector.hh"
#include "boca/Settings.hh"

namespace boca
{

/**
 * @ingroup Physics
 * @defgroup Vector Vector
 * @brief Functions used for Container (mainly std::vector) manipulation
 * @{
 */

template <typename Multiplet_>
std::vector<Multiplet_> RemoveIfOutsidePtWindow(std::vector<Multiplet_> jets, Momentum const &lower_cut, Momentum const &upper_cut)
{
    return boost::range::remove_erase_if(jets, [lower_cut, upper_cut](Multiplet_ const & jet) {
        return jet.Pt() < lower_cut || jet.Pt() > upper_cut;
    });
}

/**
 * @brief Copy if Bdt value of multiplet is larger than value (default = 0)
 *
 */
template<typename Multiplet_>
std::vector<Multiplet_> CopyIfTag(std::vector<Multiplet_> const &multiplets, double value = 0)
{
    return CopyIf(multiplets, [value](Multiplet_ const & multiplet) {
        return multiplet.Bdt() > value;
    });
}

template<typename Multiplet_>
std::vector<Multiplet_> RemoveIfSoft(std::vector<Multiplet_> multiplets, Momentum const &pt_min)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet_ const & multiplet) {
        return multiplet.Pt() < pt_min;
    });
}

template<typename Multiplet_>
std::vector<Multiplet_> RemoveIfHard(std::vector<Multiplet_> multiplets, Momentum const &pt_max)
{
    return boost::range::remove_erase_if(multiplets, [&](Multiplet_ const & multiplet) {
        return multiplet.Pt() > pt_max;
    });
}

template<typename Multiplet_>
auto CountIfHard(std::vector<Multiplet_> multiplets, Momentum const &pt_min)
{
    return boost::range::count_if(multiplets, [pt_min](Multiplet_ const & multiplet) {
        return multiplet.Pt() > pt_min;
    });
}

template <typename Multiplet_1_>
class Close
{
public:
    Close(Multiplet_1_ const &particle) :
        particle_(particle) ,
        cone_size_(Settings::JetConeSize())
    {}
    Close(Multiplet_1_ const &particle, Angle const &cone_size) :
        particle_(particle) ,
        cone_size_(cone_size)
    {}
    template <typename Multiplet_2_>
    bool operator()(Multiplet_2_ const &multiplet)
    {
        return multiplet.DeltaRTo(particle_) < cone_size_;
    }
private:
    Multiplet_1_ particle_;
    Angle cone_size_;
};

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> RemoveIfClose(std::vector<Multiplet_1_> jets, std::vector<Multiplet_2_> const &particles)
{
    for (auto const &particle : particles) jets = boost::range::remove_erase_if(jets, Close<Multiplet_2_>(particle));
    return jets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
bool CrossComparison(Multiplet_1_ const &multiplet, std::pair<Multiplet_2_, Multiplet_2_> const &particles)
{
    return (Close<Multiplet_2_>(particles.first)(multiplet.Multiplet1()) && Close<Multiplet_2_>(particles.second)(multiplet.Multiplet2())) || (Close<Multiplet_2_>(particles.first)(multiplet.Multiplet2()) && Close<Multiplet_2_>(particles.second)(multiplet.Multiplet1()));
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> RemoveIfClose(std::vector<Multiplet_1_> jets, std::vector<std::pair<Multiplet_2_, Multiplet_2_>> const &particles)
{
    for (auto const &particle : particles) jets = boost::range::remove_erase_if(jets, [&](Multiplet_1_ const & multiplet) {
        return CrossComparison(multiplet, particle);
    });
    return jets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const &multiplets, std::vector<Multiplet_2_> const &particles)
{
    if (multiplets.empty()) return multiplets;
    auto close_multiplets = std::vector<Multiplet_1_> {};
    for (auto const &particle : particles) Insert(close_multiplets, CopyIfClose(multiplets, particle));
    return close_multiplets;
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const &multiplets, Multiplet_2_ const &particle)
{
    return CopyIf(multiplets, [&](Multiplet_1_ const & multiplet) {
        return Close<Multiplet_2_>(particle)(multiplet);
    });
}

template <typename Multiplet_1_, typename Multiplet_2_>
std::vector<Multiplet_1_> CopyIfClose(std::vector<Multiplet_1_> const &multiplets, std::pair<Multiplet_2_, Multiplet_2_> const &particle)
{
    return CopyIf(multiplets, [&](Multiplet_1_ const & multiplet) {
        return CrossComparison(multiplet, particle);
    });
}

// template <typename Multiplet_>
// std::vector<Multiplet_> CopyIfClose(std::vector<Multiplet_> const& multiplets, std::vector<std::pair<Particle, Particle>> const& particles)
// {
//     if (multiplets.empty()) return multiplets;
//     std::vector<Multiplet_> final_multiplets;
//     for (auto const & particle : particles) for (auto const & multiplet : multiplets) if (CrossComparison(multiplet, particle)) final_multiplets.emplace_back(multiplet);
//     return final_multiplets;
// }

// @}

}
