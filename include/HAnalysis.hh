# ifndef HAnalysis_hh
# define HAnalysis_hh

# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "HBranch.hh"
# include "HObject.hh"
# include "HFile.hh"
# include "HEvent.hh"


/**
 * @brief Base for all analyses
 *
 */
class hanalysis::HAnalysis : public HObject
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

//     void AnalysisLoop();
//     enum HTagger {EventTagger};
    enum HTagger {HBottomTagger, HTopTagger, HHiggsTagger, HEventTagger};

    void AnalysisLoop(const HTagger Tagger);

    void AnalysisLoop() {
        AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    }


    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    virtual std::vector<HFile *> GetFiles(const std::string &StudyName) = 0;
    
protected:

//     HTagger Tagger;


    int GetEventSum(const ExRootTreeReader *const TreeReader) const {

        return std::min((int)TreeReader->GetEntries(), GetEventNumberMax());

    }

    ExRootTreeWriter *GetTreeWriter(TFile *const ExportFile, const std::string &ExportTreeName, const HTagger Tagger);

    ExRootTreeReader *GetTreeReader(const HFile *const File, HClonesArray *const ClonesArrays);

    TFile *GetExportFile(const std::string &StudyName) const;

    void FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File);

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    virtual bool Analysis(HEvent *const, const std::string &) {
        Print(HError, "Analysis 0", "should be subclassed");
        return 0;
    }

    virtual bool Analysis(HEvent *const, const std::string &, const HTagger) {
        Print(HError, "Analysis", "should be subclassed");
        return 0;
    }

    /**
     * @brief New Analysis
     *
     * @return void
     */
    virtual void NewBranches(ExRootTreeWriter *const, const HTagger) {
        Print(HError, "NewBranches", "Should be subclassed");
    }

    virtual void NewBranches(ExRootTreeWriter *const) {
        Print(HError, "NewBranches 0", "Should be subclassed");
    }

    /**
     * @brief Name of Analysis
     *
     */
    virtual inline std::string GetProjectName() const {
        return "ProjectName";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual inline int GetEventNumberMax() const {
        return 100000;
    }

    virtual inline HStrings GetStudyNames(const HTagger NewTagger) {
        Print(HError, "GetStudyName", "What are we doing here?", NewTagger);
        return {GetProjectName()};
    }


//     virtual inline HStrings GetStudyNames() const {
//         return {GetProjectName()};
//     };

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

};

#endif
