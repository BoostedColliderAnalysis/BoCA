# ifndef HEventPgs_hh
# define HEventPgs_hh

# include "HEvent.hh"
# include "HLeptonPgs.hh"
# include "HJetPgs.hh"

/**
 * @brief event topology for PGS events
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

    inline string ClassName() const {

        return ("HEventPgs");

    };

};

#endif

