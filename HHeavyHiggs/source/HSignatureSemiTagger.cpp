# include "HSignatureSemiTagger.hh"

hheavyhiggs::HSignatureSemiTagger::HSignatureSemiTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HSignatureSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::HJetPairTagger &NewJetPairTagger,
    const analysis::WSemiTagger &Neww_semi_tagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::TopSemiTagger &Newtop_semi_tagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HHeavyHiggsSemiTagger &NewHeavyHiggsSemiTagger)
{
    Print(kNotification , "Constructor");
    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_semi_tagger = Newtop_semi_tagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    HeavyHiggsSemiTagger = NewHeavyHiggsSemiTagger;
    JetPairTagger = NewJetPairTagger;
    DefineVariables();
}

void hheavyhiggs::HSignatureSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
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


    Print(kNotification, "Variables defined");

}

hheavyhiggs::HOctetBranch hheavyhiggs::HSignatureSemiTagger::GetBranch(const HOctet &Octet) const
{
    Print(kInformation, "FillPairTagger", Octet.Bdt());

    HOctetBranch eventSemiBranch;

    eventSemiBranch.Mass = Octet.Jet().m();
    eventSemiBranch.Rap = Octet.Jet().rap();
    eventSemiBranch.Phi = Octet.Jet().phi();
    eventSemiBranch.Pt = Octet.Jet().pt();
    eventSemiBranch.Ht = Octet.Ht();

    eventSemiBranch.DeltaPt = Octet.DeltaPt();
    eventSemiBranch.DeltaHt = Octet.DeltaHt();
    eventSemiBranch.DeltaM = Octet.DeltaM();
    eventSemiBranch.DeltaRap = Octet.DeltaRap();
    eventSemiBranch.DeltaPhi = Octet.DeltaPhi();
    eventSemiBranch.DeltaR = Octet.DeltaR();

    eventSemiBranch.Bdt = Octet.Bdt();
    eventSemiBranch.Tag = Octet.Tag();
    eventSemiBranch.BottomBdt = Octet.BottomBdt();
    eventSemiBranch.PairBottomBdt = Octet.PairBottomBdt();
    eventSemiBranch.PairBdt = Octet.doublet().Bdt();
    eventSemiBranch.HiggsBdt = Octet.sextet().Bdt();
    eventSemiBranch.HardTopPt = Octet.sextet().HardTopPt();
    eventSemiBranch.SoftTopPt = Octet.sextet().SoftTopPt();


    eventSemiBranch.HiggsMass = Octet.sextet().Jet().m();
    eventSemiBranch.PairRap = Octet.doublet().DeltaRap();


    return eventSemiBranch;

}

std::vector<hheavyhiggs::HOctetBranch> hheavyhiggs::HSignatureSemiTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");
    float Mass = event.mass();
    Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.leptons().GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    if (tripletsSemi.empty())Print(kInformation, "No tripletsSemi", tripletsSemi.size());

//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
    if (tripletsHadronic.empty())Print(kInformation, "No tripletsHadronic", tripletsHadronic.size());

    std::vector<analysis::Sextet> sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
    if (sextets.empty())Print(kInformation, "No sextets", sextets.size());

    Jets HiggsParticles = event.partons().Generator();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (Tag == kSignal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Print(kError, "Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//     if (doublets.empty())Print(kError, "No doublets", doublets.size());


    std::vector<analysis::Doublet> Finaldoublets;
    Jets Particles = event.partons().Generator();
    if (Tag == kSignal) {
        Particles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
                if ((doublet.Singlet1().delta_R(Particles.at(0)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(1)) < detector_geometry().JetConeSize) || (doublet.Singlet1().delta_R(Particles.at(1)) < detector_geometry().JetConeSize && doublet.Singlet2().delta_R(Particles.at(0)) < detector_geometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
            }
        }
    }
    if (Tag == kBackground) Finaldoublets = doublets;

    std::vector<HOctet> Octets;
    for (const auto & doublet : Finaldoublets) {
        for (const auto & sextet : sextets) {
            if (Tag == kSignal && sextet.Jet().m() < Mass / 2)continue;
            if (Tag == kSignal && sextet.Jet().m() > Mass * 3 / 2)continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet Octet(sextet, doublet);
            Octet.SetTag(Tag);
            Octets.emplace_back(Octet);
        }
    }
    if (Octets.empty())Print(kInformation, "No Octets", Octets.size());

    if (Tag == kSignal && Octets.size() > 1) {
        Print(kInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }

    std::vector<hheavyhiggs::HOctetBranch> OctetBranches;
    for (const auto & Octet : Octets) OctetBranches.emplace_back(GetBranch(Octet));
//     if (OctetBranches.empty())Print(kError, "No OctetBranches", OctetBranches.size());
    return OctetBranches;
}


analysis::Object::Tag hheavyhiggs::HSignatureSemiTagger::GetTag(const HOctet &)
{
    Print(kInformation, "Get sextet Tag");
    return kSignal;
}

std::vector<HOctet> hheavyhiggs::HSignatureSemiTagger::GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader)
{
    Print(kInformation, "Get event Tags");

    std::vector<HOctet> Octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet1().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().singlet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet1().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Singlet2().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().doublet().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet1()) < detector_geometry().JetConeSize) continue;
            if (sextet.triplet2().Jet().delta_R(doublet.Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet Octet(sextet, doublet);
            Branch = GetBranch(Octet);
            Octet.SetBdt(Reader.Bdt());
            Octets.emplace_back(Octet);
        }
    }

    if (Octets.size() > 1) std::sort(Octets.begin(), Octets.end());
    Octets.erase(Octets.begin() + std::min(max_combi(), int(Octets.size())), Octets.end());
    Print(kInformation, "event Number", Octets.size());


    return Octets;
}
