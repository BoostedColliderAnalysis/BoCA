# ifndef HMvaHiggs_hh
# define HMvaHiggs_hh


# include "HMva.hh"
# include "HBranchHiggsCpv.hh"

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class hhiggscpv::HMvaHiggs : public hanalysis::HMva
{

public:

    /**
    * @brief Constructor
    *
    */
    HMvaHiggs();

    /**
    * @brief Destructor
    *
    */
    ~HMvaHiggs();

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct& ReaderStruct){ return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};


    float GetBdt(TObject *Branch, TMVA::Reader *Reader);

protected:


private:

      HHiggsBranch *Higgs;

      void DefineVariables();

      virtual inline std::string NameSpaceName() const {
        return "HiggsCPV";
      };

    virtual inline std::string ClassName() const {
        return "HMva";
    };


};

# endif
