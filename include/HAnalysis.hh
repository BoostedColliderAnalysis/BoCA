# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "HFile.hh"

# include "HEvent.hh"

# include "HBranch.hh"
# include "HObject.hh"

using std::string;

class HAnlysis;

/**
 * @brief Class defining the Analysis
 *
 */
class HAnalysis : public HObject
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    HAnalysis();

    /**
     * @brief Destructor
     *
     */
    ~HAnalysis();

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
    virtual void SetFileVector() = 0;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    virtual void NewFile() = 0;
    
    /**
     * @brief Clean Analysis
     * 
     * @return void
     */
    virtual void CloseFile() = 0;

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
    vector<HFile *> FileVector;

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
    HClonesArray *ClonesArrays;
    
    bool Cut;
    
    virtual vector<string> GetStudyNameVector();
    
    vector<TFile> ExportFileVector;
    
    vector<ExRootTreeWriter> TreeWriterVector;

    string StudyName;

private:

    void EmptyFileVector();

    void NewStudy();

    void DeleteStudy();

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewFileBase();

    /**
     * @brief
     *
     * @return void
     */
    void NewEvent();

    int EventNumber;


    void CloseFileBase();


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
    int FileNumber;

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

    bool AnalysisNotEmpty;

    virtual string ClassName() const {
        
        return ("HAnalysis");
        
    };

};

#endif

