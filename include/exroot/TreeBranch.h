#ifndef TreeBranch_h
#define TreeBranch_h

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

#include "Rtypes.h"

class TTree;
class TClonesArray;

namespace exroot {

class TreeBranch
{
public:

  class MemoryAllocationExeption{};

  TreeBranch(const char *name, TClass *cl, TTree *tree = 0);
  ~TreeBranch();

  TObject *NewEntry();
  void Clear();

private:

  Int_t fSize, fCapacity;
  TClonesArray *fData;
};

}

#endif /* TreeBranch */

