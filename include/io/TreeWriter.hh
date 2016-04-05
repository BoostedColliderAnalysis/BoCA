# pragma once

#include <list>
#include "TTree.h"
#include "io/TreeBranch.hh"

class TFile;

namespace boca
{

class TreeWriter
{

public:

    TreeWriter(TFile& file, std::string const& tree_name = "Analysis");

    TreeBranch& NewBranch(std::string const& name, TClass& cl);

    template<typename Branch_>
    TreeBranch& NewBranch(std::string const& name) {
        return NewBranch(name, *Branch_::Class());
    }

    void Fill();

    void Write();

private:

    void SetTree();

    TFile* file_;

    TTree tree_;

    std::list<TreeBranch> branches_;

};

}
