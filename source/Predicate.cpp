# include "Predicate.hh"
# include "Object.hh"

fastjet::PseudoJet PseudoJet(const TLorentzVector& vector)
{
  // construct a pseudojet from explicit components
  // PseudoJet(const double px, const double py, const double pz, const double E);
  return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}


struct Not5Quark {
    bool operator()(const fastjet::PseudoJet &Jet) {
        const int ParticleId = Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id;
        return !(std::abs(ParticleId) == analysis::Object::UpId || std::abs(ParticleId) == analysis::Object::DownId || std::abs(ParticleId) == analysis::Object::CharmId || std::abs(ParticleId) == analysis::Object::StrangeId || std::abs(ParticleId) == analysis::Object::BottomId);
    }
};



struct AbsParticleId {
    AbsParticleId(const int id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
      return (std::abs(Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id) == id_);
    }
    int id_;
};

Jets copy_if_abs_particle(const Jets &jets, const int particle_id)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), AbsParticleId(particle_id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

struct ParticleId {
  ParticleId(const int id) {
    id_ = id;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    return (Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id == id_);
  }
  int id_;
};

Jets copy_if_particle(const Jets &jets, const int particle_id)
{
  Jets final_jets(jets.size());
  auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), ParticleId(particle_id));
  final_jets.resize(std::distance(final_jets.begin(), iterator));
  return final_jets;
}

Jets remove_if_particle(const Jets &jets, const int particle_id)
{
  Jets jets_ =jets;
  jets_.erase(std::remove_if(jets_.begin(), jets_.end(), ParticleId(particle_id)), jets_.end());
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

struct Close {
  Close(const fastjet::PseudoJet &particle) {
    particle_ = particle;
  }
  bool operator()(const fastjet::PseudoJet &jet) {
    return (jet.delta_R(particle_) < detector_geometry_.JetConeSize);
  }
  fastjet::PseudoJet particle_;
  analysis::DetectorGeometry detector_geometry_;
};

Jets RemoveIfClose(const Jets &jets, const Jets& particles)
{
  Jets quarks = jets;
  for(const auto &particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
  return quarks;
}

Jets CopyIfClose(const Jets &jets, const Jets& particles)
{
  Jets final_jets(jets.size());
  Jets::iterator iterator;
  for(const auto &particle : particles) {
    iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Close(particle));
  }
  final_jets.resize(std::distance(final_jets.begin(), iterator));
  return final_jets;
}

