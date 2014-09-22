# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "classes/DelphesClasses.h"

# include "HClonesArray.hh"
# include "HObject.hh"

using std::vector;

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
    virtual bool GetJets(){bool b=1; return b;};
    
    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetEFlow(){bool b=1; return b;};
    
    /**
     * @brief Get Gen Jet
     * 
     * @param  ...
     * @return void
     */
    virtual void GetGenJet(){};
    
    /**
     * @brief Initialize new event
     * 
     * @return void
     */
    void NewEvent(HClonesArray *);
    
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

protected:
    
    /**
     * @brief Get Tau Tag
     * 
     * @return void
     */
    virtual void TauTagCalculations(Jet *){};
    
    
    template<typename Template1, typename Template2>
    bool CheckIsolation(Template1 Particle1, Template2 Particle2)
    {
        
        const float DeltaRIsolationMax = 0.01; // TODO decide on best value
        bool Isolated = true;
        
        float Eta1 = Particle1->Eta;
        float Phi1 = Particle1->Phi;
        float Eta2 = Particle2->Eta;
        float Phi2 = Particle2->Phi;
        
        if (GetDistance(Eta1, Phi1, Eta2, Phi2) < DeltaRIsolationMax) {
            
            Isolated = false;
            
        }
        
        
        Isolated = true; // FIXME this destroys the isolation check (right now on purpose to get harder top jets)
        
        return (Isolated);
        
    }
    

    /**
     * @brief Clones Arrays
     *
     */
    HClonesArray *ClonesArrays;
        
    virtual TString ClassName() {
        return ("HJet");
    };
    
};

#endif
