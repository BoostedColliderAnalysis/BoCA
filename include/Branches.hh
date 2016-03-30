/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TObject.h"

#include "physics/Prefixes.hh"

#include "Observables.hh"

namespace boca
{

class File;

/**
 * @brief Basic tree branches
 *
 */
class BaseBranch : public TObject
{
public:
//     virtual ~BaseBranch();
    static float InitialValue();
protected:
private:
    ClassDef(BaseBranch, 1)
};

/**
 * @brief Basic tree branches
 *
 */
class InfoBranch : public BaseBranch
{
public:
    InfoBranch();
    InfoBranch(File const& file);
    boca::Crosssection Crosssection() const;
    boca::Crosssection CrosssectionError() const;
    boca::Mass Mass() const;
    int EventNumber() const;
    std::string Name() const;
    boca::Names Names() const;
    std::string LatexName() const;
    void SetCrosssection(boca::Crosssection crosssection);
    void SetCrosssectionError(boca::Crosssection crosssection_error);
    void SetMass(boca::Mass mass);
    void SetEventNumber(int event_number);
    void SetNames(boca::Names const& names);
private:
    float crosssection;
    float crosssection_error;
    float mass;
    int event_number;
    boca::Names names;
    ClassDef(InfoBranch, 1)
};

class ResultBranch : public BaseBranch
{
public:
    ResultBranch();
    float Tag;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Tag = int(multiplet.Tag());
    }
    virtual Observables Variables();
    virtual Observables Spectators();
private:
    ClassDef(ResultBranch, 1)
};

class BdtBranch : public ResultBranch
{
public:
    BdtBranch();
    float Bdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ResultBranch::Fill(multiplet);
        Bdt = multiplet.Bdt();
    }
    virtual Observables Variables();
    virtual Observables Spectators();
private:
    ClassDef(BdtBranch, 1)
};


class CutBranch : public ResultBranch
{

public:

    CutBranch() {};
    std::vector<bool> passed_;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ResultBranch::Fill(multiplet);
        passed_ = multiplet.Passed();
    }

private:

    ClassDef(CutBranch, 1)

};

/**
 * @brief Class for saving event informations to root
 *
 */
class ParticleBranch : public BdtBranch
{
public:
    ParticleBranch();
    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float Charge;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        BdtBranch::Fill(multiplet);
        Mass = multiplet.Mass() / GeV;
        Pt = multiplet.Pt() / GeV;
        Rap = multiplet.Rap() / rad;
        Phi = multiplet.Phi() / rad;
        Charge = multiplet.Charge();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(ParticleBranch, 1)
};


/**
 *
 * @brief Bottom tagger root tree structure base class
 * @details this construct is necessary because root can not handel virtual inheritance needed for the resulution of the dreaded diamond
 *
 */
class BottomBase
{
public:
    BottomBase();
    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multiplicity;
    float Radius;
    float Spread;
    float VertexRadius;
    float VertexSpread;
    float EnergyFraction;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Fill2(multiplet.ConstituentJet());
    }
    template<typename Singlet>
    void Fill2(Singlet const& singlet) {
        VertexMass = singlet.Info().VertexMass() / GeV;
        MaxDisplacement = singlet.MaxDisplacement();
        MeanDisplacement = singlet.MeanDisplacement();
        SumDisplacement = singlet.SumDisplacement();
        Multiplicity = singlet.Info().VertexNumber();
        Radius = singlet.Radius() / rad;
        Spread = singlet.Spread();
        VertexRadius = singlet.VertexRadius() / rad;
        VertexSpread = singlet.VertexSpread();
        EnergyFraction = singlet.EnergyFraction();
    }
    virtual Observables Variables();
    virtual Observables Spectators();
private:
    float InValue();
    ClassDef(BottomBase, 1)
};

class PairBranch : public ParticleBranch
{
public:
    PairBranch();
    float Ht;
    float DeltaPt;
    float DeltaM;
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;
    float Rho;
    float Bdt1;
    float Bdt2;
    float Pull1;
    float Pull2;
//     float Dipolarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ParticleBranch::Fill(multiplet);
        Ht = multiplet.Ht() / GeV;
        DeltaPt = multiplet.DeltaPt() / GeV;
        DeltaM = multiplet.DeltaM() / GeV;
        DeltaRap = multiplet.DeltaRap() / rad;
        DeltaPhi = multiplet.DeltaPhi() / rad;
        DeltaR = multiplet.DeltaR() / rad;
        Rho = multiplet.Rho();
        Bdt1 = multiplet.Multiplet1().Bdt();
        Bdt2 = multiplet.Multiplet2().Bdt();
        Pull1 = multiplet.Pull12() / rad;
        Pull2 = multiplet.Pull21() / rad;
//         Dipolarity = multiplet.Dipolarity();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(PairBranch, 1)
};


class MultiBranch : public PairBranch
{
public:
    MultiBranch();
    float DeltaHt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        DeltaHt = multiplet.DeltaHt() / GeV;
    }
    Observables Variables();

private:
    ClassDef(MultiBranch, 1)
};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class SignatureBranch : public ParticleBranch
{
public:
    SignatureBranch();
    float Ht;
    float Bdt1;
    float Bdt2;
    float Bdt3;
    float Mass12;
    float Mass23;
    float Mass13;
    float Pt12;
    float Pt23;
    float Pt13;
    float DeltaPt12;
    float DeltaPt23;
    float DeltaPt13;
    float Ht12;
    float Ht23;
    float Ht13;
    float Rho12;
    float Rho23;
    float Rho13;
    float DeltaRap12;
    float DeltaRap23;
    float DeltaRap13;
    float DeltaPhi12;
    float DeltaPhi23;
    float DeltaPhi13;
    float DeltaR12;
    float DeltaR23;
    float DeltaR13;
    float DeltaM12;
    float DeltaM23;
    float DeltaM13;
    float DeltaHt12;
    float DeltaHt23;
    float DeltaHt13;
    float Pull12;
    float Pull21;
    float Pull23;
    float Pull13;
    float Pull32;
    float Pull31;
//     float Dipolarity23;
//     float Dipolarity13;
    float Sphericity;
    float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        ParticleBranch::Fill(multiplet);
        Ht = multiplet.Ht() / GeV;
        Bdt1 = multiplet.Multiplet1().Bdt();
        Bdt2 = multiplet.Multiplet2().Bdt();
        Bdt3 = multiplet.Multiplet3().Bdt();
        Mass12 = multiplet.Multiplet12().Mass() / GeV;
        Mass23 = multiplet.Multiplet23().Mass() / GeV;
        Mass13 = multiplet.Multiplet13().Mass() / GeV;
        Pt12 = multiplet.Multiplet12().Pt() / GeV;
        Pt23 = multiplet.Multiplet23().Pt() / GeV;
        Pt13 = multiplet.Multiplet13().Pt() / GeV;
        DeltaPt12 = multiplet.Multiplet12().DeltaPt() / GeV;
        DeltaPt23 = multiplet.Multiplet23().DeltaPt() / GeV;
        DeltaPt13 = multiplet.Multiplet13().DeltaPt() / GeV;
        Ht12 = multiplet.Multiplet12().Ht() / GeV;
        Ht23 = multiplet.Multiplet23().Ht() / GeV;
        Ht13 = multiplet.Multiplet13().Ht() / GeV;
        Rho12 = multiplet.Multiplet12().Rho();
        Rho23 = multiplet.Multiplet23().Rho();
        Rho13 = multiplet.Multiplet13().Rho();
        DeltaRap12 = multiplet.Multiplet12().DeltaRap() / rad;
        DeltaRap23 = multiplet.Multiplet23().DeltaRap() / rad;
        DeltaRap13 = multiplet.Multiplet13().DeltaRap() / rad;
        DeltaPhi12 = multiplet.Multiplet12().DeltaPhi() / rad;
        DeltaPhi23 = multiplet.Multiplet23().DeltaPhi() / rad;
        DeltaPhi13 = multiplet.Multiplet13().DeltaPhi() / rad;
        DeltaR12 = multiplet.Multiplet12().DeltaR() / rad;
        DeltaR23 = multiplet.Multiplet23().DeltaR() / rad;
        DeltaR13 = multiplet.Multiplet13().DeltaR() / rad;
        DeltaM12 = multiplet.Multiplet12().DeltaM() / GeV;
        DeltaM23 = multiplet.Multiplet23().DeltaM() / GeV;
        DeltaM13 = multiplet.Multiplet13().DeltaM() / GeV;
        DeltaHt12 = multiplet.Multiplet12().DeltaHt() / GeV;
        DeltaHt23 = multiplet.Multiplet23().DeltaHt() / GeV;
        DeltaHt13 = multiplet.Multiplet13().DeltaHt() / GeV;
        Pull12 = multiplet.Multiplet12().Pull12() / rad;
        Pull21 = multiplet.Multiplet12().Pull21() / rad;
        Pull23 = multiplet.Multiplet23().Pull12() / rad;
        Pull32 = multiplet.Multiplet23().Pull21() / rad;
        Pull13 = multiplet.Multiplet13().Pull12() / rad;
        Pull31 = multiplet.Multiplet13().Pull21() / rad;
        //         Dipolarity23 = multiplet.Multiplet23().Dipolarity();
        //         Dipolarity13 = multiplet.Multiplet13().Dipolarity();
        Aplanarity = multiplet.EventShapes().Aplanarity();
        Sphericity = multiplet.EventShapes().Sphericity();
    }
    Observables Variables();

private:
    ClassDef(SignatureBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class JetPairBranch : public PairBranch
{
public:
    JetPairBranch();
    float Jet1Mass;
    float Jet1Pt;
    float Jet1Rap;
    float Jet1Phi;
    float Jet2Mass;
    float Jet2Pt;
    float Jet2Rap;
    float Jet2Phi;
//     float BdtRatio11;
//     float BdtRatio12;
//     float BdtRatio13;
//     float BdtRatio14;
//     float BdtRatio21;
//     float BdtRatio22;
//     float BdtRatio23;
//     float BdtRatio24;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        Jet1Pt = multiplet.Singlet1().Pt() / GeV;
        Jet1Rap = multiplet.Singlet1().Rap() / rad;
        Jet1Phi = multiplet.Singlet1().Phi() / rad;
        Jet1Mass = multiplet.Singlet1().Mass() / GeV;
        Jet2Pt = multiplet.Singlet2().Pt() / GeV;
        Jet2Rap = multiplet.Singlet2().Rap() / rad;
        Jet2Phi = multiplet.Singlet2().Phi() / rad;
        Jet2Mass = multiplet.Singlet2().Mass() / GeV;
    }
    Observables Variables();

private:
    ClassDef(JetPairBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletJetPairBranch : public PairBranch
{
public:
    TripletJetPairBranch();
    float BottomMass;
    float BottomPt;
    float BottomRap;
    float BottomPhi;
    float BottomBdt;
    float BottomBTag;
    float TopMass;
    float TopPt;
    float TopRap;
    float TopPhi;
    float TopBdt;
    float TopBTag;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.Singlet().Pt() / GeV;
//         BottomRap = std::abs(multiplet.Singlet().rap());
        BottomRap = multiplet.Singlet().Rap() / rad;
        BottomPhi = multiplet.Singlet().Phi() / rad;
        BottomMass = multiplet.Singlet().Mass() / GeV;
//         BottomBdt = multiplet.Singlet().Info().Bdt();
        TopPt = multiplet.Triplet().Pt() / GeV;
//         TopRap = std::abs(multiplet.Triplet().rap());
        TopRap = multiplet.Triplet().Rap() / rad;
        TopPhi = multiplet.Triplet().Phi() / rad;
        TopMass = multiplet.Triplet().Mass() / GeV;
        TopBdt = multiplet.Triplet().Bdt();
    }
    Observables Variables();

private:
    ClassDef(TripletJetPairBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class GlobalBase
{
public:
  GlobalBase();

  float LeptonNumber;
  float JetNumber;
  float BottomNumber;
  float MissingEt;
  float ScalarHt;
  float LeptonHt;
  float JetPt1;
  float JetPt2;
  float JetPt3;
  float JetPt4;
  float LeptonPt1;
  float LeptonPt2;

  template<typename Multiplet>
  void Fill(Multiplet const& multiplet) {
    LeptonNumber = multiplet.LeptonNumber();
    JetNumber = multiplet.JetNumber();
    BottomNumber = multiplet.BottomNumber();
    MissingEt = multiplet.MissingEt() / GeV;
    ScalarHt = multiplet.ScalarHt() / GeV;
    LeptonHt = multiplet.LeptonHt() / GeV;
    LeptonPt1 = multiplet.LeptonPt(0) / GeV;
    LeptonPt2 = multiplet.LeptonPt(1) / GeV;
    JetPt1 = multiplet.JetPt(0) / GeV;
    JetPt2 = multiplet.JetPt(1) / GeV;
    JetPt3 = multiplet.JetPt(2) / GeV;
    JetPt4 = multiplet.JetPt(3) / GeV;
  }
  virtual Observables Variables();
  virtual Observables Spectators();

private:
  float InValue();
  ClassDef(GlobalBase, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class GlobalObservableBranch : public BdtBranch, public GlobalBase
{
public:
  GlobalObservableBranch();

  template<typename Multiplet>
  void Fill(Multiplet const& multiplet) {
    BdtBranch::Fill(multiplet);
    GlobalBase::Fill(multiplet);
  }
  Observables Variables();
  Observables Spectators();

private:
  ClassDef(GlobalObservableBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class EventBranch : public MultiBranch
{
public:
    EventBranch();

    float LeptonNumber;
    float JetNumber;
    float BottomNumber;
    float MissingEt;
    float ScalarHt;

    float LeptonHt;
    float JetMass;
    float JetPt;
    float JetHt;
    float JetRap;
    float JetPhi;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        LeptonNumber = multiplet.GlobalObservables().LeptonNumber();
        JetNumber = multiplet.GlobalObservables().JetNumber();
        BottomNumber = multiplet.GlobalObservables().BottomNumber();
        MissingEt = multiplet.GlobalObservables().MissingEt() / GeV;
        ScalarHt = multiplet.GlobalObservables().ScalarHt() / GeV;
        LeptonHt = multiplet.GlobalObservables().LeptonHt() / GeV;
        JetMass = multiplet.Rest().Mass() / GeV;
        JetPt = multiplet.Rest().Pt() / GeV;
        JetHt = multiplet.GlobalObservables().JetHt() / GeV;
        JetRap = multiplet.Rest().Rap() / rad;
        JetPhi = multiplet.Rest().Phi() / rad;
    }
    Observables Variables();

private:
    ClassDef(EventBranch, 1)
};

/**
 * @brief Event Shape Branch
 *
 */
class EventShapesBranch
{
public:
  EventShapesBranch();

  float Thrust;
  float ThrustMajor;
  float ThrustMinor;
  float Oblateness;
  float CParameter;
  float DParameter;
  float Sphericity;
  float Aplanarity;
  float Planarity;
  float MHigh2;
  float MLow2;
  float BMax;
  float BMin;

  template<typename Multiplet>
  void Fill(Multiplet const& multiplet) {
    Thrust = multiplet.EventShapes().Thrust();
    ThrustMajor = multiplet.EventShapes().ThrustMajor();
    ThrustMinor = multiplet.EventShapes().ThrustMinor();
    Oblateness = multiplet.EventShapes().Oblateness();
    CParameter = multiplet.EventShapes().CParameter();
    DParameter = multiplet.EventShapes().DParameter();
    Sphericity = multiplet.EventShapes().Sphericity();
    Aplanarity = multiplet.EventShapes().Aplanarity();
    Planarity = multiplet.EventShapes().Planarity();
    MHigh2 = multiplet.EventShapes().HemisphereMasses().MHigh2();
    MLow2 = multiplet.EventShapes().HemisphereMasses().MLow2();
    BMax = multiplet.EventShapes().HemisphereMasses().BMax();
    BMin = multiplet.EventShapes().HemisphereMasses().BMin();
  }
  virtual Observables Variables();
  virtual Observables Spectators();

private:
  ClassDef(EventShapesBranch, 1)
  float InValue();
};

}
