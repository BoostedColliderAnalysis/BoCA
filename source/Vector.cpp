/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Vector.hh"

#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>

#include "Types.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca
{

struct IsParticle {
    IsParticle(Id id_1) {
        id_1_ = id_1;
        id_2_ = id_1;
    }
    IsParticle(Id id_1, Id id_2) {
        id_1_ = id_1;
        id_2_ = id_2;
    }
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        Debug(id, to_unsigned(id_1_));
        return id == to_unsigned(id_1_) || id == to_unsigned(id_2_);
    }
    Id id_1_;
    Id id_2_;
};

struct IsParticles {
    IsParticles(std::vector<Id> const& ids) {
        ids_ = ids;
    }
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return std::find_if(ids_.begin(), ids_.end(), [&](Id id_2) {
            return id == to_unsigned(id_2);
        }) != ids_.end();
    }
    std::vector<Id> ids_;
};

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(IsParticle(id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& particles, Id id_1, Id id_2)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(IsParticle(id_1, id_2)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& particles, std::vector<Id> ids)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(IsParticles(ids)), std::back_inserter(matches));
    return matches;
}

struct IsExactParticle {
    IsExactParticle(int id) {
        id_ = id;
    }
    bool operator()(Particle const& Jet) const {
        return Jet.Info().Family().Particle().Id() == id_;
    }
    int id_;
};

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& particles, int id)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered(IsExactParticle(id)), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> particles, int id)
{
    return boost::range::remove_erase_if(particles, IsExactParticle(id));
}

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& particles)
{
    std::vector<Particle> neutrinos;
    boost::range::copy(particles | boost::adaptors::filtered([](Particle const & jet) {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return id == to_unsigned(Id::electron_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::tau_neutrino);
    }), std::back_inserter(neutrinos));
    return neutrinos;
}

std::vector<Particle> CopyIfLepton(std::vector<Particle> const& particles)
{
    std::vector<Particle> leptons;
    boost::range::copy(particles | boost::adaptors::filtered([](Particle const & jet) {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon);
    }), std::back_inserter(leptons));
    return leptons;
}

std::vector<Particle> CopyIfFamily(std::vector<Particle> const& particles, Id id, Id mother_id)
{
    std::vector<Particle> matches;
    boost::range::copy(particles | boost::adaptors::filtered([id, mother_id](Particle const & Jet) {
        unsigned particle = std::abs(Jet.Info().Family().Particle().Id());
        unsigned mother = std::abs(Jet.Info().Family().Mother().Id());
        return particle == to_unsigned(id) && mother == to_unsigned(mother_id);
    }), std::back_inserter(matches));
    return matches;
}

std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> jets, Id id , Id grand_mother_id)
{
    return boost::range::remove_erase_if(jets, [id, grand_mother_id](Particle const & Jet) {
        unsigned particle = std::abs(Jet.Info().Family().Particle().Id());
        if (particle != to_unsigned(id)) return true;
        unsigned grand_mother = Jet.Info().Family().GrandMother().Id();
        return grand_mother == to_unsigned(grand_mother_id);
    });
}

std::vector<Particle> RemoveIfParticle(std::vector<Particle> particles, Id id)
{
    return boost::range::remove_erase_if(particles, IsParticle(id));
}

struct HasMother {
    HasMother(Id mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(Particle const& particle) const {
        unsigned id = std::abs(particle.Info().Family().Mother().Id());
        return id == to_unsigned(mother_id_);
    }
    Id mother_id_;
};

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Id mother_id)
{
    std::vector<Particle> daughters;
    boost::range::copy(particles | boost::adaptors::filtered(HasMother(mother_id)), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Particle mother)
{
    std::vector<Particle> daughters;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Mother().Position() == mother.Info().Family().Particle().Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Particle grand_mother)
{
    std::vector<Particle> daughters;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().GrandMother().Position() == grand_mother.Info().Family().Particle().Position();
    }), std::back_inserter(daughters));
    return daughters;
}

std::vector<Particle> RemoveIfMother(std::vector<Particle> particles, Id mother_id)
{
    return boost::range::remove_erase_if(particles, HasMother(mother_id));
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Id grand_mother_id)
{

    std::vector<Particle> grand_mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & jet) {
        unsigned grand_mother = std::abs(jet.Info().Family().GrandMother().Id());
        return grand_mother == to_unsigned(grand_mother_id);
    }), std::back_inserter(grand_mothers));
    return grand_mothers;
}

std::vector<Particle> CopyIfGreatGrandMother(std::vector<Particle> const& particles, Id grand_grand_mother_id)
{

    std::vector<Particle> great_grand_mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & jet) {
        unsigned grand_grand_mother = std::abs(jet.Info().Family().GreatGrandMother().Id());
        return grand_grand_mother == to_unsigned(grand_grand_mother_id);
    }), std::back_inserter(great_grand_mothers));
    return great_grand_mothers;
}


struct IsSingleMother {
    bool operator()(Particle const& Jet) const {
        unsigned id = std::abs(Jet.Info().Family().StepMother().Id());
        return id == to_unsigned(Id::empty);
    }
};

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> particles)
{
    return boost::range::remove_erase_if(particles, IsSingleMother());
}

struct IsLepton {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon) || id == to_unsigned(Id::tau) || id == to_unsigned(Id::tau_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::electron_neutrino);
    }
};

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> particles)
{
    return boost::range::remove_erase_if(particles, IsLepton());
}

struct IsQuark {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom) || id == to_unsigned(Id::top);
    }
};

std::vector<Particle> RemoveIfQuark(std::vector<Particle> jets)
{
    return boost::range::remove_erase_if(jets, IsQuark());
}

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& particles)
{
    std::vector<Particle> quarks;
    boost::range::copy(particles | boost::adaptors::filtered(IsQuark()), std::back_inserter(quarks));
    return quarks;
}

struct Is5Quark {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom);
    }
};

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& particles)
{

    std::vector<Particle> quarks;
    boost::range::copy(particles | boost::adaptors::filtered(Is5Quark()), std::back_inserter(quarks));
    return quarks;
}

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters)
{
    std::vector<Particle> mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&daughters](Particle const & particle) {
        for (auto const & daughter : daughters) if (particle.Info().Family().Particle().Position() == daughter.Info().Family().Mother().Position()) return true;
        return false;
    }), std::back_inserter(mothers));
    return mothers;
}

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& grand_daughters)
{
    std::vector<Particle> grand_mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&grand_daughters](Particle const & particle) {
        for (auto const & daughter : grand_daughters) if (particle.Info().Family().Particle().Position() == daughter.Info().Family().GrandMother().Position()) return true;
        return false;
    }), std::back_inserter(grand_mothers));
    return grand_mothers;
}

std::vector<Particle> CopyIfPosition(std::vector<Particle> const& particles, int position_1, int position_2)
{
    std::vector<Particle> good;
    boost::range::copy(particles | boost::adaptors::filtered([&](Particle const & particle) {
        return particle.Info().Family().Particle().Position() == position_1 || particle.Info().Family().Particle().Position() == position_2;
    }), std::back_inserter(good));
    return good;
}
std::vector< Particle > CopyIfDrellYan(const std::vector< Particle >& particles)
{
    return CopyIfPosition(particles, 6, 7);
}

}
