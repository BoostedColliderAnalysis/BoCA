# ifndef HReconstruction_hh
# define HReconstruction_hh

// # include "fastjet/tools/Filter.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "fastjet/tools/CASubJetTagger.hh"
# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

# include "HObject.hh"
# include "HJetInfo.hh"

/**
 * @brief FastJet calculations
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

protected:

  /**
   * @brief Get vecto of all fatjets
   *
   */
  vector<PseudoJet> GetFatJets(const vector<PseudoJet>&) const;

  /**
   * @brief Get vecto of all fatjets
   *
   */
  vector<PseudoJet> GetFatJets(const vector<PseudoJet>&,const fastjet::JetDefinition&) const;

  vector<PseudoJet> GetMassDropJets(const vector<PseudoJet>&) const;

    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
    PseudoJet GetMassDropJet(const PseudoJet&) const;

    PseudoJet GetMassDropJet(const PseudoJet&, const float, const float) const;
    
    
    vector<PseudoJet> GetSubJetTaggedJets(const vector<PseudoJet> &FatJets) const;
    
    PseudoJet GetSubJetTaggedJet(const PseudoJet &FatJet) const;

    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(const PseudoJet&);

    static bool JetIsBad(const PseudoJet & Jet);

    vector<PseudoJet> GetFatJetTag(vector<PseudoJet>&);

//     vector<PseudoJet> FatJetVector;

    inline string ClassName() const {

        return ("HReconstruction");

    };

};

# endif
