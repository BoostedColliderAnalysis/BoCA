#pragma once

#include "boca/branch/Multi.hh"
#include "boca/branch/Signature.hh"
#include "boca/branch/Event.hh"
#include "boca/branch/GlobalBase.hh"

namespace boca
{

namespace toppartner
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public branch::Multi
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(TopPartnerBranch, 1)
};

class VetoTopPartnerBranch : public branch::Multi, public branch::EventShapesBase
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
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
class HiggsTwoBody : public branch::Multi
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Multi::Fill(multiplet);
    }
private:
    ClassDef(HiggsTwoBody, 1)
};

// class ThreeBody : public Multi
// {
// public:
//     template<typename Multiplet>
//     void Fill(Multiplet const& multiplet) {
//         Multi::Fill(multiplet);
//     }
// private:
//     ClassDef(ThreeBody, 1)
// };

class SignatureSingleBranch : public branch::ThreeBody
{
public:
    SignatureSingleBranch();
    float VetoBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

class SignatureSingleHadronicBranch : public branch::ThreeBody, public branch::EventShapesBase
{
public:
    SignatureSingleHadronicBranch();
    float VetoBdt;
    float TopPt;
    float HiggsPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
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

class SignatureEffectiveBranch : public branch::ThreeBody, public branch::EventShapesBase
{
public:
    SignatureEffectiveBranch();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();
private:
    ClassDef(SignatureEffectiveBranch, 1)
};

// class Event : public boca::branch::Event
// {
// public:
//     template<typename Multiplet>
//     void Fill(Multiplet const& multiplet) {
//       boca::branch::Event::Fill(multiplet);
//     }
// private:
//     ClassDef(Event, 1)
// };



/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent : public branch::Bdt
{
public:
    NewEvent();

    float SignatureBdt;
    float GlobalBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
      Bdt::Fill(multiplet);
        SignatureBdt = multiplet.Signature().Bdt();
        GlobalBdt = multiplet.GlobalObservables().Bdt();
    }
    Observables Variables();

private:
    ClassDef(NewEvent, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent2 : public branch::Bdt, branch::GlobalBase
{
public:
    NewEvent2();

    float SignatureBdt;
    float VetoBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
      Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        SignatureBdt = multiplet.Signature().Bdt();
        VetoBdt = multiplet.Signature().VetoBdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEvent2, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent3 : public branch::Bdt, branch::GlobalBase
{
public:
    NewEvent3();

    float SignatureBdt;
    float VetoBdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        SignatureBdt = multiplet.Signature().Bdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEvent3, 1)
};


/**
 * @brief Class for saving event informations to root
 *
 */
class NewEvent4 : public branch::Bdt, branch::GlobalBase, branch::EventShapesBase
{
public:
    NewEvent4();
    float SignatureBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        EventShapesBase::Fill(multiplet);
        SignatureBdt = multiplet.Signature().Bdt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(NewEvent4, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class CompleteBranch : public SignatureSingleHadronicBranch, branch::GlobalBase
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
class Truth : public branch::Bdt
{
public:
    Truth();
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
    ClassDef(Truth, 1)
};

}

}
