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

    enum HTagger {
        HBottomTagger,
        HBottomReader,
        HTauTagger,
        HTauReader,
        HJetPairTagger,
        HJetPairReader,
        HWSemiTagger,
        HWSemiReader,
        HWHadronicTagger,
        HWHadronicReader,
        HTopHadronicTagger,
        HTopSemiTagger,
        HTopHadronicReader,
        HTopSemiReader,
        HTopLeptonicTagger,
        HTopLeptonicReader,
        HHeavyHiggsHadronicTagger,
        HHeavyHiggsLeptonicTagger,
        HHeavyHiggsTauTagger,
        HHeavyHiggsLeptonicReader,
        HHeavyHiggsSemiTagger,
        HHeavyHiggsSemiReader,
        HHeavyHiggsTauReader,
        HEventLeptonicTagger,
        HEventHadronicTagger,
        HEventSemiTagger,
        HEventTagger,
        HHiggsLeptonicTagger,
        HEventLeptonicReader,
        HEventSemiReader,
        HChargedHiggsSemiTagger
    };

    void AnalysisLoop(const HTagger Tagger);

    void AnalysisLoop() {
        AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
    }

    virtual std::vector<HFile> Files(const HTagger Tagger, const HTag State) {
        Print(HError, "GetFiles", "Should be subclasses", Tagger, State);
        std::vector<HFile> NewFiles;
        return NewFiles;
    }

protected:

    virtual void ResetBranch() {
        Print(HError, "Reset Branch", "should be subclassed");
    }

    int EventSum(const std::shared_ptr<ExRootTreeReader> &NewTreeReader) const {
        return std::min((int)NewTreeReader->GetEntries(), EventNumberMax());
    }

//     ExRootTreeWriter *TreeWriter(TFile *const ExportFile, const std::string &ExportTreeName, const hanalysis::HAnalysis::HTagger Tagger);

    ExRootTreeWriter TreeWriter(const TFile &NewExportFile, const std::string &ExportTreeName, const hanalysis::HAnalysis::HTagger Tagger);

    ExRootTreeReader *TreeReader(const HFile *const File, HClonesArray *const ClonesArrays);

    TFile *ExportFile(const std::string &StudyName) const;

    std::string ExportName(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag State) const;

    void FillInfoBranch(const std::shared_ptr< ExRootTreeReader > &TreeReader, ExRootTreeBranch *const InfoBranch, const hanalysis::HFile &File);

    virtual bool Analysis(HEvent *const, const HTagger Tagger, const HTag State) {
        Print(HError, "Analysis", "should be subclassed", Tagger, State);
        return 0;
    }

    /**
     * @brief New Analysis
     */
    virtual void NewBranches(ExRootTreeWriter &, const HTagger) {
        Print(HError, "NewBranches", "Should be subclassed");
    }

    virtual void NewBranches(ExRootTreeWriter *const) {
        Print(HError, "NewBranches 0", "Should be subclassed");
    }

    /**
     * @brief Name of Analysis
     *
     */
    virtual inline std::string ProjectName() const {
        return "ProjectName";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual inline int EventNumberMax() const {
        return 100000;
    }

    virtual inline std::string StudyName(const HTagger Tagger) const {
        Print(HError, "GetStudyName", "What are we doing here?", Tagger);
        return ProjectName();
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

    HStrings JoinHStrings(const HStrings &Strings1, const HStrings &Strings2);

    std::vector<hanalysis::HFile>  JoinFiles(const std::vector<hanalysis::HFile> &Files1, const std::vector<hanalysis::HFile> &Files2);

    int EventSumM;

private:

};

#endif
