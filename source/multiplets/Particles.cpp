/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
// #include <functional>
#include "boost/range/algorithm/find_if.hpp"
#include "boost/range/algorithm/sort.hpp"
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>

#include "boca/generic/Types.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

struct RelativeIs {
    RelativeIs(Relative relative, Id id)
    {
        relative_ = relative;
        id_ = id;
    }
    bool operator()(Particle const &jet) const
    {
        return std::abs(jet.Info().Family().Member(relative_).Id()) == to_int(id_);
    }
    Relative relative_;
    Id id_;
};

struct RelativeIs2 {
    RelativeIs2(Relative relative, std::vector<Id> const &ids)
    {
        relative_ = relative;
        ids_ = ids;
    }
    bool operator()(Particle const &jet) const
    {
        return boost::range::find_if(ids_, [&](Id id) {
            return std::abs(jet.Info().Family().Member(relative_).Id()) == to_int(id);
        }) != ids_.end();
    }
    Relative relative_;
    std::vector<Id> ids_;
};

struct RelativeIsExactly {
    RelativeIsExactly(Relative relative, int id)
    {
        relative_ = relative;
        ids_ = {id};
    }
    RelativeIsExactly(Relative relative, std::vector<int> const &ids)
    {
        relative_ = relative;
        ids_ = ids;
    }
    bool operator()(Particle const &jet) const
    {
        return boost::range::find_if(ids_, [&](int id) {
            return jet.Info().Family().Member(relative_).Id() == id;
        }) != ids_.end();
    }
    Relative relative_;
    std::vector<int> ids_;
};

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const &particles, Relative relative, Id id)
{
    auto matches = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIs(relative, id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const &particles, Relative relative, std::vector<Id> const &ids)
{
    auto matches = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIs2(relative, ids)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIsExactly(std::vector<Particle> const &particles, Relative relative, int id)
{
    auto matches = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIsExactly(relative, id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIsExactly(std::vector<Particle> const &particles, Relative relative, std::vector<int> const &ids)
{
    auto matches = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIsExactly(relative, ids)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> RemoveIfRelativeIs(std::vector<Particle> particles, Relative relative, Id id)
{
    return boost::range::remove_erase_if(particles, RelativeIs(relative, id));
}

std::vector<Particle> RemoveIfRelativeIs(std::vector<Particle> particles, Relative relative, std::vector<Id> const &id)
{
    return boost::range::remove_erase_if(particles, RelativeIs2(relative, id));
}

std::vector<Particle> RemoveIfRelativeIsExactly(std::vector<Particle> particles, Relative relative, int id)
{
    return boost::range::remove_erase_if(particles, RelativeIsExactly(relative, id));
}

std::vector<Particle> RemoveIfRelativeIsExactly(std::vector<Particle> particles, Relative relative, std::vector<int> const &id)
{
    return boost::range::remove_erase_if(particles, RelativeIsExactly(relative, id));
}

std::vector<Particle> CopyIfParticle(std::vector<Particle> const &particles, Id id)
{
    return CopyIfRelativeIs(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const &particles, std::vector<Id> const &ids)
{
    return CopyIfRelativeIs(particles, Relative::particle, ids);
}

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const &particles, int id)
{
    return CopyIfRelativeIsExactly(particles, Relative::particle, id);
}

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> const &particles, int id)
{
    return RemoveIfRelativeIsExactly(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const &particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::neutrino));
}

std::vector<Particle> CopyIfLepton(std::vector<Particle> const &particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::charged_lepton));
}

std::vector<Particle> CopyIfFamily(std::vector<Particle> const &particles, Id id, Id mother_id)
{
    return CopyIfRelativeIs(CopyIfRelativeIs(particles, Relative::particle, id), Relative::mother, mother_id);
}

std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> const &particles, Id id , Id grand_mother_id)
{
    return CopyIfRelativeIs(CopyIfRelativeIs(particles, Relative::particle, id), Relative::grand_mother, grand_mother_id);
}

std::vector<Particle> RemoveIfParticle(std::vector<Particle> const &particles, Id id)
{
    return RemoveIfRelativeIs(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const &particles, Id mother_id)
{
    return CopyIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const &particles, std::vector<Id> const &mother_id)
{
    return CopyIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const &particles, Particle mother)
{
    auto daughters = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::mother).Position() == mother.Info().Family().Member(Relative::particle).Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const &particles, Particle grand_mother)
{
    auto daughters = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::grand_mother).Position() == grand_mother.Info().Family().Member(Relative::particle).Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> RemoveIfMother(std::vector<Particle> const &particles, Id mother_id)
{
    return RemoveIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> RemoveIfMother(std::vector<Particle> const &particles, std::vector<Id> const &ids)
{
    return RemoveIfRelativeIs(particles, Relative::mother, ids);
}

std::vector<Particle> RemoveIfOnlyMother(std::vector<Particle> particles, Id id)
{
    return boost::range::remove_erase_if(particles, [&](Particle const & particle) {
        return RelativeIs(Relative::mother, id)(particle) && RelativeIs(Relative::step_mother, Id::none)(particle);
    });
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const &particles, Id grand_mother_id)
{
    return CopyIfRelativeIs(particles, Relative::grand_mother, grand_mother_id);
}

std::vector<Particle> CopyIfGreatGrandMother(std::vector<Particle> const &particles, Id great_grand_mother_id)
{
    return CopyIfRelativeIs(particles, Relative::great_grand_mother, great_grand_mother_id);
}

std::vector<Particle> CopyIfAncestor(std::vector<Particle> const &particles, Id id)
{
    auto matches = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([id](Particle const & particle) {
        return std::abs(particle.Info().Family().Member(Relative::mother).Id()) == to_int(id) || std::abs(particle.Info().Family().Member(Relative::step_mother).Id()) == to_int(id) || std::abs(particle.Info().Family().Member(Relative::grand_mother).Id()) == to_int(id) || std::abs(particle.Info().Family().Member(Relative::great_grand_mother).Id()) == to_int(id);
    }), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> const &particles)
{
    return RemoveIfRelativeIs(particles, Relative::step_mother, Id::none);
}

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> const &particles)
{
    return RemoveIfRelativeIs(particles, Relative::particle, Resolve(MultiId::charged_lepton));
}

std::vector<Particle> RemoveIfQuark(std::vector<Particle> const &particles)
{
    return RemoveIfRelativeIs(particles, Relative::particle, Resolve(MultiId::quark));
}

std::vector<Particle> CopyIfQuark(std::vector<Particle> const &particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::quark));
}

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const &particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::five_quark));
}

namespace
{

bool HasRelation(Particle const &particle, Particle const &member,  Relative relative)
{
    return particle.Info().Family().Member(Relative::particle).Position() == member.Info().Family().Member(relative).Position();
}

// bool HasRelation(Particle const &particle, std::vector<Particle> const &members,  Relative relative)
// {
//     for (auto const &member : members) if (HasRelation(particle,  member,  relative)) return true;
//     return false;
// }

bool HasRelation(Particle const &particle, std::vector<Particle> const &members,  Relative relative)
{
    return boost::range::find_if(members, [&](auto const& member) {
        return HasRelation(particle,  member,  relative);
    }) != members.end();
}

}

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const &particles, std::vector<Particle> const &daughters)
{
    auto mothers = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return HasRelation(particle,  daughters,  Relative::mother);
    }), std::back_inserter(mothers));
    return mothers;
}

std::vector<Particle> RemoveIfDaughter(std::vector<Particle> const &particles, std::vector<Particle> const &daughters)
{
    auto mothers = particles;
    return boost::range::remove_erase_if(mothers, [&daughters](Particle const & particle) {
        return HasRelation(particle,  daughters,  Relative::mother);
    });
}

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const &particles, std::vector<Particle> const &grand_daughters)
{
    auto grand_mothers = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&grand_daughters](Particle const & particle) {
        return HasRelation(particle,  grand_daughters,  Relative::grand_mother);
    }), std::back_inserter(grand_mothers));
    return grand_mothers;
}

std::vector<Particle> CopyIfPosition(std::vector<Particle> const &particles, int position)
{
    auto good = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::particle).Position() == position;
    }), std::back_inserter(good));
    return good;
}

std::vector<Particle> CopyIfPosition(std::vector<Particle> const &particles, int position_1, int position_2)
{
    auto good = std::vector<Particle> {};
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::particle).Position() == position_1 || particle.Info().Family().Member(Relative::particle).Position() == position_2;
    }), std::back_inserter(good));
    return good;
}

std::vector<Particle> CopyFirst(std::vector<Particle> particles, std::size_t number)
{
    if (particles.size() <= number) return particles;
    particles = boost::range::sort(particles, [](Particle const & particle_1, Particle const & particle_2) {
        return particle_1.Info().Family().Member(Relative::particle).Position() < particle_2.Info().Family().Member(Relative::particle).Position();
    });
    return {particles.begin(), particles.begin() + number};
}

std::vector< Particle > CopyIfDrellYan(const std::vector< Particle > &particles)
{
    return CopyIfPosition(particles, 6, 7);
}

namespace
{

template<typename Data>
void PrintCell(Data data)
{
    std::cout << std::right << std::setw(9) << std::setfill(' ') << data;
}

void PrintHeader()
{
    PrintCell(Name(Relative::particle));
    PrintCell(Name(Relative::mother));
    PrintCell(Name(Relative::step_mother));
    PrintCell(Name(Relative::particle));
    PrintCell(Name(Relative::mother));
    PrintCell(Name(Relative::step_mother));
    std::cout << '\n';
}

void PrintCells(Particle const &particle)
{
    PrintCell(particle.Info().Family().Member(Relative::particle).Name());
    PrintCell(particle.Info().Family().Member(Relative::mother).Name());
    PrintCell(particle.Info().Family().Member(Relative::step_mother).Name());
    PrintCell(particle.Info().Family().Member(Relative::particle).Position());
    PrintCell(particle.Info().Family().Member(Relative::mother).Position());
    PrintCell(particle.Info().Family().Member(Relative::step_mother).Position());
    std::cout << '\n';
}

}

void PrintParticles(std::vector<Particle> const &particles)
{
    INFO0;
    PrintHeader();
    for (auto const &particle : particles) PrintCells(particle);
}

}


