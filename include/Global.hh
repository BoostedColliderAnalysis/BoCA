# pragma once

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TMath.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

typedef std::vector<fastjet::PseudoJet> Jets;
typedef std::vector<TLorentzVector> Vectors;
typedef std::vector<std::string> Strings;

/**
 * @brief Main Analysis Library
 *
 */
namespace analysis
{

class HJetLeptonPair;
class HPairJetPair;
class HSuperStructure;

class HReconstruction;
class HHiggsTagger;
class HDiscriminator;
class top_hadronic_tagger;
class HSubStructure;

class TauTagger;
class TopSemiTagger;
class HTopLeptonicTagger;
class HMvaHiggsTagger;
class HHeavyHiggsHadronicTagger;
class HHeavyHiggsLeptonicTagger;
class JetPairTagger;
class TripletJetPairTagger;
class WSemiTagger;
class HeavyHiggsSemiTagger;
class HHeavyHiggsTauTagger;
class HChargedHiggsSemiTagger;
class HChargedHiggsHadronicTagger;
class HChargedHiggsLeptonicTagger;

}

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

// template <typename TParticle>
// class SortByMass
// {
//
// public:
//
//     inline bool operator()(const TParticle &Particle1,
//                            const TParticle &Particle2) {
//
//         return (Particle1.m() > Particle2.m());
//
//     }
//
// };


class SortJetByMass
{
public:
    inline bool operator()(const fastjet::PseudoJet &PseudoJet1, const fastjet::PseudoJet &PseudoJet2) {
        return (PseudoJet1.m() > PseudoJet2.m());
    }
};

// // template <typename Template1, typename Template2>
// struct SortPairs {
// //     inline bool operator()(const pair<Template1, Template2> &Pair1,
// //                            const pair<Template1, Template2> &Pair2) {
// //
// //         return (Pair1.second > Pair2.second);
// //
// //     }
//     inline bool operator()(const std::pair<int, float> &Pair1,const std::pair<int, float> &Pair2) {
//         return (Pair1.second < Pair2.second);
//     }
// };

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


// struct SortJetByDistance {
//     inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
//         return (Jet1.rap() > Jet2.rap());
//     }
// };


// template <typename TMultiplet>
// struct SortByBdt {
//   inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
//     return (Multiplet1.Bdt() > Multiplet2.Bdt());
//   }
// };




class Range
{
public:
    Range(const int sum):
        last_(sum),
        iterator_(0)
    {}
    const Range &begin() const {
        return *this;
    }
    const Range &end() const {
        return *this;
    }
    bool operator!=(const Range &) const {
        return iterator_ < last_;
    }
    void operator++() {
        ++iterator_;
    }
    int operator*() const {
        return iterator_;
    }
private:
    int last_;
    int iterator_;
};
