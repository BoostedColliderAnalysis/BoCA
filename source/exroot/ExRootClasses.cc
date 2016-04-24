/** \class ExRootClasses
 *
 *  See header classes for a description of this file
 *
 *  $Date: 2006/12/19 19:18:46 $
 *  $Revision: 1.4 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

// #include "boca/ExRootAnalysis/ExRootClasses.h"
#include "boca/exroot/ExRootClasses.h"

TCompare *TRootLHEFParticle::fgCompare = 0;
TCompare *TRootGenParticle::fgCompare = 0;
TCompare *TRootGenJet::fgCompare = TComparePT<TRootGenJet>::Instance();
TCompare *TRootPhoton::fgCompare = TComparePT<TRootPhoton>::Instance();
TCompare *TRootElectron::fgCompare = TComparePT<TRootElectron>::Instance();
TCompare *TRootMuon::fgCompare = TComparePT<TRootMuon>::Instance();
TCompare *TRootTau::fgCompare = TComparePT<TRootTau>::Instance();
TCompare *TRootJet::fgCompare = TComparePT<TRootJet>::Instance();

