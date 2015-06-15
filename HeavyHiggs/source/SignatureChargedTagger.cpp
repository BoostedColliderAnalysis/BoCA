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
    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Ht, "Ht");

    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaHt, "DeltaHt");
    AddVariable(branch().DeltaM, "DeltaM");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().DeltaR, "DeltaR");

    AddVariable(branch().HiggsMass, "HiggsMass");
    AddVariable(branch().PairRap, "PairRap");
    AddVariable(branch().BottomBdt, "BottomBdt");
    AddVariable(branch().PairBottomBdt, "PairBottomBdt");
    AddVariable(branch().PairBdt, "PairBdt");
    AddVariable(branch().HiggsBdt, "HiggsBdt");

    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int heavyhiggs::SignatureChargedTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    std::vector<analysis::Quartet31> higgs_quartets = charged_higgs_semi_reader_.Multiplets<ChargedHiggsSemiTagger>(event);

    analysis::Jets HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
    if (tag == kSignal && HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?");
    std::sort(higgs_quartets.begin(), higgs_quartets.end(), analysis::MinDeltaRTo(HiggsParticles.front()));
    if (tag == kSignal && higgs_quartets.size() > 1) higgs_quartets.erase(higgs_quartets.begin() + 1, higgs_quartets.end());

    std::vector<analysis::Quartet31> jet_quartets = triplet_jet_pair_reader_.Multiplets<analysis::TripletJetPairTagger>(event);

    std::vector<Octet44> octets;
    for (const auto higgs_quartet  : higgs_quartets)
        for (const auto & jet_quartet : jet_quartets) {
            Octet44 octet(higgs_quartet, jet_quartet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    return SaveEntries(octets);
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
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet,reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}
