# ifndef HMva_hh
# define HMva_hh

# include "string.h"
# include "TCut.h"

# include "TClonesArray.h"
# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HBranch.hh"

# include "HObject.hh"

using std::vector;



struct HReaderStruct {

  int HiggsSum;

  int TopSum;

  int FatJetSum;

  int TopEventSum;

  int HiggsEventSum;

  vector<int> EventVector;

  vector<int> HiggsEventVector;

  vector<int> TopEventVector;

  vector<int> CutFlowVector;

  vector<int> FatJetVector;

  vector<int> HiggsVector;

  vector<int> TopVector;

  vector<double> CutsMin;

  vector<double> CutsMax;

};


class HObservable// : public HObject
{

public :

    HObservable();

    HObservable(float *const NewValue, const string NewExpression, const string NewTitle, const string NewUnit, const string NewLatex);

    float *Value;

    string Expression;

    string Title;

    string Unit;

    string Latex;

};

/**
 * @brief Prepares multivariant analysis
 *
 */
class hanalysis::HMva : public HObject
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
    string AnalysisName;

    /**
     * @brief Name of the Signal File
     *
     */
    vector<string> SignalNames;

    /**
     * @brief Name of the Test File
     *
     */
    string TestName;

    string CutMethodName;

    string BdtMethodName;

    string CandidateBranchName;

    string SpectatorBranchName;

    string WeightBranchName;

    string BackgroundName;

    TCut Cut;

    /**
     * @brief Names of the Background Files
     *
     */
    vector<string> BackgroundNames;

    vector<string> BackgroundTreeNames;

    vector<string> SignalTreeNames;

    vector<string> TestTreeNames;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    vector<HObservable> Observables;

    vector<HObservable> Spectators;


    virtual HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&) = 0;

    virtual void ApplyBdt(const ExRootTreeReader * const, const string, const TFile * const, TMVA::Reader *) = 0;


protected:

    virtual void DefineVariables() = 0;

    virtual inline string ClassName() const {

        return ("HMva");

    };

    HObservable NewObservable(float *const, const string, const string, const string, const string) const;

    HObservable NewObservable(float *const, const string, const string, const string) const;

    HObservable NewObservable(float *const, const string, const string) const;

    HObservable NewObservable(float *const, const string) const;

private:

};

# endif
