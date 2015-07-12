#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"
// #include <stdlib.h>

#define STRING(s) #s

#define PAIR1(value) Obs(value, STRING(value), STRING(value))
#define PAIR2(value, string) Obs(value, STRING(value), string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define PAIRCHOOSER(...) ARGUMENTS(__VA_ARGS__, PAIR2, PAIR1, )

#define PAIR(...) PAIRCHOOSER(__VA_ARGS__)(__VA_ARGS__)

// #define PAIR(x) Obs(x,STRING(x))

namespace analysis
{

BaseBranch::~BaseBranch() {}

float BaseBranch::InitialValue()
{
    return -11.1111111; // should be non integer
    // this must be identical to the initial value in htag
    // FIXME remove the copy of the magic number
}

Observables BaseBranch::Join(const Observables &observables_1, const Observables &observables_2)
{
    Observables joined;
    joined.reserve(observables_1.size() + observables_2.size());
    joined.insert(joined.end(), observables_1.begin(), observables_1.end());
    joined.insert(joined.end(), observables_2.begin(), observables_2.end());
    return joined;
}

float BottomBase::InValue()
{
    return -11.1111111; // should be non integer
    // this must be identical to the initial value in htag
    // FIXME remove the copy of the magic number
}

InfoBranch::InfoBranch()
{
    Crosssection = InitialValue();
    CrosssectionError = InitialValue();
    EventNumber = int(InitialValue());
    PreCutNumber = int(InitialValue());
    Mass = InitialValue();
    Name = "";
}

ResultBranch::ResultBranch()
{
    Bdt = InitialValue();
    Tag = int(InitialValue());
}

Observables ResultBranch::Variables()
{
    return {};
}

Observables ResultBranch::Spectators()
{
    return {PAIR(Tag), PAIR(Bdt)};
}

ParticleBranch::ParticleBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
    Charge = int(InitialValue());
}

Observables ParticleBranch::Variables()
{
    return Join(ResultBranch::Variables(), {PAIR(Mass,"m")});
}

Observables ParticleBranch::Spectators()
{
    return Join(ResultBranch::Spectators(), {PAIR(Charge), PAIR(Pt), PAIR(Rap), PAIR(Phi)});
}

BottomBase::BottomBase()
{
    VertexMass = InValue();
    MaxDisplacement = InValue();
    MeanDisplacement = InValue();
    SumDisplacement = InValue();
    Multipliticity = int(InValue());
    Radius = InValue();
    Spread = InValue();
    VertexRadius = InValue();
    VertexSpread = InValue();
    EnergyFraction = InValue();
}

Observables BottomBase::Variables()
{
    return {PAIR(VertexMass), PAIR(MaxDisplacement), PAIR(MeanDisplacement), PAIR(SumDisplacement), PAIR(Multipliticity), PAIR(Radius), PAIR(Spread), PAIR(VertexRadius), PAIR(VertexSpread), PAIR(EnergyFraction)};
}

Observables BottomBase::Spectators()
{
    return {};
}

Observables BottomBranch::Variables()
{
    return Join(ParticleBranch::Variables(), BottomBase::Variables());
}

Observables BottomBranch::Spectators()
{
    return Join(ParticleBranch::Spectators(), BottomBase::Variables());
}

TauBranch::TauBranch()
{
    EmRadius = InitialValue();
    TrackRadius = InitialValue();
    MomentumFraction = InitialValue();
    CoreEnergyFraction = InitialValue();
    EmFraction = InitialValue();
    ClusterMass = InitialValue();
    TrackMass = InitialValue();
    FlightPath = InitialValue();
    TrtHtFraction = InitialValue();
}

Observables TauBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(EmRadius), PAIR(TrackRadius), PAIR(MomentumFraction), PAIR(CoreEnergyFraction), PAIR(EmFraction), PAIR(ClusterMass), PAIR(TrackMass), PAIR(FlightPath), PAIR(TrtHtFraction)});
}

Observables TauBranch::Spectators()
{
    return ParticleBranch::Spectators();
}

PairBranch::PairBranch()
{
    Ht = InitialValue();
    DeltaPt = InitialValue();
    DeltaM = InitialValue();
    DeltaRap = InitialValue();
    DeltaPhi = InitialValue();
    DeltaR = InitialValue();
    Rho = InitialValue();
    Bdt1 = InitialValue();
    Bdt2 = InitialValue();
}

Observables PairBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(Ht,"H_{T}"), PAIR(DeltaPt,"#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap,"#Delta #eta"), PAIR(DeltaPhi,"#Delta #phi"), PAIR(DeltaR,"#Delta R"), PAIR(Rho,"#rho"), PAIR(Bdt1,"BDT_{1}"), PAIR(Bdt2,"BDT_{2}")});
    //return Join(ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho)});
}

Observables PairBranch::Spectators()
{
    return ParticleBranch::Spectators();
}

MultiBranch::MultiBranch()
{
    DeltaHt = InitialValue();
}

Observables MultiBranch::Variables()
{
    return Join(PairBranch::Variables(), {PAIR(DeltaHt,"#Delta H_{T}")});
}

JetPairBranch::JetPairBranch()
{
    DeltaM = InitialValue();
    Jet1Mass = InitialValue();
    Jet1Pt = InitialValue();
    Jet1Rap = InitialValue();
    Jet1Phi = InitialValue();
    Jet1Bdt = InitialValue();
    Jet1BTag = InitialValue();
    Jet2Mass = InitialValue();
    Jet2Pt = InitialValue();
    Jet2Rap = InitialValue();
    Jet2Phi = InitialValue();
    Jet2Bdt = InitialValue();
    Jet2BTag = InitialValue();
    BdtRatio11 = InitialValue();
    BdtRatio12 = InitialValue();
    BdtRatio13 = InitialValue();
    BdtRatio14 = InitialValue();
    BdtRatio21 = InitialValue();
    BdtRatio22 = InitialValue();
    BdtRatio23 = InitialValue();
    BdtRatio24 = InitialValue();
}

TripletJetPairBranch::TripletJetPairBranch()
{
    BottomMass = InitialValue();
    BottomPt = InitialValue();
    BottomRap = InitialValue();
    BottomPhi = InitialValue();
    BottomBdt = InitialValue();
    BottomBTag = InitialValue();
    TopMass = InitialValue();
    TopPt = InitialValue();
    TopRap = InitialValue();
    TopPhi = InitialValue();
    TopBdt = InitialValue();
    TopBTag = InitialValue();
}

Observables TripletJetPairBranch::Variables()
{
    return Join(PairBranch::Variables(), {PAIR(BottomPt), PAIR(BottomRap), PAIR(BottomPhi), PAIR(BottomMass), PAIR(TopPt), PAIR(TopRap), PAIR(TopPhi), PAIR(TopMass), PAIR(TopBdt)});
}

WSemiBranch::WSemiBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables WSemiBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(LeptonPt), PAIR(NeutrinoPt)});
}

TopHadronicBranch::TopHadronicBranch()
{
//   std::cout << "we are here" << std::endl;
//     BottomMass = InitialValue();
//     WMass = InitialValue();
    LeptonPt = InitialValue();
//     Tau1_1 = InitialValue();
//     Tau2_1 = InitialValue();
//     Tau3_1 = InitialValue();
//     Tau21_1 = InitialValue();
//     Tau32_1 = InitialValue();
//     Tau1_2 = InitialValue();
//     Tau2_2 = InitialValue();
//     Tau3_2 = InitialValue();
//     Tau21_2 = InitialValue();
//     Tau32_2 = InitialValue();
}

Observables TopHadronicBranch::Variables()
{
    return Join(Join(MultiBranch::Variables(), BottomBase::Variables()), {PAIR(LeptonPt)});
    return  Join(Join(BottomBase::Variables(), ParticleBranch::Variables()), {PAIR(Bdt2), PAIR(LeptonPt)});
    return Join(Join(MultiBranch::Variables(), BottomBase::Variables()), {PAIR(BottomMass), PAIR(WMass), PAIR(LeptonPt)});
}

Observables TopHadronicBranch::Spectators()
{
    return Join(MultiBranch::Spectators(), BottomBase::Spectators());
}

TopSemiBranch::TopSemiBranch()
{
    BottomPt = InitialValue();
    WPt = InitialValue();
}

Observables TopSemiBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(BottomPt), PAIR(WPt)});
}

TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonicBranch::Variables()
{
    return  Join(Join(BottomBase::Variables(), ParticleBranch::Variables()), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(Bdt1), PAIR(BottomPt), PAIR(LeptonPt)});
}

Observables TopLeptonicBranch::Spectators()
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

Observables HiggsBranch::Variables()
{
    return Join(PairBranch::Variables(), BottomBase::Variables());
}

Observables HiggsBranch::Spectators()
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

EventBottomTaggerBranch::EventBottomTaggerBranch()
{
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt123 = InitialValue();
    BottomBdt1234 = InitialValue();
}

EventBranch::EventBranch()
{
    LeptonNumber = int(InitialValue());
    JetNumber = int(InitialValue());
    BottomNumber = int(InitialValue());
    MissingEt = InitialValue();
    ScalarHt = InitialValue();

    LeptonHt = InitialValue();
    JetMass = InitialValue();
    JetPt = InitialValue();
    JetHt = InitialValue();
    JetRap = InitialValue();
    JetPhi = InitialValue();
}

Observables EventBranch::Variables()
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber), PAIR(JetNumber), PAIR(BottomNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
}

void Red()
{
    static int colors[50];
    static bool initialized = false;


    double red[2] = { 0.1, 1};
    double green[2] = { 1, 0};
    double blue[2] = { 1, 0};
    double length[2] = { 0, 1};
    float opacity = 0.7;

    if (!initialized) {
        int color_table = TColor::CreateGradientColorTable(2, length, red, green, blue, 50, opacity);
        for (int step = 0; step < 50; step++) colors[step] = color_table + step;
        initialized = true;
        return;
    }
    gStyle->SetPalette(50, colors);
}

#define GRANULARITY 50
void Blue()
{
    int granularity = GRANULARITY;
    static int colors[GRANULARITY];
    static bool initialized = false;

    double red[] = { 1, 0};
    double green[] = { 1, 0};
    double blue[] = { 0.1, 1};
    double length[] = { 0, 1 };
    float opacity = 0.7;

    if (!initialized) {
        int color_table = TColor::CreateGradientColorTable(sizeof(length) / sizeof(length[0]), length, red, green, blue, granularity, opacity);
        for (int step = 0; step < granularity; step++) colors[step] = color_table + step;
        initialized = true;
        return;
    }
    gStyle->SetPalette(granularity, colors);
}

}
