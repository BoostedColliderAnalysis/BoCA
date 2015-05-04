# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh


#include "TObjArray.h"

# include "Tagger.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMva : public hanalysis::Tagger
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

//     HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&);

//     void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);

    float GetBdt(TObject *, const TMVA::Reader &){return 0;};

private:

  HHeavyHiggsLeptonicBranch *HeavyHiggs;

    void DefineVariables();

    virtual inline std::string ClassName() const {
        return "HeavyHiggs: HMva";
    };


};

# endif
