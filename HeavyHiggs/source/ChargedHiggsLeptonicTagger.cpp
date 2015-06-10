# include "ChargedHiggsLeptonicTagger.hh"

heavyhiggs::ChargedHiggsLeptonicTagger::ChargedHiggsLeptonicTagger()
{
//     DebugLevel = analysis::Object::kDebug;

    Print(kNotification, "Constructor");
    set_tagger_name("ChargedHiggsLeptonic");
    bottom_reader_.set_tagger(bottom_tagger_);
    top_leptonic_reader_.set_tagger(top_leptonic_tagger_);
    DefineVariables();
}

void heavyhiggs::ChargedHiggsLeptonicTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    AddVariable(branch_.HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(branch_.TopDeltaR, "TopDeltaR");
    AddVariable(branch_.TopDeltaRap, "TopDeltaRap");
    AddVariable(branch_.TopDeltaPhi, "TopDeltaPhi");

//     AddVariable(branch_.LargerWDeltaR, "LargerWDeltaR");
//     AddVariable(branch_.LargerWDeltaRap, "LargerWDeltaRap");
//     AddVariable(branch_.LargerWDeltaPhi, "LargerWDeltaPhi");
//
//     AddVariable(branch_.SmallerWDeltaR, "SmallerWDeltaR");
//     AddVariable(branch_.SmallerWDeltaRap, "SmallerWDeltaRap");
//     AddVariable(branch_.SmallerWDeltaPhi, "SmallerWDeltaPhi");
//
//     AddVariable(branch_.LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
//     AddVariable(branch_.LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
//     AddVariable(branch_.LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");
//
//     AddVariable(branch_.SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
//     AddVariable(branch_.SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
//     AddVariable(branch_.SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(branch_.TopBdt, "TopBdt");

    AddSpectator(branch_.HeavyHiggsTag, "HeavyHiggsTag");
    AddSpectator(branch_.HeavyHiggsMass, "HeavyHiggsMass");
}

int heavyhiggs::ChargedHiggsLeptonicTagger::Train(analysis::Event &event, const Object::Tag tag)
{
    Print(kInformation, "Higgs Tags");
    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);

    std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);
    Print(kInformation, "Number of doublets", doublets.size());

    std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & Jet : jets)  {
            if (doublet.SingletJet1() == Jet) continue;
            analysis::Triplet triplet(doublet, Jet);
//             triplet.SetTag(GetTag(triplet));
            if (triplet.Tag() != tag) continue;
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartet(quartet, MissingEt, Neutrinos, Tag);
//             for (auto & quartet : Prequartets) {
                triplets.emplace_back(triplet);
//             }
        }
    }
    Print(kInformation, "Numeber of triplets", triplets.size());


    if (tag == kSignal && triplets.size() > 1) {
        Print(kError, "Higgs Candidates", triplets.size());
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    return SaveEntries<ChargedHiggsLeptonicBranch>(triplets);
}

std::vector<analysis::Triplet>  heavyhiggs::ChargedHiggsLeptonicTagger::Multiplets(analysis::Event& event, const TMVA::Reader& reader)
{
  Print(kInformation, "Bdt");
  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
  std::vector<analysis::Doublet> doublets = top_leptonic_reader_.Multiplets<analysis::TopLeptonicTagger>(event);

  std::vector<analysis::Triplet> triplets;
    for (const auto & doublet : doublets) {
        for (const auto & jet : jets)  {
            if (doublet.SingletJet1() == jet) continue;
            analysis::Triplet triplet(doublet, jet);
//             triplet.SetTag(GetTag(triplet));
//             std::vector<Quartet31> Prequartets;
//             Prequartets = Getquartets(quartet, MissingEt);
//             for (auto & quartet : Prequartets) {
                branch_ = branch<ChargedHiggsLeptonicBranch>(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
//             }
        }
    }
    return ReduceResult(triplets);
}
