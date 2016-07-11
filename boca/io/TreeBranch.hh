#pragma once

#include <string>

#include "TClonesArray.h"

class TTree;

namespace boca
{

class TreeBranch
{

public:

    TreeBranch(char const* name, TClass* cl, TTree* tree = nullptr);

    TreeBranch(std::string const& name, TClass& cl, TTree& tree);

    TreeBranch(std::string const& name, TClass& cl);

    TObject* NewEntry();

    template<typename Branch_>
    Branch_& AddEntry() {
        return static_cast<Branch_&>(*NewEntry());
    }

    template<typename Branch_>
    void AddEntry(Branch_ const& branch) {
        AddEntry<Branch_>() = branch;
    }

    void Clear();

private:

    void SetClonesArray(std::string const& name);

    void SetTree(TTree& tree, std::string const& name);

    void CheckCapacity();

    int position_ = 0;

    int size_ = 1;

    TClonesArray clones_array_;

};

}

using ExRootTreeBranch = boca::TreeBranch;
