# ifndef __HPARTICLE_HH__
# define __HPARTICLE_HH__

# include "TObjArray.h"

# include "fastjet/PseudoJet.hh"

# ifdef MadGraph
# include "ExRootAnalysis/ExRootClasses.h"
# else
# include "classes/DelphesClasses.h"
# endif

# include "HClonesArray.hh"
# include "HObject.hh"

typedef
# ifdef MadGraph
TRootLHEFParticle
# else
GenParticle
# endif
CParticle;

using fastjet::PseudoJet;
using std::sort;
using std::vector;

/**
 * @brief stores all the information about the event topology
 *
 */
class HParticle : public HObject
{

public:

    vector<TLorentzVector> TopVector;

    vector<TLorentzVector> AntiTopVector;

    vector<TLorentzVector> ElectronVector;

    vector<TLorentzVector> MuonVector;

    vector<TLorentzVector> AntiElectronVector;

    vector<TLorentzVector> AntiMuonVector;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    vector<PseudoJet> BottomJetVector;

    vector<PseudoJet> TopJetVector;
    
    
    /**
     * @brief Vector of generator level Higgs Pseudo Jets
     *
     */
    vector<PseudoJet> HiggsJetVector;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> CharmJetVector;

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    bool GetParticles(HClonesArrayBase *);

    /**
     * @brief constructor
     *
     */
    HParticle();

    /**
     * @brief destructor
     *
     */
    ~HParticle();
    
    void NewEvent();

    vector<TLorentzVector> LeptonVector();

    vector<TLorentzVector> AntiLeptonVector();
    


private:

    /**
     * @brief Clones Arrays
     *
     */
    HClonesArrayBase *ClonesArrays;

    TLorentzVector GetLorentzVector(CParticle *);

    PseudoJet GetPseudoJet(CParticle *);
    
    virtual TString ClassName() {
        return ("HParticle");
    };

};

#endif
