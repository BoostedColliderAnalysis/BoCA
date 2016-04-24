#ifndef EXROOTCLASSES_H
#define EXROOTCLASSES_H

/** \class ExRootClasses
 *
 *  Definition of classes to be stored in the root tree.
 *  Function TCompareXYZ sorts objects by the variable XYZ that MUST be
 *  present in the data members of the root tree class of the branch.
 *
 *  $Date: 2007/07/23 14:35:57 $
 *  $Revision: 1.6 $
 *
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

// Dependencies (#includes)

#include "TRef.h"
#include "TObject.h"
#include "TRefArray.h"

#include "TMath.h"

//---------------------------------------------------------------------------

class TCompare
{
public:
  virtual Bool_t IsSortable(const TObject *) const { return kTRUE; }
  virtual Int_t Compare(const TObject *obj1, const TObject *obj2) const = 0;
};

//---------------------------------------------------------------------------

class TSortableObject: public TObject
{
public:

  Bool_t IsSortable() const { return GetCompare() ? GetCompare()->IsSortable(this) : kFALSE; }
  Int_t Compare(const TObject *obj) const { return GetCompare()->Compare(this, obj); }

  virtual const TCompare *GetCompare() const = 0;

  ClassDef(TSortableObject, 1)
};

//---------------------------------------------------------------------------

class TRootWeight: public TObject
{
public:
  Double_t Weight; // weight for the event

  ClassDef(TRootWeight, 1)
};

//---------------------------------------------------------------------------

class TRootLHEFEvent: public TObject
{
public:

  Long64_t Number; // event number

  Int_t Nparticles; // number of particles in the event | hepup.NUP
  Int_t ProcessID; // subprocess code for the event | hepup.IDPRUP

  Double_t Weight; // weight for the event | hepup.XWGTUP
  Double_t ScalePDF; // scale in GeV used in the calculation of the PDFs in the event | hepup.SCALUP
  Double_t CouplingQED; // value of the QED coupling used in the event | hepup.AQEDUP
  Double_t CouplingQCD; // value of the QCD coupling used in the event | hepup.AQCDUP

  ClassDef(TRootLHEFEvent, 2)
};

//---------------------------------------------------------------------------

class TRootLHEFParticle: public TSortableObject
{
public:

  Int_t PID; // particle HEP ID number | hepup.IDUP[number]
  Int_t Status; // particle status code | hepup.ISTUP[number]
  Int_t Mother1; // index for the particle first mother | hepup.MOTHUP[number][0]
  Int_t Mother2; // index for the particle last mother | hepup.MOTHUP[number][1]
  Int_t ColorLine1; // index for the particle color-line | hepup.ICOLUP[number][0]
  Int_t ColorLine2; // index for the particle anti-color-line | hepup.ICOLUP[number][1]

  Double_t Px; // particle momentum vector (x component) | hepup.PUP[number][0]
  Double_t Py; // particle momentum vector (y component) | hepup.PUP[number][1]
  Double_t Pz; // particle momentum vector (z component) | hepup.PUP[number][2]
  Double_t E; // particle energy | hepup.PUP[number][3]
  Double_t M; // particle mass | hepup.PUP[number][4]

  Double_t PT; // particle transverse momentum
  Double_t Eta; // particle pseudorapidity
  Double_t Phi; // particle azimuthal angle

  Double_t Rapidity; // particle rapidity

  Double_t LifeTime; // particle invariant lifetime
                     // (c*tau, distance from production to decay in mm)
                     // | hepup.VTIMUP[number]

  Double_t Spin; // cosine of the angle between the particle spin vector
                 // and the decaying particle 3-momentum,
                 // specified in the lab frame. | hepup.SPINUP[number]

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootLHEFParticle, 2)
};

//---------------------------------------------------------------------------

class TRootGenEvent: public TObject
{
public:

  Long64_t Number; // event number | hepevt.nevhep

  ClassDef(TRootGenEvent, 1)
};

//---------------------------------------------------------------------------

class TRootGenParticle: public TSortableObject
{
public:
  Int_t PID; // particle HEP ID number | hepevt.idhep[number]
  Int_t Status; // particle status | hepevt.isthep[number]
  Int_t M1; // particle 1st mother | hepevt.jmohep[number][0] - 1
  Int_t M2; // particle 2nd mother | hepevt.jmohep[number][1] - 1
  Int_t D1; // particle 1st daughter | hepevt.jdahep[number][0] - 1
  Int_t D2; // particle 2nd daughter | hepevt.jdahep[number][1] - 1

  Double_t E; // particle energy | hepevt.phep[number][3]
  Double_t Px; // particle momentum vector (x component) | hepevt.phep[number][0]
  Double_t Py; // particle momentum vector (y component) | hepevt.phep[number][1]
  Double_t Pz; // particle momentum vector (z component) | hepevt.phep[number][2]

  Double_t PT; // particle transverse momentum
  Double_t Eta; // particle pseudorapidity
  Double_t Phi; // particle azimuthal angle

  Double_t Rapidity; // particle rapidity

  Double_t T; // particle vertex position (t component) | hepevt.vhep[number][3]
  Double_t X; // particle vertex position (x component) | hepevt.vhep[number][0]
  Double_t Y; // particle vertex position (y component) | hepevt.vhep[number][1]
  Double_t Z; // particle vertex position (z component) | hepevt.vhep[number][2]

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootGenParticle, 1)
};

//---------------------------------------------------------------------------

class TRootGenJet: public TSortableObject
{
public:

  Double_t E; // jet energy
  Double_t Px; // jet momentum vector (x component)
  Double_t Py; // jet momentum vector (y component)
  Double_t Pz; // jet momentum vector (z component)

  Double_t PT; // jet transverse momentum
  Double_t Eta; // jet pseudorapidity
  Double_t Phi; // jet azimuthal angle

  Double_t Rapidity; // jet rapidity

  Double_t Mass; // jet invariant mass

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootGenJet, 1)
};

//---------------------------------------------------------------------------

class TRootEvent: public TObject
{
public:

  Long64_t Number; // event number
  Int_t Trigger; // trigger word

  ClassDef(TRootEvent, 1)
};

//---------------------------------------------------------------------------

class TRootMissingET: public TObject
{
public:
  Double_t MET; // mising transverse energy
  Double_t Phi; // mising energy azimuthal angle

  ClassDef(TRootMissingET, 1)
};

//---------------------------------------------------------------------------

class TRootPhoton: public TSortableObject
{
public:

  Double_t PT; // photon transverse momentum
  Double_t Eta; // photon pseudorapidity
  Double_t Phi; // photon azimuthal angle

  Double_t EhadOverEem; // ratio of the hadronic versus electromagnetic energy
                        // deposited in the calorimeter

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootPhoton, 2)
};

//---------------------------------------------------------------------------

class TRootElectron: public TSortableObject
{
public:

  Double_t PT; // electron transverse momentum
  Double_t Eta; // electron pseudorapidity
  Double_t Phi; // electron azimuthal angle

  Double_t Charge; // electron charge

  Double_t Ntrk; // number of tracks associated with the electron

  Double_t EhadOverEem; // ratio of the hadronic versus electromagnetic energy
                        // deposited in the calorimeter

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootElectron, 2)
};

//---------------------------------------------------------------------------

class TRootMuon: public TSortableObject
{
public:

  Double_t PT; // muon transverse momentum
  Double_t Eta; // muon pseudorapidity
  Double_t Phi; // muon azimuthal angle

  Double_t Charge; // muon charge

  Double_t Ntrk; // number of tracks associated with the muon

  Double_t PTiso; // sum of tracks transverse momentum within a cone of radius R=0.4
                  // centered on the muon (excluding the muon itself)

  Double_t ETiso; // ratio of ET in a 3x3 calorimeter cells array around the muon
                  // (including the muon's cell) to the muon PT

  Int_t JetIndex; // index of the closest jet

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootMuon, 2)
};

//---------------------------------------------------------------------------

class TRootTau: public TSortableObject
{
public:

  Double_t PT; // tau transverse momentum
  Double_t Eta; // tau pseudorapidity
  Double_t Phi; // tau azimuthal angle

  Double_t Charge; // tau charge

  Double_t Ntrk; // number of charged tracks associated with the tau

  Double_t EhadOverEem; // ratio of the hadronic versus electromagnetic energy
                        // deposited in the calorimeter

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootTau, 2)
};

//---------------------------------------------------------------------------

class TRootJet: public TSortableObject
{
public:

  Double_t PT; // jet transverse momentum
  Double_t Eta; // jet pseudorapidity
  Double_t Phi; // jet azimuthal angle

  Double_t Mass; // jet invariant mass

  Double_t Ntrk; // number of tracks associated with the jet

  Double_t BTag; // 1 or 2 for a jet that has been tagged as containing a heavy quark

  Double_t EhadOverEem; // ratio of the hadronic versus electromagnetic energy
                        // deposited in the calorimeter

  Int_t Index; // jet index in the LHC Olympics file

  static TCompare *fgCompare; //!
  const TCompare *GetCompare() const { return fgCompare; }

  ClassDef(TRootJet, 2)
};

//---------------------------------------------------------------------------
// Standard Comparison Criteria: E, ET, PT, DeltaR
//---------------------------------------------------------------------------

template <typename T>
class TCompareE: public TCompare
{
  TCompareE() {}
public:
  static TCompareE *Instance()
  {
    static TCompareE single;
    return &single;
  }

  Int_t Compare(const TObject *obj1, const TObject *obj2) const
  {
    auto t1 = static_cast<const T*>(obj1);
    auto t2 = static_cast<const T*>(obj2);
    if(t1->E > t2->E)
      return -1;
    else if(t1->E < t2->E)
      return 1;
    else
      return 0;
  }
};

//---------------------------------------------------------------------------

template <typename T>
class TComparePT: public TCompare
{
  TComparePT() {}
public:
  static TComparePT *Instance()
  {
    static TComparePT single;
    return &single;
  }

  Int_t Compare(const TObject *obj1, const TObject *obj2) const
  {
    auto t1 = static_cast<const T*>(obj1);
    auto t2 = static_cast<const T*>(obj2);
    if(t1->PT > t2->PT)
      return -1;
    else if(t1->PT < t2->PT)
      return 1;
    else
      return 0;
  }
};

//---------------------------------------------------------------------------

template <typename T>
class TCompareET: public TCompare
{
  TCompareET() {}
public:
  static TCompareET *Instance()
  {
    static TCompareET single;
    return &single;
  }

  Int_t Compare(const TObject *obj1, const TObject *obj2) const
  {
    auto t1 = static_cast<const T*>(obj1);
    auto t2 = static_cast<const T*>(obj2);
    if(t1->ET > t2->ET)
      return -1;
    else if(t1->ET < t2->ET)
      return 1;
    else
      return 0;
  }
};

//---------------------------------------------------------------------------

template <typename T1, typename T2>
class TCompareDeltaR: public TCompare
{
  TCompareDeltaR(const T2 *obj = 0) : fObj(obj) {}

  Double_t DeltaPhi(Double_t phi1, Double_t phi2)
  {
    auto phi = TMath::Abs(phi1 - phi2);
    return (phi <= TMath::Pi()) ? phi : (2.0*TMath::Pi()) - phi;
  }

  Double_t Sqr(Double_t x) { return x*x; }

  Double_t SumSqr(Double_t a, Double_t b)
  {
    auto aAbs = TMath::Abs(a);
    auto bAbs = TMath::Abs(b);
    if(aAbs > bAbs) return aAbs * TMath::Sqrt(1.0 + Sqr(bAbs / aAbs));
    else return (bAbs == 0) ? 0.0 : bAbs * TMath::Sqrt(1.0 + Sqr(aAbs / bAbs));
  };

  const T2 *fObj;

public:
    static TCompareDeltaR *Instance(const T2 *obj = 0)
  {
      static TCompareDeltaR single(obj);
      return &single;
  }

  void SetObject(const T2 *obj) { fObj = obj; }

  Int_t Compare(const TObject *obj1, const TObject *obj2) const
  {
    Double_t eta[3], phi[3], deltaR[2];
    auto t1 = static_cast<const T1*>(obj1);
    auto t2 = static_cast<const T1*>(obj2);

    eta[0] = fObj->Eta;
    phi[0] = fObj->Phi;

    eta[1] = t1->Eta;
    phi[1] = t1->Phi;

    eta[2] = t2->Eta;
    phi[2] = t2->Phi;

    deltaR[0] = SumSqr(TMath::Abs(eta[0] - eta[1]), DeltaPhi(phi[0], phi[1]));
    deltaR[1] = SumSqr(TMath::Abs(eta[0] - eta[2]), DeltaPhi(phi[0], phi[2]));

    if(deltaR[0] < deltaR[1])
      return -1;
    else if(deltaR[0] > deltaR[1])
      return 1;
    else
      return 0;
  }
};

#endif // EXROOTCLASSES_H


