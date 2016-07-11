#include "boca/io/FileWriter.hh"

namespace boca
{

FileWriter::FileWriter(const std::string& file_name):
    file_(file_name.c_str(), "Recreate") {}

TreeWriter& FileWriter::NewTree(const std::string& tree_name)
{
    tree_writers_.emplace_back(file_, tree_name);
    return tree_writers_.back();
}


}

