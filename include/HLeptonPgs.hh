# ifndef HLeptonPgs_hh
# define HLeptonPgs_hh

# include "HLepton.hh"

/**
 * @brief PGS leptons
 *
 */
class hpgs::HLepton : public hanalysis::HLepton
{

public:

    /**
     * @brief constructor
     *
     */
    HLepton();


    /**
     * @brief destructor
     *
     */
    ~HLepton();

private:

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  bool GetElectrons(HJetDetails JetDetails);

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  bool GetMuons(HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HPgs";
    }

    inline std::string ClassName() const {
        return "HLepton";
    };

};

#endif
