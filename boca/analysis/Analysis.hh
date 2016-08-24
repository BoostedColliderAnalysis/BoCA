/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <thread>

#include "boca/generic/Types.hh"
#include "boca/io/Io.hh"
#include "boca/plotting/Plotting.hh"
#include "boca/analysis/Third.hh"
#include "boca/analysis/AnalysisBase.hh"
#include "boca/Event.hh"

namespace boca
{

/**
 * @brief provides main analysis loops and logic.
 * @details This class has to be subclassed for each analysis.
 * The subclasses have to be instantiated with a Tagger as template argument.
 * Subclasses should be templated classes.
 * @author Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
template<typename Tagger_>
class Analysis : public AnalysisBase
{

protected:

    template<typename Class_>
    bool TaggerIs() const {
        return typeid(Tagger_).hash_code() == typeid(Class_).hash_code();
    }

private:

    void TagLoop(Phase phase) override {
        FileWriter file_writer(Tagger().ExportFileName(phase));
        ClearFiles();
        SetFiles(phase.Tag(), phase.Stage());
        for (auto & file : this->Files(phase.Tag())) FileLoop( {phase, file, file_writer, tagger_});
    }

    /**
     * @brief Analysis performed on each file
     *
     */
    void FileLoop(BranchWriter<Tagger_> branch_writer) {
        auto threading = true;
        if (threading) {
            auto threads = std::vector<std::thread>{};
            // int cores = std::thread::hardware_concurrency();
            auto cores = 1;
//         for (auto core : IntegerRange(cores)) // FIXME why is this not the same as next line
            for (auto core = 0; core < cores; ++core)
                threads.emplace_back([&] {
                Thread({branch_writer, TrainNumberMax(), cores, core});
            });
            for (auto & thread : threads) thread.join();
        } else Thread( {branch_writer, TrainNumberMax(), 1, 0});
    }

    void Thread(Third<Tagger_> third) {
        third.ReadEvents(PreCuts(), [&](Stage stage) {
            return EventNumberMax(stage);
        }, [&](Event const & event, Tag tag) {
            return PassPreCut(event, tag);
        });
    }

    void RunSignificance() override {
        if (Exists(Tagger().ExportFileName())) return;
        PrepareFiles(Stage::reader);
        auto plotting = Plotting<Tagger_>{Tagger()};
        plotting.OptimalCuts();
    }

    void RunEfficiency() override {
        if (Exists(Tagger().ExportFileName())) return;
        PrepareFiles(Stage::reader);
        auto plotting = Plotting<Tagger_>{Tagger()};
        plotting.TaggingEfficiency();
    }

    void RunPlots() override {
        if (Exists(Tagger().ExportFolderName())) return;
        auto plotting = Plotting<Tagger_>{Tagger()};
        PrepareFiles(Stage::trainer);
        plotting.RunPlots(Stage::trainer);
        PrepareFiles(Stage::reader);
        plotting.RunPlots(Stage::reader);
        //     if (Exists(Tagger().ExportFileName())) std::remove(Tagger().ExportFileName().c_str());
    }

    void RunPlotHist() override {
        //   if (Exists(Tagger().ExportFolderName())) return;
        auto plotting = Plotting<Tagger_>{Tagger()};
        PrepareFiles(Stage::trainer);
        plotting.RunPlotHist();
    }

    void RunCut() override {
        RunTagger(Stage::trainer);
        RunTrainer();
        RunTagger(Stage::reader);
        PrepareFiles(Stage::reader);
        auto plotting = Plotting<Tagger_>{Tagger()};
        plotting.OptimalCuts();
    }

    Tagger_& Tagger() override {
        return tagger_;
    }

    Tagger_ const& Tagger() const override {
        return tagger_;
    }

    Tagger_ tagger_;

};

}
