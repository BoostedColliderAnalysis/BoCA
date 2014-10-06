# ifndef HLeptonDelphes_hh
# define HLeptonDelphes_hh

# include "HLepton.hh"
# include "classes/DelphesClasses.h"

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonDelphes : public HLepton
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
    
    string ClassName() const {
        
        return ("HLeptonDelphes");
        
    };

};

#endif
