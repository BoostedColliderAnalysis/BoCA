# ifndef HMvaBTagger_hh
# define HMvaBTagger_hh


# include "HMva.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaBottom : public hmva::HMva
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

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){ HReaderStruct ReaderStruct; return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};

    float GetBdt(TObject *Branch, TMVA::Reader *Reader);

protected:


private:

      HBottomBranch *BTagger;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
