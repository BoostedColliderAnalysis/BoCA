#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"

#define OBS1(value) Obs(value, #value, #value)
#define OBS2(value, string) Obs(value, #value, string)

#define ARGUMENTS(arg1, arg2, arg, ...) arg
#define OBSERVABLES(...) ARGUMENTS(__VA_ARGS__, OBS2, OBS1,)

#define OBS(...) OBSERVABLES(__VA_ARGS__)(__VA_ARGS__)


namespace analysis
{

Obs::Obs(float &value, const std::string &name, const std::string &nice_name) : value_(&value)
{
    name_ = name;
    nice_name_ = nice_name;
}

float &Obs::value()const
{
    return *value_;
}

std::string Obs::name()const
{
    return name_;
}

std::string Obs::nice_name()const
{
    return nice_name_;
}

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
    return {OBS(Tag), OBS(Bdt)};
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
    return Join(ResultBranch::Variables(), {OBS(Mass, "m")});
}

Observables ParticleBranch::Spectators()
{
    return Join(ResultBranch::Spectators(), {OBS(Charge), OBS(Pt), OBS(Rap), OBS(Phi)});
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
    return {OBS(VertexMass, "m_{V}"), OBS(MaxDisplacement, "#Delta d_{max}"), OBS(MeanDisplacement, "#Delta d_{mean}"), OBS(SumDisplacement, "#Delta d_{sum}"), OBS(Multipliticity, "n_{V}"), OBS(Radius, "r"), OBS(Spread, "s"), OBS(VertexRadius, "r_{V}"), OBS(VertexSpread, "s_{V}"), OBS(EnergyFraction, "f_{E}")};
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
    return Join(ParticleBranch::Variables(), {OBS(EmRadius), OBS(TrackRadius), OBS(MomentumFraction), OBS(CoreEnergyFraction), OBS(EmFraction), OBS(ClusterMass), OBS(TrackMass), OBS(FlightPath), OBS(TrtHtFraction)});
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
    return Join(ParticleBranch::Variables(), {OBS(Ht, "H_{T}"), OBS(DeltaPt, "#Delta P_{T}"), OBS(DeltaM, "#Delta m"), OBS(DeltaRap, "#Delta #eta"), OBS(DeltaPhi, "#Delta #phi"), OBS(DeltaR, "#Delta R"), OBS(Rho, "#rho"), OBS(Bdt1, "BDT_{1}"), OBS(Bdt2, "BDT_{2}")});
    //return Join(ParticleBranch::Variables(), {OBS(Ht), OBS(DeltaPt), OBS(DeltaM), OBS(DeltaRap), OBS(DeltaPhi), OBS(DeltaR), OBS(Rho)});
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
    return Join(PairBranch::Variables(), {OBS(DeltaHt, "#Delta H_{T}")});
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
    return Join(PairBranch::Variables(), {OBS(BottomPt), OBS(BottomRap), OBS(BottomPhi), OBS(BottomMass), OBS(TopPt), OBS(TopRap), OBS(TopPhi), OBS(TopMass), OBS(TopBdt)});
}

WSemiBranch::WSemiBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables WSemiBranch::Variables()
{
    return Join(ParticleBranch::Variables(), {OBS(Ht), OBS(DeltaPt), OBS(DeltaM), OBS(DeltaRap), OBS(DeltaPhi), OBS(DeltaR), OBS(Rho), OBS(LeptonPt), OBS(NeutrinoPt)});
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
    return Join(Join(MultiBranch::Variables(), BottomBase::Variables()), {OBS(LeptonPt)});
    return  Join(Join(BottomBase::Variables(), ParticleBranch::Variables()), {OBS(Bdt2), OBS(LeptonPt)});
    return Join(Join(MultiBranch::Variables(), BottomBase::Variables()), {OBS(BottomMass), OBS(WMass), OBS(LeptonPt)});
}

Observables TopHadronicBranch::Spectators()
{
    return Join(MultiBranch::Spectators(), BottomBase::Spectators());
}

TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonicBranch::Variables()
{
    return  Join(Join(BottomBase::Variables(), ParticleBranch::Variables()), {OBS(Ht), OBS(DeltaPt), OBS(DeltaM), OBS(DeltaRap), OBS(DeltaPhi), OBS(DeltaR), OBS(Rho), OBS(Bdt2), OBS(BottomPt), OBS(LeptonPt)});
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
    return Join(MultiBranch::Variables(), {OBS(LeptonNumber), OBS(JetNumber), OBS(BottomNumber), OBS(MissingEt), OBS(ScalarHt), OBS(LeptonHt), OBS(JetMass), OBS(JetPt), OBS(JetHt), OBS(JetRap), OBS(JetPhi)});
}

void Color::Red()
{

    std::vector<double> red = { 1, 1};
    std::vector<double> green = { 1, 0};
    std::vector<double> blue = { 1, 0};
    std::vector<double> length = { 0, 1};

    static std::vector<int> colors;
    static bool initialized = false;
    if (!initialized) {
        colors = Table(length, red, green, blue);
        initialized = true;
    } else gStyle->SetPalette(colors.size(), &colors[0]);
}

void Color::Blue()
{

    std::vector<double> red = { 1, 0};
    std::vector<double> green = { 1, 0};
    std::vector<double> blue = { 1, 1};
    std::vector<double> length = { 0, 1 };

    static std::vector<int> colors;
    static bool initialized = false;
    if (!initialized) {
        colors = Table(length, red, green, blue);
        initialized = true;
    } else gStyle->SetPalette(colors.size(), &colors[0]);
}

void Color::Heat()
{
    std::vector<double> length = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    std::vector<double> red = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    std::vector<double> green = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    std::vector<double> blue = { 0.51, 1.00, 0.12, 0.00, 0.00 };

    static std::vector<int> colors;
    static bool initialized = false;
    if (!initialized) {
        colors = Table(length, red, green, blue);
        initialized = true;
        return;
    } else gStyle->SetPalette(colors.size(), &colors[0]);
}

std::vector<int> Color::Table(std::vector<double> &length, std::vector<double> &red, std::vector<double> &green, std::vector<double> &blue)
{
    std::vector<int> colors(50);
    int color_table = TColor::CreateGradientColorTable(length.size(), &length[0], &red[0], &green[0], &blue[0], colors.size());
    for (std::size_t step = 0; step < colors.size(); step++) colors[step] = color_table + step;
    //     for (const int &color : colors) colors[color] = color_table + &color - &colors[0];
    return colors;
}

}

