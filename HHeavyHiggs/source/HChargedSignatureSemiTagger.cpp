# include "HChargedSignatureSemiTagger.hh"

hheavyhiggs::HChargedSignatureSemiTagger::HChargedSignatureSemiTagger()
{
//       DebugLevel = HDetailed;
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
    Observables.push_back(NewObservable(&Branch.DeltaHt, "DeltaHt"));
    Observables.push_back(NewObservable(&Branch.DeltaM, "DeltaM"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch.PairRap, "PairRap"));
    Observables.push_back(NewObservable(&Branch.BottomBdt, "BottomBdt"));
    Observables.push_back(NewObservable(&Branch.PairBottomBdt, "PairBottomBdt"));
    Observables.push_back(NewObservable(&Branch.PairBdt, "PairBdt"));
    Observables.push_back(NewObservable(&Branch.HiggsBdt, "HiggsBdt"));

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
    EventSemiBranch.DeltaHt = Octet.DeltaHt();
    EventSemiBranch.DeltaM = Octet.DeltaM();
    EventSemiBranch.DeltaRap = Octet.DeltaRap();
    EventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    EventSemiBranch.DeltaR = Octet.DeltaR();

    EventSemiBranch.Bdt = Octet.Bdt();
    EventSemiBranch.Tag = Octet.Tag();
    EventSemiBranch.BottomBdt = Octet.BottomBdt();
    EventSemiBranch.PairBottomBdt = Octet.PairBottomBdt();
    EventSemiBranch.HiggsBdt = Octet.Quartet1().Bdt();
    EventSemiBranch.PairBdt = Octet.Quartet2().Bdt();

    EventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    EventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    return EventSemiBranch;
}

std::vector<hheavyhiggs::HChargedOctetBranch> hheavyhiggs::HChargedSignatureSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);

    HJets HiggsParticles = Event.GetParticles()->Generator();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (Tag == HSignal && HiggsParticles.size() != 1) Print(HError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), MinDeltaR(HiggsParticles.front()));
    if (Tag == HSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());


    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WTagger.GetBdt(Pieces, WReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        TripletsHadronic.insert(TripletsHadronic.end(), PieceTriplets.begin(), PieceTriplets.end());
    }
    std::vector<hanalysis::HTriplet> FinalTriplets;
    if (Tag == HSignal) {
        HJets Particles = Event.GetParticles()->Generator();
        HJets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
        if (TopParticles.size() != 1) Print(HError, "Where is the Top?");
        else for (const auto & Triplet : TripletsHadronic) if ((Triplet.Jet().delta_R(TopParticles.at(0)) < DetectorGeometry.JetConeSize)) FinalTriplets.push_back(Triplet);
    } else FinalTriplets = TripletsHadronic;

    if(FinalTriplets.size()>1){
    std::sort(FinalTriplets.begin(), FinalTriplets.end());
    FinalTriplets.erase(FinalTriplets.begin() + 1, FinalTriplets.end());
    }

    HJets FinalBottoms;
    if (Tag == HSignal) {
        HJets Particles = Event.GetParticles()->Generator();
        HJets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(HError, "Where is the Bottom?");
        else for (const auto & Jet : Jets) if ((Jet.delta_R(BottomParticles.at(0)) < DetectorGeometry.JetConeSize)) FinalBottoms.push_back(Jet);
    } else FinalBottoms = Jets;

    std::vector<hanalysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(FinalTriplets, FinalBottoms, ChargedJetPairReader);

    std::vector<HOctet44> Octets;
    for (const auto HiggsQuartet  : HiggsQuartets)
        for (const auto & JetQuartet : JetQuartets) {
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
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
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Singlet().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet1().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Singlet()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (HiggsQuartet.Triplet().Doublet().Singlet2().delta_R(JetQuartet.Triplet().Doublet().Singlet2()) < DetectorGeometry.JetConeSize) continue;
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
