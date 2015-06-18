# pragma once

// # include <algorithm>
# include "JetInfo.hh"

namespace analysis
{

struct MinDeltaRTo {
    MinDeltaRTo(const fastjet::PseudoJet &jet) {
        jet_ = jet;
    }
    template <typename Multiplet>
    inline bool operator()(const Multiplet &multiplet1, const Multiplet &multiplet2) {
        return multiplet1.Jet().delta_R(jet_)  < multiplet2.Jet().delta_R(jet_);
    }
    inline bool operator()(const fastjet::PseudoJet &jet1, const fastjet::PseudoJet &jet2) {
        return jet1.delta_R(jet_)  < jet2.delta_R(jet_);
    }
    fastjet::PseudoJet jet_;
};

struct MaxDeltaRap {
    template <typename Multiplet>
    inline bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
        return (multiplet_1.DeltaRap() > multiplet_2.DeltaRap());
    }
};

struct SortByMassTo {
    SortByMassTo(const float mass) {
        mass_ = mass;
    }
    template <typename Multiplet>
    inline bool operator()(const Multiplet &Multiplet1, const Multiplet &Multiplet2) {
          return std::abs(Multiplet1.Jet().m() - mass_) < std::abs(Multiplet2.Jet().m() - mass_);
    }
    float mass_;
};

template<typename Multiplet>
inline std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> &multiplets, const fastjet::PseudoJet &jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

struct SortPairs {
  template <typename Template>
  inline bool operator()(const std::pair<Template, float> &pair_1, const std::pair<Template, float> &pair_2) {
    return (pair_1.second < pair_2.second);
  }
};

template <class Multiplet>
inline std::vector<Multiplet> SortByMaxDeltaRap(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), MaxDeltaRap());
    return multiplets;
}

template <class HMultiplet>
inline std::vector<HMultiplet> SortedByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass)
{
    std::sort(Multiplets.begin(), Multiplets.end(), SortByMassTo(Mass));
    return Multiplets;
}

// template <class HMultiplet>
// inline std::vector<HMultiplet> SortedByMassTo(std::vector<HMultiplet> &Multiplets, const Object::ParticleId particle_id )
// {
//   return SortedByMassTo(Multiplets,Object::Mass(particle_id));
// }


struct SortByMass {
  template <typename Multiplet>
  inline bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
    return multiplet_1.Mass() > multiplet_2.Mass();
  }
  inline bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
    return jet_1.m() > jet_2.m();
  }
};

template <class Multiplet>
inline std::vector<Multiplet> SortedByMass(std::vector<Multiplet> &multiplets)
{
    std::sort(multiplets.begin(), multiplets.end(), SortByMass());
    return multiplets;
}


struct SortByPt {
  template <typename Multiplet>
  inline bool operator()(const Multiplet &multiplet_1, const Multiplet &multiplet_2) {
    return multiplet_1.Jet().pt() > multiplet_2.Jet().pt();
  }
  inline bool operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2) {
    return jet_1.pt() > jet_2.pt();
  }
  inline bool operator()(const TLorentzVector &lorentz_vector_1, const TLorentzVector &lorentz_vector_2) {
    return (lorentz_vector_1.Pt() > lorentz_vector_2.Pt());
  }

};

template <class Multiplet>
inline std::vector<Multiplet> SortedByPt(std::vector<Multiplet> &multiplets)
{
  std::sort(multiplets.begin(), multiplets.end(), SortByPt());
  return multiplets;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

// template<typename Predicate>
// Jets FindIf(const Jets &jets){
//   return std::find_if(jets.begin(),jets.end(),Predicate);
// }


/**
 * @brief Get a fastjet::PseudoJet from a TLorentzVector
 *
 */
fastjet::PseudoJet PseudoJet(const TLorentzVector &vector);

Jets copy_if_abs_particle(const Jets &jets, const int particle_id);

Jets copy_if_abs_particle(const Jets &jets, const int particle_id_1, const int particle_id_2);

Jets copy_if_neutrino(const Jets &jets);

Jets copy_if_particle(const Jets &jets, const int particle_id);

Jets remove_if_particle(const Jets &jets, const int particle_id);

Jets remove_if_not_in_pt_window(Jets &jets, const float lower_cut, const float upper_cut);

Jets RemoveIfWrongAbsFamily(const Jets &jets, const int particle_id, int mother_id);

Jets RemoveIfWrongFamily(const Jets &jets, const int particle_id, int mother_id);

Jets RemoveIfWrongAbsStepFamily(const Jets &jets, const int particle_id , const int mother_2_id);

Jets RemoveIfWrongAbsStepMother(const Jets &jets, const int mother_2_id);

Jets RemoveIfWrongParticle(const Jets &NewJets, const int particle_id);

Jets RemoveIfWrongAbsParticle(const Jets &NewJets, const int particle_id);

Jets RemoveIfWrongAbsMother(const Jets &NewJets, const int MotherId);

Jets RemoveIfAbsMother(const Jets &NewJets, const int MotherId);

Jets RemoveIfLetpons(const Jets &jets);

Jets RemoveIfQuark(const Jets &jets);

Jets RemoveIfNot5Quarks(const Jets &jets);

Jets RemoveIfSoft(const Jets &jets, const float pt_min);


struct Close {
  Close(const fastjet::PseudoJet &particle) {
    particle_ = particle;
  }
  template <typename Multiplet>
  bool operator()(const Multiplet &multiplet) {
    return (multiplet.Jet().delta_R(particle_) < detector_geometry_.JetConeSize);
  }
  bool operator()(const fastjet::PseudoJet &jet) {
    return (jet.delta_R(particle_) < detector_geometry_.JetConeSize);
  }
  fastjet::PseudoJet particle_;
  DetectorGeometry detector_geometry_;
};

template <typename Multiplet>
std::vector<Multiplet> RemoveIfClose(const std::vector<Multiplet> &jets, const Jets& particles)
{
  std::vector<Multiplet> quarks = jets;
  for(const auto &particle : particles) quarks.erase(std::remove_if(quarks.begin(), quarks.end(), Close(particle)), quarks.end());
  return quarks;
}

template <typename Multiplet>
std::vector<Multiplet> CopyIfClose(const std::vector<Multiplet> &multiplets, const Jets& particles)
{
  if(multiplets.empty()) return multiplets;
  std::vector<Multiplet> final_multiplets(multiplets.size());
  typename std::vector<Multiplet>::iterator multiplet;
  for(const auto &particle : particles) multiplet = std::copy_if(multiplets.begin(), multiplets.end(), final_multiplets.begin(), Close(particle));
  final_multiplets.resize(std::distance(final_multiplets.begin(), multiplet));
  return final_multiplets;
}


// Jets RemoveIfClose(const Jets &jets, const Jets &particles);
//
// Jets CopyIfClose(const Jets &jets, const Jets &particles);

}
