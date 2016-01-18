/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <boost/units/systems/si/io.hpp>
#include "Branches.hh"
#include "physics/Particles.hh"

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
        EmRadius = multiplet.EmRadius() / rad;
        TrackRadius = multiplet.TrackRadius() / rad;
        MomentumFraction = multiplet.Info().LeadingTrackMomentumFraction();
        CoreEnergyFraction = multiplet.CoreEnergyFraction();
        EmFraction = multiplet.Info().ElectroMagneticFraction();
        ClusterMass = multiplet.Info().ClusterMass() / GeV;
        TrackMass = multiplet.Info().TrackMass() / GeV;
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
class WLeptonicBranch : public PairBranch
{
public:
    WLeptonicBranch();
    float LeptonPt;
    float NeutrinoPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.Singlet1().Jet().Pt() / GeV;
        NeutrinoPt = multiplet.Singlet2().Jet().Pt() / GeV;
    }
    Observables Variables();

private:
    ClassDef(WLeptonicBranch, 1)
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
        BottomMass = multiplet.Singlet().Jet().Mass() / GeV;
        WMass = multiplet.Doublet().Jet().Mass() / GeV;
        LeptonPt = multiplet.LeptonPt() / GeV;
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
        BottomPt = multiplet.Singlet().Jet().Pt() / GeV;
        LeptonPt = multiplet.Doublet().Jet().Pt() / GeV; // FIXME what is with the case of W
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
        LeptonPt = multiplet.LeptonPt() / GeV;
        LeptonDeltaR = multiplet.LeptonDeltaR() / rad;
    }
    Observables Variables();
    Observables Spectators();

private:
    ClassDef(HiggsBranch, 1)
};


/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopHadronicHepBranch : public MultiBranch, public BottomBase
{
public:
    TopHadronicHepBranch();
    float BottomMass;
    float WMass;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
        BottomMass = multiplet.Singlet().Jet().Mass() / GeV;
        WMass = multiplet.Doublet().Jet().Mass() / GeV;
        LeptonPt = multiplet.Pt() / GeV;
    }
    Observables Variables();
    Observables Spectators();
private:
    ClassDef(TopHadronicHepBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TruthBranch : public ResultBranch
{
public:
    TruthBranch();
    float TopPt;
    float BottomPt;
    float WPt;
    float Quark1Pt;
    float Quark2Pt;
    float DeltaRTop;
    float DeltaRW;
    float RhoTop;
    float RhoW;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TopPt = multiplet.TopPt() / GeV;
        BottomPt = multiplet.BottomPt() / GeV;
        WPt = multiplet.WPt() / GeV;
        Quark1Pt = multiplet.Quark1Pt() / GeV;
        Quark2Pt = multiplet.Quark2Pt() / GeV;
        DeltaRTop = multiplet.DeltaRTop() / rad;
        DeltaRW = multiplet.DeltaRW() / rad;
        RhoTop = multiplet.RhoTop();
        RhoW = multiplet.RhoW();
    }
    Observables Variables() {
        return {};
    }
    Observables Spectators() {
        return {};
    }
private:
    ClassDef(TruthBranch, 1)
};


}

}
