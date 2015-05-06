# ifndef HWSemiTagger_hh
# define HWSemiTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HWSemiTagger : public Tagger
{

public:

    HWSemiTagger();

    void SetTagger();

    std::vector<HWSemiBranch> GetBranches(HEvent &Event, const HObject::Tag State);

    std::vector<HDoublet>  GetBdt(const HJets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::Reader &reader);

    HWSemiBranch GetBranch(const hanalysis::HDoublet& Triplet) const;



    int GetWSemiId(hanalysis::HEvent &Event) {
      return GetWSemiId(GetWDaughters(Event));
    };

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    };

private:

    HJets GetWDaughters(hanalysis::HEvent &Event);

    int GetWSemiId(const HJets &Jets);

    void DefineVariables();


    Tag GetTag(const hanalysis::HDoublet& Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet& Doublet)const;

    std::vector<hanalysis::HDoublet> GetNeutrino(const HDoublet &Doublet, const HJets &Neutrinos, const Tag Tag)const;
    std::vector<hanalysis::HDoublet> GetDoublets(const hanalysis::HDoublet &Doublet, const HJets &Neutrinos, const hanalysis::HObject::Tag Tag);


    HWSemiBranch Branch;

    HJetTag JetTag;

    float WMassWindow;

};

#endif
