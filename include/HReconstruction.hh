# ifndef HReconstruction_hh
# define HReconstruction_hh

// # include "fastjet/tools/Filter.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "fastjet/tools/CASubJetTagger.hh"
# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

# include "Object.hh"
# include "JetInfo.hh"

/**
 * @brief FastJet calculations
 *
 */
class analysis::HReconstruction : public analysis::Object
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
  Jets GetFatJets(const Jets&) const;

  /**
   * @brief Get vecto of all fatjets
   *
   */
  Jets GetFatJets(const Jets&,const fastjet::JetDefinition&) const;

  Jets GetMassDropJets(const Jets&) const;

    /**
     * @brief Get mass drop jet
     * 
     */
    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet&) const;

    fastjet::PseudoJet GetMassDropJet(const fastjet::PseudoJet&, const float, const float) const;


    Jets GetSubJetTaggedJets(const Jets &FatJets) const;

    fastjet::PseudoJet GetSubJetTaggedJet(const fastjet::PseudoJet &FatJet) const;

    /**
     * @brief Filter Jets
     * 
     */
    fastjet::PseudoJet GetFilteredJet(const fastjet::PseudoJet&);

    static bool JetIsBad(const fastjet::PseudoJet & Jet);

    Jets GetFatJetTag(Jets&);

//     Jets FatJetVector;

    inline std::string NameSpaceName() const {
      return "HDelphes";
    };

    inline std::string ClassName() const {
        return "HReconstruction";
    };

};

# endif
