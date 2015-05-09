# include "HSignatureSemiTagger.hh"

hheavyhiggs::HSignatureSemiTagger::HSignatureSemiTagger()
{
    //   DebugLevel = HDebug;
    Print(HNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HSignatureSemiTagger::SetTagger(
    const hanalysis::BottomTagger &NewBottomTagger,
    const hanalysis::HJetPairTagger &NewJetPairTagger,
    const hanalysis::HWSemiTagger &NewWSemiTagger,
    const hanalysis::HWHadronicTagger &NewWTagger,
    const hanalysis::HTopSemiTagger &NewTopSemiTagger,
    const hanalysis::HTopHadronicTagger &NewTopHadronicTagger,
    const hanalysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(HNotification , "Constructor");
    bottom_tagger_ = NewBottomTagger;
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
    set_tagger_name("SignatureSemi");
    ClearVectors();


    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");
    AddVariable(Branch.Ht, "Ht");

    AddVariable(Branch.DeltaPt, "DeltaPt");
    AddVariable(Branch.DeltaHt, "DeltaHt");
    AddVariable(Branch.DeltaM, "DeltaM");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaR, "DeltaR");


    AddVariable(Branch.HiggsMass, "HiggsMass");
    AddVariable(Branch.PairRap, "PairRap");
    AddVariable(Branch.BottomBdt, "BottomBdt");
    AddVariable(Branch.PairBottomBdt, "PairBottomBdt");
    AddVariable(Branch.PairBdt, "PairBdt");
    AddVariable(Branch.HiggsBdt, "HiggsBdt");

    AddVariable(Branch.HardTopPt, "HardTopPt");
    AddVariable(Branch.SoftTopPt, "SoftTopPt");

    AddVariable(Branch.Bdt, "Bdt");
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
    Jets jets = GetJets(Event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, jets, TopSemiReader);
    if (TripletsSemi.empty())Print(HInformation, "No TripletsSemi", TripletsSemi.size());

//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, jets, TopHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    if (TripletsHadronic.empty())Print(HInformation, "No TripletsHadronic", TripletsHadronic.size());

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
    if (Sextets.empty())Print(HInformation, "No Sextets", Sextets.size());

    Jets HiggsParticles = Event.GetParticles()->Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(HError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(Sextets.begin(), Sextets.end(), MinDeltaRTo(HiggsParticles.front()));
        if (Sextets.size() > 1) Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//     if (Doublets.empty())Print(HError, "No Doublets", Doublets.size());


    std::vector<hanalysis::HDoublet> FinalDoublets;
    Jets Particles = Event.GetParticles()->Generator();
    if (Tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & Doublet : Doublets) {
                if ((Doublet.Singlet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && Doublet.Singlet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (Doublet.Singlet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && Doublet.Singlet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) FinalDoublets.emplace_back(Doublet);
            }
        }
    }
    if (Tag == kBackground) FinalDoublets = Doublets;

    std::vector<HOctet> Octets;
    for (const auto & Doublet : FinalDoublets) {
        for (const auto & Sextet : Sextets) {
            if (Tag == kSignal && Sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && Sextet.Jet().m() > Mass * 3 / 2)continue;
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet Octet(Sextet, Doublet);
            Octet.SetTag(Tag);
            Octets.emplace_back(Octet);
        }
    }
    if (Octets.empty())Print(HInformation, "No Octets", Octets.size());

    if (Tag == kSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HOctetBranch> OctetBranches;
    for (const auto & Octet : Octets) OctetBranches.emplace_back(GetBranch(Octet));
//     if (OctetBranches.empty())Print(HError, "No OctetBranches", OctetBranches.size());
    return OctetBranches;
}


hanalysis::HObject::Tag hheavyhiggs::HSignatureSemiTagger::GetTag(const HOctet &)
{
    Print(HInformation, "Get Sextet Tag");
    return kSignal;
}

std::vector<HOctet> hheavyhiggs::HSignatureSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const hanalysis::Reader &Reader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet1().Singlet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Singlet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet1().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Singlet2().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Doublet().Jet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Sextet.Triplet2().Jet().delta_R(Doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet Octet(Sextet, Doublet);
            Branch = GetBranch(Octet);
            Octet.SetBdt(Reader.Bdt());
            Octets.emplace_back(Octet);
        }
    }

    if (Octets.size() > 1) std::sort(Octets.begin(), Octets.end());
    Octets.erase(Octets.begin() + std::min(max_combi(), int(Octets.size())), Octets.end());
    Print(HInformation, "Event Number", Octets.size());


    return Octets;
}
