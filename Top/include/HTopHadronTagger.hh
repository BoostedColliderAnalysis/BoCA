# pragma once

# include "Triplet.hh"
# include "WHadronicTagger.hh"
# include "BranchTop.hh"
# include "TClonesArray.h"

namespace analysis
{

namespace top
{

/**
 * @brief Hadronic top BDT tagger
 *
 */
class HTopHadronTagger : public Tagger
{

public:

    HTopHadronTagger();

    void SetTagger(const BottomTagger &NewBottomTagger, const WHadronicTagger &NewWTagger);

    std::vector<HTopHadronBranch> GetBranches(Event &event, const Object::Tag Tag, float pre_cut = 0);

    std::vector<Triplet>  GetBdt(const std::vector< Doublet > &doublets, const Jets &jets, const Reader & TopHadronicReader);

    Triplet GetBdt(Triplet &triplet, const Reader &TopHadronicReader);

    std::vector<Triplet> GetBdt(const Jets &jets, const Jets &Leptons, const Reader &TopHadronicReader, WHadronicTagger &WTagger, Reader &WReader, BottomTagger &BottomTagger, Reader &BottomReader);


    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry){
//       return ((HTopHadronBranch *) eventClonesArray.At(Entry))->Bdt;
      return 1;
    }

    BottomTagger bottom_tagger_;
    WHadronicTagger WTagger;

    Reader  BottomReader;
    Reader  WReader;

    HTopHadronBranch GetBranch(const Triplet &triplet) const;

protected:

    virtual  std::string ClassName() const {
        return "HTopHadronTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const Triplet &);

    Tag GetTag(const fastjet::PseudoJet& Jet);

    void GetBottomInfo(HTopHadronBranch &top_hadronic_branch, const fastjet::PseudoJet jet) const;

    float GetDeltaR(const fastjet::PseudoJet &Jet) const;

    float GetSpread(const fastjet::PseudoJet &Jet) const;

    HTopHadronBranch Branch;
    JetTag jet_tag;

    float TopWindow ;
    float WMassWindow ;


    void NSubJettiness(Triplet& triplet);
    SubJettiness NSubJettiness(const fastjet::PseudoJet & jet);

};

}

}
