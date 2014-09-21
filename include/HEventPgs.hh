# ifndef HEventPgs_hh
# define HEventPgs_hh

# include "HEvent.hh"
# include "HLeptonPgs.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HEventPgs : public HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEventPgs();

    /**
     * @brief destructor
     *
     */
    ~HEventPgs();
    
    void NewEvent();
    
    vector<TLorentzVector> GetLeptons();

private:
    
    bool Leptons;
    
    virtual TString ClassName() {
        return ("HEventPgs");
    };
};

#endif

