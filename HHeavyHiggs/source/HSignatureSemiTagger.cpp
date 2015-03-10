# include "HSignatureSemiTagger.hh"

hheavyhiggs::HSignatureSemiTagger::HSignatureSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HSignatureSemiTagger::SetTagger(
    const hanalysis::HBottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    TopSemiTagger = NewTopSemiTagger;
    TopHadronicTagger = NewTopHadronicTagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    JetPairTagger = NewJetPairTagger;
    DefineVariables();
}

void hheavyhiggs::HSignatureSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("SignatureSemi");
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

    Observables.push_back(NewObservable(&Branch.HardTopPt, "HardTopPt"));
    Observables.push_back(NewObservable(&Branch.SoftTopPt, "SoftTopPt"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));


    Print(HNotification, "Variables defined");

}

hheavyhiggs::HOctetBranch hheavyhiggs::HSignatureSemiTagger::GetBranch(const HOctet &Octet) const
{
    Print(HInformation, "FillPairTagger", Octet.Bdt());

    HOctetBranch EventSemiBranch;

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
    EventSemiBranch.PairBdt = Octet.Doublet().Bdt();
    EventSemiBranch.HiggsBdt = Octet.Sextet().Bdt();
    EventSemiBranch.HardTopPt = Octet.Sextet().HardTopPt();
    EventSemiBranch.SoftTopPt = Octet.Sextet().SoftTopPt();


    EventSemiBranch.HiggsMass = Octet.Sextet().Jet().m();
    EventSemiBranch.PairRap = Octet.Doublet().DeltaRap();


    return EventSemiBranch;

}

std::vector<hheavyhiggs::HOctetBranch> hheavyhiggs::HSignatureSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    HJets HiggsParticles = Event.GetParticles()->Generator();
    HJets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    HJets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == HSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
        if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);


    HJets Particles = Event.GetParticles()->Generator();
    std::vector<hanalysis::HDoublet> FinalDoublets;
    if (Tag == HSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & Doublet : Doublets) {
                if ((Doublet.Singlet1().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize) || (Doublet.Singlet1().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize)) FinalDoublets.push_back(Doublet);
            }
        }
    }
    if (Tag == HBackground) FinalDoublets = Doublets;


//     HJets BottomParticles = Event.GetParticles()->Generator();
//     BottomParticles = RemoveIfWrongAbsFamily(BottomParticles, BottomId, GluonId);
//     if (Tag == HSignal && BottomParticles.size() != 2) Print(HError, "Where is the Bottom?", BottomParticles.size());
//
//     if (Tag == HSignal && BottomParticles.size() > 1) {
//         hanalysis::HDoublet ParticleDoublet(BottomParticles.at(0), BottomParticles.at(1));
//         std::sort(Doublets.begin(), Doublets.end(), MinDeltaR(ParticleDoublet.Jet()));
//         if (Doublets.size() > 1)Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }

    std::vector<HOctet> Octets;
    for (const auto & Doublet : FinalDoublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            HOctet Octet(Sextet, Doublet);
            Octet.SetTag(Tag);
            Octets.push_back(Octet);
        }
    }

    if (Tag == HSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HOctetBranch> OctetBranches;
    for (const auto & Octet : Octets) OctetBranches.push_back(GetBranch(Octet));
    return OctetBranches;
}


hanalysis::HObject::HTag hheavyhiggs::HSignatureSemiTagger::GetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Sextet Tag");
    return HSignal;
}

std::vector<HOctet> hheavyhiggs::HSignatureSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const hanalysis::HReader &Reader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet1()) < DetectorGeometry.JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet2()) < DetectorGeometry.JetConeSize) continue;
            HOctet Octet(Sextet, Doublet);
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
