#pragma once

#include "boca/esHiggsCpv.hh"
#include "boca/branch/ThreeBody.hh"
#include "boca/branch/TwoBody.hh"
#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"

namespace higgscpv
{

namespace branch
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureT : public boca::branch::ThreeBody
{
public:
  SignatureT();
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        boca::branch::ThreeBody::Fill(signature.Multiplet());
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();
private:
    ClassDef(SignatureT, 1)
};
class SignatureLeptonT : public SignatureTTagger
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& signature) {
        SignatureT::Fill(signature);
    }
    Observables Variables();

private:
    ClassDef(SignatureLeptonT, 1)
};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureLepton : public boca::branch::Multi
{
public:
    SignatureLepton();
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
    void Fill(Multiplet const& multiplet) {
        auto signature = multiplet.Multiplet();
//         boca::branch::Multi::Fill(signature);
        Mass12 = signature.Multiplet12().Mass() / GeV;
        Mass23 = signature.Multiplet23().Mass() / GeV;
        Mass13 = signature.Multiplet13().Mass() / GeV;
        Pt12 = signature.Multiplet12().Pt() / GeV;
        Pt23 = signature.Multiplet23().Pt() / GeV;
        Pt13 = signature.Multiplet13().Pt() / GeV;
        DeltaPt23 = signature.Multiplet23().DeltaPt() / GeV;
        DeltaPt13 = signature.Multiplet13().DeltaPt() / GeV;
        Ht12 = signature.Multiplet12().Ht() / GeV;
        Ht23 = signature.Multiplet23().Ht() / GeV;
        Ht13 = signature.Multiplet13().Ht() / GeV;
        Rho23 = signature.Multiplet23().Rho();
        Rho13 = signature.Multiplet13().Rho();
        DeltaRap23 = signature.Multiplet23().DeltaRap() / rad;
        DeltaRap13 = signature.Multiplet13().DeltaRap() / rad;
        DeltaPhi23 = signature.Multiplet23().DeltaPhi() / rad;
        DeltaPhi13 = signature.Multiplet13().DeltaPhi() / rad;
        DeltaR23 = signature.Multiplet23().DeltaR() / rad;
        DeltaR13 = signature.Multiplet13().DeltaR() / rad;
        DeltaM23 = signature.Multiplet23().DeltaM() / GeV;
        DeltaM13 = signature.Multiplet13().DeltaM() / GeV;
        DeltaHt23 = signature.Multiplet23().DeltaHt() / GeV;
        DeltaHt13 = signature.Multiplet13().DeltaHt() / GeV;
//         Pull23 = signature.Multiplet23().Pull() / rad;
//         Pull13 = signature.Multiplet13().Pull() / rad;
//         DeltaPull23 = signature.Multiplet32().Pull() / rad;
//         DeltaPull13 = signature.Multiplet31().Pull() / rad;
//         Dipolarity23 = signature.Multiplet().Dipolarity23();
//         Dipolarity13 = signature.Multiplet().Dipolarity13();
        Aplanarity = signature.EventShapes().Aplanarity();
        Sphericity = signature.EventShapes().Sphericity();
    }
    Observables Variables();

private:
    ClassDef(SignatureLepton, 1)
};

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

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class Octet : public boca::branch::Multi
{
public:
    Octet();
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
        boca::branch::Multi::Fill(multiplet);
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
    ClassDef(Octet, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class Event : public boca::branch::Event
{

public:

    Event();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
//       boca::branch::Event::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();

private:

    ClassDef(boca::Event, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TopLeptonicTwoBody : public boca::branch::Multi
{
public:
    TopLeptonicTwoBody();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(TopLeptonicTwoBody, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletTwoBody : public boca::branch::TwoBody
{
public:
    TripletTwoBody();
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
        boca::branch::TwoBody::Fill(multiplet);
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
    ClassDef(TripletTwoBody, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class QuartetTwoBody : public boca::branch::TwoBody
{

    QuartetTwoBody();

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
        boca::branch::TwoBody::Fill(multiplet);
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

    ClassDef(QuartetTwoBody, 1)

};

}

}
