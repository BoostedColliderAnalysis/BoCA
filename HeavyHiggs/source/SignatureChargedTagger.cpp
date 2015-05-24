# include "SignatureChargedTagger.hh"

heavyhiggs::SignatureChargedTagger::SignatureChargedTagger()
{
//       DebugLevel = kDetailed;
    Print(kInformation , "Constructor");
    DefineVariables();
}

void heavyhiggs::SignatureChargedTagger::SetTagger(
    const analysis::BottomTagger &NewBottomTagger,
    const analysis::TripletJetPairTagger &NewChargedjet_pair_tagger,
    const analysis::WSemiTagger &Neww_semi_tagger,
    const analysis::WHadronicTagger &NewWTagger,
    const analysis::TopSemiTagger &Newtop_semi_tagger,
    const analysis::TopHadronicTagger &Newtop_hadronic_tagger,
    const analysis::HChargedHiggsSemiTagger &NewChargedHiggsSemiTagger)
{
    bottom_tagger_ = NewBottomTagger;
    w_semi_tagger = Neww_semi_tagger;
    WTagger = NewWTagger;
    top_hadronic_tagger = Newtop_hadronic_tagger;
    top_semi_tagger = Newtop_semi_tagger;
    Chargedjet_pair_tagger = NewChargedjet_pair_tagger;
    ChargedHiggsSemiTagger = NewChargedHiggsSemiTagger;
    DefineVariables();
}

void heavyhiggs::SignatureChargedTagger::DefineVariables()
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

heavyhiggs::OctetChargedBranch heavyhiggs::SignatureChargedTagger::GetBranch(const Octet44 &octet) const
{
    Print(kInformation, "branch", octet.Bdt());

    OctetChargedBranch branch;
    branch.Fill(octet);
    return branch;
}

std::vector<heavyhiggs::OctetChargedBranch> heavyhiggs::SignatureChargedTagger::GetBranches(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Get event Tags");

    Jets jets = GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<analysis::Quartet31> Higgsquartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);

    Jets HiggsParticles = event.partons().Generator();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(Higgsquartets.begin(), Higgsquartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());

//     if(Tag == HBackground && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());

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
        Jets Particles = event.partons().Generator();
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
        Jets Particles = event.partons().Generator();
        Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
        if (BottomParticles.size() != 1) Print(kError, "Where is the Bottom?");
        else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
    } else FinalBottoms = jets;

    std::vector<analysis::Quartet31> Jetquartets = Chargedjet_pair_tagger.GetBdt(Finaltriplets, FinalBottoms, ChargedJetPairReader);

//     if(Tag == HBackground && Jetquartets.size() > 1) Jetquartets.erase(Jetquartets.begin() + 1, Jetquartets.end());

//     Print(kError, "Number of Higgs and Pairs", Higgsquartets.size(), Jetquartets.size());
    std::vector<Octet44> octets;
    for (const auto Higgsquartet  : Higgsquartets)
        for (const auto & Jetquartet : Jetquartets) {
            if (Higgsquartet.singlet().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            Octet44 octet(Higgsquartet, Jetquartet);
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
//     Print(kError, "Number of Signatures", octets.size());

    std::vector<heavyhiggs::OctetChargedBranch> SignatureSemiBranches;
    for (const auto & octet : octets) SignatureSemiBranches.emplace_back(GetBranch(octet));

    return SignatureSemiBranches;
}


std::vector<Octet44> heavyhiggs::SignatureChargedTagger::GetBdt(
    const std::vector< analysis::Quartet31 > &Higgsquartets, const std::vector< analysis::Quartet31 > &Jetquartets, const analysis::Reader &Reader)
{
    Print(kInformation, "Bdt");

//     Print(kError, "Number of Higgs and Pairs", Higgsquartets.size(), Jetquartets.size());
    std::vector<Octet44> octets;
    for (const auto & Jetquartet : Jetquartets) {
        for (const auto & Higgsquartet : Higgsquartets) {
            if (Higgsquartet.singlet().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.singlet().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().singlet().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet1().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().singlet()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().doublet().Singlet1()) < detector_geometry().JetConeSize) continue;
            if (Higgsquartet.triplet().doublet().Singlet2().delta_R(Jetquartet.triplet().doublet().Singlet2()) < detector_geometry().JetConeSize) continue;
            Octet44 octet(Higgsquartet, Jetquartet);
            Branch = GetBranch(octet);
            octet.SetBdt(Reader.Bdt());
            octets.emplace_back(octet);
        }
    }
//     Print(kError, "Number of Signatures", octets.size());

    if (octets.size() > 1) std::sort(octets.begin(), octets.end());
    octets.erase(octets.begin() + std::min(max_combi(), int(octets.size())), octets.end());
    Print(kInformation, "event Number", octets.size());


    return octets;
}
