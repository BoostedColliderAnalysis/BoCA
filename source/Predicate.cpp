#include "Predicate.hh"
#include "JetInfo.hh"

namespace analysis
{

struct SortJetByRap {
    bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
        return (jet_1.rap() > jet_2.rap());
    }
};

struct MaxPt {
    template <typename Multiplet>
    bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return (multiplet_1.Jet().pt() > multiplet_2.Jet().pt());
    }
};



struct TooSmallPt {
    TooSmallPt(const float pt) {
        pt_ = pt;
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.pt() < pt_);
    }
    float pt_;
};

struct TooBigPt {
    TooBigPt(const int pt) {
        pt_ = pt;
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.pt() > pt_);
    }
    int pt_;
};

struct WrongId {
    WrongId(const int id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.user_info<JetInfo>().constituents().front().family().particle().Id != id_);
        return (jet.user_info<JetInfo>().constituents().front().family().particle().Id != id_);
    }
    int id_;
};

struct WrongAbsId {
    WrongAbsId(const Id id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != to_int(id_));
    }
    Id id_;
};

struct WrongAbsPairId {
    WrongAbsPairId(const int id_1, const int id_2) {
        id_1_ = id_1;
        id_2_ = id_2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != id_1_ && std::abs(family.particle().Id) != id_2_);
    }
    int id_1_;
    int id_2_;
};

struct WrongAbsFamily {
  WrongAbsFamily(const Id id, const Id moterh_id) {
        id_ = id;
        mother_id_ = moterh_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != to_int(id_) || std::abs(family.mother_1().Id) != to_int(mother_id_));
    }
    Id id_;
    Id mother_id_;
};

struct WrongFamily {
    WrongFamily(const int id, const int mother_id) {
        id_ = id;
        mother_id_ = mother_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (family.particle().Id != id_ || family.mother_1().Id != mother_id_);
    }
    int id_;
    int mother_id_;
};

struct WrongMother {
    WrongMother(const int mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return family.mother_1().Id != mother_id_;
    }
    int mother_id_;
};

struct WrongAbsMother {
    WrongAbsMother(const Id mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_1().Id) != to_int(mother_id_);
    }
    Id mother_id_;
};

struct AbsMother {
    AbsMother(const Id mother_id) {
        mother_id_ = mother_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_1().Id) == to_int(mother_id_);
    }
    Id mother_id_;
};

struct WrongAbsStepFamily {
    WrongAbsStepFamily(const int id, const int mother_2_id) {
        mother_2_id_ = mother_2_id;
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != id_ || std::abs(family.mother_2().Id) != mother_2_id_);
    }
    int mother_2_id_;
    int id_;
};

struct WrongAbsStepMother {
    WrongAbsStepMother(const int mother_2_id) {
        mother_2_id_ = mother_2_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_2().Id) != mother_2_id_;
    }
    int mother_2_id_;
};

struct WrongLeptons {
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) == to_int(Id::electron) ||
                std::abs(family.particle().Id) == to_int(Id::muon) ||
                std::abs(family.particle().Id) == to_int(Id::tau) ||
                std::abs(family.particle().Id) == to_int(Id::tau_neutrino) ||
                std::abs(family.particle().Id) == to_int(Id::muon_neutrino) ||
                std::abs(family.particle().Id) == to_int(Id::electron_neutrino)
               );
    }
};

struct IsQuark {
    bool operator()(const fastjet::PseudoJet &jet) {
        Family family = jet.user_info<JetInfo>().constituents().front().family();
        return (std::abs(family.particle().Id) == to_int(Id::up) ||
                std::abs(family.particle().Id) == to_int(Id::down) ||
                std::abs(family.particle().Id) == to_int(Id::charm) ||
                std::abs(family.particle().Id) == to_int(Id::strange) ||
                std::abs(family.particle().Id) == to_int(Id::bottom) ||
                std::abs(family.particle().Id) == to_int(Id::top)
               );
    }
};

struct LargeDistance {
    LargeDistance(const fastjet::PseudoJet NewJet, const float NewDistance) {
        JetM = NewJet;
        Distance = NewDistance;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (JetM.delta_R(Jet) > Distance);
    }
    fastjet::PseudoJet JetM;
    float Distance;
};

struct SmallDistance {
    SmallDistance(const fastjet::PseudoJet NewJet, const float NewDistance) {
        JetM = NewJet;
        Distance = NewDistance;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (JetM.delta_R(Jet) < Distance);
    }
    fastjet::PseudoJet JetM;
    float Distance;
};

struct Not5Quark {
    bool operator()(const fastjet::PseudoJet &Jet) {
        const int id = Jet.user_info<JetInfo>().constituents().front().family().particle().Id;
        return !(std::abs(id) == to_int(Id::up) || std::abs(id) == to_int(Id::down) || std::abs(id) == to_int(Id::charm) || std::abs(id) == to_int(Id::strange) || std::abs(id) == to_int(Id::bottom));
    }
};

struct AbsId {
    AbsId(const Id id_1) {
        id_1_ = id_1;
        id_2_ = id_1;
    }
    AbsId(const Id id_1, const Id id_2) {
        id_1_ = id_1;
        id_2_ = id_2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        int id = std::abs(Jet.user_info<JetInfo>().constituents().front().family().particle().Id);
        return (id == to_int(id_1_) | id == to_int(id_2_));
    }
    Id id_1_;
    Id id_2_;
};


struct IsNeutrino {
    bool operator()(const fastjet::PseudoJet &jet) {
        const int id = jet.user_info<JetInfo>().constituents().front().family().particle().Id;
        return (id == to_int(Id::electron_neutrino) | id == to_int(Id::muon_neutrino) | id == to_int(Id::tau_neutrino));
    }
};


fastjet::PseudoJet PseudoJet(const TLorentzVector &vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(const double px, const double py, const double pz, const double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

Jets CopyIfAbsParticle(const Jets &jets, const Id id)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsId(id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets CopyIfAbsParticle(const Jets &jets, const Id id_1, const Id id_2)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsId(id_1, id_2));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}


Jets copy_if_neutrino(const Jets &jets)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsNeutrino());
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

struct IsId {
  IsId(const int id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (Jet.user_info<JetInfo>().constituents().front().family().particle().Id == id_);
    }
    int id_;
};

Jets copy_if_particle(const Jets &jets, const int id)
{
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsId(id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets remove_if_particle(const Jets &jets, const int id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), IsId(id)), jets_.end());
    return jets;
}


struct NotInPtWindow {
    NotInPtWindow(const float lower_cut, const float upper_cut) {
        lower_cut_ = lower_cut;
        upper_cut_ = upper_cut;
    }
    bool operator()(const fastjet::PseudoJet &jet) {
        return (jet.pt() < lower_cut_ || jet.pt() > upper_cut_);
    }
    float lower_cut_;
    float upper_cut_;
};

Jets remove_if_not_in_pt_window(Jets &jets, const float lower_cut, const float upper_cut)
{
    jets.erase(std::remove_if(jets.begin(), jets.end(), NotInPtWindow(lower_cut, upper_cut)), jets.end());
    return jets;
}

Jets RemoveIfWrongAbsFamily(const Jets &jets, const Id id, Id mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsFamily(id, mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongFamily(const Jets &jets, const int id, int mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongFamily(id, mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsStepFamily(const Jets &jets, const int id , const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepFamily(id, mother_2_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepMother(mother_2_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongParticle(const Jets &jets, const int id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongId(id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsParticle(const Jets &jets, const Id id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsId(id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsMother(const Jets &jets, const Id mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsMother(mother_id)), jets_.end());
    return jets_;
}

Jets CopyIfAbsMother(const Jets &jets, const Id mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsMother(mother_id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfAbsMother(const Jets &jets, const Id mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), AbsMother(mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfLetpons(const Jets &jets)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), WrongLeptons()), quarks.end());
    return quarks;
}

Jets RemoveIfQuark(const Jets &jets)
{
    Jets leptons = jets;
    leptons.erase(std::remove_if(leptons.begin(), leptons.end(), IsQuark()), leptons.end());
    return leptons;
}

Jets CopyIfQuark(const Jets &jets)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), IsQuark());
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfNot5Quarks(const Jets &jets)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Not5Quark()), quarks.end());
    return quarks;
}

// struct Close {
//     Close(const fastjet::PseudoJet &particle) {
//         particle_ = particle;
//     }
//     bool operator()(const fastjet::PseudoJet &jet) {
//         return (jet.delta_R(particle_) < detector_geometry_.JetConeSize());
//     }
//     fastjet::PseudoJet particle_;
//     DetectorGeometry detector_geometry_;
// };
//
// Jets RemoveIfClose(const Jets &jets, const Jets& particles)
// {
//     Jets quarks = jets;
//     for(const auto &particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
//     return quarks;
// }
//
// Jets CopyIfClose(const Jets &jets, const Jets& particles)
// {
//     Jets final_jets(jets.size());
//     Jets::iterator jet;
//     for(const auto &particle : particles) jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Close(particle));
//     final_jets.resize(std::distance(final_jets.begin(), jet));
//     return final_jets;
// }

Jets RemoveIfSoft(const Jets &jets, const float pt_min)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), TooSmallPt(pt_min)), quarks.end());
    return quarks;
}


}

