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
    float veto_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

class SignatureSingleHadronicBranch : public branch::ThreeBody, public branch::EventShapesBase
{
public:
    SignatureSingleHadronicBranch();
    float veto_bdt;
    float top_pt;
    float higgs_pt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ThreeBody::Fill(multiplet);
        EventShapesBase::Fill(multiplet);
        veto_bdt = multiplet.VetoBdt();
        top_pt = multiplet.Triplet().Pt() / GeV;
        higgs_pt = multiplet.Doublet().Pt() / GeV;
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

    float signature_bdt;
    float global_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        signature_bdt = multiplet.Signature().Bdt();
        global_bdt = multiplet.GlobalObservables().Bdt();
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

    float signature_bdt;
    float veto_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        signature_bdt = multiplet.Signature().Bdt();
        veto_bdt = multiplet.Signature().VetoBdt();
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

    float signature_bdt;
    float veto_bdt;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        signature_bdt = multiplet.Signature().Bdt();
        veto_bdt = multiplet.Signature().VetoBdt();
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
    float signature_bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Bdt::Fill(multiplet);
        GlobalBase::Fill(multiplet.GlobalObservables());
        EventShapesBase::Fill(multiplet);
        signature_bdt = multiplet.Signature().Bdt();
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
    float top_pt;
    float lepton_pt;
    float boson_number;
    float hard_boson_number;
    float softest_boson_pt;
    float hardest_boson_pt;
    float detectable_boson_number;
    float boson_delta_r_min;
    float missing_et;
    float scalar_ht;
    float jet_pt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        top_pt = multiplet.TopPt(0) / GeV;
        lepton_pt = multiplet.LeptonPt(0) / GeV;
        boson_number = multiplet.BosonNumber();
        hard_boson_number = multiplet.HardBosonNumber();
        softest_boson_pt = multiplet.SoftBosonPt() / GeV;
        hardest_boson_pt = multiplet.HardBosonPt() / GeV;
        detectable_boson_number = multiplet.DetectableBosonNumber();
        boson_delta_r_min = multiplet.BosonDeltaRMin() / rad;
        missing_et = multiplet.MissingEt() / GeV;
        scalar_ht = multiplet.ScalarHt() / GeV;
        jet_pt = multiplet.JetPt(0) / GeV;
    }
    virtual Observables Variables();
private:
    ClassDef(Truth, 1)
};

}

}
