/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <vector>
#include <string>
#include "TObject.h"
#include "Rtypes.h"

namespace boca
{

class Obs
{
public:
    Obs(float & value, std::string const& name, std::string const& nice_name);
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
    float Bdt;
    float Tag;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Tag = int(multiplet.Tag());
        Bdt = multiplet.Bdt();
    }
    virtual Observables Variables();
    virtual Observables Spectators();
private:
    ClassDef(ResultBranch, 1)
};

/**
 * @brief Class for saving event informations to root
 *
 */
class ParticleBranch : public ResultBranch
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
        ResultBranch::Fill(multiplet);
        Mass = multiplet.Jet().m();
        Pt = multiplet.Jet().pt();
        Rap = multiplet.Jet().rap();
        Phi = multiplet.Jet().phi_std();
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
    virtual Observables Variables();
    virtual Observables Spectators();
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
class BottomBranch : public ParticleBranch, public BottomBase
{
public:
    Observables Variables();
    Observables Spectators();
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
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
class TauBranch : public ParticleBranch
{
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
    void Fill(Multiplet const& multiplet) {
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
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(TauBranch, 1)
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
    float Pull;
    float DeltaPull;
    float Dipolarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
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
        DeltaHt = multiplet.DeltaHt();
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
    float DeltaPull23;
    float DeltaPull13;
    float Dipolarity23;
    float Dipolarity13;
//   float Sphericity;
//   float Aplanarity;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        Bdt3 = multiplet.Multiplet3().Bdt();
        Mass12 = multiplet.Jet12().m();
        Mass23 = multiplet.Jet23().m();
        Mass13 = multiplet.Jet13().m();
        Pt12 = multiplet.Jet12().pt();
        Pt23 = multiplet.Jet23().pt();
        Pt13 = multiplet.Jet13().pt();
        DeltaPt23 = multiplet.DeltaPt23();
        DeltaPt13 = multiplet.DeltaPt13();
        Ht12 = multiplet.Ht12();
        Ht23 = multiplet.Ht23();
        Ht13 = multiplet.Ht13();
        Rho23 = multiplet.Rho23();
        Rho13 = multiplet.Rho13();
        DeltaRap23 = multiplet.DeltaRap23();
        DeltaRap13 = multiplet.DeltaRap13();
        DeltaPhi23 = multiplet.DeltaPhi23();
        DeltaPhi13 = multiplet.DeltaPhi13();
        DeltaR23 = multiplet.DeltaR23();
        DeltaR13 = multiplet.DeltaR13();
        DeltaM23 = multiplet.DeltaM23();
        DeltaM13 = multiplet.DeltaM13();
        DeltaHt23 = multiplet.DeltaHt23();
        DeltaHt13 = multiplet.DeltaHt13();
        Pull23 = multiplet.PullSum23();
        Pull13 = multiplet.PullSum13();
        DeltaPull23 = multiplet.PullDifference23();
        DeltaPull13 = multiplet.PullDifference13();
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
class WHadronicBranch : public PairBranch
{
    ClassDef(WHadronicBranch, 1)
};

/**
 *
 * @brief Z tagger root tree structure
 *
 */
class ZHadronicBranch : public PairBranch
{
    ClassDef(ZHadronicBranch, 1)
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
        Jet1Pt = multiplet.Singlet1().Jet().pt();
        Jet1Rap = multiplet.Singlet1().Jet().rap();
        Jet1Phi = multiplet.Singlet1().Jet().phi();
        Jet1Mass = multiplet.Singlet1().Jet().m();
        Jet2Pt = multiplet.Singlet2().Jet().pt();
        Jet2Rap = multiplet.Singlet2().Jet().rap();
        Jet2Phi = multiplet.Singlet2().Jet().phi();
        Jet2Mass = multiplet.Singlet2().Jet().m();
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
    Observables Variables();

private:
    ClassDef(TripletJetPairBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class WSemiBranch : public PairBranch
{
public:
    WSemiBranch();
    float LeptonPt;
    float NeutrinoPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Jet().pt();
        NeutrinoPt = multiplet.Singlet2().Jet().pt();
    }
    Observables Variables();

private:
    ClassDef(WSemiBranch, 1)
};


/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopHadronicBranch : public MultiBranch, public BottomBase
{
public:
    TopHadronicBranch();
    float BottomMass;
    float WMass;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomMass = multiplet.Singlet().Jet().m();
        WMass = multiplet.Doublet().Jet().m();
        LeptonPt = multiplet.pt();
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(TopHadronicBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopLeptonicBranch : public PairBranch, public BottomBase
{
public:
    TopLeptonicBranch();
    float BottomPt;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomPt = multiplet.Singlet().Jet().pt();
        LeptonPt = multiplet.Doublet().Jet().pt(); // FIXME what is with the case of W
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(TopLeptonicBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HiggsBranch : public PairBranch, public BottomBase
{
public:
    HiggsBranch();
    float LeptonPt;
    float LeptonDeltaR;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        LeptonPt = multiplet.LeptonPt;
        LeptonDeltaR = multiplet.LeptonDeltaR;
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(HiggsBranch, 1)
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
        MissingEt = multiplet.GlobalObservables().MissingEt();
        ScalarHt = multiplet.GlobalObservables().ScalarHt();
        LeptonHt = multiplet.GlobalObservables().LeptonHt();
        JetMass = multiplet.Singlet().Jet().m();
        JetPt = multiplet.Singlet().Jet().pt();
        JetHt = multiplet.GlobalObservables().JetHt();
        JetRap = multiplet.Singlet().Rapidity();
        JetPhi = multiplet.Singlet().Jet().phi();
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
