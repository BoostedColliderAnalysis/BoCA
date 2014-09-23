# ifndef HMva_hh
# define HMva_hh

# include "TString.h"
# include "TCut.h"

# include "HBranch.hh"

# include "HObject.hh"

using std::vector;


struct HObservable {

    float *Value;

    TString Expression;

    TString Title;

    TString Unit;

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
    TString AnalysisName;

    /**
     * @brief Name of the Signal File
     *
     */
    vector<TString> SignalVector;

    /**
     * @brief Name of the Test File
     *
     */
    TString TestName;

    TString CutMethodName;

    TString BdtMethodName;

    TString CandidateBranchName;

    TString LeptonBranchName;

    TString WeightBranchName;

    TString BackgroundName;


    TCut Cut;

    HCandidateBranch *Candidate;
    
    HHeavyHiggsBranch *HeavyHiggs;

    /**
     * @brief Names of the Background Files
     *
     */
    vector<TString> BackgroundVector;

    vector<TString> BackgroundTreeVector;

    vector<TString> SignalTreeVector;
    
    vector<TString> TestTreeVector;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    vector<HObservable> ObservableVector;

    vector<HObservable> SpectatorVector;

protected:
  
    virtual void DefineVariables() = 0;

    virtual TString ClassName() {
        return ("HMva");
    };

    HObservable NewObservable(float *, TString, TString, TString);

    HObservable NewObservable(float *, TString, TString);

    HObservable NewObservable(float *, TString);
    
private:

};

# endif
