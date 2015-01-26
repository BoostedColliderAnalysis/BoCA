# include "HChargedHiggsSemiTagger.hh"

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.SetMva(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader.SetMva(WSemiTagger);
    WTagger = NewWTagger;
    WReader.SetMva(WTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader.SetMva(TopSemiTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader.SetMva(TopHadronicTagger);

    SetTaggerName("ChargedHiggsSemi");

//     Branch = new HChargedHiggsSemiBranch();
    //JetTag = new HJetTag();

    DefineVariables();
}

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;
  Print(HNotification, "Constructor");
  SetTaggerName("ChargedHiggsSemi");
}

hanalysis::HChargedHiggsSemiTagger::~HChargedHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
    // delete Branch;
    //delete JetTag;
//     delete BottomReader;
//     delete WReader;
//     delete WSemiReader;
//     delete TopHadronicReader;
//     delete TopSemiReader;

}

void hanalysis::HChargedHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

void hanalysis::HChargedHiggsSemiTagger::FillBranch(HChargedHiggsSemiBranch *ChargedHiggsBranch, const HQuartet31 &Quartet)
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());

    ChargedHiggsBranch->Mass = Quartet.Jet().m();
    ChargedHiggsBranch->Rap = Quartet.Jet().rap();
    ChargedHiggsBranch->Phi = Quartet.Jet().phi();
    ChargedHiggsBranch->Pt = Quartet.Jet().pt();
    ChargedHiggsBranch->Ht = Quartet.Ht();

    ChargedHiggsBranch->DeltaR = Quartet.DeltaR();
    ChargedHiggsBranch->DeltaRap = Quartet.DeltaRap();
    ChargedHiggsBranch->DeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsBranch->Bdt = Quartet.Bdt();
    ChargedHiggsBranch->Tag = Quartet.Tag();

}

void hanalysis::HChargedHiggsSemiTagger::FillBranch(const hanalysis::HQuartet31 &HQuartet)
{
    Print(HInformation, "FillPairTagger", HQuartet.Bdt());
    FillBranch(&Branch, HQuartet);
}

std::vector< HChargedHiggsSemiBranch * > hanalysis::HChargedHiggsSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    JetTag.HeavyParticles = {ChargedHiggsId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    float Mass = Event->GetMass();

    Jets = BottomTagger.GetBdt(Jets, BottomReader);
    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);

    std::vector<HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<HQuartet31 > Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Jets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Quartet.SetTag(GetTag(Quartet));
            if (Quartet.Tag() != Tag) continue;
//             if (Quartet.Jet().m() < 0)continue;
            Quartets.push_back(Quartet);
        }

    Print(HInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == HSignal && Quartets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortByMass<HQuartet31>(Mass));
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch *> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) {
        HChargedHiggsSemiBranch *ChargedHiggsSemiBranch = new HChargedHiggsSemiBranch();
        FillBranch(ChargedHiggsSemiBranch, Quartet);
        ChargedHiggsBranches.push_back(ChargedHiggsSemiBranch);
    }


    return ChargedHiggsBranches;

}


hanalysis::HObject::HTag hanalysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &Quartet)
{
    Print(HInformation, "Get Sextet Tag");

    HJetInfo JetInfoB = Quartet.Singlet().user_info<HJetInfo>();
    JetInfoB.ExtractFraction(BottomId);
    if (std::abs(JetInfoB.MaximalId()) != BottomId) return HBackground;

    HJetInfo JetInfoB1 = Quartet.Triplet().Singlet().user_info<HJetInfo>();
    JetInfoB1.ExtractFraction(TopId);
    if (JetInfoB1.MaximalId() != TopId) return HBackground;
    if (sgn(JetInfoB.MaximalId()) != -sgn(JetInfoB1.MaximalId())) return HBackground;

    HJetInfo JetInfoW1 = Quartet.Triplet().Doublet().Singlet1().user_info<HJetInfo>();
    JetInfoW1.ExtractFraction(TopId);
    if (JetInfoB1.MaximalId() != JetInfoW1.MaximalId()) return HBackground;

    HJetInfo JetInfoW2 = Quartet.Triplet().Doublet().Singlet2().user_info<HJetInfo>();
    JetInfoW2.ExtractFraction(TopId);
    if (JetInfoB1.MaximalId() != JetInfoW2.MaximalId()) return HBackground;

    return HSignal;
}




std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetBdt(std::vector<HTriplet> Triplets , std::vector<fastjet::PseudoJet> Siglets, const HReader &Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
        for (const auto & Jet : Siglets) {
            if (Triplet.Singlet() == Jet) continue;
            if (Triplet.Doublet().Singlet1() == Jet) continue;
            if (Triplet.Doublet().Singlet2() == Jet) continue;
            HQuartet31 Quartet(Triplet, Jet);
            FillBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
            Quartets.push_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(MaxCombi, int(Quartets.size())), Quartets.end());
    return Quartets;
}
