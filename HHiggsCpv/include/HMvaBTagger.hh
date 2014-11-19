# ifndef HMvaBTagger_hh
# define HMvaBTagger_hh


# include "HMva.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaBTagger : public hmva::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaBTagger();

    /**
    * @brief Destructor
    *
    */
    ~HMvaBTagger();

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *);
    
    float GetBdt(hhiggscpv::HBTaggerBranch *Branch, TMVA::Reader *Reader);

protected:


private:

      HBTaggerBranch *Candidate;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
