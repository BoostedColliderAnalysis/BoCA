# ifndef HJet_hh
# define HJet_hh

# include "TObjArray.h"

# include "HClonesArray.hh"
# include "HFourVector.hh"

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
    virtual bool GetTaggedJets();

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
    virtual bool GetTaggedEFlow();

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

    template<typename Template1, typename Template2>
    bool CheckIsolation(const Template1 * const Particle1, const Template2 * const Particle2, const float DeltaRIsolationMax) const {

        bool Isolated = 1;

        if (GetPseudoJet(const_cast<Template1 *>(Particle1)->P4()).delta_R(GetPseudoJet(const_cast<Template2 *>(Particle2)->P4())) < DeltaRIsolationMax) Isolated = 0;

        return Isolated;

    }

    template<typename Template1, typename Template2>
    bool CheckIsolation(const Template1 * const Particle1, const Template2 * const Particle2) const {

        const float DeltaRIsolationMax = 0.01; // TODO decide on best value

        return CheckIsolation(Particle1, Particle2, DeltaRIsolationMax);

    }

    /**
     * @brief Clones Arrays
     *
     */
    const HClonesArray *ClonesArrays;

private:

    virtual string ClassName() const {

        return ("HJet");

    };

};

#endif

