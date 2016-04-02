
/** \class TreeWriter
 *
 *  Class handling output ROOT tree
 *
 *  $Date: 2006/09/21 13:06:18 $
 *  $Revision: 1.2 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

#include "exroot/TreeWriter.h"
#include "exroot/TreeBranch.h"

namespace exroot {

TreeWriter::TreeWriter(TFile *file, const char *treeName) :
  file_(file),
  tree_name_(treeName)
{}

TreeWriter::~TreeWriter() {
  for(auto & branch : branches_) delete branch;
  if(tree_) delete tree_;
}

TreeBranch *TreeWriter::NewBranch(const char *name, TClass *cl) {
  if(!tree_) tree_ = NewTree();
  auto branch = new TreeBranch(name, cl, tree_);
  branches_.insert(branch);
  return branch;
}

TreeBranch *TreeWriter::NewFactory(const char *name, TClass *cl) {
  auto branch = new TreeBranch(name, cl, nullptr);
  branches_.insert(branch);
  return branch;
}

void TreeWriter::Fill() {
  if(tree_) tree_->Fill();
}

void TreeWriter::Write() {
  file_ = tree_ ? tree_->GetCurrentFile() : nullptr;
  if(file_) file_->Write();
}

void TreeWriter::Clear() {
  for(auto & branch : branches_) branch->Clear();
}

TTree *TreeWriter::NewTree() {
  if(!file_) return nullptr;
  TDirectory *dir = gDirectory;
  file_->cd();
  auto * tree = new TTree(tree_name_, "Analysis tree");
  dir->cd();
  if(!tree) {
    std::cout << "** ERROR: cannot create tree" << std::endl;
    return nullptr;
  }
  tree->SetDirectory(file_);
  tree->SetAutoSave(10000000);  // autosave when 10 MB written
  return tree;
}

void TreeWriter::SetTreeFile(TFile* file) {
    file_ = file;
}

void TreeWriter::SetTreeName(const char* name) {
    tree_name_ = name;
}

}
