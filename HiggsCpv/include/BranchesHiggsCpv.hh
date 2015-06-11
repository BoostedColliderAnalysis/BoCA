# pragma once

# include "Branches.hh"

namespace higgscpv{

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
class EventBranch : public analysis::MultiBranch
{

public:

    EventBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
    float ScalarHt;

    float RestNumber;
    float RestHt;
    float RestM;
    float RestPt;
    float RestRap;
    float RestBdt;
    float RestPhi;
    float LeptonHt;

    float HardTopPt;
    float SoftTopPt;

    float MissingEt;

    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float BottomBdt5;
    float BottomBdt6;
    float BottomBdt7;
    float BottomBdt8;
    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;
    float BottomBdt78;

    float SubBottomBdt1;
    float SubBottomBdt2;
    float SubBottomBdt3;
    float SubBottomBdt4;
    float SubBottomBdt5;
    float SubBottomBdt6;
    float SubBottomBdt7;
    float SubBottomBdt8;
    float SubBottomBdt12;
    float SubBottomBdt34;
    float SubBottomBdt56;
    float SubBottomBdt78;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
      analysis::MultiBranch::Fill(multiplet);
      LeptonNumber = multiplet.LeptonNumber();
      JetNumber = multiplet.JetNumber();
      BottomNumber = multiplet.BottomNumber();
      ScalarHt = multiplet.ScalarHt();

      HiggsMass = multiplet.multiplet().Sextet().Jet().m();
      HiggsBdt = multiplet.multiplet().Sextet().Bdt();
      SignatureBdt = multiplet.multiplet().Bdt();
      PairRap = multiplet.multiplet().Doublet().DeltaRap();
      BottomBdt = multiplet.multiplet().BottomBdt();
      PairBottomBdt = multiplet.multiplet().PairBottomBdt();

      HardTopPt = multiplet.multiplet().Sextet().HardTopPt();
      SoftTopPt = multiplet.multiplet().Sextet().SoftTopPt();

      MissingEt = multiplet.MissingEt();

      BottomBdt1 = multiplet.BottomBdt(1);
      BottomBdt2 = multiplet.BottomBdt(2);
      BottomBdt3 = multiplet.BottomBdt(3);
      BottomBdt4 = multiplet.BottomBdt(4);
      BottomBdt5 = multiplet.BottomBdt(5);
      BottomBdt6 = multiplet.BottomBdt(6);
      BottomBdt7 = multiplet.BottomBdt(7);
      BottomBdt8 = multiplet.BottomBdt(8);
      BottomBdt12 = multiplet.BottomBdt(1, 2);
      BottomBdt34 = multiplet.BottomBdt(3, 4);
      BottomBdt56 = multiplet.BottomBdt(5, 6);
      BottomBdt78 = multiplet.BottomBdt(7, 8);

      SubBottomBdt1 = multiplet.SubBottomBdt(1);
      SubBottomBdt2 = multiplet.SubBottomBdt(2);
      SubBottomBdt3 = multiplet.SubBottomBdt(3);
      SubBottomBdt4 = multiplet.SubBottomBdt(4);
      SubBottomBdt5 = multiplet.SubBottomBdt(5);
      SubBottomBdt6 = multiplet.SubBottomBdt(6);
      SubBottomBdt7 = multiplet.SubBottomBdt(7);
      SubBottomBdt8 = multiplet.SubBottomBdt(8);
      SubBottomBdt12 = multiplet.SubBottomBdt(1, 2);
      SubBottomBdt34 = multiplet.SubBottomBdt(3, 4);
      SubBottomBdt56 = multiplet.SubBottomBdt(5, 6);
      SubBottomBdt78 = multiplet.SubBottomBdt(7, 8);

      RestNumber = multiplet.RestNumber();
      RestM = multiplet.RestJet().m();
      RestPt = multiplet.RestJet().pt();
      RestHt = multiplet.RestHt();
      RestRap = multiplet.RestJet().rap();
      RestPhi = multiplet.RestJet().phi();
      RestBdt = multiplet.RestBdt();

      LeptonHt = multiplet.LeptonHt();
    }

private:

    ClassDef(EventBranch, 1)

};


/**
 * @brief lepton tree structure
 *
 */
class HLeptonBranch : public analysis::Branch
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
