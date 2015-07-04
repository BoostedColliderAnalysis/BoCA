#pragma once

#include "File.hh"
#include "Configuration.hh"
#include "Reader.hh"
#include "Branches.hh"

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

    void SetConfig(const Configuration &configuration);

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

protected:

    virtual std::vector<File> Files(const Tag tag);

    std::string ExportName(const Stage stage, const Tag tag) const;

    void PrepareFiles();

    virtual void SetFiles(const Tag tag);

    exroot::TreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Stage stage);


    InfoBranch FillInfoBranch(const exroot::TreeReader &tree_reader, const analysis::File &file);

    virtual  std::string ProjectName() const;

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual  int EventNumberMax() const;

    virtual  std::string ProcessName() const;


    // in GeV
    int Mass() const;

    // in GeV
    int PreCut() const;

//      int EventNumberMax() const {
//         return configuration_.EventNumberMax();
//     };

    int BackgroundFileNumber() const;

//      ColliderType collider_type() const {
//         return configuration_.collider_type();
//     }

    virtual  std::string FilePath() const;

    std::string FileSuffix() const;

    void NewSignalFile(const std::string &name, const std::string &nice_name = " ");

    void NewBackgroundFile(const std::string &name, const std::string &nice_name = " ");

    void NewSignalFile(const std::string &name, const float crosssection);

    void NewBackgroundFile(const std::string &name, const float crosssection);

    File get_file(const std::string &name, const std::string &nice_name = " ") const;

    File get_file(const std::string &name, const float crosssection) const;

    std::string FileName(const std::string &name) const;

    std::string TreeName(const std::string &name) const;

    virtual int PassPreCut(const Event &);

    int RunAnalysis(const Event &event, const Stage stage, const Tag tag);

    PreCuts &pre_cuts();

    Tagger &tagger();

    bool Missing(const std::string &name) const;

private:

    std::string PathName(const std::string &file_name) const;

    void RunTagger(analysis::Stage stage);

    void RunFactory();

    void RunSignificance();

    void RunEfficiency();

    Tagger &tagger_;

    Reader reader_;

    PreCuts pre_cuts_;

    Configuration configuration_;

    std::vector<File> files_;

};

}
