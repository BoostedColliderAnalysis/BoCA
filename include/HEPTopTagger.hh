#ifndef HEPTopTagger_hh
#define HEPTopTagger_hh

#include "fastjet/ClusterSequence.hh"
#include "fastjet/tools/Filter.hh"


using std::max;
using std::swap;
using fastjet::cambridge_algorithm;
using std::cout;
using std::endl;
using std::min;
using std::vector;
using fastjet::sorted_by_pt;
using fastjet::ClusterSequence;
using fastjet::JetAlgorithm;
using fastjet::JetDefinition;
using fastjet::Selector;
using fastjet::Filter;
using fastjet::PseudoJet;

/**
 * @brief HEP Top Tagger
 *
 */
class HEPTopTagger
{
public:

    /**
     * @brief Constructor
     *
     * @param[in] cs Cluster Sequence
     * @param[in] jet Jet wich might be a top
     */
    HEPTopTagger(const ClusterSequence &cs
                 , const PseudoJet &jet);

    /**
     * @brief Constructor
     *
     * @param[in] cs Ckuster Sequence
     * @param[in] jet Jet wich might be a top
     * @param[in] topmass overwrites the internal top mass of 172.3
     * @param[in] wmass overwrites the internal W mass of 80.4
     */
    HEPTopTagger(const ClusterSequence &cs
                 , const PseudoJet &jet
                 , float topmass
                 , float wmass);

    /**
     * @brief Constructor
     *
     * @param[in] cs Ckuster Sequence
     * @param[in] jet Jet wich might be a top
     * @param[in] topmass overwrites the internal top mass of 172.3
     * @param[in] wmass overwrites the internal W mass of 80.4
     * @param[in] Debug debugging parameter
     */
    HEPTopTagger(const ClusterSequence &cs
                 , const PseudoJet &jet
                 , float topmass
                 , float wmass
                 , bool Debug);

    /**
     * @brief Main function wich runs the Top Tagger
     *
     * @return void
     */
    void run_tagger();

    /**
     * @brief returns if top tagging was successfull
     *
     * @return bool
     */
    bool is_maybe_top() const {
        return MightBeTop;
    }

    /**
     * @brief returns if masscuts have been passed
     *
     * @return bool
     */
    bool is_masscut_passed() const {
        return MasscutPassed;
    }

    /**
     * @brief returns top Candidate
     *
     * @return const fastjet::PseudoJet&
     */
    const PseudoJet &top_candidate() const {
        return TopJetCandidate;
    }

    /**
     * @brief returns top subjet vector
     *
     * @return const std::vector< fastjet::PseudoJet, std::allocator >&
     */
    const vector<PseudoJet> &top_subjets() const {
        return TopSubJetVector;
    }

    /**
     * @brief returns hard top Constituents
     *
     * @return const std::vector< fastjet::PseudoJet, std::allocator >&
     */
    const vector<PseudoJet> &top_hadrons() const {
        return TopHadronVector;
    }

    /**
     * @brief returns number of top candidates
     *
     * @return int int
     */
    int top_count() const {
        return TopCount;
    }

    /**
     * @brief returns the hard Substructure of the Jet
     *
     * @return const std::vector< fastjet::PseudoJet, std::allocator >&
     */
    const vector<PseudoJet> &hardparts() const {
        return TopHardSubstructureVector;
    }

    /**
     * @brief Returns the Sum of the Substructures
     *
     * @return int int
     */
    int parts_size() const {
        return TopSubStructureSum;
    }

    /**
     * @brief returns the Delta between the physical top mass and the reconstructed one
     *
     * @return float
     */
    float delta_top() const {
        return TopMassDelta;
    }

    /**
     * @brief returns the vector of all top candidates
     *
     * @return const std::vector< std::vector< fastjet::PseudoJet, std::allocator >, std::allocator >&
     */
    const vector<vector<PseudoJet> > &candjets() const {
        return CandidateVectorVector;
    }

    /**
     * @brief prints all parameter values
     *
     * @return void
     */
    void get_setting() const;

    /**
     * @brief prints all results
     *
     * @return void
     */
    void get_info() const;

    /**
     * @brief Sets the maximal subjetmass
     *
     * @return void
     */
    void set_max_subjet_mass(float x) {
        SubJetMassMax = x;
    }

    /**
     * @brief Sets the Mass Drop Threshold
     *
     * @return void
     */
    void set_mass_drop_threshold(float x) {
        MassDropThreshold = x;
    }

    /**
     * @brief Sets the Top mass Range
     *
     * @return void
     */
    void set_top_range(float xmin, float xmax) {
        TopMassMin = xmin;
        TopMassMax = xmax;
    }

    /**
     * @brief Set the Range of the ratio between W mass and Top mass
     *
     * @return void
     */
    void set_mass_ratio_range(float rmin, float rmax) {
        MassRatioMin = rmin;
        MassRatioMax = rmax;
    }
    /**
     * @brief Sets the Maximal Values for the SubJetMass Ratios
     *
     * @return void
     */
    void set_mass_ratio_cut(float m23cut, float m13cutmin, float m13cutmax) {
        M23Cut = m23cut;
        M13CutMin = m13cutmin;
        M13CutMax = m13cutmax;
    }

    /**
     * @brief Sets the Maximum Number of Constituents for the Filtering Process
     *
     * @return void
     */
    void set_nfilt(int nfilt) {
        NFilterMax = nfilt;
    }

    /**
     * @brief Sets the Jet Algorithm
     *
     * @return void
     */
    void set_filtering_jetalgorithm(JetAlgorithm jet_algorithm) {
        FilterJetAlgorithm = jet_algorithm;
    }

    /**
     * @brief Sets the Reclustering Algorithm
     *
     * @return void
     */
    void set_reclustering_jetalgorithm(JetAlgorithm jet_algorithm) {
        ReclusterJetAlgorithm = jet_algorithm;
    }

    /**
     * @brief takes top jet and the two softer subjets and returns the cosin between top jet and the softest subjet
     *
     * @return float cos top and softest subjet
     */
    float cos_theta_h() const;

    /**
     * @brief Returns the Maximal Cylinder Distance between the Top SubJets
     *
     * @return float
     */
    float dr_bjj() const;

    /**
     * @brief Returns Vector of the Cylinder Distances between the Top Sub Jets
     *
     * @return std::vector< float, std::allocator >
     */
    vector<float> dr_values() const;

    /// Debug boolean
    bool debugg;

private:
    /// Top Candidate Cluster Sequence
    const ClusterSequence *TopClusterSequence;
    /// Top Candidate Jet
    const PseudoJet TopCandidateJet;
    /// Top Mass
    const float TopMass;
    /// W Mass
    const float WMass;
    /// Threshold for Mass Dropping
    float MassDropThreshold;
    /// stop when subjet mass < 30 GeV
    float SubJetMassMax;
    /// TopMass Cuts
    float TopMassMin;
    /// TopMass Cuts
    float TopMassMax;
    /// Cuts on the Mass Ratio
    float MassRatioMin;
    /// Cuts on the Mass Ratio
    float MassRatioMax;
    /// Cuts in the Mass Planes
    float M23Cut;
    /// Cuts in the Mass Planes
    float M13CutMin;
    /// Cuts in the Mass Planes
    float M13CutMax;
    /// Maximal Filter SubStructures
    int NFilterMax;
    // filtering algorithm
    JetAlgorithm FilterJetAlgorithm;
    /// Jet Reclustering Algorithm
    JetAlgorithm ReclusterJetAlgorithm;
    /// Indicates if masscut Has been passed
    bool MasscutPassed;
    /// Indicates if the Jet might be a top
    bool MightBeTop;
    /// Delta between physical top mass and reconstructed top mass
    float TopMassDelta;
    /// Counter for Number of Tops
    int TopCount;
    /// Sum of Top Substructures
    int TopSubStructureSum;
    /// Top Candidate Jet
    PseudoJet TopJetCandidate;
    /// Vector Containing the Top Sub Jets (b W W)
    vector<PseudoJet> TopSubJetVector;
    /// hard top Constituents
    vector<PseudoJet> TopHadronVector;
    /// Vector Containign the Hard Substructure of the Top Candidate
    vector<PseudoJet> TopHardSubstructureVector;
    /// Vector of Candiate Vectors
    vector<vector<PseudoJet> > CandidateVectorVector;

    /**
     * @brief Find Hard Substructure
     *
     * @param[in] JetWithSubStructure Jet wich might contain Substructure
     * @param[out] JetSubStructureVector Vector of SubJets
     * @return void
     *
     * Takes Jet and returns Vector containing the Substructure.
     *
     */
    void FindHardSubstructure(const PseudoJet &JetWithSubStructure, vector<PseudoJet> &JetSubStructureVector);

    /**
     * @brief takes vector of Top Constituents and returns vector of constituents with pt > ptmin
     *
     * @param[in] TopConstituentsVector ...
     * @param[in] FilterJetDefinition ...
     * @return std::vector< fastjet::PseudoJet, std::allocator >
     */
    vector<PseudoJet> Filtering(const vector<PseudoJet> &TopConstituentsVector, const JetDefinition &FilterJetDefinition);


    /**
     * @brief Stores the Top SubJets in TopSubJetVector in the order b W W
     *
     * @param[out] SubTopVector (b,  W,  W)
     * @return void
     */
    void StoreTopSubJets(const vector<PseudoJet> &SubTopVector);

    /**
     * @brief Checks mass relations of TopCandidate Subjets
     *
     * @param[in] TopCandidateSubJetVector Top Sub Jets
     * @return bool Mass Check
     */
    bool CheckMassCriteria(const vector<PseudoJet> &TopCandidateSubJetVector) const;

    /**
     * @brief Taks a top Jet and two subjets and returns the cos of theta between the top jet and the softer subjet
     *
     * @param[in] Jet TopJet
     * @param[in] SubJet1 ...
     * @param[in] SubJet2 ...
     * @return float CosTheta between Top Jet and SoftWJet
     */
    float CheckCosTheta(const PseudoJet &Jet, const PseudoJet &SubJet1, const PseudoJet &SubJet2) const;

    /**
     * @brief Sum all Jets of given Vctor of Jets
     *
     * @param[in] JetVector Vector of Jets
     * @return fastjet::PseudoJet Sum all Jets
     */
    PseudoJet SumJetsOfJetVector(const vector<PseudoJet> &);

    /**
     * @brief Returns the largest Cylinder Distance R between the three Jets
     *
     * @param[in] Jet1 ...
     * @param[in] Jet2 ...
     * @param[in] Jet3 ...
     * @return float Maximal Cylinder Distance
     */
    float MaximalCylinderDistance(const PseudoJet &Jet1
                                  , const PseudoJet &Jet2
                                  , const PseudoJet &Jet3)
    const;
};

#endif
