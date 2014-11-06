# ifndef HLeptonDelphes_hh
# define HLeptonDelphes_hh

# include "HLepton.hh"

/**
 * @brief Delphes leptons
 *
 */
class hanalysis::hdelphes::HLepton : public hanalysis::HLepton
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
        return "HDelphes";
    }

    inline string ClassName() const {
        return "HLepton";
    };

};

#endif
