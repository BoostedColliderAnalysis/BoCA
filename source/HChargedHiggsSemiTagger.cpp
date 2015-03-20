# include "HChargedHiggsSemiTagger.hh"

hanalysis::HChargedHiggsSemiTagger::HChargedHiggsSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("ChargedHiggsSemi");
    DefineVariables();
}

hanalysis::HChargedHiggsSemiTagger::~HChargedHiggsSemiTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HChargedHiggsSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger)
{
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;

    SetTaggerName("ChargedHiggsSemi");
    DefineVariables();
}


void hanalysis::HChargedHiggsSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch.DeltaHt, "DeltaHt"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));
    Spectators.push_back(NewObservable(&Branch.Flag, "Flag"));

    Print(HNotification, "Variables defined");

}

HChargedHiggsSemiBranch hanalysis::HChargedHiggsSemiTagger::GetBranch(const HQuartet31 &Quartet)const
{
    Print(HInformation, "FillPairTagger", Quartet.Bdt());
    HChargedHiggsSemiBranch ChargedHiggsBranch;
    ChargedHiggsBranch.Mass = Quartet.Jet().m();
    ChargedHiggsBranch.Rap = Quartet.Jet().rap();
    ChargedHiggsBranch.Phi = Quartet.Jet().phi();
    ChargedHiggsBranch.Pt = Quartet.Jet().pt();
    ChargedHiggsBranch.Ht = Quartet.Ht();

    ChargedHiggsBranch.DeltaPt = Quartet.DeltaPt();
    ChargedHiggsBranch.DeltaM = Quartet.DeltaM();
    ChargedHiggsBranch.DeltaHt = Quartet.DeltaHt();
    ChargedHiggsBranch.DeltaR = Quartet.DeltaR();
    ChargedHiggsBranch.DeltaRap = Quartet.DeltaRap();
    ChargedHiggsBranch.DeltaPhi = Quartet.DeltaPhi();

    ChargedHiggsBranch.Bdt = Quartet.Bdt();
    ChargedHiggsBranch.Tag = Quartet.Tag();
    ChargedHiggsBranch.Flag = Quartet.Flag();
    return ChargedHiggsBranch;

}





std::vector< HChargedHiggsSemiBranch> hanalysis::HChargedHiggsSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag)
{
    Print(HInformation, "Get Higgs Tags");

    float Mass = Event.GetMass();
    fastjet::PseudoJet HiggsBoson;
    if (Tag == HSignal) {
        HJets HiggsParticles = Event.GetParticles()->Generator();
        HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
        if (Tag == HSignal) {
            if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
            else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        }
    }

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    const fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);


    int WSemiId = WSemiTagger.GetWSemiId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());
    std::vector<HTriplet> FinalTriplets;
    if (Tag == HSignal) {
        for (const auto & Triplet : Triplets) if (Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) FinalTriplets.push_back(Triplet);
    } else FinalTriplets = Triplets;

    HJets BottomJets;
    if (Tag == HSignal) {
    HJets  BottomParticles = Event.GetParticles()->Generator();
    BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, ChargedHiggsId);
    fastjet::PseudoJet BottomQuark;
    if (BottomParticles.size() == 1) BottomQuark = BottomParticles.front();
    else  Print(HError, "Where is the Bottom?");
        for (const auto & Jet : Jets) if (Jet.delta_R(BottomQuark) < DetectorGeometry.JetConeSize) BottomJets.push_back(Jet);
    } else BottomJets = Jets;

    std::vector<HQuartet31 > Quartets;

    for (const auto & Triplet : FinalTriplets)
        for (const auto & Jet : BottomJets) {
            if (Triplet.Singlet().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            if (Tag == HSignal && Quartet.Jet().m() < Mass / 2)continue;
            if (Tag == HSignal && Quartet.Jet().m() > Mass * 3 / 2)continue;
            if (Tag == HSignal && Quartet.Jet().delta_R(HiggsBoson) > 2 * DetectorGeometry.JetConeSize) continue;
            Quartets.push_back(Quartet);
        }

    Print(HInformation, "Number of Heavy Higgses", Quartets.size());

    if (Tag == HSignal && Quartets.size() > 1) {
        Print(HInformation, "Higgs Candidates", Quartets.size());
        std::sort(Quartets.begin(), Quartets.end(), SortByMass(Mass));
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    std::vector<HChargedHiggsSemiBranch> ChargedHiggsBranches;
    for (const auto & Quartet : Quartets) ChargedHiggsBranches.push_back(GetBranch(Quartet));

    return ChargedHiggsBranches;
}


hanalysis::HObject::HTag hanalysis::HChargedHiggsSemiTagger::GetTag(const HQuartet31 &)
{
    Print(HInformation, "Get Sextet Tag");

    return HSignal;
}




std::vector<hanalysis::HQuartet31>  hanalysis::HChargedHiggsSemiTagger::GetBdt(const std::vector<HTriplet> Triplets , const std::vector<fastjet::PseudoJet> Siglets, const HReader &Reader)
{

    std::vector<HQuartet31> Quartets;
    for (const auto & Triplet : Triplets)
      for (const auto & Jet : Siglets) {
        if (Triplet.Singlet().delta_R(Jet) < DetectorGeometry.JetConeSize) continue;
            HQuartet31 Quartet(Triplet, Jet);
            Branch = GetBranch(Quartet);
            Quartet.SetBdt(Reader.Bdt());
            Quartets.push_back(Quartet);
        }

    std::sort(Quartets.begin(), Quartets.end());
    Quartets.erase(Quartets.begin() + std::min(MaxCombi, int(Quartets.size())), Quartets.end());
    return Quartets;
}
