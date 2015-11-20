#pragma once

#include "Branches.hh"

namespace analysis {

namespace heavyhiggs {


/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsLeptonicBranch : public PairBranch {

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
    void Fill(const Multiplet& multiplet)
    {
        PairBranch::Fill(multiplet);
        LargerWDeltaR = multiplet.GetLargertripletDeltaR();
        LargerWDeltaRap = multiplet.GetLargertripletDeltaRap();
        LargerWDeltaPhi = multiplet.GetLargerTripleDeltaPhi();
        SmallerWDeltaR = multiplet.GetSmallertripletDeltaR();
        SmallerWDeltaRap = multiplet.GetSmallertripletDeltaRap();
        SmallerWDeltaPhi = multiplet.GetSmallertripletDeltaPhi();
        LargerNeutrinoDeltaR = multiplet.GetLargertripletDeltaR();
        LargerNeutrinoDeltaRap = multiplet.GetLargertripletDeltaRap();
        LargerNeutrinoDeltaPhi = multiplet.GetLargerTripleDeltaPhi();
        SmallerNeutrinoDeltaR = multiplet.GetSmallertripletDeltaR();
        SmallerNeutrinoDeltaRap = multiplet.GetSmallertripletDeltaRap();
        SmallerNeutrinoDeltaPhi = multiplet.GetSmallertripletDeltaPhi();
    }

    Observables Variables() const;

private:

    ClassDef(HeavyHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HeavyHiggsSemiBranch : public MultiBranch {

public:

    HeavyHiggsSemiBranch();

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
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
class ChargedHiggsSemiBranch : public MultiBranch {

public:

    float Flag;
    ChargedHiggsSemiBranch();

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
        Flag = multiplet.Flag();
    }
    virtual Observables Spectators() const;

private:

    ClassDef(ChargedHiggsSemiBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class ChargedHiggsLeptonicBranch : public MultiBranch {

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
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
        HeavyHiggsMass = multiplet.Jet().m();
        HeavyHiggsPt = multiplet.Jet().m();
        TopDeltaR = multiplet.DeltaR();
        TopDeltaRap = multiplet.DeltaRap();
        TopDeltaPhi = multiplet.DeltaPhi();
        TopBdt = multiplet.Bdt();
        HeavyHiggsTag = int(multiplet.Tag());
    }

    Observables Variables() const;
    Observables Spectators() const;

private:

    ClassDef(ChargedHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HeavyHiggsTauBranch : public PairBranch {

public:

    HeavyHiggsTauBranch();

    float LeptonPt;
    float NeutrinoPt;

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Jet().pt();
        NeutrinoPt = multiplet.Singlet2().Jet().pt();
    }

    Observables Variables() const;

private:

    ClassDef(HeavyHiggsTauBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventNeutralBranch : public EventBranch {

public:

    EventNeutralBranch();
    float HiggsMass;
    float PairRap;
    float HiggsBdt;
    float PairBdt;
    float BottomBdt;
    float PairBottomBdt;
    float JetRestNumber;
    float HardTopPt;
    float SoftTopPt;
    float BdtSum;
    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float RestBottomBdt1;
    float RestBottomBdt2;
    float RestBottomBdt3;
    float RestBottomBdt4;
    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;
    float BottomBdt78;
    float Sphericity;
    float Aplanarity;
    float Planarity;
    float Dipolarity1;
    float Dipolarity2;
    float Pull1;
    float Pull2;

    template<typename Multiplet>
    void Fill(const Multiplet& event)
    {
        EventBranch::Fill(event);
        HiggsMass = event.Multiplet().Sextet().Jet().m();
        HiggsBdt = event.Multiplet().Sextet().Bdt();
        PairBdt = event.Multiplet().Doublet().Bdt();
        PairRap = event.Multiplet().Doublet().DeltaRap();
        BottomBdt = event.Multiplet().BottomBdt();
        PairBottomBdt = event.Multiplet().Doublet().BottomBdt();
        HardTopPt = event.Multiplet().Sextet().HardTopPt();
        SoftTopPt = event.Multiplet().Sextet().SoftTopPt();
        JetRestNumber = event.GlobalObservables().JetNumber();
        BdtSum = event.Multiplet1().Bdt()+event.Multiplet2().Bdt();
        BottomBdt1 = event.BottomBdt(1);
        BottomBdt2 = event.BottomBdt(2);
        BottomBdt3 = event.BottomBdt(3);
        BottomBdt4 = event.BottomBdt(4);
        RestBottomBdt1 = event.GlobalObservables().BottomBdt(1);
        RestBottomBdt2 = event.GlobalObservables().BottomBdt(2);
        RestBottomBdt3 = event.GlobalObservables().BottomBdt(3);
        RestBottomBdt4 = event.GlobalObservables().BottomBdt(4);
        Sphericity = event.EventShape().Sphericity();
        Aplanarity = event.EventShape().Aplanarity();
        Planarity = event.EventShape().Planarity();
        Dipolarity1 = event.Multiplet().Sextet().Dipolarity1();
        Dipolarity2 = event.Multiplet().Sextet().Dipolarity2();
        Dipolarity1 = event.Multiplet().Sextet().Dipolarity1();
        Dipolarity2 = event.Multiplet().Sextet().Dipolarity2();
//         BottomBdt12 = event.GlobalObservables().BottomBdt(1, 2);
//         BottomBdt34 = event.GlobalObservables().BottomBdt(3, 4);
//         BottomBdt56 = event.GlobalObservables().BottomBdt(5, 6);
//         BottomBdt78 = event.GlobalObservables().BottomBdt(7, 8);
    }

    Observables Variables() const;

private:

    ClassDef(EventNeutralBranch, 1)

};
class EventNeutralFourTopBranch : public EventBranch {

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
    void Fill(const Multiplet& event)
    {
        EventBranch::Fill(event);
        HiggsMass = event.Multiplet().Sextet().Jet().m();
        HiggsBdt = event.Multiplet().Sextet().Bdt();
        SignatureBdt = event.Multiplet().Bdt();
        PairRap = event.Multiplet().Doublet().DeltaRap();
        BottomBdt = event.Multiplet().BottomBdt();
        PairBottomBdt = event.Multiplet().Doublet().BottomBdt();
        HardTopPt = event.Multiplet().Sextet().HardTopPt();
        SoftTopPt = event.Multiplet().Sextet().SoftTopPt();
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

    Observables Variables() const;

private:

    ClassDef(EventNeutralFourTopBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusionBranch : public EventBranch {

public:

    EventFusionBranch();


    float HiggsMass;

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        EventBranch::Fill(multiplet);
        HiggsMass = multiplet.Jet().m();
    }

    Observables Variables() const;

private:

    ClassDef(EventFusionBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutralBranch : public MultiBranch {

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
    float BdtSum;

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.Doublet().BottomBdt();
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        BdtSum = multiplet.Multiplet1().Bdt()+multiplet.Multiplet2().Bdt();
        HardTopPt = multiplet.Sextet().HardTopPt();
        SoftTopPt = multiplet.Sextet().SoftTopPt();
        HiggsMass = multiplet.Sextet().Jet().m();
        PairRap = multiplet.Doublet().DeltaRap();
    }

    Observables Variables() const;

private:

    ClassDef(OctetNeutralBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetChargedBranch : public MultiBranch {

public:

    OctetChargedBranch();

    float HiggsMass;
    float PairRap;
    float BottomBdt;
    float PairBottomBdt;
    float HiggsBdt;
    float PairBdt;


    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.Quartet2().BottomBdt();
        HiggsBdt = multiplet.Quartet1().Bdt();
        PairBdt = multiplet.Quartet2().Bdt();
        HiggsMass = multiplet.Quartet1().Jet().m();
        PairRap = multiplet.Quartet2().DeltaRap();
    }

    Observables Variables() const;

private:

    ClassDef(OctetChargedBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventChargedBranch : public EventBranch {

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
    void Fill(const Multiplet& event)
    {
        EventBranch::Fill(event);
        HiggsMass = event.Multiplet().Quartet1().Jet().m();
        HiggsBdt = event.Multiplet().Quartet1().Bdt();
        SignatureBdt = event.Multiplet().Bdt();
        PairRap = event.Multiplet().Quartet2().DeltaRap();
        BottomBdt = event.Multiplet().BottomBdt();
        PairBottomBdt = event.Multiplet().Quartet2().BottomBdt();
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
        LeptonHt = event.GlobalObservables().LeptonHt();
    }

    Observables Variables() const;

private:

    ClassDef(EventChargedBranch, 1)

};

}

}
