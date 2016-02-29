/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include<functional>
#include "boost/range/algorithm/find_if.hpp"
#include "Vector.hh"

#include "Types.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca
{

struct RelativeIs {
    RelativeIs(Relative relative, Id id) {
        relative_ = relative;
        ids_ = {id};
    }
    RelativeIs(Relative relative, std::vector<Id> ids) {
        relative_ = relative;
        ids_ = ids;
    }
    bool operator()(Particle const& jet) const {
        return boost::range::find_if(ids_, [&](Id id) {
            return std::abs(jet.Info().Family().Member(relative_).Id()) == to_unsigned(id);
        }) != ids_.end();
    }
    Relative relative_;
    std::vector<Id> ids_;
};

struct RelativeIsExactly {
    RelativeIsExactly(Relative relative, int id) {
        relative_ = relative;
        ids_ = {id};
    }
    RelativeIsExactly(Relative relative, std::vector<int> ids) {
        relative_ = relative;
        ids_ = ids;
    }
    bool operator()(Particle const& jet) const {
        return boost::range::find_if(ids_, [&](int id) {
            return jet.Info().Family().Member(relative_).Id() == id;
        }) != ids_.end();
    }
    Relative relative_;
    std::vector<int> ids_;
};

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const& particles, Relative relative, Id id)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIs(relative, id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const& particles, Relative relative, std::vector<Id> ids)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIs(relative, ids)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIsExactly(std::vector<Particle> const& particles, Relative relative, int id)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIsExactly(relative, id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfRelativeIsExactly(std::vector<Particle> const& particles, Relative relative, std::vector<int> ids)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(RelativeIsExactly(relative, ids)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> RemoveIfRelativeIs(std::vector<Particle> particles, Relative relative, Id id)
{
    return boost::range::remove_erase_if(particles, RelativeIs(relative, id));
}

std::vector<Particle> RemoveIfRelativeIs(std::vector<Particle> particles, Relative relative, std::vector<Id> id)
{
    return boost::range::remove_erase_if(particles, RelativeIs(relative, id));
}

std::vector<Particle> RemoveIfRelativeIsExactly(std::vector<Particle> particles, Relative relative, int id)
{
    return boost::range::remove_erase_if(particles, RelativeIsExactly(relative, id));
}

std::vector<Particle> RemoveIfRelativeIsExactly(std::vector<Particle> particles, Relative relative, std::vector<int> id)
{
    return boost::range::remove_erase_if(particles, RelativeIsExactly(relative, id));
}

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id)
{
    return CopyIfRelativeIs(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& particles, std::vector<Id> ids)
{
    return CopyIfRelativeIs(particles, Relative::particle, ids);
}

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& particles, int id)
{
    return CopyIfRelativeIsExactly(particles, Relative::particle, id);
}

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> particles, int id)
{
    return RemoveIfRelativeIsExactly(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::neutrino));
}

std::vector<Particle> CopyIfLepton(std::vector<Particle> const& particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::charged_lepton));
}

std::vector<Particle> CopyIfFamily(std::vector<Particle> const& particles, Id id, Id mother_id)
{
    return CopyIfRelativeIs(CopyIfRelativeIs(particles, Relative::particle, id), Relative::mother, mother_id);
}

std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> particles, Id id , Id grand_mother_id)
{
    return CopyIfRelativeIs(CopyIfRelativeIs(particles, Relative::particle, id), Relative::grand_mother, grand_mother_id);
}

std::vector<Particle> RemoveIfParticle(std::vector<Particle> particles, Id id)
{
    return RemoveIfRelativeIs(particles, Relative::particle, id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Id mother_id)
{
    return CopyIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, std::vector<Id> mother_id)
{
    return CopyIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Particle mother)
{
    std::vector<Particle> daughters;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::mother).Position() == mother.Info().Family().Member(Relative::particle).Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Particle grand_mother)
{
    std::vector<Particle> daughters;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::grand_mother).Position() == grand_mother.Info().Family().Member(Relative::particle).Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> RemoveIfMother(std::vector<Particle> particles, Id mother_id)
{
    return RemoveIfRelativeIs(particles, Relative::mother, mother_id);
}

std::vector<Particle> RemoveIfMother(std::vector<Particle> particles, std::vector<Id> ids)
{
    return RemoveIfRelativeIs(particles, Relative::mother, ids);
}

std::vector<Particle> RemoveIfOnlyMother(std::vector<Particle> particles, Id id)
{
    return boost::range::remove_erase_if(particles, [&](Particle const & particle) {
        return RelativeIs(Relative::mother, id)(particle) && RelativeIs(Relative::step_mother, Id::none)(particle);
    });
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Id grand_mother_id)
{
    return CopyIfRelativeIs(particles, Relative::grand_mother, grand_mother_id);
}

std::vector<Particle> CopyIfGreatGrandMother(std::vector<Particle> const& particles, Id great_grand_mother_id)
{
    return CopyIfRelativeIs(particles, Relative::great_grand_mother, great_grand_mother_id);
}

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> particles)
{
    return RemoveIfRelativeIs(particles, Relative::step_mother, Id::none);
}

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> particles)
{
    return RemoveIfRelativeIs(particles, Relative::particle, Resolve(MultiId::charged_lepton));
}

std::vector<Particle> RemoveIfQuark(std::vector<Particle> particles)
{
    return RemoveIfRelativeIs(particles, Relative::particle, Resolve(MultiId::quark));
}

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::quark));
}

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& particles)
{
    return CopyIfRelativeIs(particles, Relative::particle, Resolve(MultiId::five_quark));
}

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters)
{
    std::vector<Particle> mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&daughters](Particle const & particle) {
        for (auto const & daughter : daughters) if (particle.Info().Family().Member(Relative::particle).Position() == daughter.Info().Family().Member(Relative::mother).Position()) return true;
        return false;
    }), std::back_inserter(mothers));
    return mothers;
}

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& grand_daughters)
{
    std::vector<Particle> grand_mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&grand_daughters](Particle const & particle) {
        for (auto const & daughter : grand_daughters) if (particle.Info().Family().Member(Relative::particle).Position() == daughter.Info().Family().Member(Relative::grand_mother).Position()) return true;
        return false;
    }), std::back_inserter(grand_mothers));
    return grand_mothers;
}

std::vector<Particle> CopyIfPosition(std::vector<Particle> const& particles, int position_1, int position_2)
{
    std::vector<Particle> good;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Member(Relative::particle).Position() == position_1 || particle.Info().Family().Member(Relative::particle).Position() == position_2;
    }), std::back_inserter(good));
    return good;
}
std::vector< Particle > CopyIfDrellYan(const std::vector< Particle >& particles)
{
    return CopyIfPosition(particles, 6, 7);
}

}
