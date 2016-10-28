/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Flag.hh"
#include "boca/multivariant/Stage.hh"
#include "boca/PreCuts.hh"
#include "boca/FileInfo.hh"
#include "boca/Names.hh"
#include "boca/Tag.hh"

namespace boca
{
class Phase;
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

    Base(Base const&) = default;

    Base(Base &&) = default;

    Base &operator=(Base const&) & = default;

    Base &operator=(Base &&) & = default;

protected:

    ~Base() {}

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

    void ClearFiles();

    std::vector<boca::FileInfo> Files(Tag tag);

    void PrepareFiles(Stage stage);

    virtual int BackgroundFileNumber() const;

    void AddSignal(std::string const& file_name, latex::String const& latex_name = "",  boca::Crosssection const& crosssection = 0_b, boca::Mass const& mass = 0_eV, std::string const& path = "");
//
    void AddBackground(std::string const& file_name, latex::String const& latex_name = "",  boca::Crosssection const& crosssection = 0_b, boca::Mass const& mass = 0_eV, std::string const& path = "");

    void AddFile(Tag tag, boca::FileInfo const& file);

    void AddSignal(boca::FileInfo const& file);

    void AddBackground(boca::FileInfo const& file);

    boca::PreCuts PreCuts() const;

    boca::PreCuts& PreCuts();

    void PrintGeneratorLevel(Event const& event, bool signature = false) const;

private:

    virtual tagger::Base& Tagger() = 0;

    virtual void TagLoop(Phase phase) = 0;

    /**
     * @brief Main analysis loop which has to be called by main.cpp
     *
     */
    void AnalysisLoop(Stage stage);

    boca::PreCuts pre_cuts_;

    std::vector<boca::FileInfo> files_;

};

}

}
