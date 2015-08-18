/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>
#include <string>
#include "TObject.h"
#include "Rtypes.h"

namespace boca {

class Obs {
public:
    Obs(const float& value, std::string const& name, std::string const& nice_name);
    float& value() const;
    std::string name() const;
    std::string nice_name() const;
private:
    float* value_;
    std::string name_;
    std::string nice_name_;
};
typedef std::vector<Obs> Observables;

/**
 * @brief Basic tree branches
 *
 */
class BaseBranch : public TObject {
public:
    virtual ~BaseBranch();
protected:
    static float InitialValue();
    static Observables Join(const Observables& observables_1, const Observables& observables_2);
    static Observables Join(const Observables& observables_1, const Observables& observables_2, const Observables& observables_3);
private:
    ClassDef(BaseBranch, 1)
};

/**
 * @brief Basic tree branches
 *
 */
class InfoBranch : public BaseBranch {
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

class ResultBranch : public BaseBranch {
public:
    ResultBranch();
    float Bdt;
    float Tag;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        Tag = int(multiplet.Tag());
        Bdt = multiplet.Bdt();
    }
    virtual Observables Variables() const;
    virtual Observables Spectators() const;
private:
    ClassDef(ResultBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class ParticleBranch : public ResultBranch {
public:
    ParticleBranch();
    float Mass;
    float Pt;
    float Rap;
    float Phi;
    float Charge;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
      ResultBranch::Fill(multiplet);
        Mass = multiplet.Jet().m();
        Pt = multiplet.Jet().pt();
        Rap = multiplet.Jet().rap();
        Phi = multiplet.Jet().phi_std();
        Charge = multiplet.Charge();
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(ParticleBranch, 1)
};


/**
 *
 * @brief Bottom tagger root tree structure base class
 * (this construct is necessary because root can not handel virtual inheritance needed for the resulution of the dreaded diamond)
 *
 */
class BottomBase {
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
    void Fill(Multiplet const& multiplet)
    {
        Fill2(multiplet.singlet());
    }
    template<typename Singlet>
    void Fill2(Singlet const& singlet)
    {
        VertexMass = singlet.VertexMass();
        MaxDisplacement = singlet.MaxDisplacement();
        MeanDisplacement = singlet.MeanDisplacement();
        SumDisplacement = singlet.SumDisplacement();
        Multiplicity = singlet.Multiplicity();
        Radius = singlet.Radius();
        Spread = singlet.Spread();
        VertexRadius = singlet.VertexRadius();
        VertexSpread = singlet.VertexSpread();
        EnergyFraction = singlet.EnergyFraction();
    }
    virtual Observables Variables() const;
    virtual Observables Spectators() const;
    virtual ~BottomBase() {};
private:
    ClassDef(BottomBase, 1)
    float InValue();
};

/**
 *
 * @brief Bottom tagger root tree structure
 *
 */
class BottomBranch : public ParticleBranch, public BottomBase {
public:
  Observables Variables() const;
  Observables Spectators() const;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        ParticleBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }
private:
    ClassDef(BottomBranch, 1)
};

/**
 *
 * @brief Tau tagger root tree structure
 *
 */
class TauBranch : public ParticleBranch {
public:
    TauBranch();
    float EmRadius;
    float TrackRadius;
    float MomentumFraction;
    float CoreEnergyFraction;
    float EmFraction;
    float ClusterMass;
    float TrackMass;
    float FlightPath;
    float TrtHtFraction;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        ParticleBranch::Fill(multiplet);
        EmRadius = multiplet.EmRadius();
        TrackRadius = multiplet.TrackRadius();
        MomentumFraction = multiplet.MomentumFraction();
        CoreEnergyFraction = multiplet.CoreEnergyFraction();
        EmFraction = multiplet.EmFraction();
        ClusterMass = multiplet.ClusterMass();
        TrackMass = multiplet.TrackMass();
        FlightPath = multiplet.FlightPath();
        TrtHtFraction = multiplet.TrtHtFraction();
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(TauBranch, 1)
};


class PairBranch : public ParticleBranch {
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
    float Pull;
    float DeltaPull;
    float Dipolarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        ParticleBranch::Fill(multiplet);
        Ht = multiplet.Ht();
        DeltaPt = multiplet.DeltaPt();
        DeltaM = multiplet.DeltaM();
        DeltaRap = multiplet.DeltaRap();
        DeltaPhi = multiplet.DeltaPhi();
        DeltaR = multiplet.DeltaR();
        Rho = multiplet.Rho();
        Bdt1 = multiplet.Multiplet1().Bdt();
        Bdt2 = multiplet.Multiplet2().Bdt();
        Pull = multiplet.PullSum();
        DeltaPull = multiplet.PullDifference();
        Dipolarity = multiplet.Dipolarity();
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(PairBranch, 1)
};


class MultiBranch : public PairBranch {
public:
    MultiBranch();
    float DeltaHt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        DeltaHt = multiplet.DeltaHt();
    }
    Observables Variables() const;

private:
    ClassDef(MultiBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class WHadronicBranch : public PairBranch {
    ClassDef(WHadronicBranch, 1)
};

/**
 *
 * @brief Z tagger root tree structure
 *
 */
class ZHadronicBranch : public PairBranch {
    ClassDef(ZHadronicBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class JetPairBranch : public PairBranch {
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
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        Jet1Pt = multiplet.Singlet1().Jet().pt();
        Jet1Rap = multiplet.Singlet1().Jet().rap();
        Jet1Phi = multiplet.Singlet1().Jet().phi();
        Jet1Mass = multiplet.Singlet1().Jet().m();
        Jet2Pt = multiplet.Singlet2().Jet().pt();
        Jet2Rap = multiplet.Singlet2().Jet().rap();
        Jet2Phi = multiplet.Singlet2().Jet().phi();
        Jet2Mass = multiplet.Singlet2().Jet().m();
    }
    Observables Variables() const;

private:
    ClassDef(JetPairBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class TripletJetPairBranch : public PairBranch {
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
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.Singlet().Jet().pt();
//         BottomRap = std::abs(multiplet.Singlet().rap());
        BottomRap = multiplet.Singlet().Jet().rap();
        BottomPhi = multiplet.Singlet().Jet().phi();
        BottomMass = multiplet.Singlet().Jet().m();
//         BottomBdt = multiplet.Singlet().user_info<JetInfo>().Bdt();
        TopPt = multiplet.Triplet().Jet().pt();
//         TopRap = std::abs(multiplet.Triplet().Jet().rap());
        TopRap = multiplet.Triplet().Jet().rap();
        TopPhi = multiplet.Triplet().Jet().phi();
        TopMass = multiplet.Triplet().Jet().m();
        TopBdt = multiplet.Triplet().Bdt();
    }
    Observables Variables() const;

private:
    ClassDef(TripletJetPairBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class WSemiBranch : public PairBranch {
public:
    WSemiBranch();
    float LeptonPt;
    float NeutrinoPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Jet().pt();
        NeutrinoPt = multiplet.Singlet2().Jet().pt();
    }
    Observables Variables() const;

private:
    ClassDef(WSemiBranch, 1)
};


/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopHadronicBranch : public MultiBranch, public BottomBase {
public:
    TopHadronicBranch();
    float BottomMass;
    float WMass;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        MultiBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomMass = multiplet.Singlet().Jet().m();
        WMass = multiplet.Doublet().Jet().m();
        LeptonPt = multiplet.pt();
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(TopHadronicBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopLeptonicBranch : public PairBranch, public BottomBase {
public:
    TopLeptonicBranch();
    float BottomPt;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomPt = multiplet.Singlet().Jet().pt();
        LeptonPt = multiplet.Doublet().Jet().pt(); // FIXME what is with the case of W
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(TopLeptonicBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HiggsBranch : public PairBranch, public BottomBase {
public:
    HiggsBranch();
    float LeptonPt;
    float LeptonDeltaR;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet)
    {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        LeptonPt = multiplet.LeptonPt;
        LeptonDeltaR = multiplet.LeptonDeltaR;
    }
    Observables Variables() const;
    Observables Spectators() const;

private:
    ClassDef(HiggsBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class EventBranch : public MultiBranch {
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
    void Fill(Multiplet const& multiplet)
    {
        boca::MultiBranch::Fill(multiplet);
        LeptonNumber = multiplet.GlobalObservables().LeptonNumber();
        JetNumber = multiplet.GlobalObservables().JetNumber();
        BottomNumber = multiplet.GlobalObservables().BottomNumber();
        MissingEt = multiplet.GlobalObservables().MissingEt();
        ScalarHt = multiplet.GlobalObservables().ScalarHt();
        LeptonHt = multiplet.GlobalObservables().LeptonHt();
        JetMass = multiplet.Singlet().Jet().m();
        JetPt = multiplet.Singlet().Jet().pt();
        JetHt = multiplet.GlobalObservables().JetHt();
        JetRap = multiplet.Singlet().Rapidity();
        JetPhi = multiplet.Singlet().Jet().phi();
    }
    Observables Variables() const;

private:
    ClassDef(EventBranch, 1)
};

class Color {
public:
    void Red();
    void Blue();
    void Heat();
    std::vector<int> Table(std::vector<double>& length, std::vector<double>& red, std::vector<double>& green, std::vector<double>& blue);
};

}
