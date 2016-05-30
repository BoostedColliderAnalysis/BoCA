/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Branches.hh"
#include "boca/File.hh"
#include "boca/OBSERVABLE.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

float BaseBranch::InitialValue()
{
    return -11.1111111; // must be non integer
}

InfoBranch::InfoBranch()
{
    INFO0;
    crosssection = InitialValue();
    crosssection_error = InitialValue();
    mass = InitialValue();
    event_number = 0;
}

InfoBranch::InfoBranch(File const& file)
{
    INFO0;
    SetCrosssection(file.Crosssection());
    SetCrosssectionError(file.CrosssectionError());
    SetMass(file.Mass());
    SetNames(file.Names());
    event_number = 0;
}

boca::Crosssection InfoBranch::Crosssection() const
{
    INFO0;
    return static_cast<double>(crosssection) * fb;
}
boca::Crosssection InfoBranch::CrosssectionError() const
{
    INFO0;
    return static_cast<double>(crosssection_error) * fb;
}
int InfoBranch::EventNumber() const
{
    INFO0;
    return event_number;
}
boca::Mass InfoBranch::Mass() const
{
    INFO0;
    return static_cast<double>(mass) * GeV;
}
std::string InfoBranch::Name() const
{
    INFO0;
    return names.Name();
}
boca::Names InfoBranch::Names() const
{
    INFO0;
    return names;
}
latex::String InfoBranch::LatexName() const
{
    INFO0;
    return names.LatexName();
}
void InfoBranch::SetCrosssection(boca::Crosssection const& crosssection_)
{
    INFO0;
    crosssection = crosssection_ / fb;
}
void InfoBranch::SetCrosssectionError(boca::Crosssection const& crosssection_error_)
{
    INFO0;
    crosssection_error = crosssection_error_ / fb;
}
void InfoBranch::SetEventNumber(int event_number_)
{
    INFO0;
    event_number = event_number_;
}
void InfoBranch::SetMass(boca::Mass const& mass_)
{
    INFO0;
    mass = mass_ / GeV;
}
void InfoBranch::SetNames(boca::Names const& names_)
{
    INFO0;
    names = names_;
}

ResultBranch::ResultBranch()
{
    Tag = static_cast<int>(InitialValue());
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
    return ResultBranch::Variables();
}

Observables BdtBranch::Spectators()
{
    return ResultBranch::Spectators() /*+ OBSERVABLE(Bdt)*/;
}

ParticleBranch::ParticleBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
    Charge = static_cast<int>(InitialValue());
}

Observables ParticleBranch::Variables()
{
    return BdtBranch::Variables() + OBSERVABLE(Mass, latex::String("m") + " [GeV]") + OBSERVABLE(Pt, latex::String("p_{T}") + " [GeV]");
}

Observables ParticleBranch::Spectators()
{
    return BdtBranch::Spectators() + OBSERVABLE(Charge, "e") + OBSERVABLE(Rap, "\\eta") + OBSERVABLE(Phi, "\\phi");
}

TwoBodyBranch::TwoBodyBranch()
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

Observables TwoBodyBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(Ht, latex::String("H_{T}") + " [GeV]") + OBSERVABLE(DeltaPt, latex::String("\\Delta P_{T}") + " [GeV]") + OBSERVABLE(DeltaM, latex::String("\\Delta m") + " [GeV]") + OBSERVABLE(DeltaRap, latex::String("\\Delta \\eta")) + OBSERVABLE(DeltaPhi, latex::String("\\Delta \\phi")) + OBSERVABLE(DeltaR, latex::String("\\Delta R")) + OBSERVABLE(Rho, latex::String("\\rho")) + OBSERVABLE(Bdt1, "BDT_{1}") + OBSERVABLE(Bdt2, "BDT_{2}") + OBSERVABLE(Pull1, latex::String("#theta_{1}")) + OBSERVABLE(Pull2, latex::String("#theta_{2}")) /*+ OBSERVABLE(Dipolarity, latex::String("D"))*/;
    //return ParticleBranch::Variables() + OBSERVABLE(Ht) + OBSERVABLE(DeltaPt) + OBSERVABLE(DeltaM) + OBSERVABLE(DeltaRap) + OBSERVABLE(DeltaPhi) + OBSERVABLE(DeltaR) + OBSERVABLE(Rho);
}

Observables TwoBodyBranch::Spectators()
{
    return ParticleBranch::Spectators();
}

MultiBranch::MultiBranch()
{
    DeltaHt = InitialValue();
}

Observables MultiBranch::Variables()
{
    return TwoBodyBranch::Variables() + OBSERVABLE(DeltaHt, latex::String("\\Delta H_{T}") + " [GeV]");
}

ThreeBodyBranch::ThreeBodyBranch()
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

Observables ThreeBodyBranch::Variables()
{
    return ParticleBranch::Variables() + OBSERVABLE(Ht, "H_{T}") + OBSERVABLE(Bdt1, "BDT_{1}") + OBSERVABLE(Bdt2, "BDT_{2}") + OBSERVABLE(Bdt3, "BDT_{3}") + OBSERVABLE(Mass12, "m_{12}") + OBSERVABLE(Mass23, "m_{23}") + OBSERVABLE(Mass13, "m_{13}") + OBSERVABLE(Pt12, "p_{T}^{12}") + OBSERVABLE(Pt23, "p_{T}^{23}") + OBSERVABLE(Pt13, "p_{T}^{13}") + OBSERVABLE(DeltaPt12, "\\Delta p_{T}^{12}") + OBSERVABLE(DeltaPt23, "\\Delta p_{T}^{23}") + OBSERVABLE(DeltaPt13, "\\Delta p_{T}^{13}") + OBSERVABLE(Ht12, "H_{T}^{12}") + OBSERVABLE(Ht23, "H_{T}^{23}") + OBSERVABLE(Ht13, "H_{T}^{13}") + OBSERVABLE(Rho12, "\\rho_{12}") + OBSERVABLE(Rho23, "\\rho_{23}") + OBSERVABLE(Rho13, "\\rho_{13}") + OBSERVABLE(DeltaRap12, "\\Delta\\eta_{12}") + OBSERVABLE(DeltaRap23, "\\Delta\\eta_{23}") + OBSERVABLE(DeltaRap13, "\\Delta\\eta_{13}") + OBSERVABLE(DeltaPhi12, "\\Delta\\phi_{12}") + OBSERVABLE(DeltaPhi23, "\\Delta\\phi_{23}") + OBSERVABLE(DeltaPhi13, "\\Delta\\phi_{13}") + OBSERVABLE(DeltaR12, "\\Delta R_{12}") + OBSERVABLE(DeltaR23, "\\Delta R_{23}") + OBSERVABLE(DeltaR13, "\\Delta R_{13}") + OBSERVABLE(DeltaM12, "\\Delta m_{12}") + OBSERVABLE(DeltaM23, "\\Delta m_{23}") + OBSERVABLE(DeltaM13, "\\Delta m_{13}") + OBSERVABLE(DeltaHt12, "\\Delta H_{T}^{12}") + OBSERVABLE(DeltaHt23, "\\Delta H_{T}^{23}") + OBSERVABLE(DeltaHt13, "\\Delta H_{T}^{13}") + OBSERVABLE(Pull23, "#theta_{23}") + OBSERVABLE(Pull13, "#theta_{13}") + OBSERVABLE(Pull32, "#theta_{32}") + OBSERVABLE(Pull31, "#theta_{31}") /*+ OBSERVABLE(Dipolarity23, "D_{23}") + OBSERVABLE(Dipolarity13, "D_{13}")*/ /*+ OBSERVABLE(Aplanarity, "#slashed{P}") + OBSERVABLE(Sphericity, "S")*/;
}

float GlobalBase::InValue()
{
    return BaseBranch::InitialValue();
}

GlobalBase::GlobalBase()
{
    LeptonNumber = static_cast<int>(InValue());
    JetNumber = static_cast<int>(InValue());
    BottomNumber = static_cast<int>(InValue());
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
    LeptonNumber = static_cast<int>(InitialValue());
    JetNumber = static_cast<int>(InitialValue());
    BottomNumber = static_cast<int>(InitialValue());
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

float EventShapesBase::InValue()
{
    return BaseBranch::InitialValue();
}

EventShapesBase::EventShapesBase()
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

Observables EventShapesBase::Variables()
{
    return OBSERVABLE(Thrust, "T") + OBSERVABLE(ThrustMajor, "T_{maj}") + OBSERVABLE(ThrustMinor, "T_{min}") + OBSERVABLE(Oblateness, "O") + OBSERVABLE(CParameter, "C") + OBSERVABLE(DParameter, "D") + OBSERVABLE(Sphericity, "S") + OBSERVABLE(Aplanarity, "#slash P") + OBSERVABLE(Planarity, "P") + OBSERVABLE(MHigh2, "M_{max}") + OBSERVABLE(MLow2, "M_{min}") + OBSERVABLE(BMax, "B_{max}") + OBSERVABLE(BMin, "B_{min}");
}

Observables EventShapesBase::Spectators()
{
    return {};
}

SignatureBranch::SignatureBranch()
{
}

Observables SignatureBranch::Variables()
{
  return ThreeBodyBranch::Variables() + EventShapesBase::Variables();
}

Observables SignatureBranch::Spectators()
{
  return ThreeBodyBranch::Spectators() + EventShapesBase::Spectators();
}

}
