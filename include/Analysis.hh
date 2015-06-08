# pragma once

# include "Object.hh"
# include "Tagger.hh"
# include "Configuration.hh"
# include "File.hh"
# include "Reader.hh"

namespace analysis {

/**
 * @brief Base for all analyses
 *
 */
class Analysis : public Object
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    Analysis(Tagger &tagger);

    void AnalysisLoop(const Tagger::Stage stage);

    virtual std::vector<File> Files(const Tag tag) {
        Print(kError, "Files", tag);
        return files_;
    }

    void SetConfig(const Configuration &config) {
        configuration_ = config;
    }

    std::string ExportName(const Tagger::Stage stage, const Object::Tag tag) const;

protected:

    virtual void SetFiles(const Object::Tag tag) {
        Print(kError, "Set Files", "should be subclassed", tag);
    }

    inline int eventSum(const exroot::TreeReader &tree_reader) const {
//       return std::min((int)tree_reader.GetEntries(), EventNumberMax());
        return tree_reader.GetEntries();
    }

    exroot::TreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Tagger::Stage stage);


    InfoBranch FillInfoBranch(const exroot::TreeReader &tree_reader, const analysis::File &file);

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
        return "Analysis";
    }

    Strings JoinStrings(const Strings &Strings1, const Strings &Strings2) {
        return JoinVectors(Strings1, Strings2);
    }

    std::vector<File>  JoinFiles(const std::vector<File> &Files1, const std::vector<File> &Files2) {
        return JoinVectors(Files1, Files2);
    }

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
        return configuration_.Mass();
    }

    // in GeV
    inline int PreCut() const {
        return configuration_.PreCut();
    }

//     inline int EventNumberMax() const {
//         return configuration_.EventNumberMax();
//     };

    inline int BackgroundFileNumber() const {
        return configuration_.BackgroundFileNumber();
    }

//     inline ColliderType collider_type() const {
//         return configuration_.collider_type();
//     }

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

    inline File get_file(const std::string &name) const {
        return File(name, FilePath(), FileSuffix());
    }

    inline std::string FileName(const std::string &name) const {
        return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
    }

    std::string TreeName(const std::string &name) const {
        return name + "-run_01";
    }

    virtual int PassPreCut(Event &) {
        Print(kError, "Apply pre cut", "no pre cut applied");
        return 1;
    }

    PreCuts pre_cuts_;

    int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag);

private:

    Configuration configuration_;

    std::vector<File> files_;

};

}
