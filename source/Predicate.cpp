# include "Predicate.hh"
# include "HObject.hh"

struct Not5Quark {
    bool operator()(const fastjet::PseudoJet &Jet) {
        const int ParticleId = Jet.user_info<hanalysis::JetInfo>().constituents().front().Family().ParticleId;
        return !(std::abs(ParticleId) == hanalysis::HObject::UpId || std::abs(ParticleId) == hanalysis::HObject::DownId || std::abs(ParticleId) == hanalysis::HObject::CharmId || std::abs(ParticleId) == hanalysis::HObject::StrangeId || std::abs(ParticleId) == hanalysis::HObject::BottomId);
    }
};



struct AbsId {
    AbsId(const int NewId) {
        Id = NewId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::JetInfo jet_info = Jet.user_info<hanalysis::JetInfo>();
        hanalysis::HFamily Family = jet_info.constituents().front().Family();
        return (std::abs(Family.ParticleId) == Id);
    }
    int Id;
};

Jets copy_if_abs_particle(const Jets &jets, const int particle_id)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsId(particle_id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
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

Jets RemoveIfWrongParticle(const Jets &NewJets, const int ParticleId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongId(ParticleId)), jets.end());
    return jets;
}

Jets RemoveIfWrongAbsParticle(const Jets &NewJets, const int ParticleId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsId(ParticleId)), jets.end());
    return jets;
}

Jets RemoveIfWrongAbsMother(const Jets &NewJets, const int MotherId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsMother(MotherId)), jets.end());
    return jets;
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
    leptons.erase(std::remove_if(leptons.begin(), leptons.end(), WrongQuark()), leptons.end());
    return leptons;
}

Jets RemoveIfNot5Quarks(const Jets &jets)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Not5Quark()), quarks.end());
    return quarks;
}

