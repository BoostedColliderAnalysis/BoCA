/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <thread>

#include "Third.hh"
#include "AnalysisBase.hh"
#include "Event.hh"

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

public:

    /**
     * @brief Main analysis loop which has to be called by main.cpp
     *
     */
    void AnalysisLoop(Stage stage)override {
        for (auto const & tag : std::vector<Tag> {Tag::signal, Tag::background}) FirstLoop({stage, tag});
    }

protected:

    template<typename Class>
    bool TaggerIs() const {
        return typeid(tagger_).hash_code() == typeid(Class).hash_code();
    }

private:

    void FirstLoop(Phase first) {
        TFile export_file(Tagger().ExportFileName(first.Stage(), first.Tag()).c_str(), "Recreate");
        ClearFiles();
        SetFiles(first.Tag(), first.Stage());
        for (auto & file : this->Files(first.Tag())) SecondLoop( {first, file, export_file});
    }

    /**
     * @brief Analysis performed on each file
     *
     */
    void SecondLoop(boca::Files files) {
        BranchWriter<Tagger_> branch_writer(files, tagger_);
        bool do_threading = false;
        if (do_threading) {
            std::mutex branch_writer_mutex;
            std::vector<std::thread> threads;
//         int cores = std::thread::hardware_concurrency(); // breaks in the tree reader, find  a cheap way to store the position of the data
            int cores = 1;
            for (auto core : IntegerRange(cores)) {
                threads.emplace_back(std::thread([&, core, cores] {
                    branch_writer_mutex.lock();
                    Third<Tagger_> third(branch_writer, core, cores, TrainNumberMax());
                    branch_writer_mutex.unlock();
                    ReadEvents(third);
                }));
            }
            for (auto & thread : threads) thread.join();
        } else {
            int cores = 1;
            int core = 0;
            Third<Tagger_> third(branch_writer, core, cores, TrainNumberMax());
            ReadEvents(third);
        }
        branch_writer.Write();
    }

    void ReadEvents(Third<Tagger_>& third) {
        while (third.BranchWriter().KeepGoing(EventNumberMax(third.Files().Phase().Stage())) && third.KeepGoing()) third.Increment(ReadEvent(third));
    }

    int ReadEvent(Third<Tagger_>& third) const {
        if (!third.ReadEntry()) return 0;
        Event event(third.TreeReader(), third.Files().Import().Source());
        if (!PassPreCut(event, third.Files().Phase().Tag())) return 0;
        int number = Switch(event, third);
//         ERROR(number);
        third.SaveEntry();
        return number;
    }

    int Switch(Event const& event, Third<Tagger_>& third) const {
        switch (third.Files().Phase().Stage()) {
        case Stage::trainer : return third.Tagger().Train(event, PreCuts(), third.Files().Phase().Tag());
        case Stage::reader : return third.Reader().Bdt(event, PreCuts());
        default : return 0;
        }
    }

    Tagger_& Tagger()override {
        return tagger_;
    }

    Tagger_ const& Tagger() const override {
        return tagger_;
    }

    Tagger_ tagger_;

};

}
