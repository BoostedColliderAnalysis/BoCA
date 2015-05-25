# ifndef TripletJetPairTagger_hh
# define TripletJetPairTagger_hh

# include "BottomTagger.hh"
# include "Quartet31.hh"
# include "TopSemiTagger.hh"
# include "TopHadronicTagger.hh"

/**
 * @brief JetPair BDT tagger
 *
 */
class analysis::TripletJetPairTagger : public Tagger
{

public:

    TripletJetPairTagger();

    std::vector< TripletJetPairBranch> GetBranches(Event &, const Tag )
    {
        Print(kError,"get branches","depreciated");
        return std::vector< TripletJetPairBranch> {};
    }

    int Train(analysis::Event& event, const analysis::Object::Tag tag);

    std::vector< Quartet31 > GetBdt(const std::vector< analysis::Triplet > &, const Jets &, const analysis::Reader &) {
        Print(kError,"get branches","depreciated");
        return std::vector< Quartet31> {};
    }


    std::vector< Quartet31 > Quartets(Event &event, const TMVA::Reader &JetPairReader);

    TripletJetPairBranch GetBranch(const analysis::Quartet31 &quartet) const;

    BottomTagger bottom_tagger_;
    TopHadronicTagger top_hadronic_tagger;

    Reader bottom_reader_;
    Reader top_hadronic_reader_;

protected:

    virtual inline std::string ClassName() const {
        return "TripletJetPairTagger";
    }

private:

    int SaveEntries(const std::vector<Quartet31> &quartets) {
        for (const auto & quartet : quartets) static_cast<TripletJetPairBranch&>(*tree_branch().NewEntry()) = GetBranch(quartet);
        return quartets.size();
    }

    void DefineVariables();

    TripletJetPairBranch branch_;

};

#endif
