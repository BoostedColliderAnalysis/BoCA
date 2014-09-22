# ifndef HObject_hh
# define HObject_hh

# include <iostream>
# include <iomanip>
# include <math.h>
#include <typeinfo>

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


class HObject
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
    float GetDistance(float, float, float, float);

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Eta
     * @param  Phi
     * @return float distance
     */
    float GetDistance(float, float);

    /**
     * @brief Take care of phi angles around pi
     *
     * @param Phi angle
     * @param RefPhi reference angle
     * @return float Phi angle
     */
    float GetDeltaPhi(float, float);

    void Print(int debug, TString Function);

    void Printer(TString Function);

    template<typename Template>
    void Print(int debug, TString Function, Template Number) {

        if (debug < Debug) {

            Printer(Function);
            cout << " " << Number << endl;

        }

    }

    template<typename Template, typename Template2>
    void Print(int debug, TString Function, Template Number, Template2 Number2) {

        if (debug < Debug) {

            const char Separator = ' ';
            const int FunctionWidth = 10;

            Printer(Function);

//             cout << " " << endl;
            cout << left << setw(FunctionWidth) << setfill(Separator) << Number;
            cout << left << setw(FunctionWidth) << setfill(Separator) << Number2;
            cout << endl;

        }

    }

    template<typename Template>
    TLorentzVector GetLorentzVector(Template *Particle) {

        Print(2, "Get Lorentz Vector");

//         TString s = typeid(Particle).name();
//         Print(0,"Type",s);


        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;
        float E = Particle->E;

//      Print(0,"HasE",HasE<Template>::Value);

        TLorentzVector LorentzVector;
        LorentzVector.SetPtEtaPhiE(Pt, Eta, Phi, E);

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVector(Template *Particle, float Mass) {

        Print(2, "Get Lorentz Vector");

        TLorentzVector LorentzVector;

        float ParticlePt = Particle->PT;
        float ParticleEta = Particle->Eta;
        float ParticlePhi = Particle->Phi;

        LorentzVector.SetPtEtaPhiM(ParticlePt, ParticleEta, ParticlePhi, Mass);

        return LorentzVector;

    }

    template<typename Template>
    TLorentzVector GetLorentzVectorM(Template *Particle) {

        Print(2, "Get Lorentz Vector");

        TLorentzVector LorentzVector;

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;
        float Mass = Particle->Mass;

        LorentzVector.SetPtEtaPhiM(Pt, Eta, Phi, Mass);

        return LorentzVector;

    }

    template<typename Template>
    PseudoJet GetPseudoJetPt(Template *Particle) {

        Print(2, "Get Pseudo Jet");

        float Pt = Particle->PT;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;

        PseudoJet Jet = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Pt * cosh(Eta));

        return Jet;

    }

    template<typename Template>
    PseudoJet GetPseudoJetE(Template *Particle) {

        Print(2, "Get Pseudo Jet");

        float E = Particle->E;
        float Eta = Particle->Eta;
        float Phi = Particle->Phi;
        float Pt = E / cosh(Eta);

        PseudoJet Jet = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Pt * cosh(Eta));

        return Jet;

    }

    virtual TString ClassName() {
        return ("HObject");
    };


    int Debug;

    const int LargeNumber;

    const float HiggsMass;

    const float TopMass;

    const float WMass;

    /**
     * @brief Physical Muon Mass
     *
     */
    const float MuonMass;

    /**
     * @brief Physical Electron Mass
     *
     */
    const float ElectronMass;

    const int HiggsUserIndex;

    const int TopUserIndex;

    const int TopId;

    const int BottomId;
    
    const int EmptyId;

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

struct SortPairs {

    inline bool operator()(const pair<TString, int> &Pair1,
                           const pair<TString, int> &Pair2) {

        return (Pair1.second > Pair2.second);

    }

};

struct SortJetByEta {

    inline bool operator()(const PseudoJet &Jet1,
                           const PseudoJet &Jet2) {

        return (Jet1.eta() > Jet2.eta());

    }

};

#endif
