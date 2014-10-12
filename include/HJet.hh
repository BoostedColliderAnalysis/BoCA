# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"
# include "HJetTag.hh"

using std::vector;

/**
 * @brief stores all the information about the event topology
 *
 */
class HJet : public HFourVector
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
     * @brief Initialize new event
     *
     * @return void
     */
    void NewEvent(const HClonesArray * const);

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetJets();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetTaggedJets(const HJetTag * const);

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetStructuredJets();

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetEFlow();

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetTaggedEFlow(const HJetTag * const);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    virtual void GetGenJet();

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

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 * const Particle1, const TParticle2 * const Particle2, const float DeltaRIsolationMax) const {

        bool Isolated = 1;

        if (GetPseudoJet(const_cast<TParticle1 *>(Particle1)->P4()).delta_R(GetPseudoJet(const_cast<TParticle2 *>(Particle2)->P4())) < DeltaRIsolationMax) Isolated = 0;

        return Isolated;

    }

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 * const Particle1, const TParticle2 * const Particle2) const {

        const float DeltaRIsolationMax = 0.01; // TODO decide on best value // This is quiet large

        return CheckIsolation(Particle1, Particle2, DeltaRIsolationMax);

    }

    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;
        
    const HJetTag  * JetTag;

private:

    virtual string ClassName() const {

        return ("HJet");

    };

};

#endif

