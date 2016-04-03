#pragma once

#include <vector>
#include <iostream>

#include "TTreeReader.h"
#include "TTreeReaderArray.h"

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

class TreeReaderArrayBase
{
public:
    virtual void Fill() = 0 ;
};

template <typename Object_>
class TreeReaderArray : public TreeReaderArrayBase
{

public:

    TreeReaderArray(TTreeReader& tree_reader, Branch branch) : tree_reader_array_(TTreeReaderArray<Object_>(tree_reader, Name(branch).c_str())) , branch_(branch) {}

    void Fill() {
        if (tree_reader_array_.GetReadStatus() == ROOT::TTreeReaderValueBase::kReadError) std::cout << "Tree Reader read error in Branch " << Name(branch_) << std::endl;
        begin_ = tree_reader_array_.begin();
        end_ = tree_reader_array_.end();
    }

    TTreeReaderArray<Object_>& tree_reader_array() {
        return tree_reader_array_;
    }

private:

    std::vector<Object_> vector(TTreeReaderArray<Object_> const& objects) const {
        TTreeReaderArray<Object_>& obj = const_cast<TTreeReaderArray<Object_> &>(objects);
        return {obj.begin(), obj.end()};
    }

    TTreeReaderArray<Object_> tree_reader_array_;

    typename TTreeReaderArray<Object_>::Iterator_t begin_;
    typename TTreeReaderArray<Object_>::Iterator_t end_;

    std::vector<Object_> vector_;

    Branch branch_;

};

}
