/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <mutex>

#include "boca/io/FileWriter.hh"
#include "boca/multivariant/Reader.hh"
#include "boca/branch/Info.hh"
#include "boca/File.hh"
#include "boca/generic/Debug.hh"

namespace boca
{

template<typename Tagger_>
class BranchWriter
{

public:

    BranchWriter(boca::Phase& phase, boca::File& file, boca::FileWriter& file_writer, Tagger_& tagger) :
        tagger_(tagger),
        reader_(phase.Stage()),
        import_file_(file),
        phase_(phase),
        object_sum_(0),
        event_sum_(0) {
        tree_writer_ = &file_writer.NewTree(Import().Title());
        switch (Phase().Stage()) {
        case Stage::trainer : tagger_.NewBranch(TreeWriter(), Phase().Stage());
            break;
        case Stage::reader : reader_.NewBranch(TreeWriter(), Phase().Stage());
            break;
        }
        tree_branch_ = &(tree_writer_->NewBranch<branch::Info>(tagger_.WeightBranchName()));
    }

    ~BranchWriter() {
        std::cout << "PreCut ratio: " << RoundToDigits(static_cast<double>(object_sum_.load()) / event_sum_.load()) << std::endl;
        if (object_sum_.load()) TreeWriter().Write();
    }

    void SafeEntry() {
        auto info_branch = branch::Info{Import()};
        info_branch.SetEventNumber(event_sum_.load());
        std::lock_guard<std::mutex> lock(write_mutex);
        TreeBranch().AddEntry(info_branch);
        TreeWriter().Fill();
    }
    void Increment(int number) {
        object_sum_ += number;
//         if (number > 0)
        ++event_sum_;
        if (debug_) Debug("event: ", event_sum_.load(), "object: ", object_sum_.load());
    }

    boca::Reader<Tagger_> Reader() const {
        return reader_;
    }

    Tagger_ Tagger() const {
        return tagger_;
    }

    bool KeepGoing(std::function<long(Stage)> const& event_number_max) const {
        return object_sum_.load() < event_number_max(Phase().Stage());
    }

    boca::Phase Phase() const {
        return phase_;
    }

    boca::File Import() const {
        return import_file_;
    }

private:

    boca::TreeBranch& TreeBranch() {
        return *tree_branch_;
    }

    boca::TreeWriter& TreeWriter() {
        return *tree_writer_;
    }

    Tagger_& tagger_;

    boca::Reader<Tagger_> reader_;

    boca::TreeBranch* tree_branch_;

    boca::TreeWriter* tree_writer_;

    File& import_file_;

    boca::Phase phase_;

    std::mutex write_mutex;

    std::atomic<long> object_sum_;

    std::atomic<long> event_sum_;

    bool debug_ = false;

};

}


