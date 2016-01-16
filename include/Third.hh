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
    Third(boca::BranchWriter<Tagger_>& branch_writer, int core_number, int core_sum, int object_sum_max)
        : branch_writer_(branch_writer)
        , reader_(branch_writer.Reader())
        , tagger_(branch_writer.Tagger())
        , tree_reader_(Files().Import().Paths(), Files().Import().TreeName()) {
        event_number_ = FirstEntry(object_sum_max, core_number);
        core_sum_ = core_sum;
        info_branch_ = FillInfoBranch(Files().Import());
    }

    boca::InfoBranch FillInfoBranch(boca::File const& file)  {
        boca::InfoBranch info_branch;
        info_branch.SetCrosssection(file.Crosssection());
        info_branch.SetCrosssectionError(file.CrosssectionError());
        info_branch.SetMass(file.Mass());
        info_branch.SetNames(file.Names());
        return info_branch;
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

    void SaveEntry() {
        InfoBranch().SetEventNumber(BranchWriter().EventSum());
        std::lock_guard<std::mutex> tagger_guard(tagger_.mutex_);
        static_cast<boca::InfoBranch&>(*BranchWriter().TreeBranch().NewEntry()) = InfoBranch();
        BranchWriter().TreeWriter().Fill();
        BranchWriter().TreeWriter().Clear();
    }

    bool ReadEntry() {
        return TreeReader().ReadEntry(EventNumber());
    }

    void Increment(int number) {
        BranchWriter().Increment(number);
        EventNumber() += core_sum_;
    }

    bool KeepGoing() {
        return EventNumber() < GetEntries();
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
