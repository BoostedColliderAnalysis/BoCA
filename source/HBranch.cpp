# include "HBranch.hh"

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{
    Crosssection = InitialValue;
    CrosssectionError = InitialValue;
    EventNumber = InitialValue;
    Mass = InitialValue;
}

ClassImp(HEventBranch)

HEventBranch::HEventBranch()
{
    ScalarPtSum = InitialValue;
}

ClassImp(HParticleBranch)

HParticleBranch::HParticleBranch()
{
    Mass = InitialValue;
    Pt = InitialValue;
    Rap = InitialValue;
    Phi = InitialValue;
}

ClassImp(HResultBranch)

HResultBranch::HResultBranch()
{
  Bdt = InitialValue;
  Tag = InitialValue;
}


ClassImp(HBottomBranch)

HBottomBranch::HBottomBranch()
{

    VertexMass = InitialValue;
    Displacement = InitialValue;
    Multipliticity = InitialValue;
    DeltaR = InitialValue;
    Spread = InitialValue;
    EnergyFraction = InitialValue;

    Tag = InitialValue;

}

ClassImp(HPairBranch)

HPairBranch::HPairBranch()
{

    DeltaPt = InitialValue;
    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    Bdt = InitialValue;
    Tag = InitialValue;

}

ClassImp(HWBranch)

HWBranch::HWBranch()
{

}

ClassImp(HJetPairBranch)

HJetPairBranch::HJetPairBranch()
{

}

ClassImp(HWSemiBranch)

HWSemiBranch::HWSemiBranch()
{
    NeutrinoPt = InitialValue;
    LeptonPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    Tag = InitialValue;

}


ClassImp(HTopHadronicBranch)

HTopHadronicBranch::HTopHadronicBranch()
{

    BottomPt = InitialValue;
    WPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    Bdt = InitialValue;
    Tag = InitialValue;

}

ClassImp(HTopSemiBranch)

HTopSemiBranch::HTopSemiBranch()
{

    BottomPt = InitialValue;
    WPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    Bdt = InitialValue;
    Tag = InitialValue;

}

ClassImp(HTopLeptonicBranch)

HTopLeptonicBranch::HTopLeptonicBranch()
{

    BottomPt = InitialValue;
    LeptonPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    Bdt = InitialValue;
    Tag = InitialValue;

}


ClassImp(HHiggsBranch)

HHiggsBranch::HHiggsBranch()
{

    Mass = InitialValue;
    PtSum = InitialValue;
    PtDiff = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BottomBdt = InitialValue;

    Pull1 = InitialValue;
    Pull2 = InitialValue;
    Pull = InitialValue;

    HiggsTag = InitialValue;

}


ClassImp(HHeavyHiggsLeptonicBranch)

HHeavyHiggsLeptonicBranch::HHeavyHiggsLeptonicBranch()
{

    LargerWDeltaRap = InitialValue;
    LargerWDeltaPhi = InitialValue;
    LargerWDeltaR = InitialValue;

    SmallerWDeltaRap = InitialValue;
    SmallerWDeltaPhi = InitialValue;
    SmallerWDeltaR = InitialValue;

    LargerNeutrinoDeltaRap = InitialValue;
    LargerNeutrinoDeltaPhi = InitialValue;
    LargerNeutrinoDeltaR = InitialValue;

    SmallerNeutrinoDeltaRap = InitialValue;
    SmallerNeutrinoDeltaPhi = InitialValue;
    SmallerNeutrinoDeltaR = InitialValue;

}



ClassImp(HHeavyHiggsHadronicBranch)

HHeavyHiggsHadronicBranch::HHeavyHiggsHadronicBranch()
{

    HeavyHiggsMass = InitialValue;
    HeavyHiggsPt = InitialValue;

    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    TopBdt = InitialValue;
    HeavyHiggsTag = InitialValue;

}


ClassImp(HHeavyHiggsSemiBranch)

HHeavyHiggsSemiBranch::HHeavyHiggsSemiBranch()
{

}


ClassImp(HChargedHiggsSemiBranch)

HChargedHiggsSemiBranch::HChargedHiggsSemiBranch()
{

    HeavyHiggsMass = InitialValue;
    HeavyHiggsPt = InitialValue;

    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    //     LargerWDeltaRap = InitialValue;
    //     LargerWDeltaPhi = InitialValue;
    //     LargerWDeltaR = InitialValue;
    //
    //     SmallerWDeltaRap = InitialValue;
    //     SmallerWDeltaPhi = InitialValue;
    //     SmallerWDeltaR = InitialValue;

    //     LargerNeutrinoDeltaRap = InitialValue;
    //     LargerNeutrinoDeltaPhi = InitialValue;
    //     LargerNeutrinoDeltaR = InitialValue;
    //
    //     SmallerNeutrinoDeltaRap = InitialValue;
    //     SmallerNeutrinoDeltaPhi = InitialValue;
    //     SmallerNeutrinoDeltaR = InitialValue;

    TopBdt = InitialValue;
    HeavyHiggsTag = InitialValue;

}



ClassImp(HChargedHiggsHadronicBranch)

HChargedHiggsHadronicBranch::HChargedHiggsHadronicBranch()
{

    HeavyHiggsMass = InitialValue;
    HeavyHiggsPt = InitialValue;

    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    //     LargerWDeltaRap = InitialValue;
    //     LargerWDeltaPhi = InitialValue;
    //     LargerWDeltaR = InitialValue;
    //
    //     SmallerWDeltaRap = InitialValue;
    //     SmallerWDeltaPhi = InitialValue;
    //     SmallerWDeltaR = InitialValue;

    //     LargerNeutrinoDeltaRap = InitialValue;
    //     LargerNeutrinoDeltaPhi = InitialValue;
    //     LargerNeutrinoDeltaR = InitialValue;
    //
    //     SmallerNeutrinoDeltaRap = InitialValue;
    //     SmallerNeutrinoDeltaPhi = InitialValue;
    //     SmallerNeutrinoDeltaR = InitialValue;

    TopBdt = InitialValue;
    HeavyHiggsTag = InitialValue;

}


ClassImp(HChargedHiggsLeptonicBranch)

HChargedHiggsLeptonicBranch::HChargedHiggsLeptonicBranch()
{

    HeavyHiggsMass = InitialValue;
    HeavyHiggsPt = InitialValue;

    TopDeltaRap = InitialValue;
    TopDeltaPhi = InitialValue;
    TopDeltaR = InitialValue;

    LargerWDeltaRap = InitialValue;
    LargerWDeltaPhi = InitialValue;
    LargerWDeltaR = InitialValue;

    SmallerWDeltaRap = InitialValue;
    SmallerWDeltaPhi = InitialValue;
    SmallerWDeltaR = InitialValue;

    LargerNeutrinoDeltaRap = InitialValue;
    LargerNeutrinoDeltaPhi = InitialValue;
    LargerNeutrinoDeltaR = InitialValue;

    SmallerNeutrinoDeltaRap = InitialValue;
    SmallerNeutrinoDeltaPhi = InitialValue;
    SmallerNeutrinoDeltaR = InitialValue;

    TopBdt = InitialValue;
    HeavyHiggsTag = InitialValue;

}
