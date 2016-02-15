#pragma once

#include "Branches.hh"

namespace boca
{

namespace heavyhiggs
{


/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsLeptonicBranch : public PairBranch
{

public:

    HeavyHiggsLeptonicBranch();

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
        PairBranch::Fill(multiplet);
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

    ClassDef(HeavyHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsSemiBranch : public MultiBranch
{

public:

    HeavyHiggsSemiBranch();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }

private:

    ClassDef(HeavyHiggsSemiBranch, 1)

};

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class ChargedHiggsSemiBranch : public MultiBranch
{

public:

//     float Flag;
    ChargedHiggsSemiBranch();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
//         Flag = multiplet.Flag();
    }
//     virtual Observables Spectators();

private:

    ClassDef(ChargedHiggsSemiBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class ChargedHiggsLeptonicBranch : public MultiBranch
{

public:

    ChargedHiggsLeptonicBranch();

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
        MultiBranch::Fill(multiplet);
        HeavyHiggsMass = multiplet.Jet().Mass() / GeV;
        HeavyHiggsPt = multiplet.Jet().Mass() / GeV;
        TopDeltaR = multiplet.DeltaR() / rad;
        TopDeltaRap = multiplet.DeltaRap() / rad;
        TopDeltaPhi = multiplet.DeltaPhi() / rad;
        TopBdt = multiplet.Bdt();
        HeavyHiggsTag = int(multiplet.Tag());
    }

    Observables Variables();
    Observables Spectators();

private:

    ClassDef(ChargedHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HeavyHiggsTauBranch : public PairBranch
{

public:

    HeavyHiggsTauBranch();

    float LeptonPt;
    float NeutrinoPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Jet().Pt() / GeV;
        NeutrinoPt = multiplet.Singlet2().Jet().Pt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(HeavyHiggsTauBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventNeutralBranch : public EventBranch
{

public:

    EventNeutralBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float HardTopPt;
    float SoftTopPt;

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

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        EventBranch::Fill(event);
        HiggsMass = event.Signature().Sextet().Jet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        BottomBdt = event.Signature().BottomBdt();
        PairBottomBdt = event.Signature().Doublet().BottomBdt();
        HardTopPt = event.Signature().Sextet().HardTopPt() / GeV;
        SoftTopPt = event.Signature().Sextet().SoftTopPt() / GeV;
        BottomBdt1 = event.GlobalObservables().BottomBdt(1);
        BottomBdt2 = event.GlobalObservables().BottomBdt(2);
        BottomBdt3 = event.GlobalObservables().BottomBdt(3);
        BottomBdt4 = event.GlobalObservables().BottomBdt(4);
        BottomBdt5 = event.GlobalObservables().BottomBdt(5);
        BottomBdt6 = event.GlobalObservables().BottomBdt(6);
        BottomBdt7 = event.GlobalObservables().BottomBdt(7);
        BottomBdt8 = event.GlobalObservables().BottomBdt(8);
        BottomBdt12 = event.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = event.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = event.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = event.GlobalObservables().BottomBdt(7, 8);
    }

    Observables Variables();

private:

    ClassDef(EventNeutralBranch, 1)

};
class EventNeutralFourTopBranch : public EventBranch
{

public:

    EventNeutralFourTopBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float HardTopPt;
    float SoftTopPt;

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

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        EventBranch::Fill(event);
        HiggsMass = event.Signature().Sextet().Jet().Mass() / GeV;
        HiggsBdt = event.Signature().Sextet().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Doublet().DeltaRap() / rad;
        BottomBdt = event.Signature().BottomBdt();
        PairBottomBdt = event.Signature().Doublet().BottomBdt();
        HardTopPt = event.Signature().Sextet().HardTopPt() / GeV;
        SoftTopPt = event.Signature().Sextet().SoftTopPt() / GeV;
        BottomBdt1 = event.GlobalObservables().BottomBdt(1);
        BottomBdt2 = event.GlobalObservables().BottomBdt(2);
        BottomBdt3 = event.GlobalObservables().BottomBdt(3);
        BottomBdt4 = event.GlobalObservables().BottomBdt(4);
        BottomBdt5 = event.GlobalObservables().BottomBdt(5);
        BottomBdt6 = event.GlobalObservables().BottomBdt(6);
        BottomBdt7 = event.GlobalObservables().BottomBdt(7);
        BottomBdt8 = event.GlobalObservables().BottomBdt(8);
        BottomBdt12 = event.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = event.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = event.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = event.GlobalObservables().BottomBdt(7, 8);
    }

    Observables Variables();

private:

    ClassDef(EventNeutralFourTopBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusionBranch : public EventBranch
{

public:

    EventFusionBranch();


    float HiggsMass;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        EventBranch::Fill(multiplet);
        HiggsMass = multiplet.Jet().Mass() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventFusionBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutralBranch : public MultiBranch
{

public:

    OctetNeutralBranch();

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
        MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.Doublet().BottomBdt();
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        HardTopPt = multiplet.Sextet().HardTopPt() / GeV;
        SoftTopPt = multiplet.Sextet().SoftTopPt() / GeV;
        HiggsMass = multiplet.Sextet().Jet().Mass() / GeV;
        PairRap = multiplet.Doublet().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetNeutralBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetChargedBranch : public MultiBranch
{

public:

    OctetChargedBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;


    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.Quartet2().BottomBdt();
        HiggsBdt = multiplet.Quartet1().Bdt();
        PairBdt = multiplet.Quartet2().Bdt();
        HiggsMass = multiplet.Quartet1().Jet().Mass() / GeV;
        PairRap = multiplet.Quartet2().DeltaRap() / rad;
    }

    Observables Variables();

private:

    ClassDef(OctetChargedBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventChargedBranch : public EventBranch
{

public:

    EventChargedBranch();

    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float SignatureBdt;
    float BottomBdt;
    float PairBottomBdt;

    float RestBdt;

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

    template<typename Multiplet>
    void Fill(Multiplet const& event) {
        EventBranch::Fill(event);
        HiggsMass = event.Signature().Quartet1().Jet().Mass() / GeV;
        HiggsBdt = event.Signature().Quartet1().Bdt();
        SignatureBdt = event.Signature().Bdt();
        PairRap = event.Signature().Quartet2().DeltaRap() / rad;
        BottomBdt = event.Signature().BottomBdt();
        PairBottomBdt = event.Signature().Quartet2().BottomBdt();
        BottomBdt1 = event.GlobalObservables().BottomBdt(1);
        BottomBdt2 = event.GlobalObservables().BottomBdt(2);
        BottomBdt3 = event.GlobalObservables().BottomBdt(3);
        BottomBdt4 = event.GlobalObservables().BottomBdt(4);
        BottomBdt5 = event.GlobalObservables().BottomBdt(5);
        BottomBdt6 = event.GlobalObservables().BottomBdt(6);
        BottomBdt7 = event.GlobalObservables().BottomBdt(7);
        BottomBdt8 = event.GlobalObservables().BottomBdt(8);
        BottomBdt12 = event.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = event.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = event.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = event.GlobalObservables().BottomBdt(7, 8);
        RestBdt = event.GlobalObservables().BottomBdt();
        LeptonHt = event.GlobalObservables().LeptonHt() / GeV;
    }

    Observables Variables();

private:

    ClassDef(EventChargedBranch, 1)

};

class HeavyHiggsCutBranch : public CutBranch
{

public:

    HeavyHiggsCutBranch();
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
        CutBranch::Fill(multiplet);
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

    ClassDef(HeavyHiggsCutBranch, 1)

};

class HeavyHiggsCutNeutralBranch : public CutBranch
{

public:

    HeavyHiggsCutNeutralBranch();
    float JetPt1;
    float JetPt2;
    float JetPt3;
    float JetPt4;
    float Ht;
    float BottomNumber;
    float LeptonPt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        CutBranch::Fill(multiplet);
        JetPt1 = multiplet.JetPt(1) / GeV;
        JetPt2 = multiplet.JetPt(2) / GeV;
        JetPt3 = multiplet.JetPt(3) / GeV;
        JetPt4 = multiplet.JetPt(4) / GeV;
        LeptonPt = multiplet.LeptonPt(1) / GeV;
        Ht = multiplet.Ht() / GeV;
        BottomNumber = multiplet.BottomNumber();
    }
    virtual Observables Variables();

private:

    ClassDef(HeavyHiggsCutNeutralBranch, 1)

};

}

}
