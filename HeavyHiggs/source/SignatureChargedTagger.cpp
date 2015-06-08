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

    std::vector<analysis::Quartet31> higgs_quartets = charged_higgs_semi_reader_.Multiplets<ChargedHiggsSemiTagger>(event);

    analysis::Jets HiggsParticles = event.partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(higgs_quartets.begin(), higgs_quartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && higgs_quartets.size() > 1) higgs_quartets.erase(higgs_quartets.begin() + 1, higgs_quartets.end());

    std::vector<analysis::Quartet31> jet_quartets = triplet_jet_pair_reader_.Multiplets<analysis::TripletJetPairTagger>(event);

    std::vector<Octet44> octets;
    for (const auto higgs_quartet  : higgs_quartets)
        for (const auto & jet_quartet : jet_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    return SaveEntries<OctetChargedBranch>(octets);
}


std::vector<heavyhiggs::Octet44> heavyhiggs::SignatureChargedTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");

    std::vector<analysis::Quartet31> higgs_quartets = charged_higgs_semi_reader_.Multiplets<ChargedHiggsSemiTagger>(event);
    std::vector<analysis::Quartet31> jet_quartets = triplet_jet_pair_reader_.Multiplets<analysis::TripletJetPairTagger>(event);
    std::vector<Octet44> octets;
    for (const auto & jet_quartet : jet_quartets) {
        for (const auto & higgs_quartet : higgs_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.overlap()) continue;
            branch_ = branch<OctetChargedBranch>(octet);
            octet.SetBdt(Bdt(reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}
