
/** \class ExRootTreeReader
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

// #include "ExRootAnalysis/ExRootTreeReader.h"
#include "exroot/ExRootTreeReader.h"

#include "TH2.h"
#include "TStyle.h"
#include "TFolder.h"
#include "TCanvas.h"
#include "TBrowser.h"
#include "TClonesArray.h"
#include "TBranchElement.h"

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------

ExRootTreeReader::ExRootTreeReader(TTree *tree) :
  fChain(tree), fCurrentTree(-1)
{
  fFolder = new TFolder("branches", "branches");
}

//------------------------------------------------------------------------------

ExRootTreeReader::~ExRootTreeReader()
{
  TBranchMap::iterator it_map;

  for(it_map = fBranchMap.begin(); it_map != fBranchMap.end(); ++it_map)
  {
    delete it_map->second.second;
  }

//  delete fFolder;
}

//------------------------------------------------------------------------------

Bool_t ExRootTreeReader::ReadEntry(Long64_t entry)
{
  // Read contents of entry.
  if(!fChain) return kFALSE;

  Int_t treeEntry = fChain->LoadTree(entry);
  if(treeEntry < 0) return kFALSE;

  if(fChain->IsA() == TChain::Class())
  {
    TChain *chain = static_cast<TChain*>(fChain);
    if(chain->GetTreeNumber() != fCurrentTree)
    {
      fCurrentTree = chain->GetTreeNumber();
      Notify();
    }
  }

  TBranchMap::iterator it_map;
  TBranch *branch;

  for(it_map = fBranchMap.begin(); it_map != fBranchMap.end(); ++it_map)
  {
    branch = it_map->second.first;
    if(branch)
    {
      branch->GetEntry(treeEntry);
    }
  }

  return kTRUE;
}

//------------------------------------------------------------------------------

TClonesArray *ExRootTreeReader::UseBranch(const char *branchName)
{
  TClonesArray *array = 0;

  TBranchMap::iterator it_map = fBranchMap.find(branchName);

  if(it_map != fBranchMap.end())
  {
    cout << "** WARNING: branch '" << branchName << "' is already in use" << endl;
    array = it_map->second.second;
  }
  else
  {
    TBranch *branch = fChain->GetBranch(branchName);
    if(branch)
    {
      if(branch->IsA() == TBranchElement::Class())
      {
        TBranchElement *element = static_cast<TBranchElement*>(branch);
        const char *className = element->GetClonesName();
        Int_t size = element->GetMaximum();
        TClass *cl = gROOT->GetClass(className);
        if(cl)
        {
          array = new TClonesArray(cl, size);
          array->SetName(branchName);
          fFolder->Add(array);
          fBranchMap.insert(make_pair(branchName, make_pair(branch, array)));
          branch->SetAddress(&array);
        }
      }
    }
  }

  if(!array)
  {
    cout << "** WARNING: cannot access branch '" << branchName << "', return NULL pointer" << endl;
  }

  return array;
}

//------------------------------------------------------------------------------

Bool_t ExRootTreeReader::Notify()
{
  // Called when loading a new file.
  // Get branch pointers.
  if(!fChain) return kFALSE;

  TBranchMap::iterator it_map;
  TBranch *branch;

  for(it_map = fBranchMap.begin(); it_map != fBranchMap.end(); ++it_map)
  {
    branch = fChain->GetBranch(it_map->first);
    if(branch)
    {
      it_map->second.first = branch;
      branch->SetAddress(&(it_map->second.second));
    }
    else
    {
      cout << "** WARNING: cannot get branch '" << it_map->first << "'" << endl;
    }
  }
  return kTRUE;
}

//------------------------------------------------------------------------------

void ExRootTreeReader::Browse(TBrowser *b)
{
  TObject::Browse(b);
}

