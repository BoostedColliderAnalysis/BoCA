# ifndef __HJET_HH__
# define __HJET_HH__

# include "TObjArray.h"
// # include "TMathBase.h"
// # include "TMath.h"
// # include "Rtypes.h"
# include "TLorentzVector.h"

# include "fastjet/PseudoJet.hh"

# include "classes/DelphesClasses.h"

# include "HClonesArray.hh"
# include "HObject.hh"


using std::vector;
using fastjet::PseudoJet;

/**
 * @brief stores all the information about the event topology
 *
 */
class HJet : public HObject
{

public:

    /**
     * @brief vector of Jet Lorentz Vectors
     *
     */
    vector<TLorentzVector> JetLorentzVectorVector;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> TauLorentzVectorVector;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiTauLorentzVectorVector;


    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    vector<PseudoJet> EFlowJetVector;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> JetVector;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    vector<PseudoJet> BottomJetVector;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> CharmJetVector;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    vector<PseudoJet> GenJetVector;

    /**
     * @brief vector of Bottom Lorentz Vectors with their pull
     *
     */
//     vector<HPull *> BottomClassVector;

    vector<TLorentzVector> BottomLorentzVectorVector;

    vector<PseudoJet> BottomsVector;

    void TauTagCalculations();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    void AnalyseJet(HClonesArrayBase *);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    void AnalyseEFlow(HClonesArrayBase *);

    void GetGenJet(HClonesArrayBase *);

    /**
     * @brief constructor
     *
     */
    HJet();

    /**
     * @brief destructor
     *
     */
    ~HJet();

    void NewEvent();


    void TauTagCalculations(Jet *);

private:

    /**
     * @brief Clones Arrays
     *
     */
    HClonesArrayBase *ClonesArrays;

    bool CheckIsolation(float, float, float, float);

    PseudoJet FillPtJet(float, float, float);

    PseudoJet FillEJet(float, float, float);
    
    virtual TString ClassName() {
        return ("HJet");
    };
    
    

};

#endif
