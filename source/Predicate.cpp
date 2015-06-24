# include "Predicate.hh"

namespace analysis
{

struct SortJetByRap {
     bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.rap() > Jet2.rap());
    }
};

struct MaxPt {
    template <typename TMultiplet>
     bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
        return (Multiplet1.Jet().pt() > Multiplet2.Jet().pt());
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
    WrongAbsId(const int NewId) {
        Id = NewId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != Id);
    }
    int Id;
};

struct WrongAbsPairId {
    WrongAbsPairId(const int NewId, const int NewId2) {
        Id = NewId;
        Id2 = NewId2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != Id && std::abs(family.particle().Id) != Id2);
    }
    int Id;
    int Id2;
};

struct WrongAbsFamily {
    WrongAbsFamily(const int NewId, const int NewMother) {
        Id = NewId;
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != Id || std::abs(family.mother_1().Id) != Mother);
    }
    int Id;
    int Mother;
};

struct WrongFamily {
    WrongFamily(const int NewId, const int NewMother) {
        Id = NewId;
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (family.particle().Id != Id || family.mother_1().Id != Mother);
    }
    int Id;
    int Mother;
};

struct WrongMother {
    WrongMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return family.mother_1().Id != Mother;
    }
    int Mother;
};

struct WrongAbsMother {
    WrongAbsMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_1().Id) != Mother;
    }
    int Mother;
};

struct AbsMother {
    AbsMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_1().Id) == Mother;
    }
    int Mother;
};

struct WrongAbsStepFamily {
    WrongAbsStepFamily(const int Newparticle_id, const int NewMother2) {
        Mother2 = NewMother2;
        particle_id = Newparticle_id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) != particle_id || std::abs(family.mother_2().Id) != Mother2);
    }
    int Mother2;
    int particle_id;
};

struct WrongAbsStepMother {
    WrongAbsStepMother(const int NewMother2) {
        Mother2 = NewMother2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_2().Id) != Mother2;
    }
    int Mother2;
};

struct WrongLeptons {
    bool operator()(const fastjet::PseudoJet &Jet) {
        JetInfo jet_info = Jet.user_info<JetInfo>();
        Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) == family.ElectronId ||
                std::abs(family.particle().Id) == family.MuonId ||
                std::abs(family.particle().Id) == family.TauId ||
                std::abs(family.particle().Id) == family.TauNeutrinoId ||
                std::abs(family.particle().Id) == family.MuonNeutrinoId ||
                std::abs(family.particle().Id) == family.ElectronNeutrinoId
               );
    }
};

struct IsQuark {
    bool operator()(const fastjet::PseudoJet &jet) {
        Family family = jet.user_info<JetInfo>().constituents().front().family();
        return (std::abs(family.particle().Id) == family.UpId ||
                std::abs(family.particle().Id) == family.DownId ||
                std::abs(family.particle().Id) == family.CharmId ||
                std::abs(family.particle().Id) == family.StrangeId ||
                std::abs(family.particle().Id) == family.BottomId ||
                std::abs(family.particle().Id) == family.TopId
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
        const int particle_id = Jet.user_info<JetInfo>().constituents().front().family().particle().Id;
        return !(std::abs(particle_id) == Object::UpId || std::abs(particle_id) == Object::DownId || std::abs(particle_id) == Object::CharmId || std::abs(particle_id) == Object::StrangeId || std::abs(particle_id) == Object::BottomId);
    }
};

struct AbsParticleId {
    AbsParticleId(const int id_1) {
        id_1_ = id_1;
        id_2_ = id_1;
    }
    AbsParticleId(const int id_1, const int id_2) {
        id_1_ = id_1;
        id_2_ = id_2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        int id = std::abs(Jet.user_info<JetInfo>().constituents().front().family().particle().Id);
        return (id == id_1_ | id == id_2_);
    }
    int id_1_;
    int id_2_;
};


struct IsNeutrino {
    bool operator()(const fastjet::PseudoJet &jet) {
        const int particle_id = jet.user_info<JetInfo>().constituents().front().family().particle().Id;
        return (particle_id == Object::ElectronNeutrinoId | particle_id == Object::MuonNeutrinoId | particle_id == Object::TauNeutrinoId);
    }
};


fastjet::PseudoJet PseudoJet(const TLorentzVector &vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(const double px, const double py, const double pz, const double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

Jets copy_if_abs_particle(const Jets &jets, const int particle_id)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsParticleId(particle_id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets copy_if_abs_particle(const Jets &jets, const int particle_id_1, const int particle_id_2)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsParticleId(particle_id_1, particle_id_2));
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

struct Id {
    Id(const int id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (Jet.user_info<JetInfo>().constituents().front().family().particle().Id == id_);
    }
    int id_;
};

Jets copy_if_particle(const Jets &jets, const int particle_id)
{
    Jets final_jets(jets.size());
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Id(particle_id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

Jets remove_if_particle(const Jets &jets, const int particle_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), Id(particle_id)), jets_.end());
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

Jets RemoveIfWrongAbsFamily(const Jets &jets, const int particle_id, int mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsFamily(particle_id, mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongFamily(const Jets &jets, const int particle_id, int mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongFamily(particle_id, mother_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsStepFamily(const Jets &jets, const int particle_id , const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepFamily(particle_id, mother_2_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepMother(mother_2_id)), jets_.end());
    return jets_;
}

Jets RemoveIfWrongParticle(const Jets &NewJets, const int particle_id)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongId(particle_id)), jets.end());
    return jets;
}

Jets RemoveIfWrongAbsParticle(const Jets &NewJets, const int particle_id)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsId(particle_id)), jets.end());
    return jets;
}

Jets RemoveIfWrongAbsMother(const Jets &NewJets, const int MotherId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsMother(MotherId)), jets.end());
    return jets;
}

Jets CopyIfAbsMother(const Jets &jets, const int mother_id)
{
    if (jets.empty()) return jets;
    Jets final_jets(jets.size());
    auto jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsMother(mother_id));
    final_jets.resize(std::distance(final_jets.begin(), jet));
    return final_jets;
}

Jets RemoveIfAbsMother(const Jets &NewJets, const int MotherId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), AbsMother(MotherId)), jets.end());
    return jets;
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
//         return (jet.delta_R(particle_) < detector_geometry_.JetConeSize);
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
