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

    AddVariable(branch().HeavyHiggsPt, "HeavyHiggsPt");

    AddVariable(branch().TopDeltaR, "TopDeltaR");
    AddVariable(branch().TopDeltaRap, "TopDeltaRap");
    AddVariable(branch().TopDeltaPhi, "TopDeltaPhi");

//     AddVariable(branch().LargerWDeltaR, "LargerWDeltaR");
//     AddVariable(branch().LargerWDeltaRap, "LargerWDeltaRap");
//     AddVariable(branch().LargerWDeltaPhi, "LargerWDeltaPhi");
//
//     AddVariable(branch().SmallerWDeltaR, "SmallerWDeltaR");
//     AddVariable(branch().SmallerWDeltaRap, "SmallerWDeltaRap");
//     AddVariable(branch().SmallerWDeltaPhi, "SmallerWDeltaPhi");
//
//     AddVariable(branch().LargerNeutrinoDeltaR, "LargerNeutrinoDeltaR");
//     AddVariable(branch().LargerNeutrinoDeltaRap, "LargerNeutrinoDeltaRap");
//     AddVariable(branch().LargerNeutrinoDeltaPhi, "LargerNeutrinoDeltaPhi");
//
//     AddVariable(branch().SmallerNeutrinoDeltaR, "SmallerNeutrinoDeltaR");
//     AddVariable(branch().SmallerNeutrinoDeltaRap, "SmallerNeutrinoDeltaRap");
//     AddVariable(branch().SmallerNeutrinoDeltaPhi, "SmallerNeutrinoDeltaPhi");

    AddVariable(branch().TopBdt, "TopBdt");

    AddSpectator(branch().HeavyHiggsTag, "HeavyHiggsTag");
    AddSpectator(branch().HeavyHiggsMass, "HeavyHiggsMass");
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

    return SaveEntries(triplets);
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
            triplet.SetBdt(Bdt(triplet,reader));
                triplets.emplace_back(triplet);
//             }
        }
    }
    return ReduceResult(triplets);
}
