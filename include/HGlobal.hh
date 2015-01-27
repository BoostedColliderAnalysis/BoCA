# ifndef HGlobal_hh
# define HGlobal_hh

# include <iostream>
# include <iomanip>
# include <cmath>
# include <vector>

# include "TMath.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

typedef std::vector<fastjet::PseudoJet> HJets;
typedef std::vector<TLorentzVector> HVectors;
typedef std::vector<std::string> HStrings;

/**
 * @brief Main Analysis Library
 *
 */
namespace hanalysis
{

class HObject;
class HFourVector;

class HClonesArray;
class HEvent;
class HFile;
class HParticle;
class HLepton;
class HJet;
class HFamily;

class HAnalysis;
class HTag;
class HJetTag;
class HJetInfo;
class HDoublet;
class HTriplet;
class HJetLeptonPair;
class HQuartet;
class HQuartet31;
class HPairJetPair;
class HSuperStructure;

class HReconstruction;
class HHiggsTagger;
class HDiscriminator;
class HTopTagger;
class HSubStructure;
class HSextet;

class HBottomTagger;
class HTopSemiTagger;
class HTopLeptonicTagger;
class HMvaHiggsTagger;
class HHeavyHiggsHadronicTagger;
class HHeavyHiggsLeptonicTagger;
class HJetPairTagger;
class HChargedJetPairTagger;
class HWTagger;
class HWSemiTagger;
class HTopHadronicTagger;
class HHeavyHiggsSemiTagger;
class HChargedHiggsSemiTagger;
class HChargedHiggsHadronicTagger;
class HChargedHiggsLeptonicTagger;

class HMva;
class HFactory;
class HReader;

class HTagPrivate;
class HDoubletPrivate;
class HTripletPrivate;
class HSextetPrivate;
class HJetInfoPrivate;


/**
 * @brief Parton level analysis library parts
 *
 */
namespace hparton
{

class HClonesArray;
class HFile;
class HEvent;
class HParticle;

}

typedef hparton::HClonesArray HClonesArrayParton;
typedef hparton::HFile HFileParton;
typedef hparton::HEvent HEventParton;
typedef hparton::HParticle HParticleParton;


/**
 * @brief Pgs analysis library parts
 *
 */
namespace hpgs
{

class HClonesArray;
class HFile;
class HEvent;
class HLepton;
class HJet;

}

typedef hpgs::HClonesArray HClonesArrayPgs;
typedef hpgs::HFile HFilePgs;
typedef hpgs::HEvent HEventPgs;
typedef hpgs::HLepton HLeptonPgs;
typedef hpgs::HJet HJetPgs;

/**
 * @brief Delphes analysis library parts
 *
 */
namespace hdelphes
{

class HClonesArray;
class HClonesArraySnowmass;
class HFile;
class HEvent;
class HParticle;
class HLepton;
class HJet;

}

typedef hdelphes::HClonesArray HClonesArrayDelphes;
typedef hdelphes::HClonesArraySnowmass HClonesArraySnowmass;
typedef hdelphes::HFile HFileDelphes;
typedef hdelphes::HEvent HEventDelphes;
typedef hdelphes::HParticle HParticleDelphes;
typedef hdelphes::HLepton HLeptonDelphes;
typedef hdelphes::HJet HJetDelphes;



}

struct SortByPt {
    inline bool operator()(const TLorentzVector &Lorentzvector1,const TLorentzVector &Lorentzvector2) {
        return (Lorentzvector1.Pt() > Lorentzvector2.Pt());
    }
};

struct SortJetByPt {
    inline bool operator()(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2) {
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


class SortJetByMass{
public:
    inline bool operator()(const fastjet::PseudoJet &PseudoJet1,const fastjet::PseudoJet &PseudoJet2) {
        return (PseudoJet1.m() > PseudoJet2.m());
    }
};

// template <typename Template1, typename Template2>
struct SortPairs {
//     inline bool operator()(const pair<Template1, Template2> &Pair1,
//                            const pair<Template1, Template2> &Pair2) {
//
//         return (Pair1.second > Pair2.second);
//
//     }
    inline bool operator()(const std::pair<int, float> &Pair1,const std::pair<int, float> &Pair2) {
        return (Pair1.second < Pair2.second);
    }
};

struct SortJetByRap {
    inline bool operator()(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2) {
        return (Jet1.rap() > Jet2.rap());
    }
};


struct SortJetByDistance {
    inline bool operator()(const fastjet::PseudoJet &Jet1,const fastjet::PseudoJet &Jet2) {
        return (Jet1.rap() > Jet2.rap());
    }
};


// template <typename TMultiplet>
// struct SortByBdt {
//   inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
//     return (Multiplet1.Bdt() > Multiplet2.Bdt());
//   }
// };

class HRange
{

private:

    int Last;

    int Iter;

public:

    HRange(int End):
        Last(End),
        Iter(0)
    {}

    // Iterable functions
    const HRange &begin() const {
        return *this;
    }
    const HRange &end() const {
        return *this;
    }

    // Iterator functions
    bool operator!=(const HRange &) const {
        return Iter < Last;
    }
    void operator++() {
        ++Iter;
    }
    int operator*() const {
        return Iter;
    }

};

#endif
