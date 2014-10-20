# ifndef HObject_hh
# define HObject_hh

# include <iostream>
# include <iomanip>

# include "TMath.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

using fastjet::PseudoJet;
using std::string;

/**
 * @brief general base class for HAnalysis
 *
 */
class HObject
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
    void Print(const int Severity, const string Description) const;

    /**
     * @brief Print a debug messages
     *
     * @param  Severity of the debug message
     * @param  Description of the debug message
     * @param  Value relevant to the debug message
     *
     * @return void
     */
    template<typename TValue>
    void Print(const int Severity, const string Description, const TValue Value) const {

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
    template<typename TValue, typename TValue2>
    void Print(const int Severity, const string Description, const TValue Value, const TValue2 Value2) const {

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
    template<typename TValue, typename TValue2, typename TValue3>
    void Print(const int Severity, const string Description, const TValue Value, const TValue2 Value2, const TValue3 Value3) const {

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

protected:

    template <typename TValue> int sgn(const TValue Value) const {

        return (TValue(0) < Value) - (Value < TValue(0));

    }

    /**
     * @brief Calcualte distance in eta phi space
     *
     * @param  Eta1
     * @param  Phi1
     * @param  Eta2
     * @param  Phi2
     * @return float distance
     */
    float GetDistance(const float, const float, const float, const float) const;

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Eta
     * @param  Phi
     * @return float distance
     */
    float GetDistance(const float, const float) const;

    /**
     * @brief Take care of phi angles around pi
     *
     * @param Phi angle
     * @param RefPhi reference angle
     * @return float Phi angle
     */
    float GetDeltaPhi(const float, const float) const;

    virtual string ClassName() const {

        return ("HObject");

    };

    enum HStatus {
        Stable = 1,
        Unstable = 2,
        Undefined = 3
    };

    enum HParticleId {
        EmptyId = 0,
        DownId = 1,
        UpId = 2,
        StrangeId = 3,
        CharmId = 4,
        BottomId = 5,
        TopId = 6,
        ElectronId = 11,
        MuonId = 13,
        TauLeptonId = 15,
        GluonId = 21,
        WId = 24,
        HeavyHiggsId = 35,
        DownDown1Id = 1103,
        UpDown0Id = 2101,
        UpDown1Id = 2103,
        UpUp1Id = 2203,
        ProtonId = 2212,
        CpvHiggsId = 5000000,
    };


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
    int DebugLevel;

    /**
     * @brief A large number
     *
     */
    const int LargeNumber;

    /**
     * @brief Top quark mass
     *
     */
    const float TopMass;

    /**
     * @brief Higgs boson mass
     *
     */
    const float HiggsMass;

    /**
     * @brief W bsoson mass
     *
     */
    const float WMass;

    /**
     * @brief Tau lepton mass
     *
     */
    const float TauMass;

    /**
     * @brief Muon mass
     *
     */
    const float MuonMass;

    /**
     * @brief Electron mass
     *
     */
    const float ElectronMass;

    /**
     * @brief Higgs boson user index
     *
     */
    const int HiggsUserIndex;

    /**
     * @brief Top quark user index
     *
     */
    const int TopUserIndex;

    /**
     * @brief Initial user index
     *
     */
    const int EmptyUserIndex;

    /**
     * @brief Proton index
     *
     */
    const int DeltaBaryon2Id;

    /**
     * @brief Up-down di-quark index
     *
     */
    const int NeutronId;

    /**
     * @brief Down-down di-quark index
     *
     */
    const int DeltaBaryonId;

    /**
     * @brief Pion index
     *
     */
    const int BMesonSS0Id;

    /**
     * @brief Pion index
     *
     */
    const int BMesonS0Id;

    /**
     * @brief Pion index
     *
     */
    const int BMesonSId;

    /**
     * @brief Pion index
     *
     */
    const int BMesonId;

    /**
     * @brief Pion index
     *
     */
    const int BMeson0SId;

    /**
     * @brief Pion index
     *
     */
    const int BMeson0Id;

    /**
     * @brief Pion index
     *
     */
    const int DMesonS0Id;

    /**
     * @brief Pion index
     *
     */
    const int DMeson0Id;

    /**
     * @brief Pion index
     *
     */
    const int DMesonS2Id;

    /**
     * @brief Pion index
     *
     */
    const int DMesonSId;

    /**
     * @brief Pion index
     *
     */
    const int DMesonId;

    /**
     * @brief Pion index
     *
     */
    const int KMesonSId;

    /**
     * @brief Pion index
     *
     */
    const int KMesonId;

    /**
     * @brief Pion index
     *
     */
    const int KMeson0SId;

    /**
     * @brief Pion index
     *
     */
    const int KMeson0Id;

    /**
     * @brief Pion index
     *
     */
    const int RhoMesonId;

    /**
     * @brief Pion index
     *
     */
    const int PionId;

    /**
     * @brief Initial state radiation index
     *
     * Index for all possbile initial state radiation.
     * The value is self definied, be carfull with clashes.
     *
     */
    const int IsrId;

    const float OneSigma;

    const float TwoSigma;

    const float ThreeSigma;

private:

    /**
     * @brief Print Debug messages
     *
     * @param  string Function Name
     * @return void
     */
    void Printer(const string) const;

};


struct SortByPt {

    inline bool operator()(const TLorentzVector &Lorentzvector1,
                           const TLorentzVector &Lorentzvector2) {

        return (Lorentzvector1.Pt() > Lorentzvector2.Pt());

    }

};

struct SortJetByPt {

    inline bool operator()(const PseudoJet &Jet1,
                           const PseudoJet &Jet2) {

        return (Jet1.pt() > Jet2.pt());

    }

};

struct SortJetByMass {

    inline bool operator()(const PseudoJet &PseudoJet1,
                           const PseudoJet &PseudoJet2) {

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

struct SortJetByEta {

    inline bool operator()(const PseudoJet &Jet1,
                           const PseudoJet &Jet2) {

        return (Jet1.eta() > Jet2.eta());

    }

};


struct SortJetByDistance {

    inline bool operator()(const PseudoJet &Jet1,
                           const PseudoJet &Jet2) {

        return (Jet1.eta() > Jet2.eta());

    }

};

#endif

