
#include "boca/io/TreeBranch.hh"
#include "boca/generic/DEBUG.hh"

#include "TTree.h"

namespace boca
{

TreeBranch::TreeBranch(char const* name, TClass* cl, TTree* tree) :
    clones_array_(cl, size_)
{
    INFO(name);
    SetClonesArray(name);
    if (tree) SetTree(*tree, name);
}

TreeBranch::TreeBranch(std::string const& name, TClass& cl, TTree& tree) :
    clones_array_(&cl, size_)
{
    INFO0;
    SetClonesArray(name);
    SetTree(tree, name);
}

TreeBranch::TreeBranch(std::string const& name, TClass& cl) :
    clones_array_(&cl, size_)
{
    INFO(name);
    SetClonesArray(name);
}

void TreeBranch::SetClonesArray(std::string const& name)
{
    INFO(name);
    clones_array_.SetName(name.c_str());
    clones_array_.ExpandCreateFast(size_);
    clones_array_.Clear();
}

void TreeBranch::SetTree(TTree& tree, std::string const& name)
{
    INFO0;
    tree.Branch(name.c_str(), &clones_array_, 64000);
    tree.Branch((name + "_size").c_str(), &position_, (name + "_size/I").c_str());
}

TObject* TreeBranch::NewEntry()
{
    INFO(clones_array_.GetName());
    CheckCapacity();
    auto * object = clones_array_.AddrAt(position_++);
    CHECK(object, "not object to write to");
    return object;
}

void TreeBranch::CheckCapacity()
{
    INFO(size_, position_);
    if (size_ > position_) return;
    size_ *= 4;
    clones_array_.ExpandCreateFast(size_);
    clones_array_.Clear();
    clones_array_.ExpandCreateFast(position_);
}

void TreeBranch::Clear()
{
    INFO0;
    position_ = 0;
    clones_array_.Clear();
}

}


