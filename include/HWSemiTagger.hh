# pragma once

# include "Doublet.hh"
# include "Tagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HWSemiTagger : public Tagger
{

public:

    HWSemiTagger();

    WSemiBranch GetBranch(const hanalysis::Doublet &doublet) const;

    int Train(hanalysis::Event &event, const hanalysis::HObject::Tag tag);

    std::vector<Doublet> GetDoublets(Event &event, const TMVA::Reader &reader);

    int GetBdt(hanalysis::Event &event, const TMVA::Reader &reader) {
        std::vector<Doublet> doublets = GetDoublets(event, reader);
        SaveEntries(doublets);
        return doublets.size();
    }

    std::vector<hanalysis::Doublet> GetBdt(const Jets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &reader) {
      Print(kError,"get bdt", "depreciated");
    }

    std::vector<Doublet>  GetBdt(const Jets &Leptons, const fastjet::PseudoJet &MissingEt, const TMVA::Reader &reader){
      Print(kError,"get bdt", "depreciated");
    }

    void SaveEntries(const std::vector<Doublet> &doublets) {
        for (const auto & doublet : doublets) static_cast<WSemiBranch &>(*tree_branch().NewEntry()) = GetBranch(doublet);
    }

    int WSemiId(hanalysis::Event &event) {
        return WSemiId(WSemiDaughters(event));
    }

    TClass &Class() const {
      return *WSemiBranch::Class();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    }

private:

    Jets WSemiDaughters(hanalysis::Event &event);

    int WSemiId(const Jets &jets);

    void DefineVariables();

    Tag GetTag(const hanalysis::Doublet &doublet) const;

    std::vector< Doublet > GetNeutrinos(const hanalysis::Doublet &doublet)const;

    std::vector<hanalysis::Doublet> GetNeutrino(const Doublet &doublet, const Jets &Neutrinos, const Tag Tag)const;

//     std::vector<hanalysis::Doublet> GetDoublets(const hanalysis::Doublet &doublet, const Jets &Neutrinos, const hanalysis::HObject::Tag Tag);

    WSemiBranch branch_;

    float w_mass_window_;

};

