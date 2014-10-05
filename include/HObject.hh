# ifndef HObject_hh
# define HObject_hh

# include <iostream>
# include <iomanip>
# include <math.h>
# include <typeinfo>

// # include "TObject.h"
# include "TMath.h"
# include "TLorentzVector.h"
# include "fastjet/PseudoJet.hh"

# include "TString.h"

// # include "HasMember.hh"

using std::left;
using std::setw;
using std::setfill;
using std::cout;
using std::endl;
using std::pair;
using TMath::Pi;
using fastjet::PseudoJet;


// struct CheckHasE
// {
//
//   template <typename Template, double (Template::*)= &Template::E>
//     struct get
//     { };
// };
//
// template <typename Template>
// struct HasE :
//         HasMember<Template, CheckHasE>
// { };


class HObject// : public TObject
{

public:

    HObject();

    virtual ~HObject();

protected:

    /**
     * @brief Calcualte distance in eta phi space
     *
     * @param  Eta1
     * @param  Phi1
     * @param  Eta2
     * @param  Phi2
     * @return float distance
     */
    float GetDistance(float, float, float, float) const;

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Eta
     * @param  Phi
     * @return float distance
     */
    float GetDistance(float, float) const;

    /**
     * @brief Take care of phi angles around pi
     *
     * @param Phi angle
     * @param RefPhi reference angle
     * @return float Phi angle
     */
    float GetDeltaPhi(float, float) const;

    void Print(int, TString) const;

    void Printer(TString) const;

    PseudoJet GetPseudoJet(TLorentzVector) const;

    template<typename Template>
    void Print(int debug, TString Function, Template Number) const {

        if (debug < Debug) {

            Printer(Function);
            cout << " " << Number << endl;

        }

    }

    template<typename Template, typename Template2>
    void Print(int debug, TString Function, Template Number, Template2 Number2) const {

        if (debug < Debug) {

            const char Separator = ' ';
            int const FunctionWidth = 10;

            Printer(Function);

            cout << left << setw(FunctionWidth) << setfill(Separator) << Number;
            cout << left << setw(FunctionWidth) << setfill(Separator) << Number2;
            cout << endl;

        }

    }

    virtual TString ClassName() const {

        return ("HObject");

    };


    /**
     * @brief Debug level
     * 
     */
    int Debug;

    /**
     * @brief A large number
     * 
     */
    int const LargeNumber;

    /**
     * @brief Top quark mass
     * 
     */
    float const TopMass;

    /**
     * @brief Higgs boson mass
     * 
     */
    float const HiggsMass;

    /**
     * @brief W bsoson mass
     * 
     */
    float const WMass;

    /**
     * @brief Tau lepton mass
     * 
     */
    float const TauMass;

    /**
     * @brief Muon mass
     *
     */
    float const MuonMass;

    /**
     * @brief Electron mass
     *
     */
    float const ElectronMass;

    /**
     * @brief Higgs boson user index
     * 
     */
    int const HiggsUserIndex;

    /**
     * @brief Top quark user index
     * 
     */
    int const TopUserIndex;

    /**
     * @brief Initial user index
     * 
     */
    int const EmptyUserIndex;

    /**
     * @brief CP violating Higgs boson index
     * 
     */
    int const CpvHiggsId;

    /**
     * @brief Heavy Higgs boson index
     * 
     */
    int const HeavyHiggsId;

    /**
     * @brief Top quark index
     * 
     */
    int const TopId;

    /**
     * @brief Bottom quark index
     * 
     */
    int const BottomId;

    /**
     * @brief Initial index
     * 
     */
    int const EmptyId;
    
    /**
     * @brief Initial index
     * 
     */
    int const ProtonId;

private:

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

    inline bool operator()(const pair<int, float> &Pair1,
                           const pair<int, float> &Pair2) {

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
                           const PseudoJet &Jet2,
                           const PseudoJet &Jet3) {

        return (Jet1.eta() > Jet2.eta());

    }

};

#endif
