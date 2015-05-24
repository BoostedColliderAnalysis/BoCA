# pragma once

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

namespace analysis
{

/**
 * @brief JetPair BDT tagger
 *
 */
class JetPairTagger : public Tagger
{

public:

    JetPairTagger();

    std::vector< JetPairBranch> GetBranches(Event &, const Tag, const ParticleId) {
        Print(kError,"get branches","depreciaated");
        return std::vector< JetPairBranch> {};
    }

    int Train(Event &event, PreCuts &pre_cuts, const Tag tag);

    std::vector<Doublet> GetBdt(const Jets &jets, const Reader &JetPairReader) {
      Print(kError,"get bdt","depreciaated");
      return std::vector< Doublet> {};
    }

    std::vector<Doublet> Doublets(Event &event, const TMVA::Reader &reader);

    JetPairBranch GetBranch(const Doublet &doublet) const;

    float ReadBdt(const TClonesArray &clones_array, const int entry) {
        return static_cast<JetPairBranch &>(*clones_array.At(entry)).Bdt;
    }

protected:

    virtual inline std::string ClassName() const {
        return "JetPairTagger";
    }

private:

    int SaveEntries(const std::vector<Doublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<JetPairBranch&>(*tree_branch().NewEntry()) = GetBranch(doublet);
        return doublets.size();
    }

    void DefineVariables();

    BottomTagger bottom_tagger_;

    Reader bottom_reader_;

    JetPairBranch branch_;

};

}
