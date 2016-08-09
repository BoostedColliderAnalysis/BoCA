/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multivariant/Stage.hh"
#include "boca/PreCuts.hh"
#include "boca/Names.hh"

namespace boca
{

class Phase;
class File;
class Event;
namespace tagger{
class Base;
}

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

    virtual void RunPlots() = 0;

    virtual void RunPlotHist() = 0;

    virtual void RunCut() = 0;

    virtual void RunSignificance() = 0;

    virtual void RunEfficiency() = 0;

    virtual void SetFiles(Tag tag, Stage) = 0;

    virtual tagger::Base const& Tagger() const = 0;

    virtual std::string AnalysisName() const = 0;

    void RunTagger(Stage stage);

    void RunTrainer();

    virtual int PassPreCut(Event const&, Tag tag) const;

    virtual long TrainNumberMax() const;

    virtual long ReadNumberMax() const;

    virtual long EventNumberMax(Stage stage) const;

    virtual std::string FilePath() const;

    void ClearFiles();

    std::vector<boca::File> Files(Tag tag);

    void PrepareFiles(Stage stage);

    virtual int BackgroundFileNumber() const;

    void NewFile(Tag tag, std::vector<std::string> const& names, latex::String const& latex_name = "");

    void NewFile(boca::Tag tag, const std::vector< std::string >& names, const boca::Crosssection& crosssection, const boca::Names& latex_name, boca::Mass const& mass = massless);

    void NewFile(boca::Tag tag, const std::vector< std::string >& names, const boca::Crosssection& crosssection, latex::String const& latex_name = "", boca::Mass const& mass = massless);

    boca::File File(const std::vector< std::string >& names, const boca::Crosssection& crosssection, latex::String const& latex_name, const boca::Mass& mass) const;

    boca::File File(std::vector<std::string> const& names, latex::String const& latex_name = "") const;

    boca::File File(const std::vector< std::string >& names, const boca::Names& latex_name, const boca::Crosssection& crosssection, const boca::Mass& mass) const;

    void NewFile(Tag tag, std::string const& names, latex::String const& latex_name = "");

    void NewFile(boca::Tag tag, const std::string& name, const boca::Crosssection& crosssection, latex::String const& latex_name = "", boca::Mass const& mass = massless);

    void NewFile(boca::Tag tag, const std::string& name, const boca::Crosssection& crosssection, const boca::Names& latex_name, const boca::Mass& mass);

    std::string TreeName(std::string const& name) const;

    boca::PreCuts const& PreCuts() const;

    boca::PreCuts& PreCuts();

    void PrintGeneratorLevel(Event const& event, bool signature = false) const;

    std::string WorkingPath() const;

private:

    virtual tagger::Base& Tagger() = 0;

    virtual void TagLoop(Phase phase) = 0;

    /**
     * @brief Main analysis loop which has to be called by main.cpp
     *
     */
    void AnalysisLoop(Stage stage);


    std::string FileSuffix() const;

    boca::PreCuts pre_cuts_;

    std::vector<boca::File> files_;

};

}
