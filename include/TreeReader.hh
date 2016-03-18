#pragma once

// #include <mutex>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
// #include "TLeaf.h"

namespace boca
{

enum class Branch
{
    particle,
    photon,
    electron,
    muon,
    jet,
    missing_et,
    track,
    tower,
    e_flow_track,
    e_flow_photon,
    e_flow_neutral_hadron,
    e_flow_muon,
    gen_jet,
    scalar_ht,
    tau
};

std::string Name(Branch branch);

enum class Source
{
    delphes,
    pgs,
    parton
};

std::string Name(Source source);

class TreeReaderArrayBase
{
public:
    virtual void Fill() = 0 ;
};

template <typename Object>
class TreeReaderArray : public TreeReaderArrayBase
{

public:

    TreeReaderArray(TTreeReader& tree_reader, Branch branch) : tree_reader_array_(TTreeReaderArray<Object>(tree_reader, Name(branch).c_str())) , branch_(branch) {}

    void Fill() {
        if (tree_reader_array_.GetReadStatus() == ROOT::TTreeReaderValueBase::kReadError) std::cout << "Tree Reader read error in Branch " << Name(branch_) << std::endl;
        begin_ = tree_reader_array_.begin();
        end_ = tree_reader_array_.end();
    }

    TTreeReaderArray<Object>& tree_reader_array() {
        return tree_reader_array_;
    }

private:

    std::vector<Object> vector(TTreeReaderArray<Object> const& objects) const {
        // this cost cast seems to be necessary as the begin() iterator of TTreeReader is not const
        TTreeReaderArray<Object>& obj = const_cast<TTreeReaderArray<Object> &>(objects);
        return {obj.begin(), obj.end()};
    }

    TTreeReaderArray<Object> tree_reader_array_;

    typename TTreeReaderArray<Object>::Iterator_t begin_;
    typename TTreeReaderArray<Object>::Iterator_t end_;

    std::vector<Object> vector_;

    Branch branch_;

};

class TreeReader
{

public:

    TreeReader(std::vector<std::string> const& paths, std::string const& tree_name);

    long GetEntries() const;

    bool ReadEntry(long number);

    template<typename Object>
    TTreeReaderArray<Object>& Objects(Branch branch) const {
        if (!Has(branch)) std::cout << Name(branch) << " does not exist " << map_.size() << std::endl;
        return const_cast<TTreeReaderArray<Object> &>(std::dynamic_pointer_cast<TreeReaderArray<Object>>(map_.at(branch))->tree_reader_array());
    }

    bool Has(Branch branch) const;

    void Initialize();

private:

    template<typename Object>
    void NewElement(Branch branch) {
        map_.emplace(branch, std::make_shared<TreeReaderArray<Object>>(tree_reader_, branch));
    }

    void NewElements();

    std::map<Branch, std::shared_ptr<TreeReaderArrayBase>> map_;

    TChain chain_2_;

    TTreeReader tree_reader_;

//     static std::mutex mutex_;

    Source source_;

};

}
