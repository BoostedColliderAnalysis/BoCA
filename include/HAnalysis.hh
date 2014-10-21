# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "HBranch.hh"
# include "HFile.hh"
# include "HObject.hh"

# include "HEvent.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

using std::string;

/**
 * @brief Base for all analyses
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

    int GetEventSum(const ExRootTreeReader * const TreeReader) const {

        return min((int)TreeReader->GetEntries(), EventNumberMax);

    };

    ExRootTreeWriter *GetTreeWriter(TFile* ExportFile, const string ExportTreeName);

    ExRootTreeReader *GetTreeReader(const HFile*const File);

    TFile *GetExportFile(const string StudyName);

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    virtual bool Analysis(HEvent*,string) = 0;

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    virtual vector<HFile*> GetFiles() = 0;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    virtual void NewFile(ExRootTreeWriter *TreeWriter) = 0;

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
     * @brief Maximal number of Entries to analyse
     *
     */
    int EventNumberMax;

    bool Cut;

    virtual vector<string> GetStudyNames();

    vector<TFile*> ExportFiles;


private:

    void EmptyFileVector();

    HClonesArray* GetClonesArrays(const std::vector< HFile* > Files);

    HEvent* GetEvent(const std::vector< HFile* > Files);

    /**
     * @brief Initial value outside of histogram values
     *
     */
//     int InitialValue;

//     bool AnalysisNotEmpty;

    virtual string ClassName() const {

        return ("HAnalysis");

    };

};

#endif

