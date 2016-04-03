#pragma once

#include <memory>
#include <map>

#include "TChain.h"
#include "TreeReaderArray.hh"

namespace boca
{

enum class Source
{
    delphes,
    pgs,
    parton
};

std::string Name(Source source);

class TreeReader
{

public:

    TreeReader(std::vector<std::string> const& paths, std::string const& tree_name);

    long GetEntries() const;

    bool ReadEntry(long number);

    template<typename Object_>
    TTreeReaderArray<Object_>& Objects(Branch branch) const {
        if (!Has(branch)) std::cout << Name(branch) << " does not exist " << map_.size() << std::endl;
        return const_cast<TTreeReaderArray<Object_> &>(std::dynamic_pointer_cast<TreeReaderArray<Object_>>(map_.at(branch))->tree_reader_array());
    }

    bool Has(Branch branch) const;

private:

    template<typename Object_>
    void NewElement(Branch branch) {
        map_.emplace(branch, std::make_shared<TreeReaderArray<Object_>>(tree_reader_, branch));
    }

    void NewElements();

    std::map<Branch, std::shared_ptr<TreeReaderArrayBase>> map_;

    TChain chain_;

    TTreeReader tree_reader_;

    Source source_;

};

}
