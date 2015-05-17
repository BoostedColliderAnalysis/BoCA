# ifndef HLeptonDelphes_hh
# define HLeptonDelphes_hh

# include "HLepton.hh"
# include "JetInfo.hh"

/**
 * @brief Delphes leptons
 *
 */
class analysis::hdelphes::HLepton : public analysis::HLepton
{

public:


    /**
     * @brief constructor
     *
     */
    HLepton();

private:

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  bool GetElectrons();

  bool GetElectrons(HJetDetails JetDetails);

  /**
   * @brief Find the hardest of the light leptons
   *
   * @param ClonesArray ...
   * @return void
   */
  bool GetMuons();

  bool GetMuons(HJetDetails JetDetails);

//   Jets GetLeptons(HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HLepton";
    };

};

#endif
