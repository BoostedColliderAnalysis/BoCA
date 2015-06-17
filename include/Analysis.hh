# pragma once

# include "Configuration.hh"
# include "File.hh"
# include "Reader.hh"

namespace analysis
{

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

    virtual void SetFiles(const Object::Tag tag) {
        Print(kError, "Set Files", "should be subclassed", tag);
    }

protected:

    inline int EventSum(const exroot::TreeReader &tree_reader) const {
        return std::min((int)tree_reader.GetEntries(), EventNumberMax());
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

    void NewSignalFile(const std::string &name,const std::string &nicename = "") {
        files_.emplace_back(get_file(name,nicename));
        tagger_.AddSignalTreeName(TreeName(name));
    }

    void NewBackgroundFile(const std::string &name,const std::string &nicename = "") {
      files_.emplace_back(get_file(name,nicename));
        tagger_.AddBackgroundTreeName(TreeName(name));
    }

    void NewSignalFile(const std::string &name, const float crosssection) {
        files_.emplace_back(get_file(name, crosssection));
        tagger_.AddSignalTreeName(TreeName(name));
    }

    void NewBackgroundFile(const std::string &name, const float crosssection) {
        files_.emplace_back(get_file(name, crosssection));
        tagger_.AddBackgroundTreeName(TreeName(name));
    }

    inline File get_file(const std::string &name,const std::string &nicename = "") const {
        return File(name, FilePath(), FileSuffix(),nicename);
    }

    inline File get_file(const std::string &name, const float crosssection) const {
        return File(name, FilePath(), FileSuffix(), crosssection);
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

    int RunAnalysis(Event &event, const Tagger::Stage stage, const Tag tag);

    virtual std::string NiceName() const {
        return "";
    }

private:

    Configuration configuration_;

    std::vector<File> files_;

};

}
