# include "HChargedSignatureSemiTagger.hh"

hheavyhiggs::HChargedSignatureSemiTagger::HChargedSignatureSemiTagger()
{
//       DebugLevel = kDetailed;
    Print(kInformation , "Constructor");
    DefineVariables();
}

void hheavyhiggs::HChargedSignatureSemiTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::HChargedJetPairTagger &NewChargedJetPairTagger,
    const analysis::HWSemiTagger &NewWSemiTagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::HTopSemiTagger &NewTopSemiTagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{
    bottom_tagger_ = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
    WTagger = NewWTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    TopSemiTagger = NewTopSemiTagger;
    ChargedJetPairTagger = NewChargedJetPairTagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    DefineVariables();
}

void hheavyhiggs::HChargedSignatureSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    set_tagger_name("ChargedSignatureSemi");
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

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

hheavyhiggs::HChargedOctetBranch hheavyhiggs::HChargedSignatureSemiTagger::GetBranch(const HOctet44 &Octet) const
{
    Print(kInformation, "branch", Octet.Bdt());

    HChargedOctetBranch eventSemiBranch;

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
    eventSemiBranch.HiggsBdt = Octet.Quartet1().Bdt();
    eventSemiBranch.PairBdt = Octet.Quartet2().Bdt();

    eventSemiBranch.HiggsMass = Octet.Quartet1().Jet().m();
    eventSemiBranch.PairRap = Octet.Quartet2().DeltaRap();

    return eventSemiBranch;
}

std::vector<hheavyhiggs::HChargedOctetBranch> hheavyhiggs::HChargedSignatureSemiTagger::GetBranches(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Get event Tags");

    Jets jets = GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<analysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);

    Jets HiggsParticles = event.Partons().Generator();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(HiggsQuartets.begin(), HiggsQuartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());

//     if(Tag == HBackground && HiggsQuartets.size() > 1) HiggsQuartets.erase(HiggsQuartets.begin() + 1, HiggsQuartets.end());

    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
//     std::vector<analysis::Doublet> doubletsHadronic = WTagger.GetBdt(jets, WReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = WTagger.GetBdt(Pieces, WReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
    std::vector<analysis::Triplet> Finaltriplets;
    if (tag == kSignal) {
        Jets Particles = event.Partons().Generator();
        Jets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
        if (TopParticles.size() != 1) Print(kError, "Where is the Top?");
        else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
    } else Finaltriplets = tripletsHadronic;

    if (tag == kSignal && Finaltriplets.size() > 1) {
        std::sort(Finaltriplets.begin(), Finaltriplets.end());
        Finaltriplets.erase(Finaltriplets.begin() + 1, Finaltriplets.end());
    }

    Jets FinalBottoms;
    if (tag == kSignal) {
        Jets Particles = event.Partons().Generator();
        Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(kError, "Where is the Bottom?");
        else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
    } else FinalBottoms = jets;

    std::vector<analysis::HQuartet31> JetQuartets = ChargedJetPairTagger.GetBdt(Finaltriplets, FinalBottoms, ChargedJetPairReader);

//     if(Tag == HBackground && JetQuartets.size() > 1) JetQuartets.erase(JetQuartets.begin() + 1, JetQuartets.end());

//     Print(kError, "Number of Higgs and Pairs", HiggsQuartets.size(), JetQuartets.size());
    std::vector<HOctet44> Octets;
    for (const auto HiggsQuartet  : HiggsQuartets)
        for (const auto & JetQuartet : JetQuartets) {
            if (HiggsQuartet.singlet().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Octet.SetTag(tag);
            Octets.emplace_back(Octet);
        }
//     Print(kError, "Number of Signatures", Octets.size());

    std::vector<hheavyhiggs::HChargedOctetBranch> SignatureSemiBranches;
    for (const auto & Octet : Octets) SignatureSemiBranches.emplace_back(GetBranch(Octet));

    return SignatureSemiBranches;
}


std::vector<HOctet44> hheavyhiggs::HChargedSignatureSemiTagger::GetBdt(
    const std::vector< analysis::HQuartet31 > &HiggsQuartets, const std::vector< analysis::HQuartet31 > &JetQuartets, const analysis::Reader &Reader)
{
    Print(kInformation, "Bdt");

//     Print(kError, "Number of Higgs and Pairs", HiggsQuartets.size(), JetQuartets.size());
    std::vector<HOctet44> Octets;
    for (const auto & JetQuartet : JetQuartets) {
        for (const auto & HiggsQuartet : HiggsQuartets) {
            if (HiggsQuartet.singlet().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.singlet().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().singlet().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet1().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (HiggsQuartet.triplet().doublet().Singlet2().delta_R(JetQuartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            HOctet44 Octet(HiggsQuartet, JetQuartet);
            Branch = GetBranch(Octet);
            Octet.SetBdt(Reader.Bdt());
            Octets.emplace_back(Octet);
        }
    }
//     Print(kError, "Number of Signatures", Octets.size());

    if (Octets.size() > 1) std::sort(Octets.begin(), Octets.end());
    Octets.erase(Octets.begin() + std::min(max_combi(), int(Octets.size())), Octets.end());
    Print(kInformation, "event Number", Octets.size());


    return Octets;
}
