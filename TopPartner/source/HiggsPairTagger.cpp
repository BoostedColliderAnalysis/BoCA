#include "HiggsPairTagger.hh"
#include "Debug.hh"

namespace analysis {

namespace toppartner {

HiggsPairTagger::HiggsPairTagger()
{
    Note();
    DefineVariables();
}

int HiggsPairTagger::Train(const Event& event, PreCuts& pre_cuts, const Tag tag) const
{
    Info("Higgs Tags");
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Quartet22> quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap())
                continue;
            quartet.SetTag(tag);
            quartets.emplace_back(quartet);
        }
    }
    return SaveEntries(quartets);
}

std::vector<Quartet22> HiggsPairTagger::Multiplets(const Event& event, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Quartet22> quartets;
    for (auto doublet_1 = doublets.begin(); doublet_1 != doublets.end(); ++doublet_1) {
        for (auto doublet_2 = doublet_1 + 1; doublet_2 != doublets.end(); ++doublet_2) {
            Quartet22 quartet(*doublet_1, *doublet_2);
            if (quartet.Overlap())
                continue;
            quartet.SetBdt(Bdt(quartet, reader));
            quartets.emplace_back(quartet);
        }
    }
    return ReduceResult(quartets);
}

}

}
