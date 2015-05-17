# pragma once
# include "HFourVector.hh"

/**
 * @brief particles for HAnalysis
 *
 */
class analysis::HParticle : public HFourVector
{

public:

    /**
     * @brief constructor
     *
     */
    HParticle();

    void Newevent(const analysis::ClonesArrays &NewClonesArrays);

    HVectors GetLeptonLorentzVectors();

    HVectors GetAntiLeptonVectors();

    Jets GetLeptonJets();

    Jets GetNeutrinos() {
        if (!GotParticles) GotParticles = GetParticles();
        return NeutrinoJets;
    }

    Jets GetAntiLeptonJets();

    Jets GetBottomJets()  {
        if (!GotParticles) GotParticles = GetParticles();
        return BottomJets;
    }

    Jets GetCharmJets() {
        if (!GotParticles) GotParticles = GetParticles();
        return CharmJets;
    }

    Jets GetTopJets() {
        if (!GotParticles) GotParticles = GetParticles();
        return TopJets;
    }

    Jets Generator() {
//       Print(kError,"we are here");
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
      Print(kError,"should be subclassed");
      return 0;
    }

    bool GotParticles;

    HVectors TopVectors;

    HVectors AntiTopVector;

    HVectors ElectronVectors;

    HVectors MuonVectors;

    HVectors AntiElectronVectors;

    HVectors AntiMuonVectors;

    Jets ElectronJets;

    Jets MuonJets;

    Jets AntiElectronJets;

    Jets AntiMuonJets;

    Jets NeutrinoJets;

    Jets GeneratorJets;


    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    Jets BottomJets;

    Jets TopJets;


    /**
     * @brief Vector of generator level Higgs Pseudo Jets
     *
     */
    Jets HiggsJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    Jets CharmJets;

    Jets ParticleJets;

    virtual inline std::string ClassName() const {
        return ("HParticle");
    };

private:

};
