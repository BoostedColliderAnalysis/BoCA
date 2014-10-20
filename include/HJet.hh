# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"
# include "HJetTag.hh"
# include "HJetInfo.hh"

using std::vector;

/**
 * @brief Base class for jets
 *
 */
class HJet : public HFourVector
{

public:


    enum HJetDetails {Plain, Tagging, Isolation, Structure, TaggingIsolation};

//     HJetDetails JetDetails;

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

    vector<PseudoJet> GetEFlowJets() const {
        return EFlowJets;
    };

    /**
     * @brief Initialize new event
     *
     * @return void
     */
    virtual void NewEvent(const HClonesArray *const);

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetJets(const HJetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool ReadEFlow(const HJetDetails);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    virtual void GetGenJet();

    virtual float GetScalarHt();

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

    const HJetTag   *JetTag;

protected:

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

protected:

    virtual string ClassName() const {

        return ("HJet");

    };



private:

};

#endif

