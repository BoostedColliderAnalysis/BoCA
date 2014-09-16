# ifndef __HLEPTON_HH__
# define __HLEPTON_HH__

# include <algorithm>

# include "TObjArray.h"

# ifdef PGS
# include "ExRootAnalysis/ExRootClasses.h"
# else
# include "classes/DelphesClasses.h"
# endif

# include "HClonesArray.hh"
# include "HObject.hh"

using std::sort;
using std::vector;

typedef
# ifdef PGS
TRootElectron
# else
Electron
# endif
CElectron;

typedef
# ifdef PGS
TRootMuon
# else
Muon
# endif
CMuon;

/**
 * @brief calculation regarding leptons
 *
 */
class HLepton : public HObject
{

public:

    HClonesArrayBase *ClonesArray;

    /**
     * @brief Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> ElectronLorentzVectorVector;

    /**
     * @brief Anti Electron Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiElectronLorentzVectorVector;

    /**
     * @brief Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> MuonLorentzVectorVector;

    /**
     * @brief Anti Muon Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiMuonLorentzVectorVector;

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
     * @brief Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> LeptonLorentzVectorVector;

    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<TLorentzVector> AntiLeptonLorentzVectorVector;
    
    /**
     * @brief Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> LeptonJetVector;
    
    /**
     * @brief Anti Lepton Lorentz Vector
     *
     */
    vector<PseudoJet> AntiLeptonJetVector;


    void GetLeptonLorentzVectorVector();

    void GetAntiLeptonLorentzVectorVector();

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    void GetElectrons(HClonesArrayBase *);

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    void GetMuons(HClonesArrayBase *);

    /**
     * @brief Finds (Anti-)Tau with the largest Pt
     *
     * @param JetClone
     * @return void
     */
    void TauTagCalculations(Jet *);

    /**
     * @brief lepton and  Missing-Energy
     *
     * @param ClonesArrayClass ...
     * @return void
     */
    void LeptonsAndMissingEt();


    /**
     * @brief constructor
     *
     */
    HLepton();
    
    
    /**
     * @brief destructor
     *
     */
    ~HLepton();
    
    void NewEvent();

private:

    /**
     * @brief Physical Electron Mass
     *
     */
    float ElectronMass;

    /**
     * @brief Physical Muon Mass
     *
     */
    float MuonMass;
    
    virtual TString ClassName() {
        return ("HLepton");
    };

};

#endif
