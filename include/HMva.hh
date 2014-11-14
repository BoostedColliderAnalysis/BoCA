# ifndef HMva_hh
# define HMva_hh

// # include "string.h"
# include "TCut.h"

# include "TClonesArray.h"
# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HBranch.hh"
# include "HObject.hh"

struct HReaderStruct {

  int HiggsSum;

  int TopSum;

  int FatJetSum;

  int TopEventSum;

  int HiggsEventSum;

  std::vector<int> EventVector;

  std::vector<int> HiggsEventVector;

  std::vector<int> TopEventVector;

  std::vector<int> CutFlowVector;

  std::vector<int> FatJetVector;

  std::vector<int> HiggsVector;

  std::vector<int> TopVector;

  std::vector<double> CutsMin;

  std::vector<double> CutsMax;

};


class HObservable// : public HObject
{

public :

    HObservable();

    HObservable(float *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex);

    float *Value;

    std::string Expression;

    std::string Title;

    std::string Unit;

    std::string Latex;

};

/**
 * @brief Prepares multivariant analysis
 *
 */
class hmva::HMva : public hanalysis::HObject
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

    bool DoLatex;

    int Luminosity;

    /**
     * @brief Debug variable
     *
     */
//     int Debug;

    float SignalEfficiency;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string AnalysisName;

    /**
     * @brief Name of the Signal File
     *
     */
    std::vector<std::string> SignalNames;

    /**
     * @brief Name of the Test File
     *
     */
    std::string TestName;

    std::string CutMethodName;

    std::string BdtMethodName;

    std::string CandidateBranchName;

    std::string SpectatorBranchName;

    std::string WeightBranchName;

    std::string BackgroundName;

    TCut Cut;

    /**
     * @brief Names of the Background Files
     *
     */
    std::vector<std::string> BackgroundNames;

    std::vector<std::string> BackgroundTreeNames;

    std::vector<std::string> SignalTreeNames;

    std::vector<std::string> TestTreeNames;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    std::vector<HObservable> Observables;

    std::vector<HObservable> Spectators;


    virtual HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&) = 0;

    virtual void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *) = 0;


protected:

  virtual void DefineVariables() = 0;

  virtual inline std::string NameSpaceName() const {
    return "HMva";
  };

    virtual inline std::string ClassName() const {
        return "HMva";
    };

    HObservable NewObservable(float *const Value, const std::string &Expression, const std::string &Title, const std::string &Unit, const std::string &Latex) const;

    HObservable NewObservable(float *const Value, const std::string &Expression, const std::string &Title, const std::string &Unit) const;

    HObservable NewObservable(float *const Value, const std::string &Expression, const std::string &Title) const;

    HObservable NewObservable(float *const Value, const std::string &Expression) const;

//     HObservable NewObservable(float *const Value, const std::string &Title, const std::string& Unit) const;

private:

};

# endif
