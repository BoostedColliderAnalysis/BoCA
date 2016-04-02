
/** \class TreeBranch
*
*  Class handling object creation
*  It is also used for output ROOT tree branches
*
*  $Date: 2006/09/21 13:06:18 $
*  $Revision: 1.2 $
*
*
*  \author P. Demin - UCL, Louvain-la-Neuve
*
*/

#include "exroot/TreeBranch.h"

#include "TTree.h"
#include "TString.h"
#include "TClonesArray.h"

namespace exroot
{

TreeBranch::TreeBranch(const char* name, TClass* cl, TTree* tree) {
//  cl->IgnoreTObjectStreamer();
    clones_array_ = new TClonesArray(cl, capacity_);
    if (!clones_array_) throw MemoryAllocationExeption();
        clones_array_->SetName(name);
        clones_array_->ExpandCreateFast(capacity_);
        clones_array_->Clear();
        if (tree) {
            tree->Branch(name, &clones_array_, 64000);
            tree->Branch(TString(name) + "_size", &size_, TString(name) + "_size/I");
        }
}

TreeBranch::~TreeBranch()
{
    if (clones_array_) delete clones_array_;
}

TObject* TreeBranch::NewEntry()
{
    if (!clones_array_) return nullptr;
    if (size_ >= capacity_) {

        if (capacity_ < 10) capacity_ = 10;
        else if (capacity_ < 30) capacity_ = 30;
        else if (capacity_ < 100) capacity_ = 100;
        else if (capacity_ < 250) capacity_ = 250;
        else capacity_ *= 2;

        clones_array_->ExpandCreateFast(capacity_);
        clones_array_->Clear();
        clones_array_->ExpandCreateFast(size_);
    }
    return clones_array_->AddrAt(size_++);
}

void TreeBranch::Clear() {
    size_ = 0;
    if (clones_array_) clones_array_->Clear();
}

}

