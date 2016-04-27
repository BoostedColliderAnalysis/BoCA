# pragma once

#include "TFile.h"

#include "boca/io/TreeWriter.hh"

namespace boca
{

class FileWriter
{

public:

    FileWriter(std::string const& file_name);

    TreeWriter& NewTree(std::string const& tree_name);

private:

    TFile file_;

    std::list<TreeWriter> tree_writers_;

};

}
