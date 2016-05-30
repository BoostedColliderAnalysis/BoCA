#pragma once

#include "boca/../../boca/Branches.hh"

namespace boca
{

namespace toppartner
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(TopPartnerBranch, 1)
};

class VetoTopPartnerBranch : public MultiBranch, public EventShapesBase
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
    }
    virtual Observables Variables();
    virtual Observables Spectators();
private:
    ClassDef(VetoTopPartnerBranch, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class HiggsTwoBodyBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(HiggsTwoBodyBranch, 1)
};

// class ThreeBodyBranch : public MultiBranch
// {
// public:
//     template<typename Multiplet>
//     void Fill(Multiplet const& multiplet) {
//         MultiBranch::Fill(multiplet);
//     }
// private:
//     ClassDef(ThreeBodyBranch, 1)
// };

class SignatureSingleBranch : public ThreeBodyBranch
{
public:
    SignatureSingleBranch();
    float VetoBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBodyBranch::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

class SignatureSingleHadronicBranch : public ThreeBodyBranch, public EventShapesBase
{
public:
    SignatureSingleHadronicBranch();
    float VetoBdt;
    float TopPt;
    float HiggsPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBodyBranch::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
        TopPt = multiplet.Triplet().Pt() / GeV;
        HiggsPt = multiplet.Doublet().Pt() / GeV;
    }
    Observables Variables();
    Observables Spectators();
private:
    ClassDef(SignatureSingleHadronicBranch, 1)
};

class SignatureEffectiveBranch : public ThreeBodyBranch, public EventShapesBase
{
public:
    SignatureEffectiveBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBodyBranch::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();
private:
    ClassDef(SignatureEffectiveBranch, 1)
};

class EventBranch : public boca::EventBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::EventBranch::Fill(multiplet);
    }
private:
    ClassDef(EventBranch, 1)
};



/**
 * @brief Class for saving event informations to root
 *
 */
class NewEventBranch : public BdtBranch
{
public:
    NewEventBranch();

    float SignatureBdt;
    float GlobalBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::BdtBranch::Fill(multiplet);
        SignatureBdt = multiplet.Signature().Bdt();
        GlobalBdt = multiplet.GlobalObservables().Bdt();
    }
    Observables Variables();

private:
    ClassDef(NewEventBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEventBranch2 : public BdtBranch, GlobalBase
{
public:
    NewEventBranch2();

    float SignatureBdt;
    float VetoBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::BdtBranch::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        SignatureBdt = multiplet.Signature().Bdt();
        VetoBdt = multiplet.Signature().VetoBdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEventBranch2, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEventBranch3 : public BdtBranch, GlobalBase
{
public:
    NewEventBranch3();

    float SignatureBdt;
    float VetoBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        BdtBranch::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        SignatureBdt = multiplet.Signature().Bdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEventBranch3, 1)
};


/**
 * @brief Class for saving event informations to root
 *
 */
class NewEventBranch4 : public BdtBranch, GlobalBase, EventShapesBase
{
public:
    NewEventBranch4();
    float SignatureBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        BdtBranch::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        EventShapesBase::Fill(multiplet);
        SignatureBdt = multiplet.Signature().Bdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEventBranch4, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class CompleteBranch : public SignatureSingleHadronicBranch, GlobalBase
{
public:
    CompleteBranch();

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        SignatureSingleHadronicBranch::Fill(multiplet.Signature());
        GlobalBase::Fill(multiplet.GlobalObservables());
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(CompleteBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TruthBranch : public BdtBranch
{
public:
    TruthBranch();
    float TopPt;
    float LeptonPt;
    float BosonNumber;
    float HardBosonNumber;
    float SoftestBosonPt;
    float HardestBosonPt;
    float DetectableBosonNumber;
    float BosonDeltaRMin;
    float MissingEt;
    float ScalarHt;
    float JetPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TopPt = multiplet.TopPt(0) / GeV;
        LeptonPt = multiplet.LeptonPt(0) / GeV;
        BosonNumber = multiplet.BosonNumber();
        HardBosonNumber = multiplet.HardBosonNumber();
        SoftestBosonPt = multiplet.SoftBosonPt() / GeV;
        HardestBosonPt = multiplet.HardBosonPt() / GeV;
        DetectableBosonNumber = multiplet.DetectableBosonNumber();
        BosonDeltaRMin = multiplet.BosonDeltaRMin() / rad;
        MissingEt = multiplet.MissingEt() / GeV;
        ScalarHt = multiplet.ScalarHt() / GeV;
        JetPt = multiplet.JetPt(0) / GeV;
    }
    virtual Observables Variables();
private:
    ClassDef(TruthBranch, 1)
};

}

}
