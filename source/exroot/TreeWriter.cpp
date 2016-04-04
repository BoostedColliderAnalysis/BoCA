#include "TROOT.h"
#include "TFile.h"

#include "exroot/TreeWriter.hh"
#include "generic/DEBUG.hh"

namespace boca {

  TreeWriter::TreeWriter(TFile & file, std::string const& tree_name) :
  file_(&file),
  tree_(tree_name.c_str(), tree_name.c_str())
  {
    INFO0;
    SetTree();
  }

  void TreeWriter::SetTree(){
    INFO0;
    gDirectory->cd();
    file_->cd();
    tree_.SetDirectory(file_);
    tree_.SetAutoSave(10e7);
  }

  TreeBranch &TreeWriter::NewBranch(std::string const& name, TClass& cl) {
    INFO0;
    branches_.emplace_back(name, cl, tree_);
    return branches_.back();
  }

  void TreeWriter::Fill() {
    INFO0;
    tree_.Fill();
    for(auto & branch : branches_) branch.Clear();
  }

  void TreeWriter::Write() {
    INFO0;
    file_ = tree_.GetCurrentFile();
    if(file_) file_->Write();
  }

}

