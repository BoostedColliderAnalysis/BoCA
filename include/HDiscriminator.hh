# ifndef HDiscriminator_hh
# define HDiscriminator_hh

# include <algorithm>

# include "fastjet/tools/Filter.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "fastjet/ClusterSequenceArea.hh"

# include "HPull.hh"
# include "HObject.hh"

using fastjet::sorted_by_E;
using fastjet::cambridge_algorithm;
using fastjet::JetDefinition;
using fastjet::ClusterSequence;
using fastjet::JetAlgorithm;
using fastjet::MassDropTagger;
using fastjet::AreaDefinition;
using fastjet::ClusterSequenceArea;
using fastjet::Selector;
using fastjet::Filter;

using std::vector;
using std::sort;
using std::max;

/**
 * @brief Higgs Top Discriminator
 *
 *
 */
class HDiscriminator : public HObject
{

public:

    /**
     * @brief constructor
     *
     */
    HDiscriminator();

    /**
     * @brief destructor
     *
     */
    ~HDiscriminator();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewFile();
    /**
     * @brief Clean after end of Analysis
     *
     * @return void
     */

    void CloseFile();

    /**
     * @brief New Event
     *
     * @return void
     */
    void NewEvent();

    /**
     * @brief Get Fat Higgs Jets
     *
     * @param  EFlow Jet Vector
     * @param  Higgs Particle Vector
     * @param  Top Particle Vector
     * @return Higgs Candidates
     */
    vector<PseudoJet> GetTaggedCandidateJets(vector<PseudoJet>, vector<PseudoJet>, vector<PseudoJet>);

private:

    /**
     * @brief Get vecto of all fatjets
     *
     */
    void GetFatJetVector(float);

    void TestFatJetVector(float);

    bool GetSuperFatJetVector(int);

    float GetHiggsTopDistance();

    float GetTopDistance();

    bool HiggsParticleChecker();

    bool TopParticleChecker();

    void HiggsTagger();

    void TopTagger();

    void TagFatJets();

    void GetMassDropVector();
    
    static bool JetIsBad(const PseudoJet &);
    static bool JetIsBad2(const PseudoJet &);

    vector<PseudoJet> EFlowJetVector;

    vector<PseudoJet> HiggsParticleVector;

    vector<PseudoJet> TopParticleVector;

    vector<PseudoJet> FatJetVector;

    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
    PseudoJet GetMassDropJet(PseudoJet);

    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(PseudoJet);

    void FatJetTagger();

    float MinDeltaR;

    int Overlap;

    int LostHiggs;

    int FatJetSum() {

        return FatJetVector.size();

    };

    int EFlowJetSum() {

        return EFlowJetVector.size();

    };

    int HiggsParticleSum() {

        return HiggsParticleVector.size();

    };

    int TopParticleSum() {

        return TopParticleVector.size();

    };

    bool HasHiggs;

    virtual TString ClassName() {
        return ("HDiscriminator");
    };

};

# endif
