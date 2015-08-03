#pragma once

#include "Branches.hh"

namespace analysis {

  namespace higgscpv {

    /**
     *
     * @brief Higgs cpv tagger root tree structure
     *
     */
    class SignatureTTaggerBranch : public analysis::MultiBranch {
    public:
      SignatureTTaggerBranch();
      float Mass12;
      float Mass23;
      float Mass13;
      float DeltaPt23;
      float DeltaPt13;
      float Ht12;
      float Ht23;
      float Ht13;
      float DeltaRap23;
      float DeltaRap13;
      float DeltaPhi23;
      float DeltaPhi13;
      float DeltaR23;
      float DeltaR13;
      float DeltaM23;
      float DeltaM13;
      float DeltaHt23;
      float DeltaHt13;
      float Sphericity;
      float Aplanarity;
      template<typename Multiplet>
      void Fill(const Multiplet& signature)
      {
        analysis::MultiBranch::Fill(signature.Multiplet());
        Mass12 = signature.Multiplet().Jet12().m();
        Mass23 = signature.Multiplet().Jet23().m();
        Mass13 = signature.Multiplet().Jet13().m();
        DeltaPt23 = signature.Multiplet().DeltaPt23();
        DeltaPt13 = signature.Multiplet().DeltaPt13();
        Ht12 = signature.Multiplet().Ht12();
        Ht23 = signature.Multiplet().Ht23();
        Ht13 = signature.Multiplet().Ht13();
        DeltaRap23 = signature.Multiplet().DeltaRap23();
        DeltaRap13 = signature.Multiplet().DeltaRap13();
        DeltaPhi23 = signature.Multiplet().DeltaPhi23();
        DeltaPhi13 = signature.Multiplet().DeltaPhi13();
        DeltaR23 = signature.Multiplet().DeltaR23();
        DeltaR13 = signature.Multiplet().DeltaR13();
        DeltaM23 = signature.Multiplet().DeltaM23();
        DeltaM13 = signature.Multiplet().DeltaM13();
        DeltaHt23 = signature.Multiplet().DeltaHt23();
        DeltaHt13 = signature.Multiplet().DeltaHt13();
        Aplanarity = signature.EventShape().Aplanarity();
        Sphericity = signature.EventShape().Sphericity();
      }
      Observables Variables() const;

    private:
      ClassDef(SignatureTTaggerBranch, 1)
    };

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureLeptonicBranch : public analysis::MultiBranch {
public:
    SignatureLeptonicBranch();
    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HardTopPt;
    float SoftTopPt;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(const Multiplet& signature)
    {
      analysis::MultiBranch::Fill(signature.Multiplet());
      BottomBdt = signature.Multiplet().BottomBdt();
      PairBottomBdt = signature.Multiplet().Doublet().BottomBdt();
      HardTopPt = signature.Multiplet().Sextet().HardTopPt();
      SoftTopPt = signature.Multiplet().Sextet().SoftTopPt();
      HiggsMass = signature.Multiplet().Doublet().Jet().m();
      PairRap = signature.Multiplet().Sextet().DeltaRap();
      Aplanarity = signature.EventShape().Aplanarity();
      Sphericity = signature.EventShape().Sphericity();
//         BottomBdt = multiplet.BottomBdt();
//         PairBottomBdt = multiplet.PairBottomBdt();
//         HardTopPt = multiplet.Sextet().HardTopPt();
//         SoftTopPt = multiplet.Sextet().SoftTopPt();
//         HiggsMass = multiplet.Doublet().Jet().m();
//         PairRap = multiplet.Sextet().DeltaRap();
    }
    Observables Variables() const;

private:
    ClassDef(SignatureLeptonicBranch, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetBranch : public analysis::MultiBranch {
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
    void Fill(const Multiplet& multiplet)
    {
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
class EventBranch : public analysis::EventBranch {

public:

    EventBranch();
    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        analysis::EventBranch::Fill(multiplet);
    }
    Observables Variables() const;
    Observables Spectators() const;

private:

    ClassDef(EventBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TopLeptonicPairBranch : public analysis::MultiBranch {
public:
    TopLeptonicPairBranch();
    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
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
class TripletPairBranch : public analysis::PairBranch {
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
    void Fill(const Multiplet& multiplet)
    {
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
    Observables Variables() const;

private:
    ClassDef(TripletPairBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class QuartetPairBranch : public analysis::PairBranch {

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
    void Fill(const Multiplet& multiplet)
    {
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
