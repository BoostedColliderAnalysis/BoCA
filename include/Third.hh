/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "BranchWriter.hh"

namespace boca
{

template<typename Tagger_>
class Third
{
public:
    Third(boca::BranchWriter<Tagger_>& branch_writer, int core_number, int core_sum, int object_sum_max) :
        branch_writer_(branch_writer),
        reader_(branch_writer.Reader()),
        tagger_(branch_writer.Tagger()),
        tree_reader_(Files().Import().Paths(), Files().Import().TreeName()),
        info_branch_(Files().Import()) {
        event_number_ = FirstEntry(object_sum_max, core_number);
        core_sum_ = core_sum;
    }

    long FirstEntry(long object_sum_max, int core_number)  {
        long entry = core_number;
        if (Files().Phase().Stage() == Stage::reader) entry = std::min(GetEntries(), object_sum_max + core_number);  // TODO fix corner cases
        return entry;
    }

    long GetEntries() {
        return TreeReader().GetEntries();
    }

    void PreCutPassed() {}

    void SaveEntry(int number) {
        Increment(number);
        if(number == 0) return;
        InfoBranch().SetEventNumber(BranchWriter().EventSum());
        BranchWriter().TreeBranch().AddEntry(InfoBranch());
        BranchWriter().TreeWriter().Fill();
    }

    bool ReadEntry() {
        return TreeReader().ReadEntry(EventNumber());
    }

    void Increment(int number) {
//       std::cout << "Increment: " << number << std::endl;
        EventNumber() += core_sum_;
        if(number > 0) BranchWriter().Increment(number);
    }

    bool KeepGoing(int number) {
        return EventNumber() < GetEntries() && branch_writer_.KeepGoing(number);
    }

    boca::TreeReader& TreeReader() {
        return tree_reader_;
    }

    boca::InfoBranch& InfoBranch() {
        return info_branch_;
    }

    long& EventNumber() {
        return event_number_;
    }

    Tagger_& Tagger() {
        return tagger_;
    }

    boca::Files& Files()  {
        return BranchWriter().Files();
    }

    boca::BranchWriter<Tagger_>& BranchWriter() {
        return branch_writer_;
    }

    boca::Reader<Tagger_>& Reader() {
        return reader_;
    }

private:

    boca::BranchWriter<Tagger_>& branch_writer_;

    boca::Reader<Tagger_> reader_;

    Tagger_ tagger_;

    boca::TreeReader tree_reader_;

    boca::InfoBranch info_branch_;

    long event_number_;

    int core_sum_;
};

}
