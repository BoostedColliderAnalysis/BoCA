# ifndef HEventPgs_hh
# define HEventPgs_hh

# include "HEvent.hh"
# include "HLeptonPgs.hh"
# include "HJetPgs.hh"

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
    
    void NewEvent(const HClonesArray * const);
    
    vector<TLorentzVector> GetLeptons();
    
    void GetJets();

private:
    
    bool HasLeptons;
    
    bool HasJets;
    
    string ClassName() const {
        
        return ("HEventPgs");
        
    };
    
};

#endif

