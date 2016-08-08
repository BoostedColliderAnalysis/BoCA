#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/Cut.hh"

namespace heavyhiggs
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsLeptonic : public boca::branch::TwoBody
{

public:

    HeavyHiggsLeptonic();

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        LargerWDeltaR = multiplet.GetLargertripletDeltaR() / rad;
        LargerWDeltaRap = multiplet.GetLargertripletDeltaRap() / rad;
        LargerWDeltaPhi = multiplet.GetLargerTripleDeltaPhi() / rad;
        SmallerWDeltaR = multiplet.GetSmallertripletDeltaR() / rad;
        SmallerWDeltaRap = multiplet.GetSmallertripletDeltaRap() / rad;
        SmallerWDeltaPhi = multiplet.GetSmallertripletDeltaPhi() / rad;
        LargerNeutrinoDeltaR = multiplet.GetLargertripletDeltaR() / rad;
        LargerNeutrinoDeltaRap = multiplet.GetLargertripletDeltaRap() / rad;
        LargerNeutrinoDeltaPhi = multiplet.GetLargerTripleDeltaPhi() / rad;
        SmallerNeutrinoDeltaR = multiplet.GetSmallertripletDeltaR() / rad;
        SmallerNeutrinoDeltaRap = multiplet.GetSmallertripletDeltaRap() / rad;
        SmallerNeutrinoDeltaPhi = multiplet.GetSmallertripletDeltaPhi() / rad;
    }

    Observables Variables();

private:

    ClassDef(HeavyHiggsLeptonic, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsSemi : public branch::Multi
{

public:

    HeavyHiggsSemi();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }

private:

    ClassDef(HeavyHiggsSemi, 1)

};

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class ChargedHiggsSemi : public branch::Multi
{

public:

//     float Flag;
    ChargedHiggsSemi();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
//         Flag = multiplet.Flag();
    }
//     virtual Observables Spectators();

private:

    ClassDef(ChargedHiggsSemi, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class ChargedHiggsLeptonic : public branch::Multi
{

public:

    ChargedHiggsLeptonic();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;

    float TopBdt;

    float HeavyHiggsTag;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        HeavyHiggsMass = multiplet.Mass() / GeV;
        HeavyHiggsPt = multiplet.Mass() / GeV;
        TopDeltaR = multiplet.DeltaR() / rad;
        TopDeltaRap = multiplet.DeltaRap() / rad;
        TopDeltaPhi = multiplet.DeltaPhi() / rad;
        TopBdt = multiplet.Bdt();
        HeavyHiggsTag = static_cast<int>(multiplet.Tag());
    }

    Observables Variables();
    Observables Spectators();

private:

    ClassDef(ChargedHiggsLeptonic, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HeavyHiggsTau : public branch::TwoBody
{

public:

    HeavyHiggsTau();

    float LeptonPt;
    float NeutrinoPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TwoBody::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Pt() / GeV;
        NeutrinoPt = multiplet.Singlet2().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(HeavyHiggsTau, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventNeutral : public branch::Event
{

public:

    EventNeutral();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Sextet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        HardTopPt = event.Signature().Sextet().HardTopPt() / GeV;
        SoftTopPt = event.Signature().Sextet().SoftTopPt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventNeutral, 1)

};
class EventNeutralFourTop : public branch::Event
{

public:

    EventNeutralFourTop();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;

    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Sextet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        HardTopPt = event.Signature().Sextet().HardTopPt() / GeV;
        SoftTopPt = event.Signature().Sextet().SoftTopPt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventNeutralFourTop, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusion : public branch::Event
{

public:

    EventFusion();


    float HiggsMass;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Event::Fill(multiplet);
        HiggsMass = multiplet.Mass() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventFusion, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutral : public branch::Multi
{

public:

    OctetNeutral();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float PairBdt;
    float HardTopPt;
    float SoftTopPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        HardTopPt = multiplet.Sextet().HardTopPt() / GeV;
        SoftTopPt = multiplet.Sextet().SoftTopPt() / GeV;
        HiggsMass = multiplet.Sextet().Mass() / GeV;
        PairRap = multiplet.Doublet().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetNeutral, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetCharged : public branch::Multi
{

public:

    OctetCharged();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float PairBdt;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
        HiggsBdt = multiplet.Quartet1().Bdt();
        PairBdt = multiplet.Quartet2().Bdt();
        HiggsMass = multiplet.Quartet1().Mass() / GeV;
        PairRap = multiplet.Quartet2().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetCharged, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventCharged : public branch::Event
{

public:

    EventCharged();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        Event::Fill(event);
        HiggsMass = event.Signature().Quartet1().Mass() / GeV;
        HiggsBdt = event.Signature().Quartet1().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Quartet2().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(EventCharged, 1)

};

class HeavyHiggsCut : public branch::Cut
{

public:

    HeavyHiggsCut();
    float Ht;
    float EtMiss;
    float NumberJet;
    float NumberBottom;
    float InvariantMass;
    float DeltaR;
    float LeptonPt1;
    float LeptonPt2;
    float BottomMinPt;
    float BottomMaxRap;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Cut::Fill(multiplet);
        Ht = multiplet.Ht() / GeV;
        EtMiss = multiplet.EtMiss() / GeV;
        NumberJet = multiplet.JetNumber();
        NumberBottom = multiplet.BottomNumber();
        InvariantMass = multiplet.InvariantMass() / GeV;
        DeltaR = multiplet.DeltaR() / rad;
        LeptonPt1 = multiplet.LeptonPt(1) / GeV;
        LeptonPt2 = multiplet.LeptonPt(2) / GeV;
        BottomMinPt = multiplet.BottomMinPt() / GeV;
        BottomMaxRap = multiplet.BottomMaxRap() / rad;
    }
    virtual Observables Variables();

private:

    ClassDef(HeavyHiggsCut, 1)

};

class HeavyHiggsCutNeutral : public
branch::Cut
// branch::Bdt
{

public:

    HeavyHiggsCutNeutral();
    float JetPt1;
    float JetPt2;
    float JetPt3;
    float JetPt4;
    float Ht;
    float BottomNumber;
    float LeptonPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Cut::Fill(multiplet);
//         Bdt::Fill(multiplet);
        JetPt1 = multiplet.JetPt(0) / GeV;
        JetPt2 = multiplet.JetPt(1) / GeV;
        JetPt3 = multiplet.JetPt(2) / GeV;
        JetPt4 = multiplet.JetPt(3) / GeV;
        LeptonPt = multiplet.LeptonPt(0) / GeV;
        Ht = multiplet.Ht() / GeV;
        BottomNumber = multiplet.BottomNumber();
    }
    virtual Observables Variables();

private:

    ClassDef(HeavyHiggsCutNeutral, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class JetPair : public branch::TwoBody
{
public:
  JetPair();
  float Jet1Mass;
  float Jet1Pt;
  float Jet1Rap;
  float Jet1Phi;
  float Jet2Mass;
  float Jet2Pt;
  float Jet2Rap;
  float Jet2Phi;
  //     float BdtRatio11;
  //     float BdtRatio12;
  //     float BdtRatio13;
  //     float BdtRatio14;
  //     float BdtRatio21;
  //     float BdtRatio22;
  //     float BdtRatio23;
  //     float BdtRatio24;
  template<typename Multiplet>
  void Fill(Multiplet const& multiplet) {
    TwoBody::Fill(multiplet);
    Jet1Pt = multiplet.Singlet1().Pt() / GeV;
    Jet1Rap = multiplet.Singlet1().Rap() / rad;
    Jet1Phi = multiplet.Singlet1().Phi() / rad;
    Jet1Mass = multiplet.Singlet1().Mass() / GeV;
    Jet2Pt = multiplet.Singlet2().Pt() / GeV;
    Jet2Rap = multiplet.Singlet2().Rap() / rad;
    Jet2Phi = multiplet.Singlet2().Phi() / rad;
    Jet2Mass = multiplet.Singlet2().Mass() / GeV;
  }
  Observables Variables();

private:
  ClassDef(JetPair, 1)
};



/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletJetPair : public branch::TwoBody
{
public:
  TripletJetPair();
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
    TwoBody::Fill(multiplet);
    BottomPt = multiplet.Singlet().Pt() / GeV;
    //         BottomRap = std::abs(multiplet.Singlet().rap());
    BottomRap = multiplet.Singlet().Rap() / rad;
    BottomPhi = multiplet.Singlet().Phi() / rad;
    BottomMass = multiplet.Singlet().Mass() / GeV;
    //         BottomBdt = multiplet.Singlet().Info().Bdt();
    TopPt = multiplet.Triplet().Pt() / GeV;
    //         TopRap = std::abs(multiplet.Triplet().rap());
    TopRap = multiplet.Triplet().Rap() / rad;
    TopPhi = multiplet.Triplet().Phi() / rad;
    TopMass = multiplet.Triplet().Mass() / GeV;
    TopBdt = multiplet.Triplet().Bdt();
  }
  Observables Variables();

private:
  ClassDef(TripletJetPair, 1)
};

}

}
