/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"
#include "TClass.h"
#include "Pair.hh"
// #include "Debug.hh"

namespace boca {

Obs::Obs(float & value, std::string const& name, std::string const& nice_name) : value_(&value)
{
    name_ = name;
    if(nice_name == "") nice_name_ = name;
    else nice_name_ = nice_name;
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

BaseBranch::~BaseBranch(){}

float BaseBranch::InitialValue()
{
    return -11.1111111; // should be non integer
}

Observables BaseBranch::Join(Observables const& observables_1, Observables const& observables_2)
{
    Observables joined;
    joined.reserve(observables_1.size() + observables_2.size());
    joined.insert(joined.end(), observables_1.begin(), observables_1.end());
    joined.insert(joined.end(), observables_2.begin(), observables_2.end());
    return joined;
}

Observables BaseBranch::Join(Observables const& observables_1, Observables const& observables_2, Observables const& observables_3)
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
  return BaseBranch::InitialValue();
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

Observables ResultBranch::Variables()
{
    return {};
}

Observables ResultBranch::Spectators()
{
  return {PAIR(Tag), PAIR(Bdt)};
}

// void ResultBranch::Print() const
// {
//     Error(Tag);
//     Error(Bdt);
// }


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
    return Join(ResultBranch::Variables(), {PAIR(Mass, "m"), PAIR(Pt, "p_T")});
}

Observables ParticleBranch::Spectators()
{
    return Join(ResultBranch::Spectators(), {PAIR(Charge), PAIR(Rap), PAIR(Phi)});
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

Observables BottomBase::Variables()
{
    return {PAIR(VertexMass, "m_{V}"), PAIR(MaxDisplacement, "log(#Delta d_{max})"), PAIR(MeanDisplacement, "log(#Delta d_{mean})"), PAIR(SumDisplacement, "log(#Delta d_{sum})"), PAIR(Multiplicity, "n_{V}"), PAIR(Radius, "r"), PAIR(Spread, "s"), PAIR(VertexRadius, "r_{V}"), PAIR(VertexSpread, "s_{V}"), PAIR(EnergyFraction, "f_{E}")};
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
    DeltaPull = InitialValue();
    Pull = InitialValue();
    Dipolarity = InitialValue();
}

Observables PairBranch::Variables()
{
  return Join(ParticleBranch::Variables(), {PAIR(Ht, "H_{T}"), PAIR(DeltaPt, "#Delta P_{T}"), PAIR(DeltaM, "#Delta m"), PAIR(DeltaRap, "#Delta #eta"), PAIR(DeltaPhi, "#Delta #phi"), PAIR(DeltaR, "#Delta R"), PAIR(Rho, "#rho"), PAIR(Bdt1, "BDT_{1}"), PAIR(Bdt2, "BDT_{2}"),PAIR(Pull,"#theta"),PAIR(DeltaPull,"#Delta #theta"),PAIR(Dipolarity,"D")});
    //return Join(ParticleBranch::Variables() {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho)});
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
    return Join(PairBranch::Variables(), {PAIR(DeltaHt, "#Delta H_{T}")});
}

TChannelBranch::TChannelBranch()
{
  Bdt3 = InitialValue();
  Mass12 = InitialValue();
  Mass23 = InitialValue();
  Mass13 = InitialValue();
  DeltaPt23 = InitialValue();
  DeltaPt13 = InitialValue();
  Pt12 = InitialValue();
  Pt23 = InitialValue();
  Pt13 = InitialValue();
  Ht12 = InitialValue();
  Ht23 = InitialValue();
  Ht13 = InitialValue();
  Rho23 = InitialValue();
  Rho13 = InitialValue();
  DeltaRap23 = InitialValue();
  DeltaRap13 = InitialValue();
  DeltaPhi23 = InitialValue();
  DeltaPhi13 = InitialValue();
  DeltaR23 = InitialValue();
  DeltaR13 = InitialValue();
  DeltaM23 = InitialValue();
  DeltaM13 = InitialValue();
  DeltaHt23 = InitialValue();
  DeltaHt13 = InitialValue();
  Pull23 = InitialValue();
  Pull13 = InitialValue();
  DeltaPull23 = InitialValue();
  DeltaPull13 = InitialValue();
  Dipolarity23 = InitialValue();
  Dipolarity13 = InitialValue();
//   Sphericity = InitialValue();
//   Aplanarity = InitialValue();
}

Observables TChannelBranch::Variables()
{
  return Join(MultiBranch::Variables(), {PAIR(Bdt3), PAIR(Mass12), PAIR(Mass23), PAIR(Mass13), PAIR(Pt12), PAIR(Pt23), PAIR(Pt13), PAIR(DeltaPt23), PAIR(DeltaPt13), PAIR(Ht12), PAIR(Ht23), PAIR(Ht13), PAIR(Rho23), PAIR(Rho13), PAIR(DeltaRap23), PAIR(DeltaRap13), PAIR(DeltaPhi23), PAIR(DeltaPhi13), PAIR(DeltaR23), PAIR(DeltaR13), PAIR(DeltaM23), PAIR(DeltaM13), PAIR(DeltaHt23), PAIR(DeltaHt13), PAIR(Pull23), PAIR(Pull13), PAIR(DeltaPull23), PAIR(DeltaPull13), PAIR(Dipolarity23), PAIR(Dipolarity13)
//     , PAIR(Aplanarity), PAIR(Sphericity)
  });
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
//     BdtRatio11 = InitialValue();
//     BdtRatio12 = InitialValue();
//     BdtRatio13 = InitialValue();
//     BdtRatio14 = InitialValue();
//     BdtRatio21 = InitialValue();
//     BdtRatio22 = InitialValue();
//     BdtRatio23 = InitialValue();
//     BdtRatio24 = InitialValue();
}


Observables JetPairBranch::Variables()
{
    return Join(PairBranch::Variables(), {PAIR(Jet1Mass), PAIR(Jet1Pt), PAIR(Jet1Rap), PAIR(Jet1Phi), PAIR(Jet2Mass), PAIR(Jet2Pt), PAIR(Jet2Rap), PAIR(Jet2Phi)});
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
//   std::cout << "we are here\n";
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
    return Join(MultiBranch::Variables(), BottomBase::Variables(), {PAIR(LeptonPt)});
    return  Join(BottomBase::Variables(), ParticleBranch::Variables(), {PAIR(Bdt2), PAIR(LeptonPt)});
    return Join(MultiBranch::Variables(), BottomBase::Variables(), {PAIR(BottomMass), PAIR(WMass), PAIR(LeptonPt)});
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
  return  Join(BottomBase::Variables(), ParticleBranch::Variables(), {PAIR(Ht), PAIR(DeltaPt), PAIR(DeltaM), PAIR(DeltaRap), PAIR(DeltaPhi), PAIR(DeltaR), PAIR(Rho), PAIR(Bdt2), PAIR(BottomPt), PAIR(LeptonPt),PAIR(Pull,"#theta"),PAIR(DeltaPull,"#Delta #theta"),PAIR(Dipolarity,"D")});
}

Observables TopLeptonicBranch::Spectators()
{
    return Join(PairBranch::Spectators(), BottomBase::Spectators());
}

HiggsBranch::HiggsBranch(){
  LeptonPt = InitialValue();
  LeptonDeltaR = InitialValue();
}

Observables HiggsBranch::Variables()
{
  return Join(PairBranch::Variables(), BottomBase::Variables(),{PAIR(LeptonPt),PAIR(LeptonDeltaR)});
}

Observables HiggsBranch::Spectators()
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

Observables EventBranch::Variables()
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
        gStyle->SetPalette(colors.size(), &colors.front());
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
        gStyle->SetPalette(colors.size(), &colors.front());
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
        gStyle->SetPalette(colors.size(), &colors.front());
}

std::vector<int> Color::Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue)
{
    std::vector<int> colors(50);
    int color_table = TColor::CreateGradientColorTable(length.size(), &length.front(), &red.front(), &green.front(), &blue.front(), colors.size());
    for (size_t step = 0; step < colors.size(); ++step) colors[step] = color_table + step;
    // for (auto & color : colors) color = color_table + (&color - &colors.front());
    return colors;
}

}
