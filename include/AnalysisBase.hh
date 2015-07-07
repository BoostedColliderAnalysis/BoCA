#pragma once

#include "File.hh"
// #include "Configuration.hh"
#include "Branches.hh"
#include "Reader.hh"

namespace analysis
{

/**
 * @brief Base for all analyses
 *
 */
class AnalysisBase
{

public:

    virtual void AnalysisLoop(const Stage stage) = 0;

//     void SetConfig(const Configuration &configuration);

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

protected:

  void ClearFiles();

    virtual std::vector<File> Files(const Tag tag);

    std::string ExportName(const Stage stage, const Tag tag) const;

    void PrepareFiles();

    virtual void SetFiles(const Tag tag) = 0;

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

    void NewFile(const Tag tag, const std::string &name, const std::string &nice_name = "");

    void NewFile(const Tag tag, const std::string &name, const float crosssection, const std::string &nice_name = "");

    void NewSignalFile(const std::string &name, const std::string &nice_name = "");

    void NewSignalFile(const std::string &name, const float crosssection, const std::string &nice_name = "");

    void NewBackgroundFile(const std::string &name, const std::string &nice_name = "");

    void NewBackgroundFile(const std::string &name, const float crosssection, const std::string &nice_name = "");

    File get_file(const std::string &name, const std::string &nice_name = "") const;

    File get_file(const std::string &name, const float crosssection, const std::string &nice_name = "") const;

    std::string FileName(const std::string &name) const;

    std::string TreeName(const std::string &name) const;

    virtual int PassPreCut(const Event &);

    PreCuts &pre_cuts();

    virtual const Tagger &tagger() const = 0;

    virtual Tagger &tagger() = 0;

    bool Missing(const std::string &name) const;

private:

    std::string PathName(const std::string &file_name) const;

    void RunTagger(analysis::Stage stage);

    void RunFactory();

    void RunSignificance();

    void RunEfficiency();

    PreCuts pre_cuts_;

//     Configuration configuration_;

    std::vector<File> files_;

};

}




