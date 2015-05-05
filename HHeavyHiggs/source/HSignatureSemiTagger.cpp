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
    const hanalysis::HWHadronicTagger &NewWTagger,
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
    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaR, "DeltaR");


    AddObservable(Branch.HiggsMass, "HiggsMass");
    AddObservable(Branch.PairRap, "PairRap");
    AddObservable(Branch.BottomBdt, "BottomBdt");
    AddObservable(Branch.PairBottomBdt, "PairBottomBdt");
    AddObservable(Branch.PairBdt, "PairBdt");
    AddObservable(Branch.HiggsBdt, "HiggsBdt");

    AddObservable(Branch.HardTopPt, "HardTopPt");
    AddObservable(Branch.SoftTopPt, "SoftTopPt");

    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");


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

std::vector<hheavyhiggs::HOctetBranch> hheavyhiggs::HSignatureSemiTagger::GetBranches(hanalysis::HEvent &Event, const HObject::Tag Tag)
{
    Print(HInformation, "Get Event Tags");
    float Mass = Event.GetMass();
    HJets Jets = GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
    if (TripletsSemi.size() < 1)Print(HInformation, "No TripletsSemi", TripletsSemi.size());

//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(Jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WTagger, WReader, BottomTagger, BottomReader);
    if (TripletsHadronic.size() < 1)Print(HInformation, "No TripletsHadronic", TripletsHadronic.size());

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
    if (Sextets.size() < 1)Print(HInformation, "No Sextets", Sextets.size());

    HJets HiggsParticles = Event.GetParticles()->Generator();
    HJets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    HJets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaR(HiggsParticles.front()));
        if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
//     if (Doublets.size() < 1)Print(HError, "No Doublets", Doublets.size());


    std::vector<hanalysis::HDoublet> FinalDoublets;
    HJets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & Doublet : Doublets) {
                if ((Doublet.Singlet1().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize) || (Doublet.Singlet1().delta_R(Particles.at(1)) < DetectorGeometry.JetConeSize && Doublet.Singlet2().delta_R(Particles.at(0)) < DetectorGeometry.JetConeSize)) FinalDoublets.push_back(Doublet);
            }
        }
    }
    if (Tag == kBackground) FinalDoublets = Doublets;

    std::vector<HOctet> Octets;
    for (const auto & Doublet : FinalDoublets) {
        for (const auto & Sextet : Sextets) {
            if (Tag == kSignal && Sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && Sextet.Jet().m() > Mass * 3 / 2)continue;
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
    if (Octets.size() < 1)Print(HInformation, "No Octets", Octets.size());

    if (Tag == kSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HOctetBranch> OctetBranches;
    for (const auto & Octet : Octets) OctetBranches.push_back(GetBranch(Octet));
//     if (OctetBranches.size() < 1)Print(HError, "No OctetBranches", OctetBranches.size());
    return OctetBranches;
}


hanalysis::HObject::Tag hheavyhiggs::HSignatureSemiTagger::GetTag(const HOctet &)
{
    Print(HInformation, "Get Sextet Tag");
    return kSignal;
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
    Octets.erase(Octets.begin() + std::min(max_combi(), int(Octets.size())), Octets.end());
    Print(HInformation, "Event Number", Octets.size());


    return Octets;
}
