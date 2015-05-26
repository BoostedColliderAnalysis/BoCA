# pragma once

# include <cmath>
#include <algorithm>
# include  "fastjet/PseudoJet.hh"
# include  "TLorentzVector.h"
# include  "Global.hh"
# include  "JetInfo.hh"
# include  "ClonesArrays.hh"

namespace analysis
{

struct SortByPt {
    inline bool operator()(const TLorentzVector &Lorentzvector1, const TLorentzVector &Lorentzvector2) {
        return (Lorentzvector1.Pt() > Lorentzvector2.Pt());
    }
};

struct SortJetByPt {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.pt() > Jet2.pt());
    }
};

class SortJetByMass
{
public:
    inline bool operator()(const fastjet::PseudoJet &PseudoJet1, const fastjet::PseudoJet &PseudoJet2) {
        return (PseudoJet1.m() > PseudoJet2.m());
    }
};

struct SortPairs {
    template <typename Template1>
    inline bool operator()(const std::pair<Template1, float> &Pair1, const std::pair<Template1, float> &Pair2) {
        return (Pair1.second < Pair2.second);
    }
};

struct SortJetByRap {
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return (Jet1.rap() > Jet2.rap());
    }
};

/**
 * @brief Get a fastjet::PseudoJet from a TLorentzVector
 *
 */
fastjet::PseudoJet PseudoJet(const TLorentzVector &vector);

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
        return (jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id != id_);
        return (jet.user_info<analysis::JetInfo>().constituents().front().family().particle().Id != id_);
    }
    int id_;
};

struct WrongAbsId {
    WrongAbsId(const int NewId) {
        Id = NewId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
        return family.mother_1().Id != Mother;
    }
    int Mother;
};

struct WrongAbsMother {
    WrongAbsMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_1().Id) != Mother;
    }
    int Mother;
};

struct AbsMother {
    AbsMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
        return std::abs(family.mother_2().Id) != Mother2;
    }
    int Mother2;
};

struct WrongLeptons {
    bool operator()(const fastjet::PseudoJet &Jet) {
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
        return (std::abs(family.particle().Id) == family.ElectronId ||
                std::abs(family.particle().Id) == family.MuonId ||
                std::abs(family.particle().Id) == family.TauId ||
                std::abs(family.particle().Id) == family.TauNeutrinoId ||
                std::abs(family.particle().Id) == family.MuonNeutrinoId ||
                std::abs(family.particle().Id) == family.ElectronNeutrinoId
               );
    }
};

struct WrongQuark {
    bool operator()(const fastjet::PseudoJet &Jet) {
        analysis::JetInfo jet_info = Jet.user_info<analysis::JetInfo>();
        analysis::Family family = jet_info.constituents().front().family();
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

template<typename Multiplet>
inline std::vector<Multiplet> SortedByMinDeltaRTo(std::vector<Multiplet> &multiplets, const fastjet::PseudoJet &jet)
{
    std::sort(multiplets.begin(), multiplets.end(), MinDeltaRTo(jet));
    return multiplets;
}

template <class HMultiplet>
inline std::vector<HMultiplet> SortByMaxDeltaRap(std::vector<HMultiplet> &Multiplets)
{
    std::sort(Multiplets.begin(), Multiplets.end(), MaxDeltaRap());
    return Multiplets;
}

template <class HMultiplet>
inline std::vector<HMultiplet> SortByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass)
{
    std::sort(Multiplets.begin(), Multiplets.end(), SortByMass(Mass));
    return Multiplets;
}

Jets copy_if_abs_particle(const Jets &jets, const int particle_id);

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


Jets RemoveIfClose(const Jets &jets, const Jets &particles);

Jets CopyIfClose(const Jets &jets, const Jets &particles);

// template<typename Predicate>
// Jets FindIf(const Jets &jets){
//   return std::find_if(jets.begin(),jets.end(),Predicate);
// }

template <typename Element>
std::vector<Element> JoinVectors(const std::vector<Element> &vector_1, const std::vector<Element> &vector_2)
{
    std::vector<Element> joined;
    joined.reserve(vector_1.size() + vector_2.size());
    joined.insert(joined.end(), vector_1.begin(), vector_1.end());
    joined.insert(joined.end(), vector_2.begin(), vector_2.end());
    return joined;
}

template <typename Element>
bool FindInVector(const std::vector<Element> vector, const Element element)
{
    return (std::find(vector.begin(), vector.end(), element) != vector.end());
}

}
