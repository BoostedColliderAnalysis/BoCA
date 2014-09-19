# ifndef HLeptonDelphes_hh
# define HLeptonDelphes_hh

# include "classes/DelphesClasses.h"
# include "HLeptonBase.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonDelphes : public HLeptonBase
{

public:


    /**
     * @brief constructor
     *
     */
    HLeptonDelphes();
    
    
    /**
     * @brief destructor
     *
     */
    ~HLeptonDelphes();

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
