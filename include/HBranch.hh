# pragma once

# include "TObject.h"
# include "TGenericClassInfo.h"
# include "Rtypes.h"

/**
 * @brief Basic tree branches
 *
 */
class HBranch : public TObject
{

public:
    HBranch();
    virtual ~HBranch();

protected:

  float InitialValue(){
    return -11.1111111; // should be non integer
    // this must be identical to the initial value in htag
    // FIXME remove the copy of the magic number
  }

private:
    ClassDef(HBranch, 1)

};

/**
 * @brief Basic tree branches
 *
 */
class InfoBranch : public HBranch
{

public:

    float Crosssection;
    float CrosssectionError;
    float Mass;
    float eventNumber;
    float PreCutNumber;

    InfoBranch();

private:

    ClassDef(InfoBranch, 1)

};

/**
 * @brief Class for saving event informations to root
 *
 */
class EventBranch : public HBranch
{

public:

    float ScalarPtSum;
    EventBranch();

private:
    ClassDef(EventBranch, 1)

};


class HResultBranch : public HBranch
{
public:

    HResultBranch();

    float Bdt;
    float Tag;

private:

    ClassDef(HResultBranch, 1)

};

/**
 * @brief Class for saving event informations to root
 *
 */
class ParticleBranch : public HBranch
{
public:

    ParticleBranch();

    float Mass;
    float Pt;
    float Rap;
    float Phi;

protected:

  template<typename Multiplet>
  void FillBranch(const Multiplet &multiplet){
    Mass = multiplet.Mass();
    Pt = multiplet.Pt();
    Rap = multiplet.Rap();
    Phi = multiplet.Phi();
  }

private:

    ClassDef(ParticleBranch, 1)

};


/**
 *
 * @brief Bottom tagger root tree structure
 *
 */
class BottomBranch : public ParticleBranch
{

public:

    BottomBranch();

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
    float BTag;

    float Tag;
    float Bdt;

protected:

  template<typename Multiplet>
  void FillBranch(const Multiplet &multiplet){
    ParticleBranch::FillBranch(multiplet);
    VertexMass = multiplet.VertexMass();
    MaxDisplacement = multiplet.MaxDisplacement();
    MeanDisplacement = multiplet.MeanDisplacement();
    Phi = multiplet.Phi();

    VertexMass = multiplet.user_info<JetInfo>().VertexMass();
    float MaxDisp = multiplet.user_info<JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) MaxDisplacement = std::log10(MaxDisp);
    else MaxDisplacement = -3;
    float MeanDisp = multiplet.user_info<JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) MeanDisplacement = std::log10(MeanDisp);
    else MeanDisplacement = -3;
    float SumDisp = multiplet.user_info<JetInfo>().SumDisplacement();
    if (SumDisp > 0) SumDisplacement = std::log10(SumDisp);
    else SumDisplacement = -3;
    Multipliticity = multiplet.user_info<JetInfo>().VertexNumber();
//     DeltaR = GetDeltaR(jet);
//     Spread = GetSpread(jet);
//     VertexDeltaR = GetDeltaR(multiplet.user_info<JetInfo>().VertexJet());
//     VertexSpread = GetSpread(multiplet.user_info<JetInfo>().VertexJet());
    EnergyFraction = multiplet.user_info<JetInfo>().VertexEnergy() / multiplet.e();
    Tag = multiplet.user_info<JetInfo>().Tag();
    Bdt = multiplet.user_info<JetInfo>().Bdt();


  }

private:

    ClassDef(BottomBranch, 1)

};


/**
 *
 * @brief Tau tagger root tree structure
 *
 */
class HTauBranch : public ParticleBranch
{

public:

    HTauBranch();

    float EmRadius;
    float TrackRadius;
    float MomentumFraction;
    float CoreEnergyFraction;
    float EmFraction;
    float ClusterMass;
    float TrackMass;
    float FlightPath;
    float TrtHtFraction;

    float Tag;
    float Bdt;

private:

    ClassDef(HTauBranch, 1)

};


class PairBranch : public ParticleBranch
{

public:

    PairBranch();

    float Ht;
    float DeltaPt;
    float DeltaHt;
    float DeltaM;
    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float Bdt;
    float Tag;

private:

    ClassDef(PairBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class WHadronicBranch : public PairBranch
{

public:

    WHadronicBranch();

private:

    ClassDef(WHadronicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class EventJetPairBranch : public PairBranch
{

public:

    EventJetPairBranch();

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

private:

    ClassDef(EventJetPairBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedJetPairBranch : public PairBranch
{

public:

    HChargedJetPairBranch();

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

private:

    ClassDef(HChargedJetPairBranch, 1)

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

private:

    ClassDef(HWSemiBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HHeavyHiggsTauBranch : public PairBranch
{

public:

    HHeavyHiggsTauBranch();

    float LeptonPt;
    float NeutrinoPt;

private:

    ClassDef(HHeavyHiggsTauBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopHadronicBranch : public PairBranch
{

public:

    TopHadronicBranch();

    float BottomPt;
    float WPt;

    float WBdt;
    float BBdt;

    float Tau1_1;
    float Tau2_1;
    float Tau3_1;
    float Tau21_1;
    float Tau32_1;

    float Tau1_2;
    float Tau2_2;
    float Tau3_2;
    float Tau21_2;
    float Tau32_2;

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;

private:

    ClassDef(TopHadronicBranch, 1)

};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class HTopLeptonicBranch : public PairBranch
{

public:

    HTopLeptonicBranch();

    float BottomPt;
    float LeptonPt;

private:
    ClassDef(HTopLeptonicBranch, 1)
};

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class TopSemiBranch : public PairBranch
{

public:

    TopSemiBranch();
    float BottomPt;
    float WPt;

    float WBdt;
    float BBdt;

    float VertexMass;
    float MaxDisplacement;
    float MeanDisplacement;
    float SumDisplacement;
    float Multipliticity;
    float Spread;
    float VertexDeltaR;
    float VertexSpread;
    float EnergyFraction;

private:

    ClassDef(TopSemiBranch, 1)

};


/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHiggsBranch : public HBranch
{

public:

    HHiggsBranch();

    float Mass;
    float PtSum;
    float PtDiff;

    float DeltaRap;
    float DeltaPhi;
    float DeltaR;

    float BottomBdt;

    float Pull1;
    float Pull2;
    float Pull;

    float HiggsTag;

private:

    ClassDef(HHiggsBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsLeptonicBranch : public PairBranch
{

public:

    HHeavyHiggsLeptonicBranch();

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;


private:

    ClassDef(HHeavyHiggsLeptonicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsHadronicBranch : public HBranch
{

public:

    HHeavyHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HHeavyHiggsHadronicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HHeavyHiggsSemiBranch : public PairBranch
{

public:

    HHeavyHiggsSemiBranch();

private:

    ClassDef(HHeavyHiggsSemiBranch, 1)

};

/**
 *
 * @brief Charged Higgs semi tagger root tree structure
 *
 */
class HChargedHiggsSemiBranch : public PairBranch
{

public:

    HChargedHiggsSemiBranch();
    float Flag;

private:

    ClassDef(HChargedHiggsSemiBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedHiggsHadronicBranch : public HBranch
{

public:

    HChargedHiggsHadronicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsHadronicBranch, 1)

};

/**
 *
 * @brief Higgs tagger root tree structure
 *
 */
class HChargedHiggsLeptonicBranch : public HBranch
{

public:

    HChargedHiggsLeptonicBranch();

    float HeavyHiggsMass;
    float HeavyHiggsPt;

    float TopDeltaRap;
    float TopDeltaPhi;
    float TopDeltaR;

    float LargerWDeltaRap;
    float LargerWDeltaPhi;
    float LargerWDeltaR;

    float SmallerWDeltaRap;
    float SmallerWDeltaPhi;
    float SmallerWDeltaR;

    float LargerNeutrinoDeltaRap;
    float LargerNeutrinoDeltaPhi;
    float LargerNeutrinoDeltaR;

    float SmallerNeutrinoDeltaRap;
    float SmallerNeutrinoDeltaPhi;
    float SmallerNeutrinoDeltaR;

    float TopBdt;

    float HeavyHiggsTag;

private:

    ClassDef(HChargedHiggsLeptonicBranch, 1)

};

class EventBottomTaggerBranch : public HBranch
{

public:

    EventBottomTaggerBranch();

    float Bdt;
    float Tag;

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

