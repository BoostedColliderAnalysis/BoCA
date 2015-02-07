# include "HChargedSignatureSemiTagger.hh"

hheavyhiggs::HChargedSignatureSemiTagger::HChargedSignatureSemiTagger()
{
//       DebugLevel = HDebug;
    Print(HInformation , "Constructor");
    DefineVariables();
}

hheavyhiggs::HChargedSignatureSemiTagger::~HChargedSignatureSemiTagger()
{
    Print(HInformation , "Destructor");
}

void hheavyhiggs::HChargedSignatureSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    TopSemiTagger = NewTopSemiTagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HChargedSignatureSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("ChargedSignatureSemi");
    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

hheavyhiggs::HChargedOctetBranch hheavyhiggs::HChargedSignatureSemiTagger::GetBranch(const HOctet44 &Octet) const
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    HChargedOctetBranch EventSemiBranch;

    EventSemiBranch.Mass = Octet.Jet().m();
    EventSemiBranch.Rap = Octet.Jet().rap();
    EventSemiBranch.Phi = Octet.Jet().phi();
    EventSemiBranch.Pt = Octet.Jet().pt();
    EventSemiBranch.Ht = Octet.Ht();

    EventSemiBranch.DeltaPt = Octet.DeltaPt();
    EventSemiBranch.DeltaRap = Octet.DeltaRap();
    EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch.DeltaR = Octet.DeltaR();

    EventSemiBranch.Bdt = Octet.Bdt();
    EventSemiBranch.Tag = Octet.Tag();

    EventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    EventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    return EventSemiBranch;
}

std::vector<hheavyhiggs::HChargedOctetBranch> hheavyhiggs::HChargedSignatureSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);
    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(TripletsHadronic, Jets, ChargedJetPairReader);


    HJets HiggsParticles = Event->GetParticles()->GetGeneratorJets();
    HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), MinDeltaR(HiggsParticles.front()));
    if (Tag == HSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());
//     if (Tag == HBackground && HiggsQuartets.size() > 0) HiggsQuartets.erase(HiggsQuartets.begin());


    HJets TopParticles = Event->GetParticles()->GetGeneratorJets();
    TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongAbsFamily(TopId, GluonId)), TopParticles.end());
    if (TopParticles.size() != 1) Print(HError, "Where is the Top?");
    HJets BottomParticles = Event->GetParticles()->GetGeneratorJets();
    BottomParticles.erase(std::remove_if(BottomParticles.begin(), BottomParticles.end(), WrongAbsFamily(BottomId, GluonId)), BottomParticles.end());
    if (BottomParticles.size() != 1) Print(HError, "Where is the Bottom?");

    if (TopParticles.size() > 0 && BottomParticles.size() > 0) {
        hanalysis::HDoublet ParticlePair(TopParticles.front(), BottomParticles.front());
        std::sort(JetQuartets.begin(), JetQuartets.end(), MinDeltaR(ParticlePair.Jet()));
        if (Tag == HSignal && JetQuartets.size() > 1) JetQuartets.erase(JetQuartets.begin() + 1, JetQuartets.end());
    }

    std::vector<HOctet44> Octets;
    for (const auto HiggsQuartet  : HiggsQuartets)
        for (const auto & JetQuartet : JetQuartets) {
            if (HiggsQuartet.Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Octet.SetTag(Tag);
            Octets.push_back(Octet);
        }

    std::vector<hheavyhiggs::HChargedOctetBranch> SignatureSemiBranches;
    for (const auto & Octet : Octets) SignatureSemiBranches.push_back(GetBranch(Octet));

    return SignatureSemiBranches;

}


std::vector<HOctet44> hheavyhiggs::HChargedSignatureSemiTagger::GetBdt(
    const std::vector< hanalysis::HQuartet31 > &HiggsQuartets, const std::vector< hanalysis::HQuartet31 > &JetQuartets, const hanalysis::HReader &Reader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet44> Octets;
    for (const auto & JetQuartet : JetQuartets) {
        for (const auto & HiggsQuartet : HiggsQuartets) {
            if (HiggsQuartet.Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Singlet() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Singlet()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet1()) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2() == JetQuartet.Triplet().Doublet().Singlet2()) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Branch = GetBranch(Octet);
            Octet.SetBdt(Reader.Bdt());
            Octets.push_back(Octet);
        }
    }

    if (Octets.size() > 1) std::sort(Octets.begin(), Octets.end());
    Octets.erase(Octets.begin() + std::min(MaxCombi, int(Octets.size())), Octets.end());
    Print(HInformation, "Event Number", Octets.size());


    return Octets;
}
