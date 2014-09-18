# ifndef HMvaCpv_hh
# define HMvaCpv_hh

# include "HMvaBase.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class HMva : public HMvaBase
{

public:

    /**
    * @brief Constructor
    *
    */
    HMva();

    /**
    * @brief Destructor
    *
    */
    ~HMva();

private:

    void DefineVariables();
    
    virtual TString ClassName() {
        return ("HMva");
    };


};

# endif
