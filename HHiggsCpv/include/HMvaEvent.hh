# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "Tagger.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaEvent : public hanalysis::Tagger
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

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);

    float GetBdt(TObject *, const TMVA::Reader &){ return 0;};

protected:


private:

    hhiggscpv::HEventBranch *EventBranch;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
