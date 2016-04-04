
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

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TClonesArray.h"

#include <iostream>

namespace exroot{

using namespace std;

//------------------------------------------------------------------------------

TreeBranch::TreeBranch(const char *name, TClass *cl, TTree *tree) :
fSize(0), fCapacity(1), fData(0)
{
  //  cl->IgnoreTObjectStreamer();
  fData = new TClonesArray(cl, fCapacity);

  if(fData)
  {
    fData->SetName(name);
    fData->ExpandCreateFast(fCapacity);
    fData->Clear();
    if(tree)
    {
      tree->Branch(name, &fData, 64000);
      tree->Branch(TString(name) + "_size", &fSize, TString(name) + "_size/I");
    }
  }
  else
  {
    throw MemoryAllocationExeption();
  }
}

//------------------------------------------------------------------------------

TreeBranch::~TreeBranch()
{
  if(fData) delete fData;
}

//------------------------------------------------------------------------------

TObject *TreeBranch::NewEntry()
{
  if(!fData) return 0;

  if(fSize >= fCapacity)
  {
    if(fCapacity < 10) fCapacity = 10;
    else if(fCapacity < 30) fCapacity = 30;
    else if(fCapacity < 100) fCapacity = 100;
    else if(fCapacity < 250) fCapacity = 250;
    else fCapacity *= 2;

    fData->ExpandCreateFast(fCapacity);

    fData->Clear();
    fData->ExpandCreateFast(fSize);
  }

  return fData->AddrAt(fSize++);
}

//------------------------------------------------------------------------------

void TreeBranch::Clear()
{
  fSize = 0;
  if(fData) fData->Clear();
}

//------------------------------------------------------------------------------

}
