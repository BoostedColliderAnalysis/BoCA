#pragma once

#include "File.hh"
#include "Configuration.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "AnalysisBase.hh"

namespace analysis
{

/**
 * @brief Base for all analyses
 *
 */
class Analysis : public AnalysisBase
{

public:

    /**
     * @brief Constructor calls the other preparing functions
     *
     */
    Analysis(Tagger &tagger);

    void AnalysisLoop(const Stage stage);

protected:

    std::string ExportName(const Stage stage, const Tag tag) const;

    void PrepareFiles();

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

    int BackgroundFileNumber() const;

    virtual int PassPreCut(const Event &);

    int RunAnalysis(const Event &event, const Stage stage, const Tag tag);

    Tagger &tagger();

    const Tagger &tagger() const;

private:

    std::string PathName(const std::string &file_name) const;

    Tagger &tagger_;

    Reader reader_;

};

}




