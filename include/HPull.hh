# ifndef HPull_hh
# define HPull_hh

# include <iostream>

# include "TLorentzVector.h"

# include "fastjet/tools/Filter.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "fastjet/PseudoJet.hh"

# ifndef MadGraph
# include "classes/DelphesClasses.h"
# endif

using std::cout;
using std::endl;
using std::min;
using std::vector;

using fastjet::PseudoJet;
using fastjet::SelectorNHardest;
using fastjet::antikt_algorithm;
using fastjet::JetDefinition;
using fastjet::Selector;
using fastjet::Filter;

using TMath::Pi;

/**
 * @brief Calculates the pull to each Bottom
 *
 */
class HPull
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
    void BTagCalculation(Jet *);

    /**
     * @brief Pull calculation as definied in arXiv:1001.5027
     *
     * @param Jet
     */
    float SubPull(PseudoJet, PseudoJet, PseudoJet);

    /**
     * @brief DiPolarity as defined in arXiv:1102.1012
     *
     * @param  PseudoJet Jet containig two subjets
     * @return void
     */
    float CalculateDiPolarity(PseudoJet, PseudoJet, PseudoJet);

    float JingDipolarity(PseudoJet, PseudoJet);

    float DiPolarity;

    /**
     * @brief constructor
     *
     */
    HPull(int);

    /**
     * @brief destructor
     *
     */
    ~HPull();

private:

    int InitialValue;

    /**
     * @brief debug variable
     *
     */
    int Debug;

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
