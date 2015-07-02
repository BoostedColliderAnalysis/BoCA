#pragma once

#include "File.hh"
#include "Configuration.hh"
#include "Reader.hh"

namespace analysis
{

/**
 * @brief Base for all analyses
 *
 */
class Analysis
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    Analysis(Tagger &tagger);

    void AnalysisLoop(const Stage stage);

    virtual std::vector<File> Files(const Tag tag);

    void SetConfig(const Configuration &configuration) {
        configuration_ = configuration;
    }

    std::string ExportName(const Stage stage, const Tag tag) const;

    void PrepareFiles(){
      files_.clear();
      tagger_.clear_tree_names();
      SetFiles(analysis::Tag::signal);
      SetFiles(analysis::Tag::background);
    }

protected:

    virtual void SetFiles(const Tag tag);

    exroot::TreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Stage stage);


    InfoBranch FillInfoBranch(const exroot::TreeReader &tree_reader, const analysis::File &file);

    virtual  std::string ProjectName() const {
        return "ProjectName";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual  int EventNumberMax() const {
        return 100000;
    }

    virtual  std::string ProcessName() const {
        return "Process";
    }


    // in GeV
     int Mass() const {
        return configuration_.Mass();
    }

    // in GeV
     int PreCut() const {
        return configuration_.PreCut();
    }

//      int EventNumberMax() const {
//         return configuration_.EventNumberMax();
//     };

     int BackgroundFileNumber() const {
        return configuration_.BackgroundFileNumber();
    }

//      ColliderType collider_type() const {
//         return configuration_.collider_type();
//     }

    virtual  std::string FilePath() const {
        return "~/Projects/";
    }

    std::string FileSuffix() const {
        return ".root";
    }

    void NewSignalFile(const std::string &name, const std::string &nice_name = " ") {
        files_.emplace_back(get_file(name, nice_name));
        tagger_.AddSignalTreeName(TreeName(name));
    }

    void NewBackgroundFile(const std::string &name, const std::string &nice_name = " ") {
        files_.emplace_back(get_file(name, nice_name));
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

     File get_file(const std::string &name, const std::string &nice_name = " ") const {
        return File(name, FilePath(), FileSuffix(), nice_name);
    }

     File get_file(const std::string &name, const float crosssection) const {
        return File(name, FilePath(), FileSuffix(), crosssection);
    }

     std::string FileName(const std::string &name) const {
        return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
    }

    std::string TreeName(const std::string &name) const {
        return name + "-run_01";
    }

    virtual int PassPreCut(const Event &);

    int RunAnalysis(const Event &event, const Stage stage, const Tag tag);

    PreCuts &pre_cuts() {
        return pre_cuts_;
    }

    Tagger &tagger(){
      return tagger_;
    }

    bool Missing(const std::string& name) const;

private:

    Tagger &tagger_;

    Reader reader_;

    PreCuts pre_cuts_;

    Configuration configuration_;

    std::vector<File> files_;

};

}
