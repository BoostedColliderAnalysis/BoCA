# include "HBranch.hh"

ClassImp(HInfoBranch)

HInfoBranch::HInfoBranch()
{
    Crosssection = InitialValue;
    CrosssectionError = InitialValue;
    EventNumber = InitialValue;
}

ClassImp(HEventBranch)

HEventBranch::HEventBranch()
{
    ScalarPtSum = InitialValue;
}

ClassImp(HParticleBranch)

HParticleBranch::HParticleBranch()
{
    Pt = InitialValue;
    Rap = InitialValue;
    Phi = InitialValue;
}


ClassImp(HBottomBranch)

HBottomBranch::HBottomBranch()
{

    Mass = InitialValue;
    VertexMass = InitialValue;
    Pt = InitialValue;
    Displacement = InitialValue;
    Multipliticity = InitialValue;
    DeltaR = InitialValue;
    Spread = InitialValue;
    EnergyFraction = InitialValue;

    BottomTag = InitialValue;

}

ClassImp(HWBranch)

HWBranch::HWBranch()
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

    WTag = InitialValue;

}

ClassImp(HWSemiBranch)

HWSemiBranch::HWSemiBranch()
{

  Mass = InitialValue;

  Pt = InitialValue;

  NeutrinoPt = InitialValue;
  LeptonPt = InitialValue;
  MissingEt = InitialValue;

  DeltaRap = InitialValue;
  DeltaPhi = InitialValue;
  DeltaR = InitialValue;

  WTag = InitialValue;

}


ClassImp(HTopHadronicBranch)

HTopHadronicBranch::HTopHadronicBranch()
{

    Mass = InitialValue;
    JetPt = InitialValue;
    WPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    WBottomBdt = InitialValue;

    TopTag = InitialValue;

}

ClassImp(HTopSemiBranch)

HTopSemiBranch::HTopSemiBranch()
{

    Mass = InitialValue;
    PairMass = InitialValue;

    TriplePt = InitialValue;
    PairPt = InitialValue;

    JetPt = InitialValue;
    LeptonPt = InitialValue;
    MissingEt = InitialValue;

    PairDeltaRap = InitialValue;
    PairDeltaPhi = InitialValue;
    PairDeltaR = InitialValue;

    TripleDeltaRap = InitialValue;
    TripleDeltaPhi = InitialValue;
    TripleDeltaR = InitialValue;

    BottomBdt = InitialValue;

    TopTag = InitialValue;

}

ClassImp(HTopLeptonicBranch)

HTopLeptonicBranch::HTopLeptonicBranch()
{

    Mass = InitialValue;
    JetPt = InitialValue;
    LeptonPt = InitialValue;

    DeltaRap = InitialValue;
    DeltaPhi = InitialValue;
    DeltaR = InitialValue;

    BottomBdt = InitialValue;

    TopTag = InitialValue;

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



ClassImp(HHeavyHiggsHadronicBranch)

HHeavyHiggsHadronicBranch::HHeavyHiggsHadronicBranch()
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


ClassImp(HHeavyHiggsSemiBranch)

HHeavyHiggsSemiBranch::HHeavyHiggsSemiBranch()
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
