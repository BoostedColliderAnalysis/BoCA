# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "HJet.hh"
# include "classes/DelphesClasses.h"

/**
 * @brief stores all the information about the event topology
 *
 */
class HJetDelphes : public HJet
{

public:
    
    /**
     * @brief constructor
     *
     */
    HJetDelphes();
    
    /**
     * @brief Destructor
     *
     */
    ~HJetDelphes();
    
    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets();
    
    /**
     * @brief Get Tau Tag
     * 
     * @return void
     */
    void GetTau(Jet *);
    
    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow();
    
    /**
     * @brief Get Gen Jet
     * 
     * @param  ...
     * @return void
     */
    void GetGenJet();
    

private:
            
    virtual TString ClassName() {
        return ("HJetDelphes");
    };
    
};

#endif
