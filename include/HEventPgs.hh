# ifndef HEventPgs_hh
# define HEventPgs_hh

# include "HEvent.hh"
# include "HLeptonPgs.hh"
# include "HJetPgs.hh"

/**
 * @brief event topology for PGS events
 *
 */
class hanalysis::hpgs::HEvent : public hanalysis::HEvent
{

public:

    /**
    * @brief constructor
    *
    */
    HEvent();

    /**
     * @brief destructor
     *
     */
    ~HEvent();

    void NewEvent(const hanalysis::hpgs::HClonesArray *const ClonesArrays);

    vector<TLorentzVector> GetLeptons();

    void GetJets();

private:

    bool HasLeptons;

    bool HasJets;

    inline string ClassName() const {

        return ("Pgs: HEvent");

    };

};

#endif

