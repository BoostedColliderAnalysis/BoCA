
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

// #include "ExRootAnalysis/ExRootTreeWriter.h"
// #include "ExRootAnalysis/ExRootTreeBranch.h"
#include "exroot/ExRootTreeWriter.h"
#include "exroot/ExRootTreeBranch.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

#include <iostream>

using namespace std;

ExRootTreeWriter::ExRootTreeWriter(TFile *file, const char *treeName) :
  fFile(file), fTree(0), fTreeName(treeName)
{
}

//------------------------------------------------------------------------------

ExRootTreeWriter::~ExRootTreeWriter()
{
  set<ExRootTreeBranch*>::iterator it_set;
  for(it_set = fBranches.begin(); it_set != fBranches.end(); ++it_set)
  {
    delete (*it_set);
  }

  if(fTree) delete fTree;
}

//------------------------------------------------------------------------------

ExRootTreeBranch *ExRootTreeWriter::NewBranch(const char *name, TClass *cl)
{
  if(!fTree) fTree = NewTree();
  ExRootTreeBranch *branch = new ExRootTreeBranch(name, cl, fTree);
  fBranches.insert(branch);
  return branch;
}

//------------------------------------------------------------------------------

ExRootTreeBranch *ExRootTreeWriter::NewFactory(const char *name, TClass *cl)
{
  ExRootTreeBranch *branch = new ExRootTreeBranch(name, cl, 0);
  fBranches.insert(branch);
  return branch;
}

//------------------------------------------------------------------------------

void ExRootTreeWriter::Fill()
{
  if(fTree) fTree->Fill();
}

//------------------------------------------------------------------------------

void ExRootTreeWriter::Write()
{
  fFile = fTree ? fTree->GetCurrentFile() : 0;
  if(fFile) fFile->Write();
}

//------------------------------------------------------------------------------

void ExRootTreeWriter::Clear()
{
  set<ExRootTreeBranch*>::iterator it_set;
  for(it_set = fBranches.begin(); it_set != fBranches.end(); ++it_set)
  {
    (*it_set)->Clear();
  }
}

//------------------------------------------------------------------------------

TTree *ExRootTreeWriter::NewTree()
{
  if(!fFile) return 0;

  TTree *tree = 0;
  TDirectory *dir = gDirectory;

  fFile->cd();
  tree = new TTree(fTreeName, "Analysis tree");
  dir->cd();

  if(!tree)
  {
    cout << "** ERROR: cannot create tree" << endl;
    return 0;
  }

  tree->SetDirectory(fFile);
  tree->SetAutoSave(10000000);  // autosave when 10 MB written

  return tree;
}
