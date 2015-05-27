# include "SignatureChargedTagger.hh"

heavyhiggs::SignatureChargedTagger::SignatureChargedTagger()
{
//       DebugLevel = kDetailed;
    Print(kInformation , "Constructor");
    set_tagger_name("ChargedSignatureSemi");
    DefineVariables();
}

void heavyhiggs::SignatureChargedTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.PairRap, "PairRap");
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");
    AddVariable(branch_.PairBdt, "PairBdt");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int heavyhiggs::SignatureChargedTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

//     Jets jets = GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader.reader());

//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader.reader());
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//     std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_tagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);
//     std::vector<analysis::Quartet31> Higgsquartets = static_cast<analysis::ChargedHiggsSemiTagger &>(charged_higgs_semi_reader_.tagger()).Multiplets(event, charged_higgs_semi_reader_.reader());
    std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_reader_.Multiplets<analysis::ChargedHiggsSemiTagger>(event);

    analysis::Jets HiggsParticles = event.partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(Higgsquartets.begin(), Higgsquartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());

//     if(Tag == HBackground && Higgsquartets.size() > 1) Higgsquartets.erase(Higgsquartets.begin() + 1, Higgsquartets.end());

//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, WTagger, WReader, bottom_tagger_, BottomReader);
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
//     std::vector<analysis::Triplet> Finaltriplets;
//     if (tag == kSignal) {
//         Jets Particles = event.partons().GenParticles();
//         Jets TopParticles = RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
//         if (TopParticles.size() != 1) Print(kError, "Where is the Top?");
//         else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.front()) < detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
//     } else Finaltriplets = tripletsHadronic;
//
//     if (tag == kSignal && Finaltriplets.size() > 1) {
//         std::sort(Finaltriplets.begin(), Finaltriplets.end());
//         Finaltriplets.erase(Finaltriplets.begin() + 1, Finaltriplets.end());
//     }
//
//     Jets FinalBottoms;
//     if (tag == kSignal) {
//         Jets Particles = event.partons().GenParticles();
//         Jets BottomParticles = RemoveIfWrongAbsFamily(Particles, BottomId, GluonId);
//         if (BottomParticles.size() != 1) Print(kError, "Where is the Bottom?");
//         else for (const auto & Jet : jets)  if ((Jet.delta_R(BottomParticles.front()) < detector_geometry().JetConeSize)) FinalBottoms.emplace_back(Jet);
//     } else FinalBottoms = jets;

//     std::vector<analysis::Quartet31> Jetquartets = triplet_jet_pair_tagger_.GetBdt(Finaltriplets, FinalBottoms, triplet_jet_pair_reader_);
//     std::vector<analysis::Quartet31> Jetquartets = static_cast<analysis::TripletJetPairTagger &>(triplet_jet_pair_reader_.tagger()).Quartets(event, triplet_jet_pair_reader_.reader());
    std::vector<analysis::Quartet31> Jetquartets = triplet_jet_pair_reader_.Multiplets<analysis::TripletJetPairTagger>(event);

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

//     std::vector<heavyhiggs::OctetChargedBranch> SignatureSemiBranches;
//     for (const auto & octet : octets) SignatureSemiBranches.emplace_back(GetBranch(octet));

//     return SignatureSemiBranches;
return SaveEntries<OctetChargedBranch>(octets);
}


std::vector<Octet44> heavyhiggs::SignatureChargedTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");

    std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_reader_.Multiplets<analysis::ChargedHiggsSemiTagger>(event);
    std::vector<analysis::Quartet31> Jetquartets = triplet_jet_pair_reader_.Multiplets<analysis::TripletJetPairTagger>(event);
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
            branch_ = branch<OctetChargedBranch>(octet);
            octet.SetBdt(Bdt(reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}
