# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

/**
 * @brief Base class for jets
 *
 */
class hanalysis::HJet : public HFourVector
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
    void NewEvent(const hanalysis::HClonesArray *const NewClonesArrays);

    void SetJetTag(HJetTag *const NewJetTag) {
        JetTag = NewJetTag;
    }

    HJets GetJets() {
      if (!GotJets) GotJets = GetJets(Plain);
      return Jets;
    };

    HJets GetStructuredJets() {
        if (!GotJets) GotJets = GetJets(Structure);
        return Jets;
    };

    HJets GetTaggedJets() {
        if (!GotJets) GotJets = GetJets(Tagging);
        return Jets;
    };

    HJets GetTaggedJets(HJetTag *const NewJetTag) {
        JetTag = NewJetTag;
        if (!GotJets) GotJets = GetJets(Tagging);
        return Jets;
    };

    HJets GetStructuredTaggedJets(HJetTag *const NewJetTag) {
      JetTag = NewJetTag;
      if (!GotJets) GotJets = GetJets(TaggingStructure);
      return Jets;
    };

    HJets GetBottomJets() {
        if (!GotJets) GotJets = GetJets(Plain);
        return BottomJets;
    };

    HJets GetEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Plain);
      return EFlowJets;
    };

    HJets GetIsolatedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Isolation);
      return EFlowJets;
    };

    HJets GetTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    HJets GetTaggedEFlowJets(HJetTag *const NewJetTag) {
      JetTag = NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    HJets GetIsolatedTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    HJets GetIsolatedTaggedEFlowJets(HJetTag *const NewJetTag) {
      JetTag = NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    virtual float GetScalarHt();

protected:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetJets(const HJetDetails JetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetEFlow(const HJetDetails JetDetails);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    virtual void GetGenJet();

    bool GotEFlow;

    bool GotJets;

    /**
     * @brief std::vector of Jet Lorentz Vectors
     *
     */
    HVectors JetLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    HVectors TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    HVectors AntiTauLorentzVectors;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    HJets EFlowJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    HJets Jets;

    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    HJets BottomJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    HJets CharmJets;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    HJets GenJets;

    /**
     * @brief std::vector of Bottom Lorentz Vectors with their pull
     *
     */
    HVectors BottomLorentzVectors;

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 *const Particle1, const TParticle2 *const Particle2, const float DeltaRIsolationMax) const {

        bool Isolated = 1;

        if (GetPseudoJet(const_cast<TParticle1 *>(Particle1)->P4()).delta_R(GetPseudoJet(const_cast<TParticle2 *>(Particle2)->P4())) < DeltaRIsolationMax) Isolated = 0;

        return Isolated;

    }

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 *const Particle1, const TParticle2 *const Particle2) const {

        const float DeltaRIsolationMax = 0.01; // TODO decide on best value // This is quiet large

        return CheckIsolation(Particle1, Particle2, DeltaRIsolationMax);

    }

    virtual inline std::string ClassName() const {
        return "HJet";
    };

private:

};

#endif

