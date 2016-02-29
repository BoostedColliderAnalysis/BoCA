/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "PreCuts.hh"
#include "Phase.hh"
#include "Flag.hh"

namespace boca
{

class File;
class Tagger;
class Event;

enum class Output
{
    none = 0,
    fast = 1 << 0,
    normal = 1 << 1,
    significance = 1 << 2,
    efficiency = 1 << 3,
    plot = 1 << 4,
    cut = 1 << 5,
    plot_hist = 1 << 6
};

std::string Name(Output output);

template<>
struct Flag<Output> {
    static const bool enable = true;
};

extern std::string _analysis_name_; //< global variabel; FIXME remove again; is necesarry due to bug in root

/**
 * @brief Base for all analyses.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015-2016 Jan Hajer
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

    void RunFast();

    void RunNormal();

    void RunFullSignificance();

    void RunFullEfficiency();

    void RunPlots();

    void RunPlotHist();

    void RunCut();

    virtual void SetFiles(Tag tag, Stage) = 0;

    virtual int PassPreCut(Event const&, Tag tag) const = 0;

    virtual boca::Tagger const& Tagger() const = 0;

    virtual std::string AnalysisName() const = 0;

    virtual long TrainNumberMax() const;

    virtual long ReadNumberMax() const;

    virtual long EventNumberMax(Stage stage) const;

    virtual std::string FilePath() const;

    void ClearFiles();

    std::vector<boca::File> Files(Tag tag);

    void PrepareFiles(Stage stage);

    int BackgroundFileNumber() const;

    void NewFile(boca::Tag tag, std::vector<std::string> const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, std::vector<std::string> const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless);

    boca::File File(std::vector<std::string> const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless) const;

    boca::File File(std::vector<std::string> const& names, std::string const& nice_name = "") const;

    void NewFile(boca::Tag tag, std::string const& names, std::string const& nice_name = "");

    void NewFile(boca::Tag tag, std::string const& names, Crosssection crosssection, std::string const& nice_name = "", boca::Mass mass = massless);

    std::string TreeName(std::string const& name) const;

    boca::PreCuts const& PreCuts() const;

    boca::PreCuts& PreCuts();

    void PrintGeneratorLevel(Event const& event, bool signature = false) const;

    std::string WorkingPath() const;

private:

    virtual boca::Tagger& Tagger() = 0;

    virtual void AnalysisLoop(Stage stage) = 0;

    std::string FileSuffix() const;

    void RunTagger(Stage stage);

    void RunTrainer();

    void RunSignificance();

    void RunEfficiency();

    boca::PreCuts pre_cuts_;

    std::vector<boca::File> files_;

};

}
