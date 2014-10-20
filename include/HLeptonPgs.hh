# ifndef HLeptonPgs_hh
# define HLeptonPgs_hh

# include "HLepton.hh"

/**
 * @brief PGS leptons
 *
 */
class HLeptonPgs : public HLepton
{

public:

    /**
     * @brief constructor
     *
     */
    HLeptonPgs();


    /**
     * @brief destructor
     *
     */
    ~HLeptonPgs();

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

    string ClassName() const {

        return ("HLeptonPgs");

    };

};

#endif
