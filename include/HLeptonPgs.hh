# ifndef HLeptonPgs_hh
# define HLeptonPgs_hh

# include "HLepton.hh"
# include "HFourVector.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class HLeptonPgs : public HLepton, public HFourVectorExRoot
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
        
        return ("HLeptonPgs");
        
    };

};

#endif
