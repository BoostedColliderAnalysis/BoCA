# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh

# include "HMva.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class HeavyHiggs::HMva : public Analysis::HMva
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

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const string, const TFile * const, TMVA::Reader *);

private:

  HHeavyHiggsBranch *HeavyHiggs;

    void DefineVariables();

    virtual inline string ClassName() const {
        return ("HMvaHeavyHiggs");
    };


};

# endif
