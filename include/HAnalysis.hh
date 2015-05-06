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
# include "Reader.hh"


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

    void AnalysisLoop(const hanalysis::Tagger::Stage stage);

    virtual std::vector<HFile> Files(const Tag tag) {
        Print(HError, "GetFiles", tag);
//         return std::vector<HFile> {};
      return files_;
    }

    void SetConfig(const HConfig &config) {
        config_ = config;
    }

protected:

    virtual void SetFiles(const hanalysis::HObject::Tag tag) {
        Print(HError, "Set Files", "should be subclassed", tag);
    }

    inline int EventSum(const ExRootTreeReader &tree_reader) const {
//       return std::min((int)tree_reader.GetEntries(), EventNumberMax());
        return tree_reader.GetEntries();
    }

    ExRootTreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Tagger::Stage stage);

    std::string ExportName(const Tagger::Stage stage, const hanalysis::HObject::Tag tag) const;

    HInfoBranch FillInfoBranch(const ExRootTreeReader &tree_reader, const hanalysis::HFile &file);

    virtual int Analysis(HEvent &, const Tagger::Stage stage, const Tag tag) {
        Print(HError, "Analysis", "should be subclassed", stage, tag);
        return 0;
    }

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


    Strings JoinStrings(const Strings &Strings1, const Strings &Strings2) {
        return JoinVectors(Strings1, Strings2);
    };

    std::vector<hanalysis::HFile>  JoinFiles(const std::vector<hanalysis::HFile> &Files1, const std::vector<hanalysis::HFile> &Files2) {
        return JoinVectors(Files1, Files2);
    };

    int event_sum_;

    int &event_sum() {
        return event_sum_;
    }

    Tagger &tagger_;

    Reader reader_;

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

    void NewSignalFile(const std::string &name) {
        files_.emplace_back(File(name));
        files_.front().SetBasePath("~/Projects/BTagging/"); // FIXME remove this hack
        files_.front().SetFileSuffix(".root"); // FIXME remove this hack
        tagger_.AddSignalTreeName(TreeName(name));
    }

    void NewBackgroundFile(const std::string &name) {
        files_.emplace_back(File(name));
        files_.front().SetBasePath("~/Projects/BTagging/"); // FIXME remove this hack
        files_.front().SetFileSuffix(".root"); // FIXME remove this hack
        tagger_.AddBackgroundTreeName(TreeName(name));
    }

    inline hanalysis::HFile File(const std::string &name) const {
        return HFile(name);
    }

    inline std::string FileName(const std::string &name) const {
        return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
    }

    std::string TreeName(const std::string &name) const {
        return name + "-run_01";
    }

private:

    HConfig config_;

    std::vector<hanalysis::HFile> files_;


};

#endif



