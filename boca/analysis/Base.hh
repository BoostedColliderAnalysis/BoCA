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

/**
* @brief Analysis Classes
*
*/
namespace analysis
{

// global variabel; FIXME remove again; is necesarry due to bug in root
extern std::string _name_;

/**
 * @brief Base for all analyses.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015-2016 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class Base
{

public:

    Base();

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

    virtual void SetFiles(Phase const& phase) = 0;

    virtual tagger::Base const& Tagger() const = 0;

    virtual std::string Name() const;

    void RunTagger(Stage stage);

    void RunTrainer();

    virtual bool PassPreCut(Event const&) const;

    virtual long TrainNumberMax() const;

    virtual long ReadNumberMax() const;

    virtual long EventNumberMax(Stage stage) const;

    virtual std::string FilePath() const;

    void ClearFiles();

    std::vector<boca::File> Files(Tag tag);

    void PrepareFiles(Stage stage);

    virtual int BackgroundFileNumber() const;

    void NewFile(Tag tag, std::vector<std::string> const& names, latex::String const& latex_name = "");

    void NewFile(boca::Tag tag, std::vector<std::string> const& names, boca::Crosssection const& crosssection, const boca::Names& latex_name, boca::Mass const& mass = massless);

    void NewFile(boca::Tag tag, std::vector<std::string> const& names, boca::Crosssection const& crosssection, latex::String const& latex_name = "", boca::Mass const& mass = massless);

    boca::File File(std::vector<std::string> const& names, boca::Crosssection const& crosssection, latex::String const& latex_name, boca::Mass const& mass) const;

    boca::File File(std::vector<std::string> const& names, latex::String const& latex_name = "") const;

    boca::File File(std::vector<std::string> const& names, const boca::Names& latex_name, boca::Crosssection const& crosssection, boca::Mass const& mass) const;

    void NewFile(Tag tag, std::string const& name, latex::String const& latex_name = "");

    void NewFile(Tag tag, const std::string& name, boca::Crosssection const& crosssection, latex::String const& latex_name = "", boca::Mass const& mass = massless);

    void NewFile(Tag tag, const std::string& name, boca::Crosssection const& crosssection, const boca::Names& latex_name, boca::Mass const& mass);

    void AddSignal(std::string const& file_name, latex::String const& latex_name = "",  boca::Crosssection const& crosssection = 0_b);
//
    void AddBackground(std::string const& file_name, latex::String const& latex_name = "",  boca::Crosssection const& crosssection = 0_b);

    void AddFile(Tag tag, boca::File const& file);

    void AddSignal(boca::File const& file);

    void AddBackground(boca::File const& file);

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

}
