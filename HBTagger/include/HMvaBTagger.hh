# ifndef HMvaBTagger_hh
# define HMvaBTagger_hh


# include "HMva.hh"
# include "HBranchBTagger.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hbtagger::HMva : public hmva::HMva
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
