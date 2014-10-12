# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh

# include "HMva.hh"

# include "HBranchHeavyHiggs.hh"

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

    HReaderStruct CutLoop(const ExRootTreeReader * const);

    void ApplyBdt(const ExRootTreeReader * const, const string, const TFile * const, TMVA::Reader *);

private:

  HHeavyHiggsBranch *HeavyHiggs;

    void DefineVariables();

    virtual string ClassName() const {
        return ("HMvaHeavyHiggs");
    };


};

# endif
