# include "Predicate.hh"
# include "Object.hh"

fastjet::PseudoJet analysis::PseudoJet(const TLorentzVector& vector)
{
  // construct a pseudojet from explicit components
  // PseudoJet(const double px, const double py, const double pz, const double E);
  return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}


struct Not5Quark {
    bool operator()(const fastjet::PseudoJet &Jet) {
        const int particle_id = Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id;
        return !(std::abs(particle_id) == analysis::Object::UpId || std::abs(particle_id) == analysis::Object::DownId || std::abs(particle_id) == analysis::Object::CharmId || std::abs(particle_id) == analysis::Object::StrangeId || std::abs(particle_id) == analysis::Object::BottomId);
    }
};



struct Absparticle_id {
    Absparticle_id(const int id) {
        id_ = id;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
      return (std::abs(Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id) == id_);
    }
    int id_;
};

analysis::Jets analysis::copy_if_abs_particle(const Jets &jets, const int particle_id)
{
    Jets final_jets(jets.size());;
    auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Absparticle_id(particle_id));
    final_jets.resize(std::distance(final_jets.begin(), iterator));
    return final_jets;
}

struct Id {
  Id(const int id) {
    id_ = id;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    return (Jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id == id_);
  }
  int id_;
};

analysis::Jets analysis::copy_if_particle(const Jets &jets, const int particle_id)
{
  Jets final_jets(jets.size());
  auto iterator = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Id(particle_id));
  final_jets.resize(std::distance(final_jets.begin(), iterator));
  return final_jets;
}

analysis::Jets analysis::remove_if_particle(const Jets &jets, const int particle_id)
{
  Jets jets_ =jets;
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

analysis::Jets analysis::remove_if_not_in_pt_window(Jets &jets, const float lower_cut, const float upper_cut)
{
    jets.erase(std::remove_if(jets.begin(), jets.end(), NotInPtWindow(lower_cut, upper_cut)), jets.end());
    return jets;
}

analysis::Jets analysis::RemoveIfWrongAbsFamily(const Jets &jets, const int particle_id, int mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsFamily(particle_id, mother_id)), jets_.end());
    return jets_;
}

analysis::Jets analysis::RemoveIfWrongFamily(const Jets &jets, const int particle_id, int mother_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongFamily(particle_id, mother_id)), jets_.end());
    return jets_;
}

analysis::Jets analysis::RemoveIfWrongAbsStepFamily(const Jets &jets, const int particle_id , const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepFamily(particle_id, mother_2_id)), jets_.end());
    return jets_;
}

analysis::Jets analysis::RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id)
{
    Jets jets_ = jets;
    jets_.erase(std::remove_if(jets_.begin(), jets_.end(), WrongAbsStepMother(mother_2_id)), jets_.end());
    return jets_;
}

analysis::Jets analysis::RemoveIfWrongParticle(const Jets &NewJets, const int particle_id)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongId(particle_id)), jets.end());
    return jets;
}

analysis::Jets analysis::RemoveIfWrongAbsParticle(const Jets &NewJets, const int particle_id)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsId(particle_id)), jets.end());
    return jets;
}

analysis::Jets analysis::RemoveIfWrongAbsMother(const Jets &NewJets, const int MotherId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), WrongAbsMother(MotherId)), jets.end());
    return jets;
}

analysis::Jets analysis::RemoveIfAbsMother(const Jets &NewJets, const int MotherId)
{
    Jets jets = NewJets;
    jets.erase(std::remove_if(jets.begin(), jets.end(), AbsMother(MotherId)), jets.end());
    return jets;
}

analysis::Jets analysis::RemoveIfLetpons(const Jets &jets)
{
    Jets quarks = jets;
    quarks.erase(std::remove_if(quarks.begin(), quarks.end(), WrongLeptons()), quarks.end());
    return quarks;
}

analysis::Jets analysis::RemoveIfQuark(const Jets &jets)
{
    Jets leptons = jets;
    leptons.erase(std::remove_if(leptons.begin(), leptons.end(), WrongQuark()), leptons.end());
    return leptons;
}

analysis::Jets analysis::RemoveIfNot5Quarks(const Jets &jets)
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

analysis::Jets analysis::RemoveIfClose(const Jets &jets, const Jets& particles)
{
  Jets quarks = jets;
  for(const auto &particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
  return quarks;
}

analysis::Jets analysis::CopyIfClose(const Jets &jets, const Jets& particles)
{
  Jets final_jets(jets.size());
  Jets::iterator jet;
  for(const auto &particle : particles) jet = std::copy_if(jets.begin(), jets.end(), final_jets.begin(), Close(particle));
  final_jets.resize(std::distance(final_jets.begin(), jet));
  return final_jets;
}

analysis::Jets analysis::RemoveIfSoft(const Jets &jets, const float pt_min)
{
  Jets quarks = jets;
  quarks.erase(std::remove_if(quarks.begin(), quarks.end(), TooSmallPt(pt_min)), quarks.end());
  return quarks;
}

