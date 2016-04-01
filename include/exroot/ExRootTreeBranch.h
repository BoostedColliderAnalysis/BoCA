#ifndef ExRootTreeBranch_h
#define ExRootTreeBranch_h

/** \class ExRootTreeBranch
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

#include "Rtypes.h"

class TTree;
class TClonesArray;

class ExRootTreeBranch
{
public:

  class MemoryAllocationExeption{};
  
  ExRootTreeBranch(const char *name, TClass *cl, TTree *tree = 0);
  ~ExRootTreeBranch();

  TObject *NewEntry();
  void Clear();

private:

  Int_t fSize, fCapacity;
  TClonesArray *fData;  
};

#endif /* ExRootTreeBranch */

