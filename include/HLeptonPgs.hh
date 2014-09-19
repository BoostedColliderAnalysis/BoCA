# ifndef HLeptonPgs_hh
# define HLeptonPgs_hh

# include "HLeptonBase.hh"
# include "ExRootAnalysis/ExRootClasses.h"

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonPgs : public HLeptonBase
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
    
    virtual TString ClassName() {
        return ("HLepton");
    };

};

#endif
