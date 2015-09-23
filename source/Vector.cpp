/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Vector.hh"

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

Jets CopyIfParticle(Jets const& jets, Id id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets CopyIfParticles(Jets const& jets, Id id_1, Id id_2)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id_1, id_2));
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
    if (jets.empty()) return jets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), IsExactParticle(id)), jets.end());
    return jets;
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
    if (jets.empty()) return jets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), [lower_cut, upper_cut](fastjet::PseudoJet const & jet) {
        return (jet.pt() < lower_cut / GeV || jet.pt() > upper_cut / GeV);
    }), jets.end());
    return jets;
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
    if (jets.empty()) return jets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), [id, grand_mother_id](fastjet::PseudoJet const & Jet) {
        unsigned particle = std::abs(Jet.user_info<ParticleInfo>().Family().particle().id());
        if (particle != to_unsigned(id)) return true;
        unsigned grand_mother = Jet.user_info<ParticleInfo>().Family().grand_mother().id();
        return (grand_mother == to_unsigned(grand_mother_id));
    }), jets.end());
    return jets;
}

Jets RemoveIfParticle(Jets jets, Id id)
{
    if (jets.empty()) return jets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), IsParticle(id)), jets.end());
    return jets;
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
    jets.erase(std::remove_if(jets.begin(), jets.end(), HasMother(mother_id)), jets.end());
    return jets;
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


struct IsSingleMother {
    bool operator()(fastjet::PseudoJet const& Jet) {
        unsigned id = std::abs(Jet.user_info<ParticleInfo>().Family().mother_2().id());
        return id == to_unsigned(Id::empty);
    }
};

Jets RemoveIfSingleMother(Jets jets)
{
    jets.erase(std::remove_if(jets.begin(), jets.end(), IsSingleMother()), jets.end());
    return jets;
}

struct IsLepton {
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::electron) || id == to_unsigned(Id::muon) || id == to_unsigned(Id::tau) || id == to_unsigned(Id::tau_neutrino) || id == to_unsigned(Id::muon_neutrino) || id == to_unsigned(Id::electron_neutrino));
    }
};

Jets RemoveIfLetpon(Jets jets)
{
    jets.erase(std::remove_if(jets.begin(), jets.end(), IsLepton()), jets.end());
    return jets;
}

struct IsQuark {
    bool operator()(fastjet::PseudoJet const& jet) {
        unsigned id = std::abs(jet.user_info<ParticleInfo>().Family().particle().id());
        return (id == to_unsigned(Id::up) || id == to_unsigned(Id::down) || id == to_unsigned(Id::charm) || id == to_unsigned(Id::strange) || id == to_unsigned(Id::bottom) || id == to_unsigned(Id::top));
    }
};

Jets RemoveIfQuark(Jets jets)
{
    jets.erase(std::remove_if(jets.begin(), jets.end(), IsQuark()), jets.end());
    return jets;
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
    jets.erase(std::remove_if(jets.begin(), jets.end(), [&](fastjet::PseudoJet const & jet) {
        return jet.pt() < pt_min / GeV;
    }), jets.end());
    return jets;
}

}

