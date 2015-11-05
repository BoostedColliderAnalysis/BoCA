#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <map>

#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"

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
    virtual ~TreeReaderArrayBase() {}
    virtual void Fill() {}
};

template <typename Object>
class TreeReaderArray : public TreeReaderArrayBase
{

public:

    TreeReaderArray(TTreeReader& tree_reader, Branch branch) : tree_reader_array_(TTreeReaderArray<Object>(tree_reader, BranchName(branch).c_str())) {}

    void Fill() {
        vector_ = vector(tree_reader_array_);
    }

    TTreeReaderArray<Object> tree_reader_array_;

    std::vector<Object> vector_;

    std::vector<Object> vector(TTreeReaderArray<Object> const& objects) const {
        // this cost cast seems to be necessary as the begin() iterator of TTreeReader is not const
        TTreeReaderArray<Object>& obj = const_cast<TTreeReaderArray<Object> &>(objects);
        return {obj.begin(), obj.end()};
    }

};

class TreeReader
{

public:

//     TreeReader(Strings paths, std::string tree_name);

    TreeReader(TChain & chain);

    long GetEntries() const;

    bool ReadEntry(long number);

    static std::mutex& mutex() {
        return mutex_;
    }

    template<typename Object>
    std::vector< Object >Objects(Branch branch) const {
      if(!Has(branch)) return {};
      return std::dynamic_pointer_cast<TreeReaderArray<Object>>(map.at(branch))->vector_;
    }

    bool Has(Branch branch) const{
      return map.find(branch) != map.end();
    }

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

    Strings paths_;

    std::string tree_name_;

    Source source_;

};

}
