#pragma once

#include "File.hh"
// #include "Configuration.hh"
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

//     void SetConfig(const Configuration &configuration);

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

    void RunPlots();

protected:

    void ClearFiles();

    std::vector<analysis::File> files(const Tag tag);

    std::string ExportName(const Stage stage, const Tag tag) const;

    void PrepareFiles();

    virtual void SetFiles(const Tag tag) = 0;

    exroot::TreeWriter TreeWriter(TFile &export_file, const std::string &export_tree_name, Stage stage);

    virtual std::string ProjectName() const;

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual long EventNumberMax() const;

    virtual std::string ProcessName() const;

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

    virtual std::string FilePath() const;

    void NewFile(const Tag tag, const std::string &name, const std::string &nice_name = "");

    void NewFile(const Tag tag, const std::string &name, const float crosssection, const std::string &nice_name = "");

    analysis::File File(const std::string &name, const float crosssection, const std::string &nice_name = "") const;

    analysis::File File(const std::string &name, const std::string &nice_name = "") const;

    std::string FileName(const std::string &name) const;

    std::string TreeName(const std::string &name) const;

    virtual int PassPreCut(const Event &) const;

    PreCuts &pre_cuts();

    virtual const Tagger &tagger() const = 0;

    virtual Tagger &tagger() = 0;

private:

    std::string FileSuffix() const;

    void NewSignalFile(const std::string &name, const std::string &nice_name = "");

    void NewSignalFile(const std::string &name, const float crosssection, const std::string &nice_name = "");

    void NewBackgroundFile(const std::string &name, const std::string &nice_name = "");

    void NewBackgroundFile(const std::string &name, const float crosssection, const std::string &nice_name = "");

    bool Missing(const std::string &name) const;

    virtual void AnalysisLoop(const Stage stage) = 0;

    std::string PathName(const std::string &file_name, const std::string &suffix = ".root") const;

    void RunTagger(Stage stage);

    void RunFactory();

    void RunSignificance();

    void RunEfficiency();

    PreCuts pre_cuts_;

//     Configuration configuration_;

    std::vector<analysis::File> files_;

};

}




