#include "Branch.hh"

#define PAIR1(value) Obs(value, #value, #value)
#define PAIR2(value, string) Obs(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define PAIRCHOOSER(...) ARGUMENTS(__VA_ARGS__, PAIR2, PAIR1, )

#define PAIR(...) PAIRCHOOSER(__VA_ARGS__)(__VA_ARGS__)

ClassImp(analysis::heavyhiggs::HeavyHiggsLeptonicBranch)

analysis::heavyhiggs::HeavyHiggsLeptonicBranch::HeavyHiggsLeptonicBranch()
{
    LargerWDeltaRap = InitialValue();
    LargerWDeltaPhi = InitialValue();
    LargerWDeltaR = InitialValue();
    SmallerWDeltaRap = InitialValue();
    SmallerWDeltaPhi = InitialValue();
    SmallerWDeltaR = InitialValue();
    LargerNeutrinoDeltaRap = InitialValue();
    LargerNeutrinoDeltaPhi = InitialValue();
    LargerNeutrinoDeltaR = InitialValue();
    SmallerNeutrinoDeltaRap = InitialValue();
    SmallerNeutrinoDeltaPhi = InitialValue();
    SmallerNeutrinoDeltaR = InitialValue();
}

ClassImp(analysis::heavyhiggs::HHeavyHiggsHadronicBranch)

analysis::heavyhiggs::HHeavyHiggsHadronicBranch::HHeavyHiggsHadronicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}

ClassImp(analysis::heavyhiggs::HeavyHiggsSemiBranch)

analysis::heavyhiggs::HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ClassImp(analysis::heavyhiggs::ChargedHiggsSemiBranch)

analysis::heavyhiggs::ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
    Flag = int(InitialValue());
}

ClassImp(analysis::heavyhiggs::HChargedHiggsHadronicBranch)

analysis::heavyhiggs::HChargedHiggsHadronicBranch::HChargedHiggsHadronicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}


ClassImp(analysis::heavyhiggs::ChargedHiggsLeptonicBranch)

analysis::heavyhiggs::ChargedHiggsLeptonicBranch::ChargedHiggsLeptonicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    LargerWDeltaRap = InitialValue();
    LargerWDeltaPhi = InitialValue();
    LargerWDeltaR = InitialValue();
    SmallerWDeltaRap = InitialValue();
    SmallerWDeltaPhi = InitialValue();
    SmallerWDeltaR = InitialValue();
    LargerNeutrinoDeltaRap = InitialValue();
    LargerNeutrinoDeltaPhi = InitialValue();
    LargerNeutrinoDeltaR = InitialValue();
    SmallerNeutrinoDeltaRap = InitialValue();
    SmallerNeutrinoDeltaPhi = InitialValue();
    SmallerNeutrinoDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}


ClassImp(analysis::heavyhiggs::HeavyHiggsTauBranch)

analysis::heavyhiggs::HeavyHiggsTauBranch::HeavyHiggsTauBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

ClassImp(analysis::heavyhiggs::EventNeutralBranch)

analysis::heavyhiggs::EventNeutralBranch::EventNeutralBranch()
{
    HiggsMass = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();
}

ClassImp(analysis::heavyhiggs::EventFusionBranch)

analysis::heavyhiggs::EventFusionBranch::EventFusionBranch()
{
    HiggsMass = InitialValue();
}


ClassImp(analysis::heavyhiggs::OctetNeutralBranch)

analysis::heavyhiggs::OctetNeutralBranch::OctetNeutralBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
    HardTopPt = InitialValue();
    SoftTopPt = InitialValue();
}


ClassImp(analysis::heavyhiggs::OctetChargedBranch)

analysis::heavyhiggs::OctetChargedBranch::OctetChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    HiggsBdt = InitialValue();
    PairBdt = InitialValue();
}

ClassImp(analysis::heavyhiggs::EventChargedBranch)

analysis::heavyhiggs::EventChargedBranch::EventChargedBranch()
{
    HiggsMass = InitialValue();
    PairRap = InitialValue();
    HiggsBdt = InitialValue();
    SignatureBdt = InitialValue();
    BottomBdt = InitialValue();
    PairBottomBdt = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt7 = InitialValue();
    BottomBdt8 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt78 = InitialValue();
}
namespace analysis
{
namespace heavyhiggs
{
analysis::Observables HeavyHiggsLeptonicBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(LargerWDeltaR), PAIR(LargerWDeltaRap), PAIR(LargerWDeltaPhi), PAIR(SmallerWDeltaR), PAIR(SmallerWDeltaRap), PAIR(SmallerWDeltaPhi), PAIR(LargerNeutrinoDeltaR), PAIR(LargerNeutrinoDeltaRap), PAIR(LargerNeutrinoDeltaPhi), PAIR(SmallerNeutrinoDeltaR), PAIR(SmallerNeutrinoDeltaRap), PAIR(SmallerNeutrinoDeltaPhi)});
}
Observables ChargedHiggsLeptonicBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(HeavyHiggsMass), PAIR(HeavyHiggsPt), PAIR(TopDeltaR), PAIR(TopDeltaRap), PAIR(TopDeltaPhi), PAIR(TopBdt)});
}
Observables ChargedHiggsLeptonicBranch::Spectators()
{
    return Join(ParticleBranch::Spectators(), {PAIR(HeavyHiggsTag)});
}
Observables HeavyHiggsTauBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(LeptonPt), PAIR(NeutrinoPt)});
}
Observables EventNeutralBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}
Observables EventFusionBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass)});
}
Observables OctetNeutralBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(HardTopPt), PAIR(SoftTopPt), PAIR(PairBottomBdt)});
}
Observables OctetChargedBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(PairBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt)});
}
Observables EventChargedBranch::Variables()
{
    return Join(EventBranch::Variables(), {PAIR(HiggsMass), PAIR(HiggsBdt), PAIR(SignatureBdt), PAIR(PairRap), PAIR(BottomBdt), PAIR(PairBottomBdt), PAIR(BottomBdt1), PAIR(BottomBdt2), PAIR(BottomBdt3), PAIR(BottomBdt4), PAIR(BottomBdt5), PAIR(BottomBdt6), PAIR(BottomBdt7), PAIR(BottomBdt8), PAIR(BottomBdt12), PAIR(BottomBdt34), PAIR(BottomBdt56), PAIR(BottomBdt78)});
}
Observables ChargedHiggsSemiBranch::Spectators()
{
    return Join(ParticleBranch::Spectators(), {PAIR(Flag)});
}
}
}

