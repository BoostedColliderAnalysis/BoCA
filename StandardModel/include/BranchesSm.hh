/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"

namespace boca
{

namespace standardmodel
{

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

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class WHadronicBranch : public PairBranch, public BottomBase
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();
    ClassDef(WHadronicBranch, 1)
};

/**
 *
 * @brief Z tagger root tree structure
 *
 */
class ZHadronicBranch : public PairBranch, public BottomBase
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
    }
    Observables Variables();
    Observables Spectators();
    ClassDef(ZHadronicBranch, 1)
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


}

}
