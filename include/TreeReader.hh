#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include "TLeaf.h"

namespace boca
{

typedef std::vector<std::string> Strings;

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

std::string BranchName(Branch branch);

enum class Source
{
    delphes,
    pgs,
    parton
};

class TreeReaderArrayBase
{
public:
//     virtual ~TreeReaderArrayBase() = 0;
    virtual void Fill() = 0 ;
};

template <typename Object>
class TreeReaderArray : public TreeReaderArrayBase
{

public:

    TreeReaderArray(TTreeReader& tree_reader, Branch branch) : tree_reader_array_(TTreeReaderArray<Object>(tree_reader, BranchName(branch).c_str())) , branch_(branch) {}

    void Fill() {

      if(tree_reader_array_.GetReadStatus() == ROOT::TTreeReaderValueBase::kReadError) std::cout << "Tree Reader read error in Branch " << BranchName(branch_) << std::endl;

//         vector_ = vector(tree_reader_array_);
      begin_ = tree_reader_array_.begin();
      end_ = tree_reader_array_.end();
    }

//     std::vector<Object> vector()  {
//         vector_ = vector(tree_reader_array_);
//       return vector_;
//     };

    TTreeReaderArray<Object>& tree_reader_array() {
//         std::cout << "Returning " << BranchName(branch_) << std::endl;
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

    TreeReader(TChain& chain);

    TreeReader(Strings const& paths, std::string const& tree_name);

    long GetEntries() const;

    bool ReadEntry(long number);

//     template<typename Object>
//     std::vector< Object >Vector(Branch branch) const {
//       if(!Has(branch)) return {};
// //       return std::dynamic_pointer_cast<TreeReaderArray<Object>>(map.at(branch))->vector();
//       auto object = std::dynamic_pointer_cast<TreeReaderArray<Object>>(map.at(branch));
//       return {object->begin, object->end};
//     }

    template<typename Object>
    TTreeReaderArray<Object>& Objects(Branch branch) const {
        if (!Has(branch)) std::cout << BranchName(branch) << " does not exist" << std::endl;
//          return TTreeReaderArray<Object>();
//         std::cout << "Reading " << BranchName(branch) << std::endl;
        return const_cast<TTreeReaderArray<Object> &>(std::dynamic_pointer_cast<TreeReaderArray<Object>>(map_.at(branch))->tree_reader_array());
    }

//     template<typename Object>
//     std::vector< Object > Objects(Branch branch) const {
// //       if(!Has(branch)) return TTreeReaderArray<Object>();
//       return Vector<Object>(branch);
//     }

    bool Has(Branch branch) const;

    void Initialize();

private:

    template<typename Object>
    void NewElement(Branch branch) {
        map_.emplace(branch, std::make_shared<TreeReaderArray<Object>>(tree_reader_, branch));
    }

    void NewElements();

    std::map<Branch, std::shared_ptr<TreeReaderArrayBase>> map_;

    TChain* chain_;

    TChain chain_2_;

    TTreeReader tree_reader_;

    static std::mutex mutex_;

    Source source_;

};

}
