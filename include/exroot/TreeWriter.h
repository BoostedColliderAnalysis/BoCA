# pragma once

/** \class ExRootTreeWriter
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

#include <set>
#include "TNamed.h"
#include "exroot/TreeBranch.h"


class TFile;
class TTree;
class TClass;

namespace exroot {

class TreeWriter : public TNamed
{
public:

    TreeWriter ( TFile* file = 0, const char* treeName = "Analysis");

    ~TreeWriter();

    void SetTreeFile ( TFile* file );

    void SetTreeName ( const char* name );

    TreeBranch* NewBranch ( const char* name, TClass* cl );

    TreeBranch* NewFactory ( const char* name, TClass* cl );

    void Clear();

    void Fill();

    void Write();

private:

    TTree* NewTree();

    TFile* file_;

    TTree* tree_ = nullptr;

    TString tree_name_;

    std::set<TreeBranch*> branches_;

};

}
