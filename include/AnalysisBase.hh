#pragma once

#include "Tagger.hh"
#include "Identification.hh"
#include "PreCuts.hh"

class TFile;

namespace analysis {

class File;

/**
 * @brief Base for all analyses
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

    std::vector<analysis::File> files(Tag tag);

    void PrepareFiles();

    virtual void SetFiles(Tag tag) = 0;

    exroot::TreeWriter TreeWriter(TFile& export_file, const std::string& export_tree_name, Stage stage);

    virtual std::string ProjectName() const;

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual long EventNumberMax() const;
    
    virtual long ReaderNumberMax() const {
      return EventNumberMax();
    }

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

    void NewFile(analysis::Tag tag, const analysis::Strings& names, const std::string& nice_name = "");

    void NewFile(analysis::Tag tag, const analysis::Strings& names, float crosssection, const std::string& nice_name = "", int mass = 0);

    analysis::File File(const Strings& names, float crosssection, const std::string& nice_name = "", int mass = 0) const;

    analysis::File File(const Strings& names, const std::string& nice_name = "") const;

    void NewFile(analysis::Tag tag, const std::string& names, const std::string& nice_name = "");

    void NewFile(analysis::Tag tag, const std::string& names, float crosssection, const std::string& nice_name = "", int mass = 0);

    std::string FileName(const std::string& name) const;

    std::string TreeName(const std::string& name) const;

    virtual int PassPreCut(const Event&, Tag tag) const = 0;

    const PreCuts& pre_cuts() const;

    PreCuts& pre_cuts();

    virtual const Tagger& tagger() const = 0;

private:

    virtual Tagger& tagger() = 0;

    std::string FileSuffix() const;

    virtual void AnalysisLoop(Stage stage) = 0;

    void RunTagger(const analysis::Stage stage);

    void RunTrainer();

    void RunSignificance();

    void RunEfficiency();

    PreCuts pre_cuts_;

//     Configuration configuration_;

    std::vector<analysis::File> files_;

};

}




