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

    Observables Variables();
private:

    ClassDef(HeavyHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsHadronicBranch : public BaseBranch {

public:

    HHeavyHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HHeavyHiggsHadronicBranch, 1)

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
    virtual Observables Spectators();

private:

    ClassDef(ChargedHiggsSemiBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedHiggsHadronicBranch : public BaseBranch {

public:

    HChargedHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsHadronicBranch, 1)

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

    Observables Variables();
    virtual Observables Spectators();

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
        LeptonPt = multiplet.SingletJet1().pt();
        NeutrinoPt = multiplet.SingletJet2().pt();
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
class EventNeutralBranch : public EventBranch {

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
    void Fill(const Multiplet& multiplet)
    {
        EventBranch::Fill(multiplet);
        HiggsMass = multiplet.Multiplet().Sextet().Jet().m();
        HiggsBdt = multiplet.Multiplet().Sextet().Bdt();
        SignatureBdt = multiplet.Multiplet().Bdt();
        PairRap = multiplet.Multiplet().Doublet().DeltaRap();
        BottomBdt = multiplet.Multiplet().BottomBdt();
        PairBottomBdt = multiplet.Multiplet().PairBottomBdt();
        HardTopPt = multiplet.Multiplet().Sextet().HardTopPt();
        SoftTopPt = multiplet.Multiplet().Sextet().SoftTopPt();
        BottomBdt1 = multiplet.GlobalObservables().BottomBdt(1);
        BottomBdt2 = multiplet.GlobalObservables().BottomBdt(2);
        BottomBdt3 = multiplet.GlobalObservables().BottomBdt(3);
        BottomBdt4 = multiplet.GlobalObservables().BottomBdt(4);
        BottomBdt5 = multiplet.GlobalObservables().BottomBdt(5);
        BottomBdt6 = multiplet.GlobalObservables().BottomBdt(6);
        BottomBdt7 = multiplet.GlobalObservables().BottomBdt(7);
        BottomBdt8 = multiplet.GlobalObservables().BottomBdt(8);
        BottomBdt12 = multiplet.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = multiplet.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = multiplet.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = multiplet.GlobalObservables().BottomBdt(7, 8);
    }

    Observables Variables();

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
    void Fill(const Multiplet& multiplet)
    {
        EventBranch::Fill(multiplet);
        HiggsMass = multiplet.Multiplet().Sextet().Jet().m();
        HiggsBdt = multiplet.Multiplet().Sextet().Bdt();
        SignatureBdt = multiplet.Multiplet().Bdt();
        PairRap = multiplet.Multiplet().Doublet().DeltaRap();
        BottomBdt = multiplet.Multiplet().BottomBdt();
        PairBottomBdt = multiplet.Multiplet().PairBottomBdt();
        HardTopPt = multiplet.Multiplet().Sextet().HardTopPt();
        SoftTopPt = multiplet.Multiplet().Sextet().SoftTopPt();
        BottomBdt1 = multiplet.GlobalObservables().BottomBdt(1);
        BottomBdt2 = multiplet.GlobalObservables().BottomBdt(2);
        BottomBdt3 = multiplet.GlobalObservables().BottomBdt(3);
        BottomBdt4 = multiplet.GlobalObservables().BottomBdt(4);
        BottomBdt5 = multiplet.GlobalObservables().BottomBdt(5);
        BottomBdt6 = multiplet.GlobalObservables().BottomBdt(6);
        BottomBdt7 = multiplet.GlobalObservables().BottomBdt(7);
        BottomBdt8 = multiplet.GlobalObservables().BottomBdt(8);
        BottomBdt12 = multiplet.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = multiplet.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = multiplet.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = multiplet.GlobalObservables().BottomBdt(7, 8);
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

    Observables Variables();


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

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.PairBottomBdt();
        PairBdt = multiplet.Doublet().Bdt();
        HiggsBdt = multiplet.Sextet().Bdt();
        HardTopPt = multiplet.Sextet().HardTopPt();
        SoftTopPt = multiplet.Sextet().SoftTopPt();
        HiggsMass = multiplet.Sextet().Jet().m();
        PairRap = multiplet.Doublet().DeltaRap();
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
        PairBottomBdt = multiplet.PairBottomBdt();
        HiggsBdt = multiplet.Quartet1().Bdt();
        PairBdt = multiplet.Quartet2().Bdt();
        HiggsMass = multiplet.Quartet1().Jet().m();
        PairRap = multiplet.Quartet2().DeltaRap();
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
    void Fill(const Multiplet& multiplet)
    {
        EventBranch::Fill(multiplet);
        HiggsMass = multiplet.Multiplet().Quartet1().Jet().m();
        HiggsBdt = multiplet.Multiplet().Quartet1().Bdt();
        SignatureBdt = multiplet.Multiplet().Bdt();
        PairRap = multiplet.Multiplet().Quartet2().DeltaRap();
        BottomBdt = multiplet.Multiplet().BottomBdt();
        PairBottomBdt = multiplet.Multiplet().PairBottomBdt();
        BottomBdt1 = multiplet.GlobalObservables().BottomBdt(1);
        BottomBdt2 = multiplet.GlobalObservables().BottomBdt(2);
        BottomBdt3 = multiplet.GlobalObservables().BottomBdt(3);
        BottomBdt4 = multiplet.GlobalObservables().BottomBdt(4);
        BottomBdt5 = multiplet.GlobalObservables().BottomBdt(5);
        BottomBdt6 = multiplet.GlobalObservables().BottomBdt(6);
        BottomBdt7 = multiplet.GlobalObservables().BottomBdt(7);
        BottomBdt8 = multiplet.GlobalObservables().BottomBdt(8);
        BottomBdt12 = multiplet.GlobalObservables().BottomBdt(1, 2);
        BottomBdt34 = multiplet.GlobalObservables().BottomBdt(3, 4);
        BottomBdt56 = multiplet.GlobalObservables().BottomBdt(5, 6);
        BottomBdt78 = multiplet.GlobalObservables().BottomBdt(7, 8);
        RestBdt = multiplet.GlobalObservables().BottomBdt();
        LeptonHt = multiplet.GlobalObservables().LeptonHt();
    }

    Observables Variables();

private:

    ClassDef(EventChargedBranch, 1)

};

}

}
