// @(#)root/physics:$Id$
// Author: Pasha Murat, Peter Malzacher   12/02/99
//    Aug 11 1999: added Pt == 0 guard to Eta()
//    Oct  8 1999: changed Warning to Error and
//                 return fX in Double_t & operator()
//    Oct 20 1999: Bug fix: sign in PseudoRapidity
//                 Warning-> Error in Double_t operator()
//           2015  Jan Hajer

#include "TVector3.h"
#include "physics/Vector3.hh"

namespace boca {

// template<>
// Vector3< double >::Vector3(const TVector3& vector)
// {
//     x_ = vector.X();
//     y_ = vector.Y();
//     z_ = vector.Z();
// }
}
