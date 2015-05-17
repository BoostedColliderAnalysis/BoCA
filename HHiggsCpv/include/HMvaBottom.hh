# ifndef HMvaBTagger_hh
# define HMvaBTagger_hh


# include "Tagger.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaBottom : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaBottom();

    /**
    * @brief Destructor
    *
    */
    ~HMvaBottom();

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct&){ ReaderStruct ReaderStruct; return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &){};

    float GetBdt(TObject *Branch, const TMVA::Reader &Reader);

protected:


private:

      BottomBranch *BTagger;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
