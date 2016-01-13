/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <iostream>
#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"
#include "TClass.h"
#include "Pair.hh"
#include "plotting/Font.hh"
// #include "Debug.hh"

namespace boca
{

BaseBranch::~BaseBranch() {}

float BaseBranch::InitialValue()
{
    return -11.1111111; // must be non integer
}

float BottomBase::InValue()
{
    return BaseBranch::InitialValue();
}

InfoBranch::InfoBranch()
{
    crosssection = InitialValue();
    crosssection_error = InitialValue();
    event_number = int(InitialValue());
    mass = InitialValue();
}

boca::Crosssection InfoBranch::Crosssection() const
{
    return double(crosssection) * fb;
}
boca::Crosssection InfoBranch::CrosssectionError() const
{
    return double(crosssection_error) * fb;
}
int InfoBranch::EventNumber() const
{
    return event_number;
}
boca::Mass InfoBranch::Mass() const
{
    return double(mass) * GeV;
}
std::string InfoBranch::Name() const
{
    return names.Name();
}
std::string InfoBranch::LatexName() const
{
    return names.LatexName();
}
void InfoBranch::SetCrosssection(boca::Crosssection crosssection_)
{
    crosssection = crosssection_ / fb;
}
void InfoBranch::SetCrosssectionError(boca::Crosssection crosssection_error_)
{
    crosssection_error = crosssection_error_ / fb;
}
void InfoBranch::SetEventNumber(int event_number_)
{
    event_number = event_number_;
}
void InfoBranch::SetMass(boca::Mass mass_)
{
    mass = mass_ / GeV;
}
void InfoBranch::SetNames(Names const& names_)
{
    names = names_;
}

ResultBranch::ResultBranch()
{
    Tag = int(InitialValue());
}

Observables ResultBranch::Variables()
{
    return {};
}

Observables ResultBranch::Spectators()
{
    return PAIR(Tag);
}

BdtBranch::BdtBranch()
{
    Bdt = InitialValue();
}

Observables BdtBranch::Variables()
{
    return {};
}

Observables BdtBranch::Spectators()
{
    return PAIR(Bdt);
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
    return ResultBranch::Variables() + PAIR(Mass, Formula("m")) + PAIR(Pt, Formula("p_{T}"));
}

Observables ParticleBranch::Spectators()
{
    return ResultBranch::Spectators() + PAIR(Charge) + PAIR(Rap) + PAIR(Phi);
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
    return PAIR(VertexMass, Formula("m_{V}")) + PAIR(MaxDisplacement, Formula("log(#Delta d_{max})")) + PAIR(MeanDisplacement, Formula("log(#Delta d_{mean})")) + PAIR(SumDisplacement, Formula("log(#Delta d_{sum})")) + PAIR(Multiplicity, Formula("n_{V}")) + PAIR(Radius, Formula("r")) + PAIR(Spread, Formula("s")) + PAIR(VertexRadius, Formula("r_{V}")) + PAIR(VertexSpread, Formula("s_{V}")) + PAIR(EnergyFraction, Formula("f_{E}"));
}

Observables BottomBase::Spectators()
{
    return {};
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
    Pull1 = InitialValue();
    Pull2 = InitialValue();
    Dipolarity = InitialValue();
}

Observables PairBranch::Variables()
{
    return ParticleBranch::Variables() + PAIR(Ht, "H_{T}") + PAIR(DeltaPt, "#Delta P_{T}") + PAIR(DeltaM, "#Delta m") + PAIR(DeltaRap, "#Delta #eta") + PAIR(DeltaPhi, "#Delta #phi") + PAIR(DeltaR, "#Delta R") + PAIR(Rho, "#rho") + PAIR(Bdt1, "BDT_{1}") + PAIR(Bdt2, "BDT_{2}") + PAIR(Pull1, "#theta_{1}") + PAIR(Pull2, "#theta_{2}") + PAIR(Dipolarity, "D");
    //return ParticleBranch::Variables() + PAIR(Ht) + PAIR(DeltaPt) + PAIR(DeltaM) + PAIR(DeltaRap) + PAIR(DeltaPhi) + PAIR(DeltaR) + PAIR(Rho);
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
    return PairBranch::Variables() + PAIR(DeltaHt, "#Delta H_{T}");
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
    Pull32 = InitialValue();
    Pull31 = InitialValue();
    Dipolarity23 = InitialValue();
    Dipolarity13 = InitialValue();
//   Sphericity = InitialValue();
//   Aplanarity = InitialValue();
}

Observables TChannelBranch::Variables()
{
    return MultiBranch::Variables() + PAIR(Bdt3) + PAIR(Mass12) + PAIR(Mass23) + PAIR(Mass13) + PAIR(Pt12) + PAIR(Pt23) + PAIR(Pt13) + PAIR(DeltaPt23) + PAIR(DeltaPt13) + PAIR(Ht12) + PAIR(Ht23) + PAIR(Ht13) + PAIR(Rho23) + PAIR(Rho13) + PAIR(DeltaRap23) + PAIR(DeltaRap13) + PAIR(DeltaPhi23) + PAIR(DeltaPhi13) + PAIR(DeltaR23) + PAIR(DeltaR13) + PAIR(DeltaM23) + PAIR(DeltaM13) + PAIR(DeltaHt23) + PAIR(DeltaHt13) + PAIR(Pull23) + PAIR(Pull13) + PAIR(Pull32) + PAIR(Pull31) + PAIR(Dipolarity23) + PAIR(Dipolarity13)
//      + PAIR(Aplanarity) + PAIR(Sphericity)
           ;
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
    return PairBranch::Variables() + PAIR(Jet1Mass) + PAIR(Jet1Pt) + PAIR(Jet1Rap) + PAIR(Jet1Phi) + PAIR(Jet2Mass) + PAIR(Jet2Pt) + PAIR(Jet2Rap) + PAIR(Jet2Phi);
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
    return PairBranch::Variables() + PAIR(BottomPt) + PAIR(BottomRap) + PAIR(BottomPhi) + PAIR(BottomMass) + PAIR(TopPt) + PAIR(TopRap) + PAIR(TopPhi) + PAIR(TopMass) + PAIR(TopBdt);
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
    return MultiBranch::Variables() + PAIR(LeptonNumber) + PAIR(JetNumber) + PAIR(BottomNumber) + PAIR(MissingEt) + PAIR(ScalarHt) + PAIR(LeptonHt) + PAIR(JetMass) + PAIR(JetPt) + PAIR(JetHt) + PAIR(JetRap) + PAIR(JetPhi);

}

namespace {

std::vector<int> Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue)
{
    std::vector<int> colors(50);
    int color_table = TColor::CreateGradientColorTable(length.size(), &length.front(), &red.front(), &green.front(), &blue.front(), colors.size());
    for (size_t step = 0; step < colors.size(); ++step) colors.at(step) = color_table + step;
    // for (auto & color : colors) color = color_table + (&color - &colors.front());
    return colors;
}

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
    }
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
    }
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
    }
    gStyle->SetPalette(colors.size(), &colors.front());
}

}




