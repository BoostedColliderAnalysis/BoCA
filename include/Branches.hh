# pragma once

# include "TObject.h"
# include "Rtypes.h"

namespace analysis
{

typedef std::pair<float &, std::string> ObservablePair;
typedef std::vector<ObservablePair> Observables;
# define STRING(s) #s
# define PAIR(x) ObservablePair(x,STRING(x))

/**
 * @brief Basic tree branches
 *
 */
class Branch : public TObject
{
public:
    Branch();
    virtual ~Branch();
protected:
    static float InitialValue();
    static Observables Join(const Observables &observables_1, const Observables &observables_2);
private:
    ClassDef(Branch, 1)
};

/**
 * @brief Basic tree branches
 *
 */
class InfoBranch : public Branch
{
public:
    InfoBranch();
    float Crosssection;
    float CrosssectionError;
    float Mass;
    float EventNumber;
    float PreCutNumber;
    std::string Name;
private:
    ClassDef(InfoBranch, 1)
};

class ResultBranch : public Branch
{
public:
    ResultBranch();
    float Bdt;
    float Tag;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        Tag = multiplet.Tag();
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
    void Fill(const Multiplet &multiplet) {
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
 * @brief Bottom tagger root tree structure
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
    float Multipliticity;
    float Radius;
    float Spread;
    float VertexRadius;
    float VertexSpread;
    float EnergyFraction;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        Fill2(multiplet.singlet());
    }
    template<typename Singlet>
    void Fill2(const Singlet &singlet) {
        VertexMass = singlet.VertexMass();
        MaxDisplacement = singlet.MaxDisplacement();
        MeanDisplacement = singlet.MeanDisplacement();
        SumDisplacement = singlet.SumDisplacement();
        Multipliticity = singlet.Multiplicity();
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
    void Fill(const Multiplet &multiplet) {
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
    void Fill(const Multiplet &multiplet) {
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
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
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
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        DeltaHt = multiplet.DeltaHt();
    }
    Observables Variables();
private:
    ClassDef(MultiBranch, 1)
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
    float DeltaM;
    float Jet1Mass;
    float Jet1Pt;
    float Jet1Rap;
    float Jet1Phi;
    float Jet1Bdt;
    float Jet1BTag;
    float Jet2Mass;
    float Jet2Pt;
    float Jet2Rap;
    float Jet2Phi;
    float Jet2Bdt;
    float Jet2BTag;
    float BdtRatio11;
    float BdtRatio12;
    float BdtRatio13;
    float BdtRatio14;
    float BdtRatio21;
    float BdtRatio22;
    float BdtRatio23;
    float BdtRatio24;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        DeltaM = multiplet.DeltaM();
        Jet1Pt = multiplet.SingletJet1().pt();
//         Jet1Rap = std::abs(multiplet.SingletJet1().rap());
        Jet1Rap = multiplet.SingletJet1().rap();
        Jet1Phi = multiplet.SingletJet1().phi();
        Jet1Mass = multiplet.SingletJet1().m();
//         Jet1Bdt = multiplet.SingletJet1().user_info<JetInfo>().Bdt();
        Jet2Pt = multiplet.SingletJet2().pt();
//         Jet2Rap = std::abs(multiplet.SingletJet2().rap());
        Jet2Rap = multiplet.SingletJet2().rap();
        Jet2Phi = multiplet.SingletJet2().phi();
        Jet2Mass = multiplet.SingletJet2().m();
    }
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
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.SingletJet().pt();
//         BottomRap = std::abs(multiplet.Singlet().rap());
        BottomRap = multiplet.SingletJet().rap();
        BottomPhi = multiplet.SingletJet().phi();
        BottomMass = multiplet.SingletJet().m();
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
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        LeptonPt = multiplet.SingletJet1().pt();
        NeutrinoPt = multiplet.SingletJet2().pt();
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
//     float Tau1_1;
//     float Tau2_1;
//     float Tau3_1;
//     float Tau21_1;
//     float Tau32_1;
//     float Tau1_2;
//     float Tau2_2;
//     float Tau3_2;
//     float Tau21_2;
//     float Tau32_2;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        MultiBranch::Fill(multiplet);
        BottomBase::Fill(multiplet);
        BottomMass = multiplet.SingletJet().m();
        WMass = multiplet.Doublet().Jet().m();
        LeptonPt = multiplet.pt();
//         Tau1_1 = multiplet.sub_jettiness().tau1_beta1;
//         Tau2_1 = multiplet.sub_jettiness().tau2_beta1;
//         Tau3_1 = multiplet.sub_jettiness().tau3_beta1;
//         Tau21_1 = multiplet.sub_jettiness().tau21_beta1;
//         Tau32_1 = multiplet.sub_jettiness().tau32_beta1;
//         Tau1_2 = multiplet.sub_jettiness().tau1_beta2;
//         Tau2_2 = multiplet.sub_jettiness().tau2_beta2;
//         Tau3_2 = multiplet.sub_jettiness().tau3_beta2;
//         Tau21_2 = multiplet.sub_jettiness().tau21_beta2;
//         Tau32_2 = multiplet.sub_jettiness().tau32_beta2;
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
class TopLeptonicBranch : public PairBranch
{
public:
    TopLeptonicBranch();
    float BottomPt;
    float LeptonPt;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        PairBranch::Fill(multiplet);
        BottomPt = multiplet.SingletJet1().pt();
        LeptonPt = multiplet.SingletJet2().pt();
    }
    Observables Variables();
private:
    ClassDef(TopLeptonicBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopSemiBranch : public MultiBranch
{
public:
    TopSemiBranch();
    float BottomPt;
    float WPt;
    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        MultiBranch::Fill(multiplet);
        BottomPt = multiplet.SingletJet().pt();
        WPt = multiplet.Doublet().Jet().pt();
    }
    Observables Variables();
private:
    ClassDef(TopSemiBranch, 1)
};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HiggsBranch : public PairBranch
{
private:
    ClassDef(HiggsBranch, 1)
};


class EventBottomTaggerBranch : public ResultBranch
{

public:

    EventBottomTaggerBranch();

    float BottomBdt1;
    float BottomBdt2;
    float BottomBdt3;
    float BottomBdt4;
    float BottomBdt5;
    float BottomBdt6;
    float BottomBdt7;

    float BottomBdt12;
    float BottomBdt34;
    float BottomBdt56;

    float BottomBdt123;
    float BottomBdt1234;


private:

    ClassDef(EventBottomTaggerBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonBranch : public PairBranch
{

public:

    HTopLeptonBranch();

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float DeltaR;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;
    float JetMass;
    float LeptonPt;

    float WBdt;
    float BBdt;

private:

    ClassDef(HTopLeptonBranch, 1)

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
    void Fill(const Multiplet &multiplet) {
        analysis::MultiBranch::Fill(multiplet);
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

}
