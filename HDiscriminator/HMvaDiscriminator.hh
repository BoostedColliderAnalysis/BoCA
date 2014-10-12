# ifndef HMvaDiscriminator_hh
# define HMvaDiscriminator_hh

# include "HMva.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class HMvaDiscriminator : public HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaDiscriminator();

    /**
    * @brief Destructor
    *
    */
    ~HMvaDiscriminator();

private:

    void DefineVariables();
    
    virtual string ClassName() const {
        return ("HMvaDiscriminator");
    };


};

# endif
