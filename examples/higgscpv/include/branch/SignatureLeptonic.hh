#pragma once

#include "boca/branch/ThreeBody.hh"
#include "boca/branch/TwoBody.hh"
#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"

namespace higgscpv
{

using namespace boca;

namespace branch
{

  /**
   *
   * @brief Higgs cpv tagger root tree structure
   *
   */
  class SignatureLeptonic : public boca::branch::Multi
  {
  public:
    SignatureLeptonic();
    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HardTopPt;
    float SoftTopPt;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
      boca::branch::Multi::Fill(signature.Multiplet());
      //         BottomBdt = signature.Multiplet().BottomBdt();
      //         PairBottomBdt = signature.Multiplet().Doublet().BottomBdt();
      HardTopPt = signature.Multiplet().Sextet().HardTopPt() / GeV;
      SoftTopPt = signature.Multiplet().Sextet().SoftTopPt() / GeV;
      HiggsMass = signature.Multiplet().Doublet().Mass() / GeV;
      PairRap = signature.Multiplet().Sextet().DeltaRap() / rad;
      Aplanarity = signature.EventShapes().Aplanarity();
      Sphericity = signature.EventShapes().Sphericity();
      //         BottomBdt = multiplet.BottomBdt();
      //         PairBottomBdt = multiplet.PairBottomBdt();
      //         HardTopPt = multiplet.Sextet().HardTopPt();
      //         SoftTopPt = multiplet.Sextet().SoftTopPt();
      //         HiggsMass = multiplet.Doublet().Mass() / GeV;
      //         PairRap = multiplet.Sextet().DeltaRap();
    }
    Observables Variables();

  private:
    ClassDef(SignatureLeptonic, 1)
  };

}

}
