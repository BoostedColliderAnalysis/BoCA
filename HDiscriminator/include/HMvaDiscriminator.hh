# ifndef HMvaDiscriminator_hh
# define HMvaDiscriminator_hh


# include "Tagger.hh"
# include "HBranchDiscriminator.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hcpvhiggs::HMva : public hanalysis::Tagger
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

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);

    float GetBdt(TObject *, const TMVA::Reader &){ return 0;};

protected:


private:

      HCandidateBranch *Candidate;

    void DefineVariables();

    virtual inline std::string ClassName() const {
        return "HiggsCPV: HMva";
    };


};

# endif
