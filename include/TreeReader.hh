#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <map>
#include <iostream>

#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
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

    TreeReaderArray(TTreeReader& tree_reader, Branch branch) : tree_reader_array_(TTreeReaderArray<Object>(tree_reader, BranchName(branch).c_str())) {}

    void Fill() {
//         vector_ = vector(tree_reader_array_);
      begin = tree_reader_array_.begin();
      end = tree_reader_array_.end();
    }

    std::vector<Object> vector()  {
        vector_ = vector(tree_reader_array_);
      return vector_;
    };

    TTreeReaderArray<Object> tree_reader_array_;

    typename TTreeReaderArray<Object>::Iterator_t begin;
    typename TTreeReaderArray<Object>::Iterator_t end;

private:

    std::vector<Object> vector(TTreeReaderArray<Object> const& objects) const {
        // this cost cast seems to be necessary as the begin() iterator of TTreeReader is not const
        TTreeReaderArray<Object>& obj = const_cast<TTreeReaderArray<Object> &>(objects);
        return {obj.begin(), obj.end()};
    }

    std::vector<Object> vector_;

};

class TreeReader
{

public:

    TreeReader(TChain & chain);

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
    TTreeReaderArray< Object > & Objects(Branch branch) const {
//       if(!Has(branch)) return TTreeReaderArray<Object>();
      return const_cast<TTreeReaderArray<Object> &>(std::dynamic_pointer_cast<TreeReaderArray<Object>>(map.at(branch))->tree_reader_array_);
    }

//     template<typename Object>
//     std::vector< Object > Objects(Branch branch) const {
// //       if(!Has(branch)) return TTreeReaderArray<Object>();
//       return Vector<Object>(branch);
//     }

    bool Has(Branch branch) const;

    void Initialize();

private:

    std::map<Branch, std::shared_ptr<TreeReaderArrayBase>> map;

    template<typename Object>
    void NewElement(Branch branch) {
      map.emplace(branch, std::make_shared<TreeReaderArray<Object>>(tree_reader_, branch));
    }

    void NewElements();

    TChain * chain_;

    TTreeReader tree_reader_;

    static std::mutex mutex_;

    Source source_;

};

}
