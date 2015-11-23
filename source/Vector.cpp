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
        return (id == to_unsigned(id_1_) || id == to_unsigned(id_2_));
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

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& jets, Id id)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(IsParticle(id)), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& jets, Id id_1, Id id_2)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(IsParticle(id_1, id_2)), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& jets, std::vector<Id> ids)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(IsParticles(ids)), std::back_inserter(final_jets));
    return final_jets;
}

struct IsExactParticle {
    IsExactParticle(int id) {
        id_ = id;
    }
    bool operator()(Particle const& Jet) const {
        return (Jet.Info().Family().Particle().Id() == id_);
    }
    int id_;
};

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& jets, int id)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(IsExactParticle(id)), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> jets, int id)
{
    return boost::range::remove_erase_if(jets, IsExactParticle(id));
}

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& jets)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered([](Particle const & jet) {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return (id == to_unsigned(Id::electron_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::tau_neutrino));
    }), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> CopyIfLepton(std::vector<Particle> const& jets)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered([](Particle const & jet) {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return (id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon));
    }), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Jet> RemoveIfOutsidePtWindow(std::vector<Jet> jets, Momentum lower_cut, Momentum upper_cut)
{
    return boost::range::remove_erase_if(jets, [lower_cut, upper_cut](Jet const & jet) {
        return (jet.Pt() < lower_cut || jet.Pt() > upper_cut);
    });
}

std::vector<Particle> CopyIfFamily(std::vector<Particle> const& jets, Id id, Id mother_id)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered([id, mother_id](Particle const & Jet) {
        unsigned particle = std::abs(Jet.Info().Family().Particle().Id());
        unsigned mother = std::abs(Jet.Info().Family().Mother().Id());
        return (particle == to_unsigned(id) && mother == to_unsigned(mother_id));
    }), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> jets, Id id , Id grand_mother_id)
{
    return boost::range::remove_erase_if(jets, [id, grand_mother_id](Particle const & Jet) {
        unsigned particle = std::abs(Jet.Info().Family().Particle().Id());
        if (particle != to_unsigned(id)) return true;
        unsigned grand_mother = Jet.Info().Family().GrandMother().Id();
        return (grand_mother == to_unsigned(grand_mother_id));
    });
}

std::vector<Particle> RemoveIfParticle(std::vector<Particle> jets, Id id)
{
    return boost::range::remove_erase_if(jets, IsParticle(id));
}

struct HasMother {
    HasMother(Id mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Mother().Id());
        return id == to_unsigned(mother_id_);
    }
    Id mother_id_;
};

std::vector<Particle> CopyIfMother(std::vector<Particle> const& jets, Id mother_id)
{

    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(HasMother(mother_id)), std::back_inserter(final_jets));
    return final_jets;
}
std::vector<Particle> RemoveIfMother(std::vector<Particle> jets, Id mother_id)
{
    return boost::range::remove_erase_if(jets, HasMother(mother_id));
}

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& jets, Id grand_mother_id)
{

    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered([&](Particle const & jet) {
        unsigned grand_mother = std::abs(jet.Info().Family().GrandMother().Id());
        return grand_mother == to_unsigned(grand_mother_id);
    }), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> CopyIfGrandGrandMother(std::vector<Particle> const& jets, Id grand_grand_mother_id)
{

    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered([&](Particle const & jet) {
        unsigned grand_grand_mother = std::abs(jet.Info().Family().GreatGrandMother().Id());
        return grand_grand_mother == to_unsigned(grand_grand_mother_id);
    }), std::back_inserter(final_jets));
    return final_jets;
}


struct IsSingleMother {
    bool operator()(Particle const& Jet) const {
        unsigned id = std::abs(Jet.Info().Family().StepMother().Id());
        return id == to_unsigned(Id::empty);
    }
};

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> jets)
{
    return boost::range::remove_erase_if(jets, IsSingleMother());
}

struct IsLepton {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return (id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon) || id == to_unsigned(Id::tau) || id == to_unsigned(Id::tau_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::electron_neutrino));
    }
};

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> jets)
{
    return boost::range::remove_erase_if(jets, IsLepton());
}

struct IsQuark {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return (id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom) || id == to_unsigned(Id::top));
    }
};

std::vector<Particle> RemoveIfQuark(std::vector<Particle> jets)
{
    return boost::range::remove_erase_if(jets, IsQuark());
}

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& jets)
{
    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(IsQuark()), std::back_inserter(final_jets));
    return final_jets;
}

struct Is5Quark {
    bool operator()(Particle const& jet) const {
        unsigned id = std::abs(jet.Info().Family().Particle().Id());
        return (id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom));
    }
};

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& jets)
{

    std::vector<Particle> final_jets;
    boost::range::copy(jets | boost::adaptors::filtered(Is5Quark()), std::back_inserter(final_jets));
    return final_jets;
}

std::vector<Particle> RemoveIfSoft(std::vector<Particle> jets, Momentum pt_min)
{
    return boost::range::remove_erase_if(jets, [&](Jet const & jet) {
        return jet.Pt() < pt_min;
    });
}

std::vector<Particle> RemoveIfHard(std::vector<Particle> jets, Momentum pt_max)
{
    return boost::range::remove_erase_if(jets, [&](Jet const & jet) {
        return jet.Pt() > pt_max;
    });
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

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters)
{
    std::vector<Particle> mothers;
    boost::range::copy(particles | boost::adaptors::filtered([&daughters](Particle const & particle) {
        for (auto const & daughter : daughters) if (particle.Info().Family().Particle().Position() == daughter.Info().Family().GrandMother().Position()) return true;
        return false;
    }), std::back_inserter(mothers));
    return mothers;
}

}
