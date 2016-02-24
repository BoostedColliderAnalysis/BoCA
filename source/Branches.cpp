/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <iostream>
#include "Branches.hh"
#include "TColor.h"
#include "TStyle.h"
#include "TClass.h"
#include "OBSERVABLE.hh"
#include "File.hh"
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
    mass = InitialValue();
    event_number = 0;
}

InfoBranch::InfoBranch(File const& file)
{
    SetCrosssection(file.Crosssection());
    SetCrosssectionError(file.CrosssectionError());
    SetMass(file.Mass());
    SetNames(file.Names());
    event_number = 0;
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
boca::Names InfoBranch::Names() const
{
    return names;
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
void InfoBranch::SetNames(boca::Names const& names_)
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
    return OBSERVABLE(Tag);
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
    return OBSERVABLE(Bdt);
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
    return ResultBranch::Variables() + OBSERVABLE(Mass, Formula("m") + " [GeV]") + OBSERVABLE(Pt, Formula("p_{T}") + " [GeV]");
}

Observables ParticleBranch::Spectators()
{
    return ResultBranch::Spectators() + OBSERVABLE(Charge, "e") + OBSERVABLE(Rap, "#eta") + OBSERVABLE(Phi, "#phi");
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
    return OBSERVABLE(VertexMass, Formula("m_{V}") + " [GeV]") + OBSERVABLE(MaxDisplacement, "log(" + Formula("#Delta d") + "_{max} / mm)") + OBSERVABLE(MeanDisplacement, "log(" + Formula("#Delta d") + "_{mean} / mm)") + OBSERVABLE(SumDisplacement, "log(" + Formula("#Delta d") + "_{sum} / mm)") + OBSERVABLE(Multiplicity, Formula("n_{V}")) + OBSERVABLE(Radius, Formula("r")) + OBSERVABLE(Spread, Formula("s")) + OBSERVABLE(VertexRadius, Formula("r_{V}")) + OBSERVABLE(VertexSpread, Formula("s_{V}")) + OBSERVABLE(EnergyFraction, Formula("f_{E}"));
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
    return ParticleBranch::Variables() + OBSERVABLE(Ht, Formula("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("#Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("#Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("#Delta #eta")) + OBSERVABLE(DeltaPhi, Formula("#Delta #phi")) + OBSERVABLE(DeltaR, Formula("#Delta R")) + OBSERVABLE(Rho, Formula("#rho")) + OBSERVABLE(Bdt1, "BDT_{1}") + OBSERVABLE(Bdt2, "BDT_{2}") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) + OBSERVABLE(Dipolarity, Formula("D"));
    //return ParticleBranch::Variables() + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaM) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho);
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
    return PairBranch::Variables() + OBSERVABLE(DeltaHt, Formula("#Delta H_{T}") + " [GeV]");
}

SignatureBranch::SignatureBranch()
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

Observables SignatureBranch::Variables()
{
    return MultiBranch::Variables() + OBSERVABLE(Bdt3, "BDT_{3}") + OBSERVABLE(Mass12, "m_{12}") + OBSERVABLE(Mass23, "m_{23}") + OBSERVABLE(Mass13, "m_{13}") + OBSERVABLE(Pt12, "p_{T}^{12}") + OBSERVABLE(Pt23, "p_{T}^{23}") + OBSERVABLE(Pt13, "p_{T}^{13}") + OBSERVABLE(DeltaPt23, "#Delta p_{T}^{23}") + OBSERVABLE(DeltaPt13, "#Delta p_{T}^{13}") + OBSERVABLE(Ht12, "H_{T}^{12}") + OBSERVABLE(Ht23, "H_{T}^{23}") + OBSERVABLE(Ht13, "H_{T}^{13}") + OBSERVABLE(Rho23, "#rho_{23}") + OBSERVABLE(Rho13, "#rho_{13}") + OBSERVABLE(DeltaRap23, "#Delta#eta_{23}") + OBSERVABLE(DeltaRap13, "#Delta#eta_{13}") + OBSERVABLE(DeltaPhi23, "#Delta#phi_{23}") + OBSERVABLE(DeltaPhi13, "#Delta#phi_{13}") + OBSERVABLE(DeltaR23, "#Delta R_{23}") + OBSERVABLE(DeltaR13, "#Delta R_{13}") + OBSERVABLE(DeltaM23, "#Delta m_{23}") + OBSERVABLE(DeltaM13, "#Delta m_{13}") + OBSERVABLE(DeltaHt23, "#Delta H_{T}^{23}") + OBSERVABLE(DeltaHt13, "#Delta H_{T}^{13}") + OBSERVABLE(Pull23, "#theta_{23}") + OBSERVABLE(Pull13, "#theta_{13}") + OBSERVABLE(Pull32, "#theta_{32}") + OBSERVABLE(Pull31, "#theta_{31}") + OBSERVABLE(Dipolarity23, "D_{23}") + OBSERVABLE(Dipolarity13, "D_{13}")
//      + OBSERVABLE(Aplanarity) + OBSERVABLE(Sphericity)
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
    return PairBranch::Variables() + OBSERVABLE(Jet1Mass) + OBSERVABLE(Jet1Pt) + OBSERVABLE(Jet1Rap) + OBSERVABLE(Jet1Phi) + OBSERVABLE(Jet2Mass) + OBSERVABLE(Jet2Pt) + OBSERVABLE(Jet2Rap) + OBSERVABLE(Jet2Phi);
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
    return PairBranch::Variables() + OBSERVABLE(BottomPt) + OBSERVABLE(BottomRap) + OBSERVABLE(BottomPhi) + OBSERVABLE(BottomMass) + OBSERVABLE(TopPt) + OBSERVABLE(TopRap) + OBSERVABLE(TopPhi) + OBSERVABLE(TopMass) + OBSERVABLE(TopBdt);
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
  return MultiBranch::Variables() + OBSERVABLE(LeptonNumber, "##l") + OBSERVABLE(BottomNumber, "##b") + OBSERVABLE(JetNumber, "##j") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}^{scalar}") + OBSERVABLE(LeptonHt, "H_{T}^{l}") + OBSERVABLE(JetMass, "m_{j}") + OBSERVABLE(JetPt, "p_{T}^{j}") + OBSERVABLE(JetHt, "H_{T}^{j}") + OBSERVABLE(JetRap, "#eta_{j}") + OBSERVABLE(JetPhi, "#phi_{j}");
}

// namespace
// {
//
// std::vector<int> Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue)
// {
//     std::vector<int> colors(50);
//     int color_table = TColor::CreateGradientColorTable(length.size(), &length.front(), &red.front(), &green.front(), &blue.front(), colors.size());
//     for (auto & color : colors) color = color_table + (&color - &colors.front());
//     return colors;
// }
//
// void Colors(bool& initialized, std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue, std::vector<int>& colors)
// {
//     if (!initialized) {
//         colors = Table(length, red, green, blue);
//         initialized = true;
//     }
//     gStyle->SetPalette(colors.size(), &colors.front());
// }
//
// }
//
// void Color::Red()
// {
//     std::vector<double> red = { 1, 1};
//     std::vector<double> green = { 1, 0};
//     std::vector<double> blue = { 1, 0};
//     std::vector<double> length = { 0, 1};
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }
//
// void Color::Blue()
// {
//     std::vector<double> red = { 1, 0};
//     std::vector<double> green = { 1, 0};
//     std::vector<double> blue = { 1, 1};
//     std::vector<double> length = { 0, 1};
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }
//
// void Color::Heat()
// {
//     std::vector<double> length = { 0., 0.34, 0.61, 0.84, 1. };
//     std::vector<double> red = { 0., 0., 0.87, 1., 0.51 };
//     std::vector<double> green = { 0., 0.81, 1., 0.2, 0. };
//     std::vector<double> blue = { 0.51, 1., 0.12, 0., 0. };
//     static std::vector<int> colors;
//     static bool initialized = false;
//     Colors(initialized, length, red, green, blue, colors);
// }

bool Red::initialized_ = false;
std::vector<int> Red::colors_;

bool Blue::initialized_ = false;
std::vector<int> Blue::colors_;

bool Heat::initialized_ = false;
std::vector<int> Heat::colors_;

Color::Color()
{
    Initialize();
    gStyle->SetPalette(Palette().size(), &Palette().front());
}
void Color::Initialize()
{
    if (Initialized()) return;
    Colors().reserve(50);
    int color_table = TColor::CreateGradientColorTable(Length().size(), &Length().front(), &RedPart().front(), &GreenPart().front(), &BluePart().front(), Colors().size());
    for (auto & color : Colors()) color = color_table + (&color - &Colors().front());
    Initialized() = true;
}
std::vector< double > Color::RedPart() const
{
    return { 1, 0};
}
std::vector< double > Color::GreenPart() const
{
    return { 1, 0};
}
std::vector< double > Color::BluePart() const
{
    return { 1, 0};
}
std::vector< double > Color::Length() const
{
    return { 0, 1};
}

std::vector< double > Red::RedPart() const
{
    return { 1, 1};
}
std::string Red::Action()
{
    return "boca::Red();";
}

std::vector< double > Blue::BluePart() const
{
    return { 1, 1};
}
std::string Blue::Action()
{
    return "boca::Blue();";
}
std::vector< double > Heat::RedPart() const
{
    return { 0., 0., 0.87, 1., 0.51 };
}
std::vector< double > Heat::GreenPart() const
{
    return { 0., 0.81, 1., 0.2, 0. };
}
std::vector< double > Heat::BluePart() const
{
    return { 0.51, 1., 0.12, 0., 0. };
}
std::vector< double > Heat::Length() const
{
    return { 0., 0.34, 0.61, 0.84, 1. };
}
std::string Heat::Action()
{
    return "boca::Heat();";
}
std::vector< int >& Red::Colors()
{
    return colors_;
}
bool& Red::Initialized()
{
    return initialized_;
}
std::vector< int >& Blue::Colors()
{
    return colors_;
}
bool& Blue::Initialized()
{
    return initialized_;
}
std::vector< int >& Heat::Colors()
{
    return colors_;
}
bool& Heat::Initialized()
{
    return initialized_;
}
std::vector< int >& Color::Palette()
{
    return Colors();
}

}
