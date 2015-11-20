#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"
#include "Pair.hh"

namespace analysis {

Obs::Obs(const float& value, const std::string& name, const std::string& nice_name) : value_(&const_cast<float&>(value))
{
    name_ = name;
    nice_name_ = nice_name;
}

float& Obs::value() const
{
    return *value_;
}

std::string Obs::name() const
{
    return name_;
}

std::string Obs::nice_name() const
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

Observables BaseBranch::Join(const Observables& observables_1, const Observables& observables_2)
{
    Observables joined;
    joined.reserve(observables_1.size() + observables_2.size());
    joined.insert(joined.end(), observables_1.begin(), observables_1.end());
    joined.insert(joined.end(), observables_2.begin(), observables_2.end());
    return joined;
}

Observables BaseBranch::Join(const Observables& observables_1, const Observables& observables_2, const Observables& observables_3)
{
  Observables joined;
  joined.reserve(observables_1.size() + observables_2.size() + observables_3.size());
  joined.insert(joined.end(), observables_1.begin(), observables_1.end());
  joined.insert(joined.end(), observables_2.begin(), observables_2.end());
  joined.insert(joined.end(), observables_3.begin(), observables_3.end());
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
    Mass = InitialValue();
    Name = "";
}

ResultBranch::ResultBranch()
{
    Bdt = InitialValue();
    Tag = int(InitialValue());
}

Observables ResultBranch::Variables() const
{
    return {};
}

Observables ResultBranch::Spectators() const
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

Observables ParticleBranch::Variables() const
{
  return Join(ResultBranch::Variables(), {PAIR(Mass, "m"), PAIR(Pt), PAIR(Rap), PAIR(Phi)});
}

Observables ParticleBranch::Spectators() const
{
  return Join(ResultBranch::Spectators(), {PAIR(Charge)});
}

BottomBase::BottomBase()
{
    VertexMass = InValue();
    MaxDisplacement = InValue();
    MeanDisplacement = InValue();
    SumDisplacement = InValue();
    Multiplicity = int(InValue());
    Radius = InValue();
    Spread = InValue();
    VertexRadius = InValue();
    VertexSpread = InValue();
    EnergyFraction = InValue();
}

Observables BottomBase::Variables() const
{
    return {PAIR(VertexMass, "m_{V}"), PAIR(MaxDisplacement, "log(#Delta d_{max})"), PAIR(MeanDisplacement, "log(#Delta d_{mean})"), PAIR(SumDisplacement, "log(#Delta d_{sum})"), PAIR(Multiplicity, "n_{V}"), PAIR(Radius, "r"), PAIR(Spread, "s"), PAIR(VertexRadius, "r_{V}"), PAIR(VertexSpread, "s_{V}"), PAIR(EnergyFraction, "f_{E}")};
}

Observables BottomBase::Spectators() const
{
    return {};
}

Observables BottomBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), BottomBase::Variables());
}

Observables BottomBranch::Spectators() const
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

Observables TauBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(EmRadius), PAIR(TrackRadius), PAIR(MomentumFraction), PAIR(CoreEnergyFraction), PAIR(EmFraction), PAIR(ClusterMass), PAIR(TrackMass), PAIR(FlightPath), PAIR(TrtHtFraction)});
}

Observables TauBranch::Spectators() const
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
    DeltaPull = InitialValue();
    Pull = InitialValue();
    Dipolarity = InitialValue();
}

Observables PairBranch::Variables() const
{
  return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Rho, "#rho"), PAIR(Bdt1, "BDT_{1}"), PAIR(Bdt2, "BDT_{2}"),PAIR(Pull,"#theta"),PAIR(DeltaPull,"#Delta #theta"),PAIR(Dipolarity,"D")});
  
    //return Join(ParticleBranch::Variables() {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho)});
}

Observables PairBranch::Spectators() const
{
    return ParticleBranch::Spectators();
}

MultiBranch::MultiBranch()
{
    DeltaHt = InitialValue();
}

Observables MultiBranch::Variables() const
{
    return Join(PairBranch::Variables(), {PAIR(DeltaHt, "#Delta H_{T}")});
}

JetPairBranch::JetPairBranch()
{
//     DeltaM = InitialValue();
    Jet1Mass = InitialValue();
    Jet1Pt = InitialValue();
    Jet1Rap = InitialValue();
    Jet1Phi = InitialValue();
//     Jet1Bdt = InitialValue();
//     Jet1BTag = InitialValue();
    Jet2Mass = InitialValue();
    Jet2Pt = InitialValue();
    Jet2Rap = InitialValue();
    Jet2Phi = InitialValue();
//     Jet2Bdt = InitialValue();
//     Jet2BTag = InitialValue();
    BdtSum = InitialValue();
    BdtRatio11 = InitialValue();
    BdtRatio12 = InitialValue();
    BdtRatio13 = InitialValue();
    BdtRatio14 = InitialValue();
    BdtRatio21 = InitialValue();
    BdtRatio22 = InitialValue();
    BdtRatio23 = InitialValue();
    BdtRatio24 = InitialValue();
}


Observables JetPairBranch::Variables() const
{
//   return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Rho, "#rho"), PAIR(Bdt1, "BDT_{1}"), PAIR(Bdt2, "BDT_{2}"),PAIR(Pull,"#theta"),PAIR(Dipolarity,"D"), PAIR(Jet1Mass), PAIR(Jet1Pt), PAIR(Jet1Rap), PAIR(Jet1Phi), PAIR(Jet2Mass), PAIR(Jet2Pt), PAIR(Jet2Rap),PAIR(Jet2Phi),PAIR(BdtRatio11),PAIR(BdtRatio12),PAIR(BdtRatio13),PAIR(BdtRatio14),PAIR(BdtRatio21),PAIR(BdtRatio22),PAIR(BdtRatio23),PAIR(BdtRatio24)});

    return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Bdt1, "BDT_{1}"), PAIR(Bdt2, "BDT_{2}"), PAIR(Jet1Mass), PAIR(Jet1Pt), PAIR(Jet1Rap), PAIR(Jet1Phi), PAIR(Jet2Mass), PAIR(Jet2Pt), PAIR(Jet2Rap),PAIR(Jet2Phi),/*PAIR(BdtSum),*/PAIR(BdtRatio11),PAIR(BdtRatio12),PAIR(BdtRatio13),PAIR(BdtRatio14),PAIR(BdtRatio21),PAIR(BdtRatio22),PAIR(BdtRatio23),PAIR(BdtRatio24)});
  
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

Observables TripletJetPairBranch::Variables() const
{
    return Join(PairBranch::Variables(), {PAIR(BottomPt), PAIR(BottomRap), PAIR(BottomPhi), PAIR(BottomMass), PAIR(TopPt), PAIR(TopRap), PAIR(TopPhi), PAIR(TopMass), PAIR(TopBdt)});
}

WSemiBranch::WSemiBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables WSemiBranch::Variables() const
{
    return Join(ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(LeptonPt), PAIR(NeutrinoPt)});
}

TopHadronicBranch::TopHadronicBranch()
{
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

Observables TopHadronicBranch::Variables() const
{
    return Join(MultiBranch::Variables(), BottomBase::Variables(), {PAIR(LeptonPt)});
    return  Join(BottomBase::Variables(), ParticleBranch::Variables(), {PAIR(Bdt2), PAIR(LeptonPt)});
    return Join(MultiBranch::Variables(), BottomBase::Variables(), {PAIR(BottomMass), PAIR(WMass), PAIR(LeptonPt)});
}

Observables TopHadronicBranch::Spectators() const
{
    return Join(MultiBranch::Spectators(), BottomBase::Spectators());
}

TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

Observables TopLeptonicBranch::Variables() const
{
  return  Join(BottomBase::Variables(), ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(Bdt2), PAIR(BottomPt), PAIR(LeptonPt),PAIR(Pull,"#theta"),PAIR(DeltaPull,"#Delta #theta"),PAIR(Dipolarity,"D")});
}

Observables TopLeptonicBranch::Spectators() const
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

HiggsBranch::HiggsBranch(){
  LeptonPt = InitialValue();
  LeptonDeltaR = InitialValue();
}

Observables HiggsBranch::Variables() const
{
  return Join(PairBranch::Variables(), BottomBase::Variables(),{PAIR(LeptonPt),PAIR(LeptonDeltaR)});
}

Observables HiggsBranch::Spectators() const
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
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

Observables EventBranch::Variables() const
{
    return Join(MultiBranch::Variables(), {PAIR(LeptonNumber), PAIR(JetNumber), PAIR(BottomNumber), PAIR(MissingEt), PAIR(ScalarHt), PAIR(LeptonHt), PAIR(JetMass), PAIR(JetPt), PAIR(JetHt), PAIR(JetRap), PAIR(JetPhi)});
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
    } else
        gStyle->SetPalette(colors.size(), &colors[0]);
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
    } else
        gStyle->SetPalette(colors.size(), &colors[0]);
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
    } else
        gStyle->SetPalette(colors.size(), &colors[0]);
}

std::vector<int> Color::Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue)
{
    std::vector<int> colors(50);
    int color_table = TColor::CreateGradientColorTable(length.size(), &length[0], &red[0], &green[0], &blue[0], colors.size());
    for (size_t step = 0; step < colors.size(); ++step) colors[step] = color_table + step;
    //     for (const auto &color : colors) colors[color] = color_table + (&color - &colors[0]);
    return colors;
}

}

