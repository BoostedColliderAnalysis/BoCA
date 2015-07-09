#pragma once

#include "Branches.hh"

#define STRING(s) #s
#define PAIR(x) ObservablePair(x,STRING(x))

namespace analysis
{

namespace higgscpv {

  /**
   *
   * @brief Higgs cpv tagger root tree structure
   *
   */
  class SignatureLeptonicBranch : public analysis::MultiBranch
  {
  public:
    SignatureLeptonicBranch();
    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HardTopPt;
    float SoftTopPt;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
      analysis::MultiBranch::Fill(multiplet);
      BottomBdt = multiplet.BottomBdt();
      PairBottomBdt = multiplet.PairBottomBdt();
      HardTopPt = multiplet.Sextet().HardTopPt();
      SoftTopPt = multiplet.Sextet().SoftTopPt();
      HiggsMass = multiplet.Doublet().Jet().m();
      PairRap = multiplet.Sextet().DeltaRap();
    }
    Observables Variables() {
      return Join(MultiBranch::Variables(), {PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(HardTopPt), PAIR(SoftTopPt), PAIR(HiggsMass), PAIR(PairRap)});
    }

  private:
    ClassDef(SignatureLeptonicBranch, 1)
  };

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetBranch : public analysis::MultiBranch
{
public:
    OctetBranch();
    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        analysis::MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.PairBottomBdt();
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        HardTopPt = multiplet.Sextet().HardTopPt();
        SoftTopPt = multiplet.Sextet().SoftTopPt();
        HiggsMass = multiplet.Sextet().Jet().m();
        PairRap = multiplet.Doublet().DeltaRap();
    }
private:
    ClassDef(OctetBranch, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventBranch : public analysis::EventBranch
{

public:

    EventBranch();
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
      analysis::EventBranch::Fill(multiplet);
    }

private:

    ClassDef(EventBranch, 1)

};


/**
 * @brief lepton tree structure
 *
 */
class HLeptonBranch : public analysis::BaseBranch
{

public:

    HLeptonBranch();

    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float Charge;

private:

    ClassDef(HLeptonBranch, 1)

};


/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TopLeptonicPairBranch : public analysis::MultiBranch
{
public:
    TopLeptonicPairBranch();
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(TopLeptonicPairBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletPairBranch : public analysis::PairBranch
{
public:
    TripletPairBranch();
    float BottomMass;
    float BottomPt;
    float BottomRap;
    float BottomPhi;
    float BottomBdt;
    float BottomBTag;
    float TopMass;
    float TopPt;
    float TopRap;
    float TopPhi;
    float TopBdt;
    float TopBTag;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.Triplet1().Jet().pt();
        //         BottomRap = std::abs(multiplet.singlet().rap());
        BottomRap = multiplet.Triplet1().Jet().rap();
        BottomPhi = multiplet.Triplet1().Jet().phi();
        BottomMass = multiplet.Triplet1().Jet().m();
        //         BottomBdt = multiplet.singlet().user_info<JetInfo>().Bdt();
        TopPt = multiplet.Triplet2().Jet().pt();
        //         TopRap = std::abs(multiplet.triplet().Jet().rap());
        TopRap = multiplet.Triplet2().Jet().rap();
        TopPhi = multiplet.Triplet2().Jet().phi();
        TopMass = multiplet.Triplet2().Jet().m();
        TopBdt = multiplet.Triplet2().Bdt();
    }
    Observables Variables() {
      return Join(PairBranch::Variables(), {PAIR(BottomPt), PAIR(BottomRap), PAIR(BottomPhi), PAIR(BottomMass), PAIR(TopPt), PAIR(TopRap), PAIR(TopPhi), PAIR(TopMass), PAIR(TopBdt)});
    }
private:
    ClassDef(TripletPairBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class QuartetPairBranch : public analysis::PairBranch
{

    QuartetPairBranch();

    float BottomMass;
    float BottomPt;
    float BottomRap;
    float BottomPhi;
    float BottomBdt;
    float BottomBTag;

    float TopMass;
    float TopPt;
    float TopRap;
    float TopPhi;
    float TopBdt;
    float TopBTag;

    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.Doublet1().Jet().pt();
        //         BottomRap = std::abs(multiplet.singlet().rap());
        BottomRap = multiplet.Doublet1().Jet().rap();
        BottomPhi = multiplet.Doublet1().Jet().phi();
        BottomMass = multiplet.Doublet1().Jet().m();
        //         BottomBdt = multiplet.singlet().user_info<JetInfo>().Bdt();

        TopPt = multiplet.Doublet2().Jet().pt();
        //         TopRap = std::abs(multiplet.triplet().Jet().rap());
        TopRap = multiplet.Doublet2().Jet().rap();
        TopPhi = multiplet.Doublet2().Jet().phi();
        TopMass = multiplet.Doublet2().Jet().m();
        TopBdt = multiplet.Doublet2().Bdt();
    }

private:

    ClassDef(QuartetPairBranch, 1)

};

}

}
