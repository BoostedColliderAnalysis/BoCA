#pragma once

/** \class TreeBranch
 *
 *  Class handling object creation.
 *  It is also used for output ROOT tree branches
 *
 *  $Date: 2006/09/21 13:06:18 $
 *  $Revision: 1.2 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include "TObject.h"

class TTree;

namespace exroot
{

class TreeBranch
{
public:

    class MemoryAllocationExeption {};

    TreeBranch(const char* name, TClass* cl, TTree* tree = nullptr);

    ~TreeBranch();

    TObject* NewEntry();

    void Clear();

private:

    int size_ = 0;
    int capacity_ = 1;
    TClonesArray* clones_array_ = nullptr;
};

}
