# ifndef HAnalysisBase_hh
# define HAnalysisBase_hh

// # include "HBranch.hh"
// # include "HAnalysisDiscriminator.hh"


/**
 * @brief Manages study input and output
 *
 */
class HAnalysisBase : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisBase(HAnalysis *, HEvent *);

    /**
     * @brief Destructor
     *
     */
    ~HAnalysisBase();
    
    void NewMva(TString);

    /**
     * @brief takes the root file at the PathNumber and fills the Clones Arrays
     *
     * @param PathNumber
     * @return int EntrySum
     */
    int NewAnalysis(int);


    /**
     * @brief clean up after the analysis
     *
     * @return void
     */
    void CleanAnalysisBase();
    

private:

    /**
     * @brief number which indicates which file we are in
     *
     */
    int AnalysisNumber;

    /**
     * @brief Branch structure for general tree infos
     *
     */
//     HInfoBranch *Info;


    /**
     * @brief Observable Class
     *
     */
    HAnalysis *Analysis;

    /**
     * @brief Observable Class
     *
     */
    HEvent *Event;

    /**
     * @brief Export Pdf
     *
     */
//     HPdf *Pdf;

    /**
     * @brief vector containing the string pairs describing the path to the root file
     *
     */
//     vector<HPath *> AnalysisVector;

//     float Crosssection;
    
    
//     vector<HHistogram *> ObservableVector;
    
    
    
    //     HInfoBranch *Info;
    
    virtual TString ClassName() {
        return ("HAnalysisBase");
    };

};


#endif

