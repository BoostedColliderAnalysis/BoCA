# ifndef HObject_hh
# define HObject_hh

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


/**
 * @brief general base class for HAnalysis
 *
 */
class hanalysis::HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HObject();

    /**
     * @brief Destructor
     *
     */
    virtual ~HObject();

    /**
     * @brief Print a debug message
     *
     * @param  Severity of the debug message
     * @param  Description of the debug message
     * @return void
     */

    enum HSeverity {
        HError,
        HNotification,
        HInformation,
        HDebug,
        HDetailed
    };

    enum HTag {HBackground = 0, HSignal = 1};

    template <typename TSeverity>
    void Print(const TSeverity Severity, const std::string &Description) const {

        if (Severity <= DebugLevel) {

            Printer(Description);
            std::cout << std::endl;
        }

    }

    /**
     * @brief Print a debug messages
     *
     * @param  Severity of the debug message
     * @param  Description of the debug message
     * @param  Value relevant to the debug message
     *
     * @return void
     */
    template<typename TSeverity, typename TValue>
    void Print(const TSeverity Severity, const std::string Description, const TValue Value) const {

        if (Severity <= DebugLevel) {

            Printer(Description);
            std::cout << " " << Value << std::endl;

        }

    }

    /**
     * @brief Print a debug messages
     *
     * @param  Severity of the debug message
     * @param  Description of the debug message
     * @param  Value relevant to the debug message
     * @param  Value2 relevant to the debug message
     *
     * @return void
     */
    template<typename TSeverity, typename TValue, typename TValue2>
    void Print(const TSeverity Severity, const std::string Description, const TValue Value, const TValue2 Value2) const {

        if (Severity <= DebugLevel) {

            const char Separator = ' ';
            const int FunctionWidth = 10;

            Printer(Description);

            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value2;
            std::cout << std::endl;

        }

    }

    /**
     * @brief Print a debug messages
     *
     * @param  Severity of the debug message
     * @param  Description of the debug message
     * @param  Value relevant to the debug message
     * @param  Value2 relevant to the debug message
     * @param  Value3 relevant to the debug message
     *
     * @return void
     */
    template<typename TSeverity, typename TValue, typename TValue2, typename TValue3>
    void Print(const TSeverity Severity, const std::string Description, const TValue Value, const TValue2 Value2, const TValue3 Value3) const {

        if (Severity <= DebugLevel) {

            const char Separator = ' ';
            const int FunctionWidth = 10;

            Printer(Description);

            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value2;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value3;
            std::cout << std::endl;

        }

    }

    template<typename TSeverity, typename TValue, typename TValue2, typename TValue3, typename TValue4>
    void Print(const TSeverity Severity, const std::string Description, const TValue Value, const TValue2 Value2, const TValue3 Value3, const TValue4 Value4) const {

        if (Severity <= DebugLevel) {

            const char Separator = ' ';
            const int FunctionWidth = 15;

            Printer(Description);

            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value2;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value3;
            std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << Value4;
            std::cout << std::endl;

        }

    }

    template<typename TSeverity>
    void Print(const TSeverity Severity, const std::string Description, const fastjet::PseudoJet Jet) const {
        if (Severity <= DebugLevel) Print(Severity, Description, Jet.e(), Jet.px(), Jet.py(), Jet.pz());
    }

    template<typename TSeverity>
    void Print(const TSeverity Severity, const std::string Description, float Momentum[]) const {
        if (Severity <= DebugLevel) Print(Severity, Description, Momentum[0], Momentum[1], Momentum[2], Momentum[3]);
    }

    enum HParticleId {
        EmptyId = 0, ///< 0
        DownId = 1,///< \f$d\f$
        UpId = 2,///< \f$u\f$
        StrangeId = 3,///< \f$s\f$
        CharmId = 4,///< \f$c\f$
        BottomId = 5,///< \f$b\f$
        TopId = 6,///< \f$t\f$
        ElectronId = 11,
        ElectronNeutrinoId = 12,
        MuonId = 13,
        MuonNeutrinoId = 14,
        TauLeptonId = 15,
        TauNeutrinoId = 16,
        GluonId = 21,
        PhotonId = 22,
        ZId = 23,
        WId = 24,
        HiggsId = 25,
        HeavyHiggsId = 35,
        CPOddHiggsId = 36,
        ChargedHiggsId = 37,
        AnyId = 86,
        IsrId = 87,
        MarkerId = 88,
        MixedJetId = 90,
        ClusterId = 91,
        StringId = 92,
        Pi0MesonId = 111,
        Rho0MesonId = 113,
        K0LMesonId = 130,
        PionId = 211,
        RhoMesonId = 213,
        RapMesonId = 221,
        OmegaMesonId = 223,
        K0SMesonId = 310,
        KMeson0Id = 311,
        KMeson0SId = 313,
        KMesonId = 321,
        KMesonSId = 323,
        RapPMesonId = 331,
        DMesonId = 411,
        DMesonSId = 413,
        DMesonS2Id = 415,
        DMeson0Id = 421,
        DMesonS0Id = 423,
        RapCMesonId = 441,
        BMeson0Id = 511,
        BMeson0SId = 513,
        BMesonId = 521,
        BMesonSId = 523,
        BMesonS0Id = 531,
        BMesonSS0Id = 533,
        DownDown1Id = 1103,
        UpDown0Id = 2101,
        UpDown1Id = 2103,
        DeltaBaryonId = 1114,
        NeutronId = 2112,
        UpUp1Id = 2203,
        ProtonId = 2212,
        DeltaBaryon2Id = 2224,
        CpvHiggsId = 5000000
    };

    /**
     * @brief Top quark mass
     *
     */
    constexpr static float TopMass = 173.5;

    /**
     * @brief W bsoson mass
     *
     */
    constexpr static float WMass = 80.39;

protected:

    template <typename TValue>
    int sgn(const TValue Value) const {
        return (TValue(0) < Value) - (Value < TValue(0));
    }

    /**
     * @brief Calcualte distance in eta phi space
     *
     * @param  Rap1
     * @param  Phi1
     * @param  Rap2
     * @param  Phi2
     * @return float distance
     */
    float GetDistance(const float, const float, const float, const float) const;

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Rap
     * @param  Phi
     * @return float distance
     */
    float GetDistance(const float, const float) const;

    /**
     * @brief Take care of phi angles around pi
     *
     */
    float GetDeltaPhi(const float Phi, const float ReferencePhi) const;

    virtual inline std::string NameSpaceName() const {
        return ("hanalysis");
    }

    virtual inline std::string ClassName() const {

        return ("HObject");

    };

    enum HStatus {
        StableParticle = 1,
        UnstableParticle = 2,
        GeneratorParticle = 3
    };

    std::string GetParticleName(const int ParticleId) const;

    float GetParticleMass(const hanalysis::HObject::HParticleId ParticleId) const;


    /**
     * @brief Debug level
     *
     * 0: Errors
     * 1: Analysis Information
     * 2: Event Information
     * 3: Detailed Information
     * 4: Step by Step Information
     *
     */
    HSeverity DebugLevel;

    /**
     * @brief A large number
     *
     */
    static const int LargeNumber = 999999999;

    /**
     * @brief Higgs boson mass
     *
     */
    constexpr static float HiggsMass = 125;

    /**
     * @brief W bsoson mass
     *
     */
    constexpr static float ZMass = 91.188;

    /**
     * @brief Tau lepton mass
     *
     */
    constexpr static float TauMass = 1.776;

    /**
     * @brief Muon mass
     *
     */
    constexpr static float MuonMass = 0.1134;

    /**
     * @brief Electron mass
     *
     */
    constexpr static float ElectronMass = 0.000511;

    constexpr static float NeutrinoMass = 0;

    /**
     * @brief Initial user index
     *
     */
    static const int EmptyUserIndex = -1;

    static const int EmptyPosition = -1;

    constexpr static float Pi = 3.14159265;

    constexpr static float TwoPi = 2 * Pi;

    constexpr static float OneSigma = 0.6827;

    constexpr static float TwoSigma = 0.9545;

    constexpr static float ThreeSigma = 0.9973;

private:

    /**
     * @brief Print Debug messages
     *
     * @param  std::string Function Name
     * @return void
     */
    void Printer(const std::string &) const;

};


struct SortByPt {

    inline bool operator()(const TLorentzVector &Lorentzvector1,
                           const TLorentzVector &Lorentzvector2) {

        return (Lorentzvector1.Pt() > Lorentzvector2.Pt());

    }

};

struct SortJetByPt {

    inline bool operator()(const fastjet::PseudoJet &Jet1,
                           const fastjet::PseudoJet &Jet2) {

        return (Jet1.pt() > Jet2.pt());

    }

};

template <typename TParticle>
class SortByMass
{

public:

    inline bool operator()(const TParticle &Particle1,
                           const TParticle &Particle2) {

        return (Particle1.m() > Particle2.m());

    }

};


class SortJetByMass
{

public:

    inline bool operator()(const fastjet::PseudoJet &PseudoJet1,
                           const fastjet::PseudoJet &PseudoJet2) {

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

    inline bool operator()(const std::pair<int, float> &Pair1,
                           const std::pair<int, float> &Pair2) {

        return (Pair1.second < Pair2.second);

    }

};

struct SortJetByRap {

    inline bool operator()(const fastjet::PseudoJet &Jet1,
                           const fastjet::PseudoJet &Jet2) {

        return (Jet1.rap() > Jet2.rap());

    }

};


struct SortJetByDistance {

    inline bool operator()(const fastjet::PseudoJet &Jet1,
                           const fastjet::PseudoJet &Jet2) {

        return (Jet1.rap() > Jet2.rap());

    }

};



// template <typename TMultiplet>
// struct SortByBdt {
//   inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
//     return (Multiplet1.GetBdt() > Multiplet2.GetBdt());
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

