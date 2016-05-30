#pragma once

#include "boca/Branches.hh"

namespace boca
{

namespace higgscpv
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureTTaggerBranch : public boca::ThreeBodyBranch
{
public:
  SignatureTTaggerBranch();
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::ThreeBodyBranch::Fill(signature.Multiplet());
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();
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
    Observables Variables();

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
//     float Dipolarity23;
//     float Dipolarity13;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::MultiBranch::Fill(signature.Multiplet());
        Mass12 = signature.Multiplet().Jet12().Mass() / GeV;
        Mass23 = signature.Multiplet().Jet23().Mass() / GeV;
        Mass13 = signature.Multiplet().Jet13().Mass() / GeV;
        Pt12 = signature.Multiplet().Jet12().Pt() / GeV;
        Pt23 = signature.Multiplet().Jet23().Pt() / GeV;
        Pt13 = signature.Multiplet().Jet13().Pt() / GeV;
        DeltaPt23 = signature.Multiplet().DeltaPt23() / GeV;
        DeltaPt13 = signature.Multiplet().DeltaPt13() / GeV;
        Ht12 = signature.Multiplet().Ht12() / GeV;
        Ht23 = signature.Multiplet().Ht23() / GeV;
        Ht13 = signature.Multiplet().Ht13() / GeV;
        Rho23 = signature.Multiplet().Rho23();
        Rho13 = signature.Multiplet().Rho13();
        DeltaRap23 = signature.Multiplet().DeltaRap23() / rad;
        DeltaRap13 = signature.Multiplet().DeltaRap13() / rad;
        DeltaPhi23 = signature.Multiplet().DeltaPhi23() / rad;
        DeltaPhi13 = signature.Multiplet().DeltaPhi13() / rad;
        DeltaR23 = signature.Multiplet().DeltaR23() / rad;
        DeltaR13 = signature.Multiplet().DeltaR13() / rad;
        DeltaM23 = signature.Multiplet().DeltaM23() / GeV;
        DeltaM13 = signature.Multiplet().DeltaM13() / GeV;
        DeltaHt23 = signature.Multiplet().DeltaHt23() / GeV;
        DeltaHt13 = signature.Multiplet().DeltaHt13() / GeV;
        Pull23 = signature.Multiplet().Pull23() / rad;
        Pull13 = signature.Multiplet().Pull13() / rad;
        DeltaPull23 = signature.Multiplet().Pull32() / rad;
        DeltaPull13 = signature.Multiplet().Pull31() / rad;
//         Dipolarity23 = signature.Multiplet().Dipolarity23();
//         Dipolarity13 = signature.Multiplet().Dipolarity13();
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();

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
        HardTopPt = multiplet.Sextet().HardTopPt() / GeV;
        SoftTopPt = multiplet.Sextet().SoftTopPt() / GeV;
        HiggsMass = multiplet.Sextet().Mass() / GeV;
        PairRap = multiplet.Doublet().DeltaRap() / rad;
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
    Observables Variables();
    Observables Spectators();

private:

    ClassDef(EventBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TopLeptonicTwoBodyBranch : public boca::MultiBranch
{
public:
    TopLeptonicTwoBodyBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(TopLeptonicTwoBodyBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletTwoBodyBranch : public boca::TwoBodyBranch
{
public:
    TripletTwoBodyBranch();
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
        TwoBodyBranch::Fill(multiplet);
        BottomPt = multiplet.Triplet1().Pt() / GeV;
        //         BottomRap = std::abs(multiplet.Rap() / rad);
        BottomRap = multiplet.Triplet1().Rap() / rad;
        BottomPhi = multiplet.Triplet1().Phi() / rad;
        BottomMass = multiplet.Triplet1().Mass() / GeV;
        //         BottomBdt = multiplet.Info().Bdt();
        TopPt = multiplet.Triplet2().Pt() / GeV;
        //         TopRap = std::abs(multiplet.triplet().Rap() / rad);
        TopRap = multiplet.Triplet2().Rap() / rad;
        TopPhi = multiplet.Triplet2().Phi() / rad;
        TopMass = multiplet.Triplet2().Mass() / GeV;
        TopBdt = multiplet.Triplet2().Bdt();
    }
    Observables Variables();

private:
    ClassDef(TripletTwoBodyBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class QuartetTwoBodyBranch : public boca::TwoBodyBranch
{

    QuartetTwoBodyBranch();

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
        TwoBodyBranch::Fill(multiplet);
        BottomPt = multiplet.Doublet1().Pt() / GeV;
        //         BottomRap = std::abs(multiplet.Rap() / rad);
        BottomRap = multiplet.Doublet1().Rap() / rad;
        BottomPhi = multiplet.Doublet1().Phi() / rad;
        BottomMass = multiplet.Doublet1().Mass() / GeV;
        //         BottomBdt = multiplet.Info().Bdt();
        TopPt = multiplet.Doublet2().Pt() / GeV;
        //         TopRap = std::abs(multiplet.triplet().Rap() / rad);
        TopRap = multiplet.Doublet2().Rap() / rad;
        TopPhi = multiplet.Doublet2().Phi() / rad;
        TopMass = multiplet.Doublet2().Mass() / GeV;
        TopBdt = multiplet.Doublet2().Bdt();
    }

private:

    ClassDef(QuartetTwoBodyBranch, 1)

};

}

}
