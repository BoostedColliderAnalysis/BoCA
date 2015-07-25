#include "JetInfo.hh"
#include "Predicate.hh"
#include "TLorentzVector.h"
#include "Debug.hh"

namespace analysis {

fastjet::PseudoJet PseudoJet(const TLorentzVector& vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(double px, double py, double pz, double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

fastjet::PseudoJet PseudoJet(const LorentzVector& vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(double px, double py, double pz, double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

struct IsParticle {
    IsParticle(Id id_1)
    {
        id_1_ = id_1;
        id_2_ = id_1;
    }
    IsParticle(Id id_1, Id id_2)
    {
        id_1_ = id_1;
        id_2_ = id_2;
    }
    bool operator()(const fastjet::PseudoJet& jet)
    {
        int id = std::abs(jet.user_info<JetInfo>().constituents().front().family().particle().id());
        return (id == to_int(id_1_) || id == to_int(id_2_));
    }
    Id id_1_;
    Id id_2_;
};

Jets CopyIfParticle(const Jets& jets, Id id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets CopyIfParticles(const Jets& jets, Id id_1, Id id_2)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsParticle(id_1, id_2));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

struct IsExactParticle {
    IsExactParticle(int id)
    {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet& Jet)
    {
        return (Jet.user_info<JetInfo>().constituents().front().family().particle().id() == id_);
    }
    int id_;
};

Jets CopyIfExactParticle(const Jets& jets, int id)
{
    if (jets.empty())
        return jets;
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsExactParticle(id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets RemoveIfExactParticle(const Jets& jets, int id)
{
    if (jets.empty())
        return jets;
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), IsExactParticle(id)), jets_.end());
    return jets;
}

struct IsNeutrino {
    bool operator()(const fastjet::PseudoJet& jet)
    {
        int id = jet.user_info<JetInfo>().constituents().front().family().particle().id();
        return (id == to_int(Id::electron_neutrino) || id == to_int(Id::muon_neutrino) || id == to_int(Id::tau_neutrino));
    }
};

Jets CopyIfNeutrino(const Jets& jets)
{
    if (jets.empty())
        return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsNeutrino());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

struct OutsidePtWindow {
    OutsidePtWindow(float lower_cut, float upper_cut)
    {
        lower_cut_ = lower_cut;
        upper_cut_ = upper_cut;
    }
    bool operator()(const fastjet::PseudoJet& jet)
    {
        return (jet.pt() < lower_cut_ || jet.pt() > upper_cut_);
    }
    float lower_cut_;
    float upper_cut_;
};

Jets RemoveIfOutsidePtWindow(Jets& jets, float lower_cut, float upper_cut)
{
    if (jets.empty()) return jets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), OutsidePtWindow(lower_cut, upper_cut)), jets.end());
    return jets;
}

struct IsFamily {
    IsFamily(Id id, Id moterh_id)
    {
        id_ = id;
        mother_id_ = moterh_id;
    }
    bool operator()(const fastjet::PseudoJet& Jet)
    {
        Family family = Jet.user_info<JetInfo>().constituents().front().family();
        return (std::abs(family.particle().id()) == to_int(id_) && std::abs(family.mother_1().id()) == to_int(mother_id_));
    }
    Id id_;
    Id mother_id_;
};

Jets CopyIfFamily(const Jets& jets, Id id, Id mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsFamily(id,mother_id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

struct IsGrandFamily {
    IsGrandFamily(Id id, Id grand_mother_id)
    {
        grand_mother_id_ = grand_mother_id;
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet& Jet)
    {
        Family family = Jet.user_info<JetInfo>().constituents().front().family();
        if(std::abs(family.particle().id()) != to_int(id_)) return true;
        return (std::abs(family.grand_mother().id()) == to_int(grand_mother_id_));
    }
    Id grand_mother_id_;
    Id id_;
};

Jets RemoveIfGrandFamily(const Jets& jets, Id id , Id grand_mother_id)
{
    if (jets.empty()) return jets;
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), IsGrandFamily(id, grand_mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfParticle(const Jets& jets, Id id)
{
    if (jets.empty()) return jets;
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), IsParticle(id)), jets_.end());
    return jets_;
}

struct HasMother {
    HasMother(Id mother_id)
    {
        mother_id_ = mother_id;
    }
    bool operator()(const fastjet::PseudoJet& Jet)
    {
        Family family = Jet.user_info<JetInfo>().constituents().front().family();
        return std::abs(family.mother_1().id()) == to_int(mother_id_);
    }
    Id mother_id_;
};

Jets CopyIfMother(const Jets& jets, Id mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), HasMother(mother_id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}


Jets RemoveIfMother(const Jets& jets, Id mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), HasMother(mother_id)), jets_.end());
    return jets_;
}

struct IsSingleMother {
  bool operator()(const fastjet::PseudoJet& Jet)
  {
    Family family = Jet.user_info<JetInfo>().constituents().front().family();
    return std::abs(family.mother_2().id()) == to_int(Id::empty);
  }
};

Jets RemoveIfSingleMother(const Jets& jets)
{
  Jets jets_ = jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), IsSingleMother()), jets_.end());
  return jets_;
}

struct IsLepton {
    bool operator()(const fastjet::PseudoJet& jet)
    {
        Family family = jet.user_info<JetInfo>().constituents().front().family();
        return (std::abs(family.particle().id()) == to_int(Id::electron) ||
        std::abs(family.particle().id()) == to_int(Id::muon) ||
        std::abs(family.particle().id()) == to_int(Id::tau) ||
        std::abs(family.particle().id()) == to_int(Id::tau_neutrino) ||
        std::abs(family.particle().id()) == to_int(Id::muon_neutrino) ||
        std::abs(family.particle().id()) == to_int(Id::electron_neutrino)
        );
    }
};

Jets RemoveIfLetpon(const Jets& jets)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), IsLepton()), quarks.end());
    return quarks;
}

struct IsQuark {
    bool operator()(const fastjet::PseudoJet& jet)
    {
        Family family = jet.user_info<JetInfo>().constituents().front().family();
        return (std::abs(family.particle().id()) == to_int(Id::up) ||
        std::abs(family.particle().id()) == to_int(Id::down) ||
        std::abs(family.particle().id()) == to_int(Id::charm) ||
        std::abs(family.particle().id()) == to_int(Id::strange) ||
        std::abs(family.particle().id()) == to_int(Id::bottom) ||
        std::abs(family.particle().id()) == to_int(Id::top)
        );
    }
};

Jets RemoveIfQuark(const Jets& jets)
{
    Jets leptons = jets;
    leptons.erase(std::remove_if(leptons.begin(), leptons.end(), IsQuark()), leptons.end());
    return leptons;
}

Jets CopyIfQuark(const Jets& jets)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsQuark());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

struct Is5Quark {
    bool operator()(const fastjet::PseudoJet& jet)
    {
        int id = jet.user_info<JetInfo>().constituents().front().family().particle().id();
        return (std::abs(id) == to_int(Id::up) || std::abs(id) == to_int(Id::down) || std::abs(id) == to_int(Id::charm) || std::abs(id) == to_int(Id::strange) || std::abs(id) == to_int(Id::bottom));
    }
};

Jets CopyIf5Quark(const Jets& jets)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Is5Quark());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfSoft(const Jets& jets, float pt_min)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), [&](const fastjet::PseudoJet& jet){
        return jet.pt() < pt_min;
    }), quarks.end());
    return quarks;
}

float Distance(float rapidity_1, float phi_1, float rapidity_2, float phi_2)
{
    return std::sqrt(std::pow((rapidity_2 - rapidity_1), 2) + std::pow(DeltaPhi(phi_2, phi_1), 2));
}

float Length(float rapidity, float phi)
{
    return std::sqrt(std::pow(rapidity, 2) + std::pow(phi, 2));
}

float DeltaPhi(float phi_1, float phi_2)
{
    return RestrictPhi(phi_1 - phi_2);
}

float RestrictPhi(float phi){
  while (std::abs(phi) > M_PI) {
    if (phi < - M_PI) phi += 2 * M_PI;
    else if (phi > M_PI) phi -= 2 * M_PI;
    else Error(phi);
  }
  return phi;
}

}

