# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "HMva.hh"
# include "HBranchHeavyHiggs.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hheavyhiggs::HMvaEvent : public hanalysis::HMva
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

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};

    float GetBdt(TObject *, TMVA::Reader *){ return 0;};

protected:


private:

    hheavyhiggs::HEventBranch *EventBranch;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
      };

    virtual inline std::string ClassName() const {
        return "HMvaEvent";
    };


};

# endif
