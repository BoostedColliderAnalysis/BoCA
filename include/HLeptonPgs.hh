# ifndef HLeptonPgs_hh
# define HLeptonPgs_hh

# include "HLepton.hh"

/**
 * @brief PGS leptons
 *
 */
class hanalysis::hpgs::HLepton : public hanalysis::HLepton
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
  bool GetElectrons();

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  bool GetMuons();

    inline string NameSpaceName() const {
        return "HPgs";
    }

    inline string ClassName() const {
        return "HLepton";
    };

};

#endif
