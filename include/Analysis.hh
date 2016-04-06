/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <thread>

#include "generic/Types.hh"
#include "io/Io.hh"
#include "plotting/Plotting.hh"
#include "Third.hh"
#include "Event.hh"
#include "AnalysisBase.hh"

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

    void TagLoop(Phase phase) {
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
        bool do_threading = true;
        if (do_threading) {
            std::vector<std::thread> threads;
//             int cores = std::thread::hardware_concurrency(); // breaks in the tree reader, find  a cheap way to store the position of the data
            int cores = 1;
            for (auto core : IntegerRange(cores)) threads.emplace_back(Thread(branch_writer, cores, core));
            for (auto & thread : threads) thread.join();
        } else {
            int cores = 1;
            int core = 0;
            Third<Tagger_> third(branch_writer, core, cores, TrainNumberMax());
            third.ReadEvents(PreCuts(), EventNumberMax(third.BranchWriter().Phase().Stage()), [&](Event const & event, Tag tag) {
                return PassPreCut(event, tag);
            });
        }
    }

    auto Thread(BranchWriter<Tagger_> & branch_writer, int cores, int core) {
        return std::thread([&, core, cores] {
            Third<Tagger_> third(branch_writer, core, cores, TrainNumberMax());
            third.ReadEvents(PreCuts(), EventNumberMax(third.BranchWriter().Phase().Stage()), [&](Event const & event, Tag tag) {
              return PassPreCut(event, tag);
            });
        });
    }

    void RunSignificance() {
        if (Exists(Tagger().ExportFileName())) return;
        PrepareFiles(Stage::reader);
        Plotting<Tagger_> plotting(Tagger());
        plotting.OptimalCuts();
    }

    void RunEfficiency() {
        if (Exists(Tagger().ExportFileName())) return;
        PrepareFiles(Stage::reader);
        Plotting<Tagger_> plotting(Tagger());
        plotting.TaggingEfficiency();
    }

    void RunPlots() {
        if (Exists(Tagger().ExportFolderName())) return;
        Plotting<Tagger_> plotting(Tagger());
        PrepareFiles(Stage::trainer);
        plotting.RunPlots(Stage::trainer);
        PrepareFiles(Stage::reader);
        plotting.RunPlots(Stage::reader);
        //     if (Exists(Tagger().ExportFileName())) std::remove(Tagger().ExportFileName().c_str());
    }

    void RunPlotHist() {
        //   if (Exists(Tagger().ExportFolderName())) return;
        Plotting<Tagger_> plotting(Tagger());
        PrepareFiles(Stage::trainer);
        plotting.RunPlotHist();
    }

    void RunCut() {
        RunTagger(Stage::trainer);
        RunTrainer();
        RunTagger(Stage::reader);
        PrepareFiles(Stage::reader);
        Plotting<Tagger_> plotting(Tagger());
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
