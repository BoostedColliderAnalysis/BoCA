# ifndef HMva_hh
# define HMva_hh

# include "string.h"
# include "TCut.h"

# include "HBranch.hh"

# include "HObject.hh"

using std::vector;


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
class HMva : public HObject
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

    bool Latex;

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
    vector<string> SignalNameVector;

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

    HCandidateBranch *Candidate;

    HHeavyHiggsBranch *HeavyHiggs;

    /**
     * @brief Names of the Background Files
     *
     */
    vector<string> BackgroundNameVector;

    vector<string> BackgroundTreeNameVector;

    vector<string> SignalTreeNameVector;

    vector<string> TestTreeNameVector;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    vector<HObservable> ObservableVector;

    vector<HObservable> SpectatorVector;

protected:

    virtual void DefineVariables() = 0;

    virtual string ClassName() const {

        return ("HMva");

    };

    HObservable NewObservable(float *const, const string, const string, const string, const string) const;

    HObservable NewObservable(float *const, const string, const string, const string) const;

    HObservable NewObservable(float *const, const string, const string) const;

    HObservable NewObservable(float *const, const string) const;

private:

};

# endif
