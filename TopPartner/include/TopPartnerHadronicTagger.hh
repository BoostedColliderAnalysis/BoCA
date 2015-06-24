# pragma once

# include "Quintet.hh"
# include "TopHadronicTagger.hh"
# include "ZHadronicTagger.hh"
# include "BranchesTopPartner.hh"

namespace analysis
{

namespace toppartner
{

/**
 * @brief Semi leptonic heavy higgs BDT tagger
 *
 */
class TopPartnerHadronicTagger : public BranchTagger<TopPartnerBranch>
{

public:

    TopPartnerHadronicTagger();

    int Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag);

    std::vector<Quintet> Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader);

    int GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) {
      return SaveEntries(Multiplets(event,pre_cuts, reader));
    }

    auto Multiplets(Event &event, const TMVA::Reader &reader){
      PreCuts pre_cuts;
      return Multiplets(event, pre_cuts, reader);
    }

protected:

    virtual  std::string ClassName() const {
        return "TopPartnerHadronicTagger";
    }

private:

    TopHadronicTagger top_tagger_;

    ZHadronicTagger z_hadronic_tagger;

    Reader top_reader_;

    Reader z_hadronic_reader_;
};

}

}
