# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "HMva.hh"
# include "HBranchHiggsCpv.hh"

/**
 * \class HMvaDiscriminator
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMva : public hanalysis::HMva
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

      virtual inline string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline string ClassName() const {
        return "HMva";
    };


};

# endif
