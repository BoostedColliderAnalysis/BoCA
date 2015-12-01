/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "TObject.h"
#include "Rtypes.h"
#include "physics/Prefixes.hh"

namespace boca
{

class Obs
{
public:
    Obs(float& value, std::string const& name, std::string const& nice_name = "");
    float& value() const;
    std::string name() const;
    std::string nice_name() const;
private:
    float* value_;
    std::string name_;
    std::string nice_name_;
};
typedef std::vector<boca::Obs> Observables;

/**
 * @brief Basic tree branches
 *
 */
class BaseBranch : public TObject
{
public:
    virtual ~BaseBranch();
    static float InitialValue();
protected:
    static Observables Join(Observables const& observables_1, Observables const& observables_2);
    static Observables Join(Observables const& observables_1, Observables const& observables_2, Observables const& observables_3);
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
    float Crosssection;
    float CrosssectionError;
    float Mass;
    float EventNumber;
    std::string Name;
private:
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

  CutBranch(){};
  std::vector<bool> passed_;

  template<typename Multiplet>
  void Fill(Multiplet const& multiplet) {
    ResultBranch::Fill(multiplet);
    passed_ = multiplet.passed_;
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
        Mass = multiplet.Jet().Mass() / GeV;
        Pt = multiplet.Jet().Pt() / GeV;
        Rap = multiplet.Jet().Rap() / rad;
        Phi = multiplet.Jet().Phi() / rad;
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
        Fill2(multiplet.singlet());
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
    virtual ~BottomBase() {};
private:
    ClassDef(BottomBase, 1)
    float InValue();
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
    float Dipolarity;
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
        Dipolarity = multiplet.Dipolarity();
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
class TChannelBranch : public MultiBranch
{
public:
    TChannelBranch();
    float Bdt3;
    float Mass12;
    float Mass23;
    float Mass13;
    float Pt12;
    float Pt23;
    float Pt13;
    float DeltaPt23;
    float DeltaPt13;
    float Ht12;
    float Ht23;
    float Ht13;
    float Rho23;
    float Rho13;
    float DeltaRap23;
    float DeltaRap13;
    float DeltaPhi23;
    float DeltaPhi13;
    float DeltaR23;
    float DeltaR13;
    float DeltaM23;
    float DeltaM13;
    float DeltaHt23;
    float DeltaHt13;
    float Pull23;
    float Pull13;
    float Pull32;
    float Pull31;
    float Dipolarity23;
    float Dipolarity13;
//   float Sphericity;
//   float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        Bdt3 = multiplet.Multiplet3().Bdt();
        Mass12 = multiplet.Jet12().Mass() / GeV;
        Mass23 = multiplet.Jet23().Mass() / GeV;
        Mass13 = multiplet.Jet13().Mass() / GeV;
        Pt12 = multiplet.Jet12().Pt() / GeV;
        Pt23 = multiplet.Jet23().Pt() / GeV;
        Pt13 = multiplet.Jet13().Pt() / GeV;
        DeltaPt23 = multiplet.DeltaPt23() / GeV;
        DeltaPt13 = multiplet.DeltaPt13() / GeV;
        Ht12 = multiplet.Ht12() / GeV;
        Ht23 = multiplet.Ht23() / GeV;
        Ht13 = multiplet.Ht13() / GeV;
        Rho23 = multiplet.Rho23();
        Rho13 = multiplet.Rho13();
        DeltaRap23 = multiplet.DeltaRap23() / rad;
        DeltaRap13 = multiplet.DeltaRap13() / rad;
        DeltaPhi23 = multiplet.DeltaPhi23() / rad;
        DeltaPhi13 = multiplet.DeltaPhi13() / rad;
        DeltaR23 = multiplet.DeltaR23() / rad;
        DeltaR13 = multiplet.DeltaR13() / rad;
        DeltaM23 = multiplet.DeltaM23() / GeV;
        DeltaM13 = multiplet.DeltaM13() / GeV;
        DeltaHt23 = multiplet.DeltaHt23() / GeV;
        DeltaHt13 = multiplet.DeltaHt13() / GeV;
        Pull23 = multiplet.Pull23() / rad;
        Pull13 = multiplet.Pull13() / rad;
        Pull32 = multiplet.Pull32() / rad;
        Pull31 = multiplet.Pull31() / rad;
        Dipolarity23 = multiplet.Dipolarity23();
        Dipolarity13 = multiplet.Dipolarity13();
        //     Aplanarity = signature.EventShape().Aplanarity(); // FIXME reenable this
//     Sphericity = signature.EventShape().Sphericity(); // FIXME reenable this
    }
    Observables Variables();

private:
    ClassDef(TChannelBranch, 1)
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
        Jet1Pt = multiplet.Singlet1().Jet().Pt() / GeV;
        Jet1Rap = multiplet.Singlet1().Jet().Rap() / rad;
        Jet1Phi = multiplet.Singlet1().Jet().Phi() / rad;
        Jet1Mass = multiplet.Singlet1().Jet().Mass() / GeV;
        Jet2Pt = multiplet.Singlet2().Jet().Pt() / GeV;
        Jet2Rap = multiplet.Singlet2().Jet().Rap() / rad;
        Jet2Phi = multiplet.Singlet2().Jet().Phi() / rad;
        Jet2Mass = multiplet.Singlet2().Jet().Mass() / GeV;
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
        BottomPt = multiplet.Singlet().Jet().Pt() / GeV;
//         BottomRap = std::abs(multiplet.Singlet().rap());
        BottomRap = multiplet.Singlet().Jet().Rap() / rad;
        BottomPhi = multiplet.Singlet().Jet().Phi() / rad;
        BottomMass = multiplet.Singlet().Jet().Mass() / GeV;
//         BottomBdt = multiplet.Singlet().Info().Bdt();
        TopPt = multiplet.Triplet().Jet().Pt() / GeV;
//         TopRap = std::abs(multiplet.Triplet().Jet().rap());
        TopRap = multiplet.Triplet().Jet().Rap() / rad;
        TopPhi = multiplet.Triplet().Jet().Phi() / rad;
        TopMass = multiplet.Triplet().Jet().Mass() / GeV;
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
        JetMass = multiplet.Rest().Jet().Mass() / GeV;
        JetPt = multiplet.Rest().Jet().Pt() / GeV;
        JetHt = multiplet.GlobalObservables().JetHt() / GeV;
        JetRap = multiplet.Rest().Rap() / rad;
        JetPhi = multiplet.Rest().Jet().Phi() / rad;
    }
    Observables Variables();

private:
    ClassDef(EventBranch, 1)
};

class Color
{
public:
    void Red();
    void Blue();
    void Heat();
    std::vector<int> Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue);
};

}
