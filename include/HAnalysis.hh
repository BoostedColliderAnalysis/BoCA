# ifndef HAnalysis_hh
# define HAnalysis_hh

#include <sys/stat.h>

# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootProgressBar.h"

# include "HBranch.hh"
# include "HObject.hh"
# include "HFile.hh"
# include "HEvent.hh"
# include "HConfig.hh"
# include "Tagger.hh"


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
    HAnalysis(hanalysis::Tagger &tagger);

    enum HTagger {
        HBottomTagger,
//         HBottomReader,
        HTauTagger,
//         HTauReader,
        HJetPairTagger,
//         HJetPairReader,
        HWSemiTagger,
//         HWSemiReader,
        HWHadronicTagger,
//         HWHadronicReader,
        HTopHadronicTagger,
        HTopSemiTagger,
//         HTopHadronicReader,
//         HTopSemiReader,
        HTopLeptonicTagger,
//         HTopLeptonicReader,
        HHeavyHiggsHadronicTagger,
        HHeavyHiggsLeptonicTagger,
        HHeavyHiggsTauTagger,
//         HHeavyHiggsLeptonicReader,
        HHeavyHiggsSemiTagger,
//         HHeavyHiggsSemiReader,
//         HHeavyHiggsTauReader,
        HEventLeptonicTagger,
        HEventHadronicTagger,
        HEventSemiTagger,
//         HEventSemiReader,
        HSignatureSemiTagger,
//         HSignatureSemiReader,
        HEventTagger,
        HHiggsLeptonicTagger,
//         HEventLeptonicReader,
        HChargedHiggsSemiTagger
    };

    void AnalysisLoop(const hanalysis::Tagger::Stage stage);

//     void AnalysisLoop() {
//         AnalysisLoop(hanalysis::HAnalysis::HEventTagger);
//     }

    virtual std::vector<HFile> Files(const Tag tag) {
        Print(HError, "GetFiles", "Should be subclasses", tag);
        return std::vector<HFile> {};
    }

    void SetConfig(const HConfig &config) {
        config_ = config;
    }

protected:

    inline int EventSum(const ExRootTreeReader &tree_reader) const {
//       return std::min((int)tree_reader.GetEntries(), EventNumberMax());
        return tree_reader.GetEntries();
    }

    ExRootTreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Tagger::Stage stage);

//     ExRootTreeReader *TreeReader(const HFile *const File, HClonesArray *const ClonesArrays);

//     TFile *ExportFile(const std::string &StudyName) const;

    std::string ExportName(const Tagger::Stage stage, const hanalysis::HObject::Tag tag) const;

    HInfoBranch FillInfoBranch(const ExRootTreeReader &tree_reader, const hanalysis::HFile &file);

    virtual bool Analysis(HEvent &,const Tagger::Stage stage, const Tag tag) {
        Print(HError, "Analysis", "should be subclassed", tag);
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

//     /**
//      * @brief Maximal number of Entries to analyse
//      *
//      */
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

    template <typename HElement>
    std::vector<HElement>  JoinVectors(const std::vector<HElement> &Vector1, const std::vector<HElement> &Vector2) {
        std::vector<HElement>  Combined;
        Combined.reserve(Vector1.size() + Vector2.size());
        Combined.insert(Combined.end(), Vector1.begin(), Vector1.end());
        Combined.insert(Combined.end(), Vector2.begin(), Vector2.end());
        return Combined;
    }


    HStrings JoinHStrings(const HStrings &Strings1, const HStrings &Strings2) {
        return JoinVectors(Strings1, Strings2);
    };

    std::vector<hanalysis::HFile>  JoinFiles(const std::vector<hanalysis::HFile> &Files1, const std::vector<hanalysis::HFile> &Files2) {
        return JoinVectors(Files1, Files2);
    };

    int event_sum_;

    int &event_sum() {
        return event_sum_;
    }

    /**
     * @brief Branch to write results into
     *
     */
//     ExRootTreeBranch *Branch;

    Tagger &tagger_;

    int ObjectNumber;

    virtual inline std::string ProcessName() const {
        return "Process";
    }


    // in GeV
    inline int Mass() const {
        return config_.Mass();
    }

    // in GeV
    inline int PreCut() const {
        return config_.PreCut();
    }

//     inline int EventNumberMax() const {
//         return config_.EventNumberMax();
//     };

    inline int BackgroundFileNumber() const {
        return config_.BackgroundFileNumber();
    }

    inline HColliderType ColliderType() const {
        return config_.ColliderType();
    }

private:

    HConfig config_;


};

#endif



