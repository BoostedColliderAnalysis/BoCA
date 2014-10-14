# ifndef HReconstruction_hh
# define HReconstruction_hh

// # include "fastjet/tools/Filter.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "fastjet/ClusterSequenceArea.hh"

# include "HObject.hh"
# include "HJetInfo.hh"

using std::vector;

/**
 * @brief Higgs Top Discriminator
 *
 *
 */
class HReconstruction : public HObject
{

public:

    /**
     * @brief constructor
     *
     */
    HReconstruction();

    /**
     * @brief destructor
     *
     */
    ~HReconstruction();

    virtual void NewEvent();

    /**
     * @brief Get Fat Higgs Jets
     *
     * @param  EFlow Jet Vector
     * @return Candidates
     */

//     virtual vector<PseudoJet> GetCandidateJets(vector<PseudoJet>) = 0;

protected:

  /**
   * @brief Get vecto of all fatjets
   *
   */
  vector<PseudoJet> GetFatJetVector(const vector<PseudoJet>&) const;

  /**
   * @brief Get vecto of all fatjets
   *
   */
  vector<PseudoJet> GetFatJetVector(const vector<PseudoJet>&,const fastjet::JetDefinition&) const;

  vector<PseudoJet> GetMassDropVector(const vector<PseudoJet>&) const;

    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
    PseudoJet GetMassDropJet(const PseudoJet&) const;

    PseudoJet GetMassDropJet(const PseudoJet&, const float, const float) const;

    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(const PseudoJet&);

    static bool JetIsBad(const PseudoJet &);

    vector<PseudoJet> GetFatJetTag(vector<PseudoJet>&);

//     vector<PseudoJet> FatJetVector;

    string ClassName() const {

        return ("HReconstruction");

    };

};

# endif