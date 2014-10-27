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

        return "HPgs: HLepton";

    };

};

#endif
