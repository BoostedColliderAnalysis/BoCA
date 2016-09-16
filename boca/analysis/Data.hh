/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/analysis/Files.hh"

namespace boca
{

namespace analysis
{

template<typename Tagger_>
class Data
{
public:

    Data(boca::analysis::Files<Tagger_>& files, long object_sum_max, int core_number, int core_sum) :
        files_(files),
        reader_(files.Reader()),
        tagger_(files.Tagger()),
        tree_reader_(Files().Import().Paths(), Files().Import().TreeName()) {
        event_number_ = FirstEntry(object_sum_max, core_number);
        core_sum_ = core_sum;
    }

    void ReadEvents(PreCuts const& pre_cuts, std::function<long(Stage)> const& event_number_max, std::function<bool(boca::Event const&)> const& pass_pre_cut) {
        while (KeepGoing(event_number_max)) ReadEvent(pre_cuts, pass_pre_cut);
    }

private:

    long FirstEntry(long object_sum_max, long core_number)  {
        auto entry = core_number;
        if (Files().Phase().Stage() == Stage::reader) entry = std::min(GetEntries(), object_sum_max + core_number);  // TODO fix corner cases
        return entry;
    }

    void ReadEvent(PreCuts const& pre_cuts, std::function<bool(boca::Event const&)> const& pass_pre_cut) {
        if (!ReadEntry()) return;
        switch (Settings::Source()) {
        case Source::snowmass :
        case Source::delphes : return ReadDelphesEvent(pre_cuts, pass_pre_cut);
        case Source::pgs : ;
        case Source::parton : return ReadExRootEvent(pre_cuts, pass_pre_cut);
        case Source::tagger : return;
        }
    }

    void ReadDelphesEvent(PreCuts const& pre_cuts, std::function<bool(boca::Event const&)> const& pass_pre_cut) {
        auto event = TreeReader().DelphesEvent();
        if (pass_pre_cut(event)) return SaveEntry(Switch(event, pre_cuts));
        Increment(0);
    }

    void ReadExRootEvent(PreCuts const& pre_cuts, std::function<bool(boca::Event const&)> const& pass_pre_cut) {
        auto event = TreeReader().ExRootEvent();
        if (pass_pre_cut(event)) return SaveEntry(Switch(event, pre_cuts));
        Increment(0);
    }

    void SaveEntry(int number) {
        Increment(number);
        if (number == 0) return;
        Files().SafeEntry();
    }

    int Switch(boca::Event const& event, PreCuts const& pre_cuts) {
        switch (Files().Phase().Stage()) {
        case Stage::trainer : return Tagger().Train(event, pre_cuts, Files().Phase().Tag());
        case Stage::reader : return Reader().Bdt(event, pre_cuts);
        default : return 0;
        }
    }

    bool ReadEntry() {
        return TreeReader().ReadEntry(EventNumber());
    }

    long GetEntries() const {
        return TreeReader().GetEntries();
    }

    void Increment(int number) {
        EventNumber() += core_sum_;
//         if (number > 0)
        Files().Increment(number);
    }

    bool KeepGoing(std::function<long(Stage)> const& event_number_max) const {
        return EventNumber() < GetEntries() && Files().KeepGoing(event_number_max);
    }

    boca::analysis::Files<Tagger_>& Files() {
        return files_;
    }

    boca::TreeReader& TreeReader() {
        return tree_reader_;
    }

    boca::TreeReader const& TreeReader() const {
        return tree_reader_;
    }

    long& EventNumber() {
        return event_number_;
    }

    long EventNumber() const {
        return event_number_;
    }

    Tagger_& Tagger() {
        return tagger_;
    }

    boca::analysis::Files<Tagger_> const& Files() const {
        return files_;
    }

    boca::Reader<Tagger_>& Reader() {
        return reader_;
    }

    boca::analysis::Files<Tagger_>& files_;

    boca::Reader<Tagger_> reader_;

    Tagger_ tagger_;

    boca::TreeReader tree_reader_;

    long event_number_;

    int core_sum_;

};

}

}
