# include "SignatureNeutralTagger.hh"

heavyhiggs::SignatureNeutralTagger::SignatureNeutralTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    DefineVariables();
}

void heavyhiggs::SignatureNeutralTagger::SetTagger(
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

void heavyhiggs::SignatureNeutralTagger::DefineVariables()
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

heavyhiggs::HOctetBranch heavyhiggs::SignatureNeutralTagger::GetBranch(const Octet62 &octet) const
{
    Print(kInformation, "FillPairTagger", octet.Bdt());

    HOctetBranch eventSemiBranch;

    eventSemiBranch.Mass = octet.Jet().m();
    eventSemiBranch.Rap = octet.Jet().rap();
    eventSemiBranch.Phi = octet.Jet().phi();
    eventSemiBranch.Pt = octet.Jet().pt();
    eventSemiBranch.Ht = octet.Ht();

    eventSemiBranch.DeltaPt = octet.DeltaPt();
    eventSemiBranch.DeltaHt = octet.DeltaHt();
    eventSemiBranch.DeltaM = octet.DeltaM();
    eventSemiBranch.DeltaRap = octet.DeltaRap();
    eventSemiBranch.DeltaPhi = octet.DeltaPhi();
    eventSemiBranch.DeltaR = octet.DeltaR();

    eventSemiBranch.Bdt = octet.Bdt();
    eventSemiBranch.Tag = octet.Tag();
    eventSemiBranch.BottomBdt = octet.BottomBdt();
    eventSemiBranch.PairBottomBdt = octet.PairBottomBdt();
    eventSemiBranch.PairBdt = octet.doublet().Bdt();
    eventSemiBranch.HiggsBdt = octet.sextet().Bdt();
    eventSemiBranch.HardTopPt = octet.sextet().HardTopPt();
    eventSemiBranch.SoftTopPt = octet.sextet().SoftTopPt();


    eventSemiBranch.HiggsMass = octet.sextet().Jet().m();
    eventSemiBranch.PairRap = octet.doublet().DeltaRap();


    return eventSemiBranch;

}

std::vector<heavyhiggs::HOctetBranch> heavyhiggs::SignatureNeutralTagger::GetBranches(analysis::Event &event, const Object::Tag Tag)
{
    Print(kInformation, "Get event Tags");
    float Mass = event.mass();
    Jets jets = GetJets(event);
    //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this

    Jets Leptons = event.leptons().GetTaggedJets(jet_tag);
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

    std::vector<Octet62> octets;
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
            Octet62 octet(sextet, doublet);
            octet.SetTag(Tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty())Print(kInformation, "No octets", octets.size());

    if (Tag == kSignal && octets.size() > 1) {
        Print(kInformation, "more than one event", octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    std::vector<heavyhiggs::HOctetBranch> octetBranches;
    for (const auto & octet : octets) octetBranches.emplace_back(GetBranch(octet));
//     if (octetBranches.empty())Print(kError, "No octetBranches", octetBranches.size());
    return octetBranches;
}


analysis::Object::Tag heavyhiggs::SignatureNeutralTagger::GetTag(const Octet62 &)
{
    Print(kInformation, "Get sextet Tag");
    return kSignal;
}

std::vector<Octet62> heavyhiggs::SignatureNeutralTagger::GetBdt(const std::vector< analysis::Sextet > &sextets, const std::vector< analysis::Doublet > &doublets, const analysis::Reader &Reader)
{
    Print(kInformation, "Get event Tags");

    std::vector<Octet62> octets;
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
            Octet62 octet(sextet, doublet);
            Branch = GetBranch(octet);
            octet.SetBdt(Reader.Bdt());
            octets.emplace_back(octet);
        }
    }

    if (octets.size() > 1) std::sort(octets.begin(), octets.end());
    octets.erase(octets.begin() + std::min(max_combi(), int(octets.size())), octets.end());
    Print(kInformation, "event Number", octets.size());


    return octets;
}
