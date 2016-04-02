
/** \class TreeReader
 *
 *  Class simplifying access to ROOT tree branches
 *
 *  $Date: 2007/07/23 14:36:04 $
 *  $Revision: 1.3 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */
#include <iostream>

#include "TFolder.h"
#include "TBrowser.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "TBranchElement.h"
#include "TROOT.h"

#include "exroot/TreeReader.h"

namespace exroot
{

TreeReader::TreeReader(TTree* tree) :
    chain_(tree) {
    folder_ = new TFolder("branches", "branches");
}

TreeReader::~TreeReader()
{
    for (auto & map : branch_map_) delete map.second.second;
//  delete fFolder; // FIXME why is this switched off?
}

bool TreeReader::ReadEntry(long entry) {
    // Read contents of entry.
    if (!chain_) return false;
    auto treeEntry = chain_->LoadTree(entry);
    if (treeEntry < 0) return false;
    if (chain_->IsA() == TChain::Class()) {
        auto * chain = static_cast<TChain*>(chain_);
        if (chain->GetTreeNumber() != current_tree_) {
            current_tree_ = chain->GetTreeNumber();
            Notify();
        }
    }
    for (auto & map : branch_map_) {
        auto * branch = map.second.first;
        if (branch) branch->GetEntry(treeEntry);
    }
    return true;
}

TClonesArray* TreeReader::UseBranch(const char* branchName) {
    TClonesArray* array = nullptr;
    auto it_map = branch_map_.find(branchName);
    if (it_map != branch_map_.end()) {
        std::cout << "** WARNING: branch '" << branchName << "' is already in use" << std::endl;
        array = it_map->second.second;
    } else {
        TBranch* branch = chain_->GetBranch(branchName);
        if (branch) {
            if (branch->IsA() == TBranchElement::Class()) {
                TBranchElement* element = static_cast<TBranchElement*>(branch);
                const char* className = element->GetClonesName();
                int size = element->GetMaximum();
                TClass* cl = gROOT->GetClass(className);
                if (cl) {
                    array = new TClonesArray(cl, size);
                    array->SetName(branchName);
                    folder_->Add(array);
                    branch_map_.insert(std::make_pair(branchName, std::make_pair(branch, array)));
                    branch->SetAddress(&array);
                }
            }
        }
    }
    if (!array) std::cout << "** WARNING: cannot access branch '" << branchName << "', return NULL pointer" << std::endl;
    return array;
}

bool TreeReader::Notify() {
    // Called when loading a new file.
    // Get branch pointers.
    if (!chain_) return false;
    for (auto & map : branch_map_) {
        auto * branch = chain_->GetBranch(map.first);
        if (branch) {
            map.second.first = branch;
            branch->SetAddress(&(map.second.second));
        } else std::cout << "** WARNING: cannot get branch '" << map.first << "'" << std::endl;
    }
    return true;
}

void TreeReader::Browse(TBrowser* b) {
    TObject::Browse(b);
}

void TreeReader::SetTree(TTree* tree) {
    chain_ = tree;
}

long TreeReader::GetEntries() const {
    return chain_ ? chain_->GetEntries() : 0;
}

bool TreeReader::IsFolder() const {
    return true;
}


}
