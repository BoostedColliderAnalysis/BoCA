# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh

# include "HMva.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class HMvaHeavyHiggs : public HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaHeavyHiggs();

    /**
    * @brief Destructor
    *
    */
    ~HMvaHeavyHiggs();

private:

    void DefineVariables();
    
    virtual TString ClassName() {
        return ("HMvaHeavyHiggs");
    };


};

# endif
