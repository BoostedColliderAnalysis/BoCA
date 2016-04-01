/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "plotting/Font.hh"
#include "Branches.hh"
#include "File.hh"
#include "OBSERVABLE.hh"
#include "generic/DEBUG.hh"

namespace boca
{

// BaseBranch::~BaseBranch() {}

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
    return ResultBranch::Spectators() + OBSERVABLE(Charge, "e") + OBSERVABLE(Rap, "\\eta") + OBSERVABLE(Phi, "\\phi");
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
    return OBSERVABLE(VertexMass, Formula("m_{V}") + " [GeV]") + OBSERVABLE(MaxDisplacement, "log(" + Formula("\\Delta d") + "_{max} / mm)") + OBSERVABLE(MeanDisplacement, "log(" + Formula("\\Delta d") + "_{mean} / mm)") + OBSERVABLE(SumDisplacement, "log(" + Formula("\\Delta d") + "_{sum} / mm)") + OBSERVABLE(Multiplicity, Formula("n_{V}")) + OBSERVABLE(Radius, Formula("r")) + OBSERVABLE(Spread, Formula("s")) + OBSERVABLE(VertexRadius, Formula("r_{V}")) + OBSERVABLE(VertexSpread, Formula("s_{V}")) + OBSERVABLE(EnergyFraction, Formula("f_{E}"));
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
//     Dipolarity = InitialValue();
}

Observables PairBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(Ht, Formula("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, Formula("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, Formula("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, Formula("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, Formula("\\Delta \\phi")) + OBSERVABLE(DeltaR, Formula("\\Delta R")) + OBSERVABLE(Rho, Formula("\\rho")) + OBSERVABLE(Bdt1, "BDT_{1}") + OBSERVABLE(Bdt2, "BDT_{2}") + OBSERVABLE(Pull1, Formula("#theta_{1}")) + OBSERVABLE(Pull2, Formula("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, Formula("D"))*/;
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
    return PairBranch::Variables() + OBSERVABLE(DeltaHt, Formula("\\Delta H_{T}") + " [GeV]");
}

SignatureBranch::SignatureBranch()
{
    Ht = InitialValue();
    Bdt1 = InitialValue();
    Bdt2 = InitialValue();
    Bdt3 = InitialValue();
    Mass12 = InitialValue();
    Mass23 = InitialValue();
    Mass13 = InitialValue();
    DeltaPt12 = InitialValue();
    DeltaPt23 = InitialValue();
    DeltaPt13 = InitialValue();
    Pt12 = InitialValue();
    Pt23 = InitialValue();
    Pt13 = InitialValue();
    Ht12 = InitialValue();
    Ht23 = InitialValue();
    Ht13 = InitialValue();
    Rho12 = InitialValue();
    Rho23 = InitialValue();
    Rho13 = InitialValue();
    DeltaRap12 = InitialValue();
    DeltaRap23 = InitialValue();
    DeltaRap13 = InitialValue();
    DeltaPhi12 = InitialValue();
    DeltaPhi23 = InitialValue();
    DeltaPhi13 = InitialValue();
    DeltaR12 = InitialValue();
    DeltaR23 = InitialValue();
    DeltaR13 = InitialValue();
    DeltaM12 = InitialValue();
    DeltaM23 = InitialValue();
    DeltaM13 = InitialValue();
    DeltaHt23 = InitialValue();
    DeltaHt13 = InitialValue();
    Pull23 = InitialValue();
    Pull13 = InitialValue();
    Pull32 = InitialValue();
    Pull31 = InitialValue();
//     Dipolarity23 = InitialValue();
//     Dipolarity13 = InitialValue();
    Sphericity = InitialValue();
    Aplanarity = InitialValue();
}

Observables SignatureBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(Ht, "H_{T}") + OBSERVABLE(Bdt1, "BDT_{1}") + OBSERVABLE(Bdt2, "BDT_{2}") + OBSERVABLE(Bdt3, "BDT_{3}") + OBSERVABLE(Mass12, "m_{12}") + OBSERVABLE(Mass23, "m_{23}") + OBSERVABLE(Mass13, "m_{13}") + OBSERVABLE(Pt12, "p_{T}^{12}") + OBSERVABLE(Pt23, "p_{T}^{23}") + OBSERVABLE(Pt13, "p_{T}^{13}") + OBSERVABLE(DeltaPt12, "\\Delta p_{T}^{12}") + OBSERVABLE(DeltaPt23, "\\Delta p_{T}^{23}") + OBSERVABLE(DeltaPt13, "\\Delta p_{T}^{13}") + OBSERVABLE(Ht12, "H_{T}^{12}") + OBSERVABLE(Ht23, "H_{T}^{23}") + OBSERVABLE(Ht13, "H_{T}^{13}") + OBSERVABLE(Rho12, "\\rho_{12}") + OBSERVABLE(Rho23, "\\rho_{23}") + OBSERVABLE(Rho13, "\\rho_{13}") + OBSERVABLE(DeltaRap12, "\\Delta\\eta_{12}") + OBSERVABLE(DeltaRap23, "\\Delta\\eta_{23}") + OBSERVABLE(DeltaRap13, "\\Delta\\eta_{13}") + OBSERVABLE(DeltaPhi12, "\\Delta\\phi_{12}") + OBSERVABLE(DeltaPhi23, "\\Delta\\phi_{23}") + OBSERVABLE(DeltaPhi13, "\\Delta\\phi_{13}") + OBSERVABLE(DeltaR12, "\\Delta R_{12}") + OBSERVABLE(DeltaR23, "\\Delta R_{23}") + OBSERVABLE(DeltaR13, "\\Delta R_{13}") + OBSERVABLE(DeltaM12, "\\Delta m_{12}") + OBSERVABLE(DeltaM23, "\\Delta m_{23}") + OBSERVABLE(DeltaM13, "\\Delta m_{13}") + OBSERVABLE(DeltaHt12, "\\Delta H_{T}^{12}") + OBSERVABLE(DeltaHt23, "\\Delta H_{T}^{23}") + OBSERVABLE(DeltaHt13, "\\Delta H_{T}^{13}") + OBSERVABLE(Pull23, "#theta_{23}") + OBSERVABLE(Pull13, "#theta_{13}") + OBSERVABLE(Pull32, "#theta_{32}") + OBSERVABLE(Pull31, "#theta_{31}") /*+ OBSERVABLE(Dipolarity23, "D_{23}") + OBSERVABLE(Dipolarity13, "D_{13}")*/ /*+ OBSERVABLE(Aplanarity, "#slashed{P}") + OBSERVABLE(Sphericity, "S")*/;
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


float GlobalBase::InValue()
{
    return BaseBranch::InitialValue();
}

GlobalBase::GlobalBase()
{
    LeptonNumber = int(InValue());
    JetNumber = int(InValue());
    BottomNumber = int(InValue());
    MissingEt = InValue();
    ScalarHt = InValue();
    LeptonHt = InValue();
    JetPt1 = InValue();
    JetPt2 = InValue();
    JetPt3 = InValue();
    JetPt4 = InValue();
    LeptonPt1 = InValue();
    LeptonPt2 = InValue();
}

Observables GlobalBase::Variables()
{
    return OBSERVABLE(LeptonNumber, "#l") + OBSERVABLE(BottomNumber, "#b") + OBSERVABLE(JetNumber, "#j") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}^{scalar}") + OBSERVABLE(LeptonHt, "H_{T}^{l}") + OBSERVABLE(JetPt1, "p_{T}(j_{1})") + OBSERVABLE(JetPt2, "p_{T}(j_{2})") + OBSERVABLE(JetPt3, "p_{T}(j_{3})") + OBSERVABLE(JetPt4, "p_{T}(j_{4})") + OBSERVABLE(LeptonPt1, "p_{T}(l_{1})") + OBSERVABLE(LeptonPt2, "p_{T}(l_{2})");
}

Observables GlobalBase::Spectators()
{
    return {};
}

GlobalObservableBranch::GlobalObservableBranch()
{}

Observables GlobalObservableBranch::Variables()
{
    return BdtBranch::Variables() + GlobalBase::Variables();
}

Observables GlobalObservableBranch::Spectators()
{
    return BdtBranch::Spectators() + GlobalBase::Spectators();
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
    return MultiBranch::Variables() + OBSERVABLE(LeptonNumber, "#l") + OBSERVABLE(BottomNumber, "#b") + OBSERVABLE(JetNumber, "#j") + OBSERVABLE(MissingEt, "E_{T}^{miss}") + OBSERVABLE(ScalarHt, "H_{T}^{scalar}") + OBSERVABLE(LeptonHt, "H_{T}^{l}") + OBSERVABLE(JetMass, "m_{j}") + OBSERVABLE(JetPt, "p_{T}^{j}") + OBSERVABLE(JetHt, "H_{T}^{j}") + OBSERVABLE(JetRap, "\\eta_{j}") + OBSERVABLE(JetPhi, "\\phi_{j}");
}

float EventShapesBranch::InValue()
{
    return BaseBranch::InitialValue();
}

EventShapesBranch::EventShapesBranch()
{
    Thrust = InValue();
    ThrustMajor = InValue();
    ThrustMinor = InValue();
    Oblateness = InValue();
    CParameter = InValue();
    DParameter = InValue();
    Sphericity = InValue();
    Aplanarity = InValue();
    Planarity = InValue();
    MHigh2 = InValue();
    MLow2 = InValue();
    BMax = InValue();
    BMin = InValue();
}

Observables EventShapesBranch::Variables()
{
    return OBSERVABLE(Thrust, "T") + OBSERVABLE(ThrustMajor, "T_{maj}") + OBSERVABLE(ThrustMinor, "T_{min}") + OBSERVABLE(Oblateness, "O") + OBSERVABLE(CParameter, "C") + OBSERVABLE(DParameter, "D") + OBSERVABLE(Sphericity, "S") + OBSERVABLE(Aplanarity, "#slash P") + OBSERVABLE(Planarity, "P") + OBSERVABLE(MHigh2, "M_{max}") + OBSERVABLE(MLow2, "M_{min}") + OBSERVABLE(BMax, "B_{max}") + OBSERVABLE(BMin, "B_{min}");
}

Observables EventShapesBranch::Spectators()
{
    return {};
}

}
