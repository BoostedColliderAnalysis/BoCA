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
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

typedef Analysis::HDelphes::HFile HFileDelphes;

/**
 * @brief Base for all analyses
 *
 */
class Analysis::HAnalysis : public HObject
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

    int GetEventSum(const ExRootTreeReader *const TreeReader) const {

        return min((int)TreeReader->GetEntries(), GetEventNumberMax());

    };

    ExRootTreeWriter *GetTreeWriter(TFile *const ExportFile, const string ExportTreeName);

    ExRootTreeReader *GetTreeReader(const HFile *const File, HClonesArray *const ClonesArrays);

    TFile *GetExportFile(const string StudyName) const;

    void FillInfoBranch(const ExRootTreeReader *const TreeReader, ExRootTreeBranch *const InfoBranch, const HFile *const File);

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    virtual bool Analysis(HEvent * const, const string) = 0;

    /**
     * @brief prepares the vector describing the input root files
     *
     * @return void
     */
    virtual vector<HFile*> GetFiles(const string StudyName) const = 0;

    /**
     * @brief New Analysis
     *
     * @return void
     */
    virtual void NewBranches(ExRootTreeWriter * const TreeWriter) = 0;

    /**
     * @brief Name of Analysis
     *
     */
    virtual inline string GetProjectName() const {

        return "ProjectName";

    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual inline int GetEventNumberMax() const {

        return 100000;

    };

    virtual inline vector<string> GetStudyNames() const {

        return {GetProjectName()};

    };

private:

    void DeleteFiles(const vector<HFile *> Files) const;

    HClonesArray *GetClonesArrays(const string StudyName) const;

    HEvent *GetEvent(const string StudyName) const;

    virtual inline string ClassName() const {

        return "HAnalysis";

    };

};

#endif
