# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"
# include "HJetTag.hh"
# include "HJetInfo.hh"

// using std::vector;

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
    virtual void NewEvent(const hanalysis::HClonesArray *const NewClonesArrays);

    void SetJetTag(HJetTag *const NewJetTag) {
        JetTag = NewJetTag;
    }

    vector<PseudoJet> GetJets() {
      if (!GotJets) GotJets = GetJets(Plain);
      return Jets;
    };

    vector<PseudoJet> GetStructuredJets() {
        if (!GotJets) GotJets = GetJets(Structure);
        return Jets;
    };

    vector<PseudoJet> GetTaggedJets() {
        if (!GotJets) GotJets = GetJets(Tagging);
        return Jets;
    };

    vector<PseudoJet> GetTaggedJets(HJetTag *const NewJetTag) {
        JetTag = NewJetTag;
        if (!GotJets) GotJets = GetJets(Tagging);
        return Jets;
    };

    vector<PseudoJet> GetBottomJets() {
        if (!GotJets) GotJets = GetJets(Plain);
        return BottomJets;
    };

    vector<PseudoJet> GetEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Plain);
      return EFlowJets;
    };

    vector<PseudoJet> GetIsolatedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Isolation);
      return EFlowJets;
    };

    vector<PseudoJet> GetTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    vector<PseudoJet> GetTaggedEFlowJets(HJetTag *const NewJetTag) {
      JetTag = NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    vector<PseudoJet> GetIsolatedTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    vector<PseudoJet> GetIsolatedTaggedEFlowJets(HJetTag *const NewJetTag) {
      JetTag = NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    virtual float GetScalarHt();

protected:

    enum HJetDetails {Plain, Tagging, Isolation, Structure, TaggingIsolation};

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
     * @brief vector of Jet Lorentz Vectors
     *
     */
    vector<TLorentzVector> JetLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    vector<TLorentzVector> AntiTauLorentzVectors;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    vector<PseudoJet> EFlowJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> Jets;

    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    vector<PseudoJet> BottomJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    vector<PseudoJet> CharmJets;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    vector<PseudoJet> GenJets;

    /**
     * @brief vector of Bottom Lorentz Vectors with their pull
     *
     */
    vector<TLorentzVector> BottomLorentzVectors;

    HJetTag *JetTag;

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

    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;

    virtual inline string ClassName() const {
        return "HJet";
    };

private:

};

#endif

