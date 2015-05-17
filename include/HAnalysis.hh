# pragma once

# include "Object.hh"
# include "Tagger.hh"
# include "HConfig.hh"
# include "File.hh"
# include "Reader.hh"



/**
 * @brief Base for all analyses
 *
 */
class analysis::HAnalysis : public Object
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    HAnalysis(analysis::Tagger &tagger);

    void AnalysisLoop(const analysis::Tagger::Stage stage);

    virtual std::vector<File> Files(const Tag tag) {
        Print(kError, "GetFiles", tag);
        return files_;
    }

    void SetConfig(const HConfig &config) {
        config_ = config;
    }

    std::string ExportName(const Tagger::Stage stage, const analysis::Object::Tag tag) const;

protected:

    virtual void SetFiles(const analysis::Object::Tag tag) {
        Print(kError, "Set Files", "should be subclassed", tag);
    }

    inline int eventSum(const ExRootTreeReader &tree_reader) const {
//       return std::min((int)tree_reader.GetEntries(), EventNumberMax());
        return tree_reader.GetEntries();
    }

    ExRootTreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Tagger::Stage stage);


    InfoBranch FillInfoBranch(const ExRootTreeReader &tree_reader, const analysis::File &file);

    virtual int Analysis(Event &, const Tagger::Stage stage, const Tag tag) {
        Print(kError, "Analysis", "should be subclassed", stage, tag);
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

    Strings JoinStrings(const Strings &Strings1, const Strings &Strings2) {
        return JoinVectors(Strings1, Strings2);
    };

    std::vector<analysis::File>  JoinFiles(const std::vector<analysis::File> &Files1, const std::vector<analysis::File> &Files2) {
        return JoinVectors(Files1, Files2);
    };

    int event_sum_;

    int &event_sum() {
        return event_sum_;
    }

    Tagger &tagger_;

    Reader reader_;

    int object_number_;

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

    virtual inline std::string FilePath() const {
        return "~/Projects/Tagging/";
    }

    std::string FileSuffix() const {
        return ".root";
    }

    void NewSignalFile(const std::string &name) {
        files_.emplace_back(get_file(name));
        tagger_.AddSignalTreeName(TreeName(name));
    }

    void NewBackgroundFile(const std::string &name) {
        files_.emplace_back(get_file(name));
        tagger_.AddBackgroundTreeName(TreeName(name));
    }

    inline analysis::File get_file(const std::string &name) const {
        return File(name, FilePath(), FileSuffix());
    }

    inline std::string FileName(const std::string &name) const {
        return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
    }

    std::string TreeName(const std::string &name) const {
        return name + "-run_01";
    }

    virtual int PassPreCut(analysis::Event &) {
        Print(kError, "Apply pre cut", "no pre cut applied");
        return 1;
    }

    PreCuts pre_cuts_;

private:

    HConfig config_;

    std::vector<analysis::File> files_;


};
