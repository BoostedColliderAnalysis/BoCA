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
class hdelphes::HReconstruction : public hanalysis::HObject
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
  HJets GetFatJets(const HJets&) const;

  /**
   * @brief Get vecto of all fatjets
   *
   */
  HJets GetFatJets(const HJets&,const fastjet::JetDefinition&) const;

  HJets GetMassDropJets(const HJets&) const;

    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
    PseudoJet GetMassDropJet(const PseudoJet&) const;

    PseudoJet GetMassDropJet(const PseudoJet&, const float, const float) const;


    HJets GetSubJetTaggedJets(const HJets &FatJets) const;

    PseudoJet GetSubJetTaggedJet(const PseudoJet &FatJet) const;

    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(const PseudoJet&);

    static bool JetIsBad(const PseudoJet & Jet);

    HJets GetFatJetTag(HJets&);

//     HJets FatJetVector;

    inline std::string NameSpaceName() const {
      return "HDelphes";
    };

    inline std::string ClassName() const {
        return "HReconstruction";
    };

};

# endif
