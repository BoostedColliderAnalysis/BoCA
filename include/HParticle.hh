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

    HVectors GetAntiLeptonVectors();

    HJets GetLeptonJets();

    HJets GetNeutrinos() {
        if (!GotParticles) GotParticles = GetParticles();
        return NeutrinoJets;
    }

    HJets GetAntiLeptonJets();

    HJets GetBottomJets()  {
        if (!GotParticles) GotParticles = GetParticles();
        return BottomJets;
    }

    HJets GetCharmJets() {
        if (!GotParticles) GotParticles = GetParticles();
        return CharmJets;
    }

    HJets GetTopJets() {
        if (!GotParticles) GotParticles = GetParticles();
        return TopJets;
    }

    HJets Generator() {
//       Print(HError,"we are here");
      if (!GotParticles) GotParticles = GetParticles();
        return GeneratorJets;
    }

protected:

    /**
     * @brief extract electrons and muon particle
     *
     * @return void
     */
    virtual bool GetParticles() {
      Print(HError,"should be subclassed");
      return 0;
    }

    bool GotParticles;

    HVectors TopVectors;

    HVectors AntiTopVector;

    HVectors ElectronVectors;

    HVectors MuonVectors;

    HVectors AntiElectronVectors;

    HVectors AntiMuonVectors;

    HJets ElectronJets;

    HJets MuonJets;

    HJets AntiElectronJets;

    HJets AntiMuonJets;

    HJets NeutrinoJets;

    HJets GeneratorJets;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    HJets BottomJets;

    HJets TopJets;


    /**
     * @brief Vector of generator level Higgs Pseudo Jets
     *
     */
    HJets HiggsJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    HJets CharmJets;


    /**
     * @brief Clones Arrays
     *
     */
//     const HClonesArray *ClonesArrays;

    HJets ParticleJets;

    virtual inline std::string ClassName() const {
        return ("HParticle");
    };

private:

};

#endif
