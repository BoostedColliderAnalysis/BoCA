# ifndef HParticle_hh
# define HParticle_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

/**
 * @brief particles for HAnalysis
 *
 */
class hanalysis::HParticle : public HFourVector
{

public:

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

    void NewEvent(const HClonesArray *const);

    HVectors GetLeptonLorentzVectors();

    HVectors GetAntiLeptonLorentzVectors();

    HJets GetLeptonJets();

    HJets GetAntiLeptonJets();

    HJets GetBottomJets()  {
        if(!GotParticles) GotParticles = GetParticles();
        return BottomJetVector;
    }

    HJets GetCharmJets() {
      if(!GotParticles) GotParticles = GetParticles();
        return CharmJetVector;
    }

    HJets GetTopJets() {
      if(!GotParticles) GotParticles = GetParticles();
        return TopJetVector;
    }

protected:

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    virtual bool GetParticles() = 0;

    bool GotParticles;

    HVectors TopVector;

    HVectors AntiTopVector;

    HVectors ElectronLorentzVectors;

    HVectors MuonLorentzVectors;

    HVectors AntiElectronLorentzVectors;

    HVectors AntiMuonLorentzVectors;

    HJets ElectronJets;

    HJets MuonJets;

    HJets AntiElectronJets;

    HJets AntiMuonJets;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    HJets BottomJetVector;

    HJets TopJetVector;


    /**
     * @brief Vector of generator level Higgs Pseudo Jets
     *
     */
    HJets HiggsJetVector;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    HJets CharmJetVector;


    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;

    HJets ParticleJetVector;

    virtual inline std::string ClassName() const {
        return ("HParticle");
    };

private:

};

#endif
