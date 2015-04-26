# pragma once

#include <cmath>
#include  "fastjet/PseudoJet.hh"
#include  "HGlobal.hh"
#include  "HJetInfo.hh"

struct SortByMass {
  SortByMass(const float NewMass) {
    Mass = NewMass;
  }
  template <typename TMultiplet>
  inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
    if (Multiplet1.Jet().m() != Multiplet2.Jet().m()) return std::abs(Multiplet1.Jet().m() - Mass) < std::abs(Multiplet2.Jet().m() - Mass);
    else return Multiplet1.Bdt() > Multiplet2.Bdt();
  }
  float Mass;
};

struct MinDeltaR {
  MinDeltaR(const fastjet::PseudoJet &NewParticle) {
    Particle = NewParticle;
  }
  template <typename TMultiplet>
  inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
    return Multiplet1.Jet().delta_R(Particle)  < Multiplet2.Jet().delta_R(Particle);
  }
  inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
    return Jet1.delta_R(Particle)  < Jet2.delta_R(Particle);
  }
  fastjet::PseudoJet Particle;
};



struct MaxDeltaRap {
  template <typename TMultiplet>
  inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
    return (Multiplet1.DeltaRap() > Multiplet2.DeltaRap());
  }
};

struct MaxPt {
  template <typename TMultiplet>
  inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
    return (Multiplet1.Jet().pt() > Multiplet2.Jet().pt());
  }
};



struct TooSmallPt {
  TooSmallPt(const int pt) {
    pt_ = pt;
  }
  bool operator()(const fastjet::PseudoJet &jet) {
    return (jet.pt() < pt_);
  }
  int pt_;
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
    return (jet.user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId != id_);
  }
  int id_;
};

struct WrongAbsId {
  WrongAbsId(const int NewId) {
    Id = NewId;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) != Id);
  }
  int Id;
};

struct WrongAbsPairId {
  WrongAbsPairId(const int NewId, const int NewId2) {
    Id = NewId;
    Id2 = NewId2;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) != Id && std::abs(Family.ParticleId) != Id2);
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
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) != Id || std::abs(Family.Mother1Id) != Mother);
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
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (Family.ParticleId != Id || Family.Mother1Id != Mother);
  }
  int Id;
  int Mother;
};

struct WrongMother {
  WrongMother(const int NewMother) {
    Mother = NewMother;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return Family.Mother1Id != Mother;
  }
  int Mother;
};

struct WrongAbsMother {
  WrongAbsMother(const int NewMother) {
    Mother = NewMother;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return std::abs(Family.Mother1Id) != Mother;
  }
  int Mother;
};

struct AbsMother {
  AbsMother(const int NewMother) {
    Mother = NewMother;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return std::abs(Family.Mother1Id) == Mother;
  }
  int Mother;
};

struct WrongAbsStepFamily {
  WrongAbsStepFamily(const int NewParticleId, const int NewMother2) {
    Mother2 = NewMother2;
    ParticleId = NewParticleId;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) != ParticleId || std::abs(Family.Mother2Id) != Mother2);
  }
  int Mother2;
  int ParticleId;
};

struct WrongAbsStepMother {
  WrongAbsStepMother(const int NewMother2) {
    Mother2 = NewMother2;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return std::abs(Family.Mother2Id) != Mother2;
  }
  int Mother2;
};

struct WrongLeptons {
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) == Family.ElectronId ||
    std::abs(Family.ParticleId) == Family.MuonId ||
    std::abs(Family.ParticleId) == Family.TauId ||
    std::abs(Family.ParticleId) == Family.TauNeutrinoId ||
    std::abs(Family.ParticleId) == Family.MuonNeutrinoId ||
    std::abs(Family.ParticleId) == Family.ElectronNeutrinoId
    );
  }
};

struct WrongQuark {
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) == Family.UpId ||
    std::abs(Family.ParticleId) == Family.DownId ||
    std::abs(Family.ParticleId) == Family.CharmId ||
    std::abs(Family.ParticleId) == Family.StrangeId ||
    std::abs(Family.ParticleId) == Family.BottomId ||
    std::abs(Family.ParticleId) == Family.TopId
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

template<typename TMultiplet>
inline std::vector<TMultiplet> SortByDeltaRTo(std::vector<TMultiplet> &Multiplets, fastjet::PseudoJet Jet) {
  std::sort(Multiplets.begin(), Multiplets.end(), MinDeltaR(Jet));
  return Multiplets;
}

template <class HMultiplet>
inline std::vector<HMultiplet> SortByMaxDeltaRap(std::vector<HMultiplet> &Multiplets) {
  std::sort(Multiplets.begin(), Multiplets.end(), MaxDeltaRap());
  return Multiplets;
}

template <class HMultiplet>
inline std::vector<HMultiplet> SortByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass) {
  std::sort(Multiplets.begin(), Multiplets.end(), SortByMass(Mass));
  return Multiplets;
}

HJets RemoveIfWrongAbsFamily(const HJets &jets, const int particle_id, int mother_id);

HJets RemoveIfWrongFamily(const HJets &jets, const int particle_id, int mother_id);

HJets RemoveIfWrongAbsStepFamily(const HJets &jets, const int particle_id , const int mother_2_id);

HJets RemoveIfWrongAbsStepMother(const HJets &jets, const int mother_2_id);

HJets RemoveIfWrongParticle(const HJets &NewJets, const int ParticleId);

HJets RemoveIfWrongAbsParticle(const HJets &NewJets, const int ParticleId);

HJets RemoveIfWrongAbsMother(const HJets &NewJets, const int MotherId);

HJets RemoveIfAbsMother(const HJets &NewJets, const int MotherId);


HJets RemoveIfLetpons(const HJets &Jets);

HJets RemoveIfQuark(const HJets &Jets);

HJets RemoveIfNot5Quarks(const HJets &Jets);

// template<typename Predicate>
// HJets FindIf(const HJets &jets){
//   return std::find_if(jets.begin(),jets.end(),Predicate);
// }
