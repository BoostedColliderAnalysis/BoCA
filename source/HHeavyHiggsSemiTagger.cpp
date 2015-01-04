# include "HHeavyHiggsSemiTagger.hh"

hanalysis::HHeavyHiggsSemiTagger::HHeavyHiggsSemiTagger(hanalysis::HBottomTagger*const NewBottomTagger, hanalysis::HWSemiTagger*const NewWSemiTagger, hanalysis::HWTagger*const NewWTagger, hanalysis::HTopSemiTagger*const NewTopSemiTagger, hanalysis::HTopHadronicTagger*const NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new HReader(WSemiTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new HReader(TopSemiTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new HReader(TopHadronicTagger);

    SetTaggerName("HeavyHiggsSemi");

    Branch = new HHeavyHiggsSemiBranch();
    JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HHeavyHiggsSemiTagger::~HHeavyHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
    delete BottomReader;
    delete WReader;
    delete WSemiReader;
    delete TopHadronicReader;
    delete TopSemiReader;

}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(const hanalysis::HSextet &Sextet)
{
  Print(HInformation, "FillPairTagger", Sextet.GetBdt());
  FillBranch(Branch, Sextet);
}

void hanalysis::HHeavyHiggsSemiTagger::FillBranch(HHeavyHiggsSemiBranch *HeavyHiggsBranch, const HSextet &Sextet)
{
    Print(HInformation, "FillPairTagger", Sextet.GetBdt());

    HeavyHiggsBranch->HeavyHiggsMass = Sextet.GetSextetJet().m();
    HeavyHiggsBranch->HeavyHiggsPt = Sextet.GetSextetJet().pt();

    HeavyHiggsBranch->TopDeltaR = Sextet.GetDeltaR();
    HeavyHiggsBranch->TopDeltaRap = Sextet.GetDeltaRap();
    HeavyHiggsBranch->TopDeltaPhi = Sextet.GetDeltaPhi();

//     HeavyHiggsBranch->LargerWDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerWDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerWDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerWDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerWDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerWDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();
//
//     HeavyHiggsBranch->LargerNeutrinoDeltaR = TriplePair.GetLargerTripleDeltaR();
//     HeavyHiggsBranch->LargerNeutrinoDeltaRap = TriplePair.GetLargerTripleDeltaRap();
//     HeavyHiggsBranch->LargerNeutrinoDeltaPhi = TriplePair.GetLargerTripleDeltaPhi();
//
//     HeavyHiggsBranch->SmallerNeutrinoDeltaR = TriplePair.GetSmallerTripleDeltaR();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaRap = TriplePair.GetSmallerTripleDeltaRap();
//     HeavyHiggsBranch->SmallerNeutrinoDeltaPhi = TriplePair.GetSmallerTripleDeltaPhi();

    HeavyHiggsBranch->TopBdt = Sextet.GetBdt();
    HeavyHiggsBranch->HeavyHiggsTag = Sextet.GetTag();

}

void hanalysis::HHeavyHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->HeavyHiggsPt, "HeavyHiggsPt"));

    Observables.push_back(NewObservable(&Branch->TopDeltaR, "TopDeltaR"));
    Observables.push_back(NewObservable(&Branch->TopDeltaRap, "TopDeltaRap"));
    Observables.push_back(NewObservable(&Branch->TopDeltaPhi, "TopDeltaPhi"));

//     Observables.push_back(NewObservable(&Branch->LargerWDeltaR, "LargerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaRap, "LargerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerWDeltaPhi, "LargerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaR, "SmallerWDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaRap, "SmallerWDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerWDeltaPhi, "SmallerWDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi"));
//
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap"));
//     Observables.push_back(NewObservable(&Branch->SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi"));

    Observables.push_back(NewObservable(&Branch->TopBdt, "TopBdt"));

    Spectators.push_back(NewObservable(&Branch->HeavyHiggsTag, "HeavyHiggsTag"));
    Spectators.push_back(NewObservable(&Branch->HeavyHiggsMass, "HeavyHiggsMass"));

    Print(HNotification, "Variables defined");

}


std::vector< HHeavyHiggsSemiBranch * > hanalysis::HHeavyHiggsSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag->HeavyParticles = {WId, TopId, HeavyHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    Jets = BottomTagger->GetTruthBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<HDoublet> DoubletsSemi = WSemiTagger->GetTruthBdt(Leptons,MissingEt,WSemiReader);

    std::vector<HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);


    std::vector<HSextet > Sextets;
    for (const auto & Triplet1 : TripletsSemi)
        for (const auto & Triplet2 : TripletsHadronic) {
            if (Triplet1.GetJet() == Triplet2.GetJet()) continue;
            if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet1()) continue;
            if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet2()) continue;
            if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetJet()) continue;
            if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet1()) continue;
            if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet2()) continue;
            if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetJet()) continue;
            if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet1()) continue;
            if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet2()) continue;
            HSextet Sextet(Triplet1, Triplet2);
            Sextet.SetTag(GetTag(Sextet));
            if (Sextet.GetTag() != Tag) continue;
            if(Sextet.GetSextetJet().m()<0)continue;
            Sextets.push_back(Sextet);
        }

    Print(HInformation, "Number of Heavy Higgses", Sextets.size());

    if (Tag == HSignal && Sextets.size() > 1) {
        Print(HError, "Higgs Candidates", Sextets.size());
//         std::sort(TriplePairs.begin(), TriplePairs.end(), SortByError());
//         TriplePairs.erase(TriplePairs.begin() + 1, TriplePairs.end());
    }

    std::vector<HHeavyHiggsSemiBranch *> HeavyHiggsBranches;
    for (const auto & Sextet : Sextets) {
        HHeavyHiggsSemiBranch *HeavyHiggsSemiBranch = new HHeavyHiggsSemiBranch();
        FillBranch(HeavyHiggsSemiBranch, Sextet);
        HeavyHiggsBranches.push_back(HeavyHiggsSemiBranch);
    }


    return HeavyHiggsBranches;

}


hanalysis::HObject::HTag hanalysis::HHeavyHiggsSemiTagger::GetTag(const HSextet &Sextet)
{
    Print(HInformation, "Get Sextet Tag");


    if (Sextet.GetTriplet1().GetTag() == HBackground)return HBackground;
    if (Sextet.GetTriplet2().GetTag() == HBackground)return HBackground;
    if (Sextet.GetTriplet1().GetJet().user_index() != -Sextet.GetTriplet2().GetJet().user_index()) return HBackground;

    return HSignal;
}




std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetBdt(std::vector<HTriplet> TripletsSemi ,std::vector<HTriplet> TripletsHadronic, const HReader *const Reader)
{

  std::vector<HSextet > Sextets;
  for (const auto & Triplet1 : TripletsSemi)
    for (const auto & Triplet2 : TripletsHadronic) {
      if (Triplet1.GetJet() == Triplet2.GetJet()) continue;
      if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet2()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetJet()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet2()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetJet()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet2()) continue;
      HSextet Sextet(Triplet1, Triplet2);
      Sextet.SetTag(GetTag(Sextet));
      if(Sextet.GetSextetJet().m()<0)continue;
      FillBranch(Sextet);
      Sextet.SetBdt(Reader->GetBdt());
      Sextets.push_back(Sextet);
    }

  return Sextets;
}


std::vector<hanalysis::HSextet>  hanalysis::HHeavyHiggsSemiTagger::GetSextets(const HReader *const Reader)
{

  std::vector<HTriplet> TripletsSemi = TopSemiTagger->GetTriplets(TopSemiReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger->GetTriplets(TopHadronicReader);

  std::vector<HSextet > Sextets;
  for (const auto & Triplet1 : TripletsSemi)
    for (const auto & Triplet2 : TripletsHadronic) {
      if (Triplet1.GetJet() == Triplet2.GetJet()) continue;
      if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetJet() == Triplet2.GetDoublet().GetJet2()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetJet()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetDoublet().GetJet1() == Triplet2.GetDoublet().GetJet2()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetJet()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet1()) continue;
      if (Triplet1.GetDoublet().GetJet2() == Triplet2.GetDoublet().GetJet2()) continue;
      HSextet Sextet(Triplet1, Triplet2);
      Sextet.SetTag(GetTag(Sextet));
      if(Sextet.GetSextetJet().m()<0)continue;
      FillBranch(Sextet);
      Sextet.SetBdt(Reader->GetBdt());
      Sextets.push_back(Sextet);
    }

    return Sextets;
}
