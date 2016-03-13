#pragma once

#include "../../include/Branches.hh"

namespace boca
{

namespace naturalness
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

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class HiggsPairBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(HiggsPairBranch, 1)
};

// class SignatureBranch : public MultiBranch
// {
// public:
//     template<typename Multiplet>
//     void Fill(Multiplet const& multiplet) {
//         MultiBranch::Fill(multiplet);
//     }
// private:
//     ClassDef(SignatureBranch, 1)
// };

class SignatureSingleBranch : public SignatureBranch
{
public:
    SignatureSingleBranch();
    float VetoBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        SignatureBranch::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

class SignatureSingleHadronicBranch : public SignatureBranch
{
public:
    SignatureSingleHadronicBranch();
    float VetoBdt;
    float TopPt;
    float HiggsPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        SignatureBranch::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
        TopPt = multiplet.Triplet().Pt() / GeV;
        HiggsPt = multiplet.Doublet().Pt() / GeV;
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleHadronicBranch, 1)
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
