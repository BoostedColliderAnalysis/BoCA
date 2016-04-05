/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "io/TreeWriter.hh"
#include "Reader.hh"
#include "Branches.hh"
#include "Files.hh"

namespace boca
{

template<typename Tagger_>
class BranchWriter
{

public:
    BranchWriter(boca::Files& files, Tagger_& tagger) :
        files_(files),
        tagger_(tagger),
        reader_(files.Phase().Stage()),
        tree_writer_(files.Export(), files.Import().Title()) {
        Initialize();
    }

    void Initialize() {
        switch (Files().Phase().Stage()) {
        case Stage::trainer : tagger_.NewBranch(TreeWriter(), Files().Phase().Stage());
            break;
        case Stage::reader : reader_.NewBranch(TreeWriter(), Files().Phase().Stage());
            break;
        }
        tree_branch_ = &tree_writer_.NewBranch<InfoBranch>(tagger_.WeightBranchName());
        for (auto const & path : Files().Import().Paths()) chain_.AddFile(path.c_str(), TChain::kBigNumber, Files().Import().TreeName().c_str());
    }

    ~BranchWriter() {
        std::cout << "PreCut ratio: " << RoundToDigits(double(object_sum_) / event_sum_) << std::endl;
    }

    void Write() {
//         std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        if (object_sum_) TreeWriter().Write();
    }

    boca::Files& Files()  {
        return files_;
    }

    boca::TreeBranch& TreeBranch() {
        return *tree_branch_;
    }

    boca::TreeWriter& TreeWriter() {
        return tree_writer_;
    }

//     long ObjectSum() {
//         std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
//         return object_sum_;
//     }

    long EventSum() {
//         std::lock_guard<std::mutex> event_sum_guard(event_sum_mutex_);
        return event_sum_;
    }

//     void Increment() {
//         std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
//         ++object_sum_;
//     }

    void Increment(int number) {
//         std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        object_sum_ += number;
//         std::lock_guard<std::mutex> event_sum_guard(event_sum_mutex_);
//         if(number)
        if(number > 0) ++event_sum_;
    }

    bool KeepGoing(long max) {
//         std::lock_guard<std::mutex> object_sum_guard(object_sum_mutex_);
        return object_sum_ < max;
    }

    boca::Reader<Tagger_> Reader() const {
        return reader_;
    }

    Tagger_ Tagger() const {
        return tagger_;
    }

    TChain& Chain() {
        return chain_;
    }

private:

    TChain chain_;

    boca::Files& files_;

    Tagger_& tagger_;

    boca::Reader<Tagger_> reader_;

    boca::TreeWriter tree_writer_;

    boca::TreeBranch* tree_branch_;

    long object_sum_ = 0;
//     std::mutex object_sum_mutex_;

    long event_sum_ = 0;
//     std::mutex event_sum_mutex_;

};

}
