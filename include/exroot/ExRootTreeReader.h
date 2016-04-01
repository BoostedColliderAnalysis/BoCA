#ifndef ExRootTreeReader_h
#define ExRootTreeReader_h

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

#include "TROOT.h"
#include "TNamed.h"
#include "TChain.h"
#include "TFile.h"

#include <map>

class TFolder;
class TBrowser;

class ExRootTreeReader : public TNamed
{
public :

  ExRootTreeReader(TTree *tree = 0);
  ~ExRootTreeReader();

  void SetTree(TTree *tree) { fChain = tree; }

  Long64_t GetEntries() const { return fChain ? static_cast<Long64_t>(fChain->GetEntries()) : 0; }
  Bool_t ReadEntry(Long64_t entry);

  TClonesArray *UseBranch(const char *branchName);

  virtual void Browse(TBrowser *b);
  virtual Bool_t IsFolder() const { return kTRUE; }

private:

  Bool_t Notify();

  TTree *fChain;  // pointer to the analyzed TTree or TChain
  Int_t fCurrentTree; // current Tree number in a TChain

  TFolder *fFolder;

  typedef std::map<TString, std::pair<TBranch*, TClonesArray*> > TBranchMap;

  TBranchMap fBranchMap;

  ClassDef(ExRootTreeReader, 1)
};

#endif // ExRootTreeReader_h
