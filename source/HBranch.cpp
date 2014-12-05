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

ClassImp(HHadronicWBranch)

HHadronicWBranch::HHadronicWBranch()
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

ClassImp(HHadronicTopBranch)

HHadronicTopBranch::HHadronicTopBranch()
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

ClassImp(HLeptonicTopBranch)

HLeptonicTopBranch::HLeptonicTopBranch()
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


ClassImp(HHeavyHiggsBranch)

HHeavyHiggsBranch::HHeavyHiggsBranch()
{

  HeavyHiggsMass = InitialValue;
  HeavyHiggsPt = InitialValue;

  BetterTopMass = InitialValue;
  WorseTopMass = InitialValue;

  BetterWMass = InitialValue;
  WorseWMass = InitialValue;

  BetterNeutrinoMass = InitialValue;
  WorseNeutrinoMass = InitialValue;

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
