# pragma once

# include "Branches.hh"

namespace heavyhiggs {


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventNeutralBranch : public analysis::MultiBranch
{

public:

    EventNeutralBranch();

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

        HiggsMass = multiplet.multiplet().sextet().Jet().m();
        HiggsBdt = multiplet.multiplet().sextet().Bdt();
        SignatureBdt = multiplet.multiplet().Bdt();
        PairRap = multiplet.multiplet().doublet().DeltaRap();
        BottomBdt = multiplet.multiplet().BottomBdt();
        PairBottomBdt = multiplet.multiplet().PairBottomBdt();

        HardTopPt = multiplet.multiplet().sextet().HardTopPt();
        SoftTopPt = multiplet.multiplet().sextet().SoftTopPt();

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

    ClassDef(EventNeutralBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventFusionBranch : public analysis::MultiBranch
{

public:

    EventFusionBranch();


    float HiggsMass;
    float HiggsBdt;

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

private:

    ClassDef(EventFusionBranch, 1)

};


/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetNeutralBranch : public analysis::MultiBranch
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
    void Fill(const Multiplet &multiplet) {
        analysis::MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.PairBottomBdt();
        PairBdt = multiplet.doublet().Bdt();
        HiggsBdt = multiplet.sextet().Bdt();
        HardTopPt = multiplet.sextet().HardTopPt();
        SoftTopPt = multiplet.sextet().SoftTopPt();
        HiggsMass = multiplet.sextet().Jet().m();
        PairRap = multiplet.doublet().DeltaRap();
    }

private:

    ClassDef(OctetNeutralBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class OctetChargedBranch : public analysis::MultiBranch
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
    void Fill(const Multiplet &multiplet) {
        analysis::MultiBranch::Fill(multiplet);
        BottomBdt = multiplet.BottomBdt();
        PairBottomBdt = multiplet.PairBottomBdt();
        HiggsBdt = multiplet.quartet1().Bdt();
        PairBdt = multiplet.quartet2().Bdt();

        HiggsMass = multiplet.quartet1().Jet().m();
        PairRap = multiplet.quartet2().DeltaRap();
    }

private:

    ClassDef(OctetChargedBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class EventChargedBranch : public analysis::MultiBranch
{

public:

    EventChargedBranch();

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

        HiggsMass = multiplet.multiplet().quartet1().Jet().m();
        PairRap = multiplet.multiplet().quartet2().DeltaRap();
        HiggsBdt = multiplet.multiplet().quartet1().Bdt();
        SignatureBdt = multiplet.multiplet().Bdt();
        BottomBdt = multiplet.multiplet().BottomBdt();
        PairBottomBdt = multiplet.multiplet().PairBottomBdt();

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
        MissingEt = multiplet.MissingEt();

        LeptonHt = multiplet.LeptonHt();
    }

private:

    ClassDef(EventChargedBranch, 1)

};

}
