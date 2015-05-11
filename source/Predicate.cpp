# include "Predicate.hh"
# include "HObject.hh"

struct Not5Quark {
  bool operator()(const fastjet::PseudoJet &Jet) {
    const int ParticleId = Jet.user_info<hanalysis::JetInfo>().constituents().front().Family().ParticleId;
    return !(std::abs(ParticleId) == hanalysis::HObject::UpId || std::abs(ParticleId) == hanalysis::HObject::DownId || std::abs(ParticleId) == hanalysis::HObject::CharmId || std::abs(ParticleId) == hanalysis::HObject::StrangeId || std::abs(ParticleId) == hanalysis::HObject::BottomId);
  }
};

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

