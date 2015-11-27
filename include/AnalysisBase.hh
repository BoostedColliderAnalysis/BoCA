/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Tagger.hh"
#include "PreCuts.hh"
#include "File.hh"

namespace boca
{

  class File;

  enum class Output
  {
    fast = 1 << 0,
    normal = 1 << 1,
    significance = 1 << 2,
    efficiency = 1 << 3,
    plot = 1 << 4,
    cut = 1 << 5
  };

  template<>
  struct Flag<Output> {
    static const bool enable = true;
  };

/**
 * @brief Base for all analyses.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class AnalysisBase
{

public:

    AnalysisBase();

    void Run(Output output);

protected:

    void Initialize();

//     void SetConfig(const Configuration &configuration);

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

    void RunPlots();

    void RunCut();

    virtual void SetFiles(Tag tag, Stage) = 0;

    virtual int PassPreCut(Event const&, Tag tag) const = 0;

    virtual Tagger const& tagger() const = 0;


    void ClearFiles();

    std::vector<boca::File> Files(Tag tag);

    void PrepareFiles(Stage stage);

    virtual std::string AnalysisName() const = 0;

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    virtual long TrainNumberMax() const;

    virtual long ReadNumberMax() const;

    virtual long EventNumberMax(Stage stage) const;

    boca::Mass Mass() const;

    Momentum PreCut() const;

    //      int TrainNumberMax() const {
    //         return configuration_.TrainNumberMax();
    //     };

    int BackgroundFileNumber() const;

    //      ColliderType collider_type() const {
    //         return configuration_.collider_type();
    //     }

    virtual std::string FilePath() const;

    void NewFile(boca::Tag tag, boca::Strings const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, boca::Strings const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless);

    boca::File File(Strings const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless) const;

    boca::File File(Strings const& names, std::string const& nice_name = "") const;

    void NewFile(boca::Tag tag, std::string const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, std::string const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless);

//     std::string FileName(std::string const& name) const = 0;

    std::string TreeName(std::string const& name) const;

    PreCuts const& pre_cuts() const;

    PreCuts& pre_cuts();

    std::string working_path_;

    void PrintGeneratorLevel(Event const& event, bool signature = false) const;

private:

    virtual Tagger& tagger() = 0;

    virtual void AnalysisLoop(Stage stage) = 0;

    std::string FileSuffix() const;

    void RunTagger(Stage stage);

    void RunTrainer();

    void RunSignificance();

    void RunEfficiency();

    PreCuts pre_cuts_;

//     Configuration configuration_;

    std::vector<boca::File> files_;

    std::string WorkingPath();

};

// void Run(AnalysisBase & analysis, Output run);

}
