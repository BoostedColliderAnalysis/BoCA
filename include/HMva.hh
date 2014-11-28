# ifndef HMva_hh
# define HMva_hh

# include "TCut.h"
# include "TClonesArray.h"
# include "TObjArray.h"
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

class HObservable //: public hanalysis::HObject
{

public:

    HObservable() {};

    HObservable(float *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {

//         Print(HInformation, "Float Constructor", *NewValue);

        Value = NewValue;
        Expression = NewExpression;
        Title = NewTitle;
        Unit = NewUnit;
        Latex = NewLatex;
        Type = 'F';
    }



    HObservable(int *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {

//         Print(HInformation, "Int Constructor", *NewValue);

        Value = (float *)NewValue;
        Expression = NewExpression;
        Title = NewTitle;
        Unit = NewUnit;
        Latex = NewLatex;
        Type = 'I';

    }

    float *GetValue() {
        return Value;
    }

//     void SetValue(const float *NewValue);

//     void SetValue(const int *NewValue);

    std::string Expression;

    std::string Title;

    std::string Unit;

    char Type;

    std::string Latex;

private:

    float *Value;

    inline std::string ClassName() const {
        return "HObservable";
    }

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

//     template<typename TBranch, typename TParticle>
//     virtual void FillBranch(HBranch * const Branch, const fastjet::PseudoJet& Jet) {
//         Print(HError, "Fill Branch", "Should be subclassed");
//     }

    void SetSignalTreeNames(const HStrings &NewSignalTreeNames) {
        SignalTreeNames = NewSignalTreeNames;
    }

    void SetBackgroundTreeNames(const HStrings &NewBackgroundTreeNames) {
        BackgroundTreeNames = NewBackgroundTreeNames;
    }

    void SetInputTreeNames(const HStrings &NewSignalTreeNames, const HStrings &NewBackgroundTreeNames) {
        SignalTreeNames = NewSignalTreeNames;
        BackgroundTreeNames = NewBackgroundTreeNames;
    }

    void SetBranchName(const std::string &NewBranchName) {
        CandidateBranchName = NewBranchName;
    }

    std::string GetTaggerName() const {
        return TaggerName;
    }

    std::string GetAnalysisName() const {
        return AnalysisName;
    }

    std::vector<HObservable> GetObservables() const {
        return Observables;
    }

    void SetObservables(std::vector<HObservable> NewObservables) {
        Observables = NewObservables;
    }

    std::vector<HObservable> GetSpectators() const {
        return Spectators;
    }

    HStrings GetSignalNames() const {
        return SignalNames;
    }

    HStrings GetSignalTreeNames() const {
        return SignalTreeNames;
    }

    HStrings GetBackgroundNames() const {
        return BackgroundNames;
    }

    HStrings GetBackgroundTreeNames() const {
        return BackgroundTreeNames;
    }

    std::string GetTestName() const {
        return TestName;
    }

    HStrings GetTestTreeNames() const {
        return TestTreeNames;
    }


    float GetSignalEfficiency() const {
        return SignalEfficiency;
    }

    float GetLuminosity() const {
        return Luminosity;
    }

    TCut GetCut() const {
        return Cut;
    }

    void SetAnalysisName(const std::string NewAnalysisName) {
        AnalysisName = NewAnalysisName;
    }

    void SetTestTreeNames(const HStrings NewTestTreeNames) {
        TestTreeNames = NewTestTreeNames;
    }

    std::string GetCutMethodName()const {
        return CutMethodName;
    }

    std::string GetBdtMethodName()const {
        return BdtMethodName;
    }

    std::string GetWeightBranchName()const {
        return WeightBranchName;
    }

    bool LaTeX()const {
        return DoLatex;
    }

    virtual HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {
        HReaderStruct ReaderStruct;
        return ReaderStruct;
    };

    virtual void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    virtual float GetBdt(TObject *Branch, TMVA::Reader *Reader);

protected:

    virtual void DefineVariables() = 0;

    virtual inline std::string NameSpaceName() const {
        return "HMva";
    };

    virtual inline std::string ClassName() const {
        return "HMva";
    };

    template<typename TValue>
    HObservable NewObservable(TValue *const Value, const std::string &Title) const {

        Print(HDebug, "New Observable", *Value);
        const std::string Expression = CandidateBranchName + "." + Title;
        HObservable Observable(Value, Expression, Title, "", "");
        return Observable;

    }

    template<typename TValue>
    HObservable NewObservable(TValue *const Value, const std::string &Title, const std::string &Latex) const {

        Print(HDebug, "New Observable", *Value);
        const std::string Expression = CandidateBranchName + "." + Title;
        HObservable Observable(Value, Expression, Title, "", Latex);
        return Observable;

    }



    bool DoLatex;

    int Luminosity;

    float SignalEfficiency;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string AnalysisName;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string TaggerName;

    /**
     * @brief Name of the Signal File
     *
     */
    HStrings SignalNames;

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
    HStrings BackgroundNames;

    HStrings BackgroundTreeNames;

    HStrings SignalTreeNames;

    HStrings TestTreeNames;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    std::vector<HObservable> Observables;

    std::vector<HObservable> Spectators;

private:

};

# endif
