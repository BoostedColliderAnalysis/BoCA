# include "Branches.hh"

ClassImp(analysis::Branch)

analysis::Branch::Branch() {}

analysis::Branch::~Branch() {}

ClassImp(analysis::InfoBranch)

analysis::InfoBranch::InfoBranch()
{
    Crosssection = InitialValue();
    CrosssectionError = InitialValue();
    EventNumber = int(InitialValue());
    PreCutNumber = int(InitialValue());
    Mass = InitialValue();
}

ClassImp(analysis::EventBranch)

analysis::EventBranch::EventBranch()
{
    ScalarPtSum = InitialValue();
}

ClassImp(analysis::ParticleBranch)

analysis::ParticleBranch::ParticleBranch()
{
    Mass = InitialValue();
    Pt = InitialValue();
    Rap = InitialValue();
    Phi = InitialValue();
}

ClassImp(analysis::HResultBranch)

analysis::HResultBranch::HResultBranch()
{
    Bdt = InitialValue();
    Tag = int(InitialValue());
}


ClassImp(analysis::BottomBranch)

analysis::BottomBranch::BottomBranch()
{
    VertexMass = InitialValue();
    MaxDisplacement = InitialValue();
    MeanDisplacement = InitialValue();
    SumDisplacement = InitialValue();
    Multipliticity = int(InitialValue());
    DeltaR = InitialValue();
    Spread = InitialValue();
    VertexDeltaR = InitialValue();
    VertexSpread = InitialValue();
    EnergyFraction = InitialValue();
    Tag = int(InitialValue());
    Bdt = InitialValue();
}

ClassImp(analysis::TauBranch)

analysis::TauBranch::TauBranch()
{
    EmRadius = InitialValue();
    TrackRadius = InitialValue();
    MomentumFraction = InitialValue();
    CoreEnergyFraction = InitialValue();
    EmFraction = InitialValue();
    ClusterMass = InitialValue();
    TrackMass = InitialValue();
    FlightPath = InitialValue();
    TrtHtFraction = InitialValue();
    Tag = int(InitialValue());
    Bdt = InitialValue();
}

ClassImp(analysis::PairBranch)

analysis::PairBranch::PairBranch()
{
    Ht = InitialValue();
    DeltaPt = InitialValue();
    DeltaM = InitialValue();
    DeltaRap = InitialValue();
    DeltaPhi = InitialValue();
    DeltaR = InitialValue();
    Bdt = InitialValue();
    Tag = int(InitialValue());
}

ClassImp(analysis::MultiBranch)

analysis::MultiBranch::MultiBranch()
{
    DeltaHt = InitialValue();
}

ClassImp(analysis::WHadronicBranch)

analysis::WHadronicBranch::WHadronicBranch() {}

ClassImp(analysis::ZHadronicBranch)

analysis::ZHadronicBranch::ZHadronicBranch() {}

ClassImp(analysis::JetPairBranch)

analysis::JetPairBranch::JetPairBranch()
{
    DeltaM = InitialValue();
    Jet1Mass = InitialValue();
    Jet1Pt = InitialValue();
    Jet1Rap = InitialValue();
    Jet1Phi = InitialValue();
    Jet1Bdt = InitialValue();
    Jet1BTag = InitialValue();
    Jet2Mass = InitialValue();
    Jet2Pt = InitialValue();
    Jet2Rap = InitialValue();
    Jet2Phi = InitialValue();
    Jet2Bdt = InitialValue();
    Jet2BTag = InitialValue();
    BdtRatio11 = InitialValue();
    BdtRatio12 = InitialValue();
    BdtRatio13 = InitialValue();
    BdtRatio14 = InitialValue();
    BdtRatio21 = InitialValue();
    BdtRatio22 = InitialValue();
    BdtRatio23 = InitialValue();
    BdtRatio24 = InitialValue();
}

ClassImp(analysis::TripletJetPairBranch)

analysis::TripletJetPairBranch::TripletJetPairBranch()
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

ClassImp(analysis::WSemiBranch)

analysis::WSemiBranch::WSemiBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

ClassImp(analysis::HHeavyHiggsTauBranch)

analysis::HHeavyHiggsTauBranch::HHeavyHiggsTauBranch()
{
    NeutrinoPt = InitialValue();
    LeptonPt = InitialValue();
}

ClassImp(analysis::TopHadronicBranch)

analysis::TopHadronicBranch::TopHadronicBranch()
{
    BottomPt = InitialValue();
    WPt = InitialValue();
    WBdt = InitialValue();
    BBdt = InitialValue();
    Tau1_1 = InitialValue();
    Tau2_1 = InitialValue();
    Tau3_1 = InitialValue();
    Tau21_1 = InitialValue();
    Tau32_1 = InitialValue();
    Tau1_2 = InitialValue();
    Tau2_2 = InitialValue();
    Tau3_2 = InitialValue();
    Tau21_2 = InitialValue();
    Tau32_2 = InitialValue();
//     VertexMass = InitialValue();
//     MaxDisplacement = InitialValue();
//     MeanDisplacement = InitialValue();
//     SumDisplacement = InitialValue();
//     Multipliticity = int(InitialValue());
//     Spread = InitialValue();
//     VertexDeltaR = InitialValue();
//     VertexSpread = InitialValue();
//     EnergyFraction = InitialValue();
}

ClassImp(analysis::TopSemiBranch)

analysis::TopSemiBranch::TopSemiBranch()
{
    BottomPt = InitialValue();
    WPt = InitialValue();
    WBdt = InitialValue();
    BBdt = InitialValue();
//     VertexMass = InitialValue();
//     MaxDisplacement = InitialValue();
//     MeanDisplacement = InitialValue();
//     SumDisplacement = InitialValue();
//     Multipliticity = int(InitialValue());
//     Spread = InitialValue();
//     VertexDeltaR = InitialValue();
//     VertexSpread = InitialValue();
//     EnergyFraction = InitialValue();
}

ClassImp(analysis::TopLeptonicBranch)

analysis::TopLeptonicBranch::TopLeptonicBranch()
{
    BottomPt = InitialValue();
    LeptonPt = InitialValue();
}

ClassImp(analysis::HiggsBranch)

analysis::HiggsBranch::HiggsBranch()
{
//     Mass = InitialValue();
//     PtSum = InitialValue();
//     PtDiff = InitialValue();
//     DeltaRap = InitialValue();
//     DeltaPhi = InitialValue();
//     DeltaR = InitialValue();
//     BottomBdt = InitialValue();
//     Pull1 = InitialValue();
//     Pull2 = InitialValue();
//     Pull = InitialValue();
//     HiggsTag = int(InitialValue());
}

ClassImp(analysis::HeavyHiggsLeptonicBranch)

analysis::HeavyHiggsLeptonicBranch::HeavyHiggsLeptonicBranch()
{
    LargerWDeltaRap = InitialValue();
    LargerWDeltaPhi = InitialValue();
    LargerWDeltaR = InitialValue();
    SmallerWDeltaRap = InitialValue();
    SmallerWDeltaPhi = InitialValue();
    SmallerWDeltaR = InitialValue();
    LargerNeutrinoDeltaRap = InitialValue();
    LargerNeutrinoDeltaPhi = InitialValue();
    LargerNeutrinoDeltaR = InitialValue();
    SmallerNeutrinoDeltaRap = InitialValue();
    SmallerNeutrinoDeltaPhi = InitialValue();
    SmallerNeutrinoDeltaR = InitialValue();
}

ClassImp(analysis::HHeavyHiggsHadronicBranch)

analysis::HHeavyHiggsHadronicBranch::HHeavyHiggsHadronicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}

ClassImp(analysis::HeavyHiggsSemiBranch)

analysis::HeavyHiggsSemiBranch::HeavyHiggsSemiBranch() {}

ClassImp(analysis::ChargedHiggsSemiBranch)

analysis::ChargedHiggsSemiBranch::ChargedHiggsSemiBranch()
{
    Flag = int(InitialValue());
}

ClassImp(analysis::HChargedHiggsHadronicBranch)

analysis::HChargedHiggsHadronicBranch::HChargedHiggsHadronicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}


ClassImp(analysis::ChargedHiggsLeptonicBranch)

analysis::ChargedHiggsLeptonicBranch::ChargedHiggsLeptonicBranch()
{
    HeavyHiggsMass = InitialValue();
    HeavyHiggsPt = InitialValue();
    TopDeltaRap = InitialValue();
    TopDeltaPhi = InitialValue();
    TopDeltaR = InitialValue();
    LargerWDeltaRap = InitialValue();
    LargerWDeltaPhi = InitialValue();
    LargerWDeltaR = InitialValue();
    SmallerWDeltaRap = InitialValue();
    SmallerWDeltaPhi = InitialValue();
    SmallerWDeltaR = InitialValue();
    LargerNeutrinoDeltaRap = InitialValue();
    LargerNeutrinoDeltaPhi = InitialValue();
    LargerNeutrinoDeltaR = InitialValue();
    SmallerNeutrinoDeltaRap = InitialValue();
    SmallerNeutrinoDeltaPhi = InitialValue();
    SmallerNeutrinoDeltaR = InitialValue();
    TopBdt = InitialValue();
    HeavyHiggsTag = int(InitialValue());
}

ClassImp(analysis::EventBottomTaggerBranch)

analysis::EventBottomTaggerBranch::EventBottomTaggerBranch()
{
    Bdt = InitialValue();
    Tag = InitialValue();
    BottomBdt1 = InitialValue();
    BottomBdt2 = InitialValue();
    BottomBdt3 = InitialValue();
    BottomBdt4 = InitialValue();
    BottomBdt5 = InitialValue();
    BottomBdt6 = InitialValue();
    BottomBdt12 = InitialValue();
    BottomBdt34 = InitialValue();
    BottomBdt56 = InitialValue();
    BottomBdt123 = InitialValue();
    BottomBdt1234 = InitialValue();
}

ClassImp(analysis::HTopLeptonBranch)

analysis::HTopLeptonBranch::HTopLeptonBranch()
{
    VertexMass = InitialValue();
    MaxDisplacement = InitialValue();
    MeanDisplacement = InitialValue();
    SumDisplacement = InitialValue();
    Multipliticity = int(InitialValue());
    DeltaR = InitialValue();
    Spread = InitialValue();
    VertexDeltaR = InitialValue();
    VertexSpread = InitialValue();
    EnergyFraction = InitialValue();
    JetMass = InitialValue();
    LeptonPt = InitialValue();
    WBdt = InitialValue();
    BBdt = InitialValue();
}
