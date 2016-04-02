#pragma once

/** \class ExRootTreeReader
 *
 *  Class simplifying access to ROOT tree branches
 *
 *  $Date: 2006/09/21 13:06:18 $
 *  $Revision: 1.2 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include <map>

#include "TNamed.h"
#include "TClonesArray.h"

class TFolder;
class TBrowser;
class TTree;
class TBranch;

namespace exroot
{

class TreeReader : public TNamed
{

public :

    TreeReader ( TTree* tree = 0 );

    ~TreeReader();

    void SetTree ( TTree* tree );

    long GetEntries() const;

    bool ReadEntry ( long entry );

    TClonesArray* UseBranch ( const char* branchName );

    virtual void Browse ( TBrowser* b );

    virtual bool IsFolder() const;

private:

    bool Notify();

    TTree* chain_;  // pointer to the analyzed TTree or TChain

    int current_tree_ = -1; // current Tree number in a TChain

    TFolder* folder_;

    std::map<TString, std::pair<TBranch*, TClonesArray*> > branch_map_;

};

}
