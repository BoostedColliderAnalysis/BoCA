# ifndef HMvaDiscriminator_hh
# define HMvaDiscriminator_hh


# include "HMva.hh"
# include "HBranchDiscriminator.hh"

/**
 * \class HMvaDiscriminator
 *
 * @brief Prepares multivariant analysis
 *
 */
class hcpvhiggs::HMva : public hanalysis::HMva
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

protected:


private:

      HCandidateBranch *Candidate;

    void DefineVariables();

    virtual inline string ClassName() const {
        return "HiggsCPV: HMva";
    };


};

# endif
