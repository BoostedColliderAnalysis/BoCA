# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "HMva.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaEvent : public hmva::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaEvent();

    /**
    * @brief Destructor
    *
    */
    ~HMvaEvent();

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *);
    
    float GetBdt(TObject *Branch, TMVA::Reader *Reader){};

protected:


private:

      HEventBranch *Candidate;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
