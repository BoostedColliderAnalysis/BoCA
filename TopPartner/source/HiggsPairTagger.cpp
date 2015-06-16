# include "HiggsPairTagger.hh"

namespace analysis
{

namespace toppartner
{

HiggsPairTagger::HiggsPairTagger()
{
//         DebugLevel = Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HiggsPairPair");
    higgs_reader_.set_tagger(higgs_tagger_);
    DefineVariables();
}

int HiggsPairTagger::Train(Event &event,  PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Higgs Tags");
    std::vector< Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Quartet22 > quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap()) continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }

    }
    return SaveEntries(quartets);
}

std::vector<Quartet22> HiggsPairTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    std::vector< Doublet> doublets = higgs_reader_.Multiplets<HiggsTagger>(event);
    std::vector< Quartet22 > quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap()) continue;
            quartet.SetBdt(Bdt(quartet,reader));
            quartets.emplace_back(quartet);
        }
    }
    return ReduceResult(quartets);
}

}

}
