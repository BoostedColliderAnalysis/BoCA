# ifndef HPull_hh
# define HPull_hh

# include "fastjet/tools/Filter.hh"

# include "HFourVector.hh"

using std::min;
using std::vector;

using TMath::Pi;

using fastjet::SelectorNHardest;
using fastjet::antikt_algorithm;
using fastjet::JetDefinition;
using fastjet::Selector;
using fastjet::Filter;

/**
 * @brief Calculates the pull to each Bottom
 *
 */
class HPull : public HFourVector
{

public:

    /**
     * @brief LorentzVector of the Bottom
     *
     */
    TLorentzVector BottomLorentzVector;

    /**
     * @brief Pseudo Jet of Bottoms
     *
     */
    PseudoJet BottomJet;

    /**
     * @brief angle of the Pull Variable
     *
     */
    float PullAngle(float, float);

    /**
     * @brief Pull calculation as definied in arXiv:1001.5027
     *
     * @param Jet
     */
    void BTagCalculation(const Jet&);

    /**
     * @brief Pull calculation as definied in arXiv:1001.5027
     *
     * @param Jet
     */
    float SubPull(const PseudoJet&, const PseudoJet&, const PseudoJet&);

    /**
     * @brief DiPolarity as defined in arXiv:1102.1012
     *
     * @param  PseudoJet Jet containig two subjets
     * @return void
     */
    float CalculateDiPolarity(const PseudoJet&, const PseudoJet&, const PseudoJet&);

    float JingDipolarity(const PseudoJet &CandidateJet);

//     float DiPolarity;

    /**
     * @brief constructor
     *
     */
    HPull();

    /**
     * @brief destructor
     *
     */
    ~HPull();

private:

    int InitialValue;

    /**
     * @brief Phi component of the pull variable
     *
     */
    float PullPhi;

    /**
     * @brief Y component of the pull variable
     *
     */
    float PullRap;

    float ConfineAngle(float);
};

#endif
