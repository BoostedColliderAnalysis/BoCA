# pragma once

#include "TFile.h"

#include "io/TreeWriter.hh"

class TFile;

namespace boca
{

class FileWriter
{

public:

    FileWriter(std::string const& file_name) :
        file_(file_name.c_str(), "Recreate") {}

    TreeWriter& NewTree(std::string const& tree_name) {
        tree_writers_.emplace_back(file_, tree_name);
        return tree_writers_.back();
    }

private:

    TFile file_;

    std::list<TreeWriter> tree_writers_;

};

}
