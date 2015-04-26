# include "Predicate.hh"
# include "HObject.hh"

struct Not5Quark {
  bool operator()(const fastjet::PseudoJet &Jet) {
    const int ParticleId = Jet.user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId;
    return !(std::abs(ParticleId) == hanalysis::HObject::UpId || std::abs(ParticleId) == hanalysis::HObject::DownId || std::abs(ParticleId) == hanalysis::HObject::CharmId || std::abs(ParticleId) == hanalysis::HObject::StrangeId || std::abs(ParticleId) == hanalysis::HObject::BottomId);
  }
};

HJets RemoveIfWrongAbsFamily(const HJets &jets, const int particle_id, int mother_id)
{
  HJets jets_ = jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsFamily(particle_id, mother_id)), jets_.end());
  return jets_;
}

HJets RemoveIfWrongFamily(const HJets &jets, const int particle_id, int mother_id)
{
  HJets jets_ = jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongFamily(particle_id, mother_id)), jets_.end());
  return jets_;
}

HJets RemoveIfWrongAbsStepFamily(const HJets &jets, const int particle_id , const int mother_2_id)
{
  HJets jets_ = jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepFamily(particle_id, mother_2_id)), jets_.end());
  return jets_;
}

HJets RemoveIfWrongAbsStepMother(const HJets &jets, const int mother_2_id)
{
  HJets jets_ = jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepMother(mother_2_id)), jets_.end());
  return jets_;
}

HJets RemoveIfWrongParticle(const HJets &NewJets, const int ParticleId)
{
  HJets Jets = NewJets;
  Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongId(ParticleId)), Jets.end());
  return Jets;
}

HJets RemoveIfWrongAbsParticle(const HJets &NewJets, const int ParticleId)
{
  HJets Jets = NewJets;
  Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsId(ParticleId)), Jets.end());
  return Jets;
}

HJets RemoveIfWrongAbsMother(const HJets &NewJets, const int MotherId)
{
  HJets Jets = NewJets;
  Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsMother(MotherId)), Jets.end());
  return Jets;
}

HJets RemoveIfAbsMother(const HJets &NewJets, const int MotherId)
{
  HJets Jets = NewJets;
  Jets.erase(std::remove_if(Jets.begin(), Jets.end(), AbsMother(MotherId)), Jets.end());
  return Jets;
}


HJets RemoveIfLetpons(const HJets &jets)
{
  HJets quarks = jets;
  quarks.erase(std::remove_if(quarks.begin(), quarks.end(), WrongLeptons()), quarks.end());
  return quarks;
}

HJets RemoveIfQuark(const HJets &jets)
{
  HJets leptons = jets;
  leptons.erase(std::remove_if(leptons.begin(), leptons.end(), WrongQuark()), leptons.end());
  return leptons;
}

HJets RemoveIfNot5Quarks(const HJets &jets)
{
  HJets quarks = jets;
  quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Not5Quark()), quarks.end());
  return quarks;
}

