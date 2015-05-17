# ifndef HMvaHiggsCpv_hh
# define HMvaHiggsCpv_hh


# include "Tagger.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaevent : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaevent();

    /**
    * @brief Destructor
    *
    */
    ~HMvaevent();

//     ReaderStruct CutLoop(const ExRootTreeReader * const, ReaderStruct&);

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, const TMVA::Reader &);

    float GetBdt(TObject *, const TMVA::Reader &){ return 0;};

protected:


private:

    hhiggscpv::EventBranch *eventBranch;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
