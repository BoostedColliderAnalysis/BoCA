# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh


#include "TObjArray.h"

# include "HMva.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMva : public hanalysis::HMva
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

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *);

    float GetBdt(TObject *, TMVA::Reader *){return 0;};

private:

  HHeavyHiggsBranch *HeavyHiggs;

    void DefineVariables();

    virtual inline std::string ClassName() const {
        return "HeavyHiggs: HMva";
    };


};

# endif
