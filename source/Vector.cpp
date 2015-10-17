/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Vector.hh"

#include <boost/range/algorithm_ext/erase.hpp>
// #include <boost/range/algorithm/copy.hpp>
// #include <boost/range/adaptors.hpp>

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
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
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
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return std::find_if(ids_.begin(), ids_.end(), [&](Id id_2) {
            return id == to_unsigned(id_2);
        }) != ids_.end();
    }
    std::vector<Id> ids_;
};

Jets CopyIfParticle(Jets const& jets, Id id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
//     return boost::range::copy(jets, boost::adaptors::filtered(IsParticle(id)), final_jets);
}

Jets CopyIfParticles(Jets const& jets, Id id_1, Id id_2)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id_1, id_2));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets CopyIfParticles(Jets const& jets, std::vector<Id> ids)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticles(ids));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

struct IsExactParticle {
    IsExactParticle(int id) {
        id_ = id;
    }
    bool operator()(fastjet::PseudoJet const& Jet) {
        return (Jet.user_info<ParticleInfo>().Family().particle().id() == id_);
    }
    int id_;
};

Jets CopyIfExactParticle(Jets const& jets, int id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsExactParticle(id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets RemoveIfExactParticle(Jets jets, int id)
{
    return boost::range::remove_erase_if(jets, IsExactParticle(id));
}

Jets CopyIfNeutrino(Jets const& jets)
{
    if (jets.empty())
        return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), [](fastjet::PseudoJet const & jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::electron_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::tau_neutrino));
    });
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets CopyIfLepton(Jets const& jets)
{
    if (jets.empty())
        return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), [](fastjet::PseudoJet const & jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon));
    });
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfOutsidePtWindow(boca::Jets jets, Momentum lower_cut, Momentum upper_cut)
{
    return boost::range::remove_erase_if(jets, [lower_cut, upper_cut](fastjet::PseudoJet const & jet) {
        return (jet.pt() < lower_cut / GeV || jet.pt() > upper_cut / GeV);
    });
}

Jets CopyIfFamily(Jets const& jets, Id id, Id mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), [id, mother_id](fastjet::PseudoJet const & Jet) {
        unsigned particle = std::abs(Jet.user_info<ParticleInfo>().Family().particle().id());
        unsigned mother = std::abs(Jet.user_info<ParticleInfo>().Family().mother_1().id());
        return (particle == to_unsigned(id) && mother == to_unsigned(mother_id));
    });
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfGrandFamily(Jets jets, Id id , Id grand_mother_id)
{
    return boost::range::remove_erase_if(jets, [id, grand_mother_id](fastjet::PseudoJet const & Jet) {
        unsigned particle = std::abs(Jet.user_info<ParticleInfo>().Family().particle().id());
        if (particle != to_unsigned(id)) return true;
        unsigned grand_mother = Jet.user_info<ParticleInfo>().Family().grand_mother().id();
        return (grand_mother == to_unsigned(grand_mother_id));
    });
}

Jets RemoveIfParticle(Jets jets, Id id)
{
    return boost::range::remove_erase_if(jets, IsParticle(id));
}

struct HasMother {
    HasMother(Id mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().mother_1().id());
        return id == to_unsigned(mother_id_);
    }
    Id mother_id_;
};

Jets CopyIfMother(Jets const& jets, Id mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), HasMother(mother_id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}
Jets RemoveIfMother(Jets jets, Id mother_id)
{
    return boost::range::remove_erase_if(jets, HasMother(mother_id));
}

Jets CopyIfGrandMother(Jets const& jets, Id grand_mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), [&](fastjet::PseudoJet const & jet) {
        unsigned grand_mother = std::abs(jet.user_info<ParticleInfo>().Family().grand_mother().id());
        return grand_mother == to_unsigned(grand_mother_id);
    });
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets CopyIfGrandGrandMother(Jets const& jets, Id grand_grand_mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), [&](fastjet::PseudoJet const & jet) {
        unsigned grand_grand_mother = std::abs(jet.user_info<ParticleInfo>().Family().grand_grand_mother().id());
        return grand_grand_mother == to_unsigned(grand_grand_mother_id);
    });
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}


struct IsSingleMother {
    bool operator()(fastjet::PseudoJet const& Jet) {
        unsigned id = std::abs(Jet.user_info<ParticleInfo>().Family().mother_2().id());
        return id == to_unsigned(Id::empty);
    }
};

Jets RemoveIfSingleMother(Jets jets)
{
    return boost::range::remove_erase_if(jets, IsSingleMother());
}

struct IsLepton {
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon) || id == to_unsigned(Id::tau) || id == to_unsigned(Id::tau_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::electron_neutrino));
    }
};

Jets RemoveIfLetpon(Jets jets)
{
    return boost::range::remove_erase_if(jets, IsLepton());
}

struct IsQuark {
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom) || id == to_unsigned(Id::top));
    }
};

Jets RemoveIfQuark(Jets jets)
{
    return boost::range::remove_erase_if(jets, IsQuark());
}

Jets CopyIfQuark(Jets const& jets)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsQuark());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

struct Is5Quark {
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom));
    }
};

Jets CopyIf5Quark(Jets const& jets)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Is5Quark());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfSoft(Jets jets, Momentum pt_min)
{
    return boost::range::remove_erase_if(jets, [&](fastjet::PseudoJet const & jet) {
        return jet.pt() < pt_min / GeV;
    });
}

}


