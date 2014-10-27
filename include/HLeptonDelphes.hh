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

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    void GetElectrons();

    /**
     * @brief Find the hardest of the light leptons
     *
     * @param ClonesArray ...
     * @return void
     */
    void GetMuons();

private:

    inline string ClassName() const {

        return "HDelphes: HLepton";

    };

};

#endif
