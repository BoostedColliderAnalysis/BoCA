#pragma once

#include "Branches.hh"

namespace boca
{

namespace higgscpv
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureTTaggerBranch : public boca::TChannelBranch
{
public:
  SignatureTTaggerBranch();
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::TChannelBranch::Fill(signature.Multiplet());
        Aplanarity = signature.EventShape().Aplanarity();
        Sphericity = signature.EventShape().Sphericity();
    }
    Observables Variables() const;
private:
    ClassDef(SignatureTTaggerBranch, 1)
};
class SignatureLeptonTTaggerBranch : public SignatureTTaggerBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        SignatureTTaggerBranch::Fill(signature);
    }
    Observables Variables() const;

private:
    ClassDef(SignatureLeptonTTaggerBranch, 1)
};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureLeptonTaggerBranch : public boca::MultiBranch
{
public:
    SignatureLeptonTaggerBranch();
    float Mass12;
    float Mass23;
    float Mass13;
    float Pt12;
    float Pt23;
    float Pt13;
    float DeltaPt23;
    float DeltaPt13;
    float Ht12;
    float Ht23;
    float Ht13;
    float Rho23;
    float Rho13;
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
    float Pull23;
    float Pull13;
    float DeltaPull23;
    float DeltaPull13;
    float Dipolarity23;
    float Dipolarity13;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::MultiBranch::Fill(signature.Multiplet());
        Mass12 = signature.Multiplet().Jet12().m();
        Mass23 = signature.Multiplet().Jet23().m();
        Mass13 = signature.Multiplet().Jet13().m();
        Pt12 = signature.Multiplet().Jet12().pt();
        Pt23 = signature.Multiplet().Jet23().pt();
        Pt13 = signature.Multiplet().Jet13().pt();
        DeltaPt23 = signature.Multiplet().DeltaPt23();
        DeltaPt13 = signature.Multiplet().DeltaPt13();
        Ht12 = signature.Multiplet().Ht12();
        Ht23 = signature.Multiplet().Ht23();
        Ht13 = signature.Multiplet().Ht13();
        Rho23 = signature.Multiplet().Rho23();
        Rho13 = signature.Multiplet().Rho13();
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
        Pull23 = signature.Multiplet().PullSum23();
        Pull13 = signature.Multiplet().PullSum13();
        DeltaPull23 = signature.Multiplet().PullDifference23();
        DeltaPull13 = signature.Multiplet().PullDifference13();
        Dipolarity23 = signature.Multiplet().Dipolarity23();
        Dipolarity13 = signature.Multiplet().Dipolarity13();
        Aplanarity = signature.EventShape().Aplanarity();
        Sphericity = signature.EventShape().Sphericity();
    }
    Observables Variables() const;

private:
    ClassDef(SignatureLeptonTaggerBranch, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureLeptonicBranch : public boca::MultiBranch
{
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
    void Fill(Multiplet const& signature) {
        boca::MultiBranch::Fill(signature.Multiplet());
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
class OctetBranch : public boca::MultiBranch
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
    void Fill(Multiplet const& multiplet) {
        boca::MultiBranch::Fill(multiplet);
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
class EventBranch : public boca::EventBranch
{

public:

    EventBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::EventBranch::Fill(multiplet);
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
class TopLeptonicPairBranch : public boca::MultiBranch
{
public:
    TopLeptonicPairBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
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
class TripletPairBranch : public boca::PairBranch
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
    void Fill(Multiplet const& multiplet) {
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
class QuartetPairBranch : public boca::PairBranch
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
    void Fill(Multiplet const& multiplet) {
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
