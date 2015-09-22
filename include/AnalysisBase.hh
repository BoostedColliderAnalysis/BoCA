/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Tagger.hh"
#include "Identification.hh"
#include "PreCuts.hh"
#include "Units.hh"

class TFile;

namespace boca {

class File;

/**
 * @brief Base for all analyses.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class AnalysisBase {

public:

  void Initialize();

//     void SetConfig(const Configuration &configuration);

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

    void RunPlots();

protected:

    void ClearFiles();

    std::vector<boca::File> files(Tag tag);

    void PrepareFiles();

    virtual void SetFiles(Tag tag) = 0;

    exroot::TreeWriter TreeWriter(TFile& export_file, std::string const& export_tree_name, Stage stage);

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

    void NewFile(boca::Tag tag, boca::Strings const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, boca::Strings const& names, Crosssection crosssection, std::string const& nice_name = "", int mass = 0);

    boca::File File(Strings const& names, Crosssection crosssection, std::string const& nice_name = "", int mass = 0) const;

    boca::File File(Strings const& names, std::string const& nice_name = "") const;

    void NewFile(boca::Tag tag, std::string const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, std::string const& names, Crosssection crosssection, std::string const& nice_name = "", int mass = 0);

    std::string FileName(std::string const& name) const;

    std::string TreeName(std::string const& name) const;

    virtual int PassPreCut(Event const&, Tag tag) const = 0;

    PreCuts const& pre_cuts() const;

    PreCuts& pre_cuts();

    virtual Tagger const& tagger() const = 0;

    std::string working_path_;

private:

    virtual Tagger& tagger() = 0;

    std::string FileSuffix() const;

    virtual void AnalysisLoop(Stage stage) = 0;

    void RunTagger(Stage stage);

    void RunTrainer();

    void RunSignificance();

    void RunEfficiency();

    PreCuts pre_cuts_;

//     Configuration configuration_;

    std::vector<boca::File> files_;

    std::string WorkingPath();

};

}




