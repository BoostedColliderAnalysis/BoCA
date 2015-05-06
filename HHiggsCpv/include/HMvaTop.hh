# ifndef HMvaTop_hh
# define HMvaTop_hh


# include "Tagger.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaTop : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaTop();

    /**
    * @brief Destructor
    *
    */
    ~HMvaTop();

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct& ReaderStruct){ return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &){};


    float GetBdt(TObject *Branch, const TMVA::Reader &Reader);

protected:


private:

      HTopLeptonicBranch *Top;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMvaTop";
    };


};

# endif
