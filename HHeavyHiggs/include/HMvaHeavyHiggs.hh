# ifndef HMvaHeavyHiggs_hh
# define HMvaHeavyHiggs_hh


#include "TObjArray.h"

# include "Tagger.hh"

# include "HBranchHeavyHiggs.hh"

/**
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMva : public analysis::Tagger
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

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct&);

//     void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);

    float GetBdt(TObject *, const TMVA::Reader &){return 0;};

private:

  analysis::HHeavyHiggsLeptonicBranch *HeavyHiggs;

    void DefineVariables();

    virtual inline std::string ClassName() const {
        return "HeavyHiggs: HMva";
    };


};

# endif
