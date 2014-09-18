# ifndef HJet_hh
# define HJet_hh

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
     * @brief constructor
     *
     */
    HJet();
    
    /**
     * @brief Destructor
     *
     */
    ~HJet();
    
    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    void AnalyseJet(HClonesArrayBase *);
    
    /**
     * @brief Get Tau Tag
     * 
     * @return void
     */
    void TauTagCalculations(Jet *);
    
    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool AnalyseEFlow(HClonesArrayBase *ImportClonesArrays);
    
    /**
     * @brief Get Gen Jet
     * 
     * @param  ...
     * @return void
     */
    void GetGenJet(HClonesArrayBase *);
    
    /**
     * @brief Initialize new event
     * 
     * @return void
     */
    void NewEvent();
    
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
    vector<TLorentzVector> BottomLorentzVectorVector;


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
