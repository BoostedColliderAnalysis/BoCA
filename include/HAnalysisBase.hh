# ifndef HAnalysisBase_hh
# define HAnalysisBase_hh

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "HPath.hh"

# include "HEvent.hh"

# include "HBranch.hh"
# include "HObject.hh"

using std::string;

class HAnlysis;

/**
 * @brief Class defining the Analysis
 *
 */
class HAnalysisBase : public HConstants
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    HAnalysisBase();

    /**
     * @brief Destructor
     *
     */
    ~HAnalysisBase();

    void AnalysisLoop();

protected:

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    virtual bool Analysis() = 0;

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    virtual void FillAnalysisVector() = 0;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    virtual void NewAnalysis() = 0;
    
    virtual void CleanAnalysis() = 0;

    vector<string> MvaNameVector;

    /**
     * @brief Name of Analysis
     *
     */
    string ProjectName;

    /**
     * @brief Tree Writer
     *
     */
    ExRootTreeWriter *TreeWriter;

    /**
     * @brief Name of Analysis
     *
     */
    string AnalysisName;

    /**
     * @brief vector containing the string pairs describing the path to the root file
     *
     */
    vector<HPathBase *> AnalysisVector;

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    int EventNumberMax;

    HEvent *Event;
    
    /**
     * @brief Clones Arrays
     *
     */
    HClonesArrayBase *ClonesArrays;

private:

    void DefineHistograms();

    void NewMva();

    string MvaName;

    void CleanMva();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewAnalysisBase();

    /**
     * @brief
     *
     * @return void
     */
    void NewEvent();

    int EventNumber;


    void CleanAnalysisBase();


    /**
     * @brief Branch containing general tree infos
     *
     */
    ExRootTreeBranch *InfoBranch;

    /**
     * @brief Initial value outside of histogram values
     *
     */
    int InitialValue;

    /**
     * @brief Number of this Analysis
     *
     */
    int AnalysisNumber;

    /**
     * @brief Import File
     *
     */
    TFile *ImportFile;

    /**
     * @brief TFile for the exportet root
     *
     */
    TFile *ExportFile;

    /**
     * @brief Tree Reader
     *
     */
    ExRootTreeReader *TreeReader;

    TTree *ImportTree;

    int EventSum;

    /**
     * @brief Vector containing the number of entries in each file
     *
     */
    vector<int> EntrySumVector;

    bool AnalysisNotEmpty;

    virtual TString ClassName() {
        return ("HAnalysisBase");
    };

};

#endif

