# ifndef HWSemiTagger_hh
# define HWSemiTagger_hh

# include "HTriplet.hh"
# include "HBottomTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HWSemiTagger : public HMva
{

public:

    HWSemiTagger();

    ~HWSemiTagger();

    void SetTagger();

    std::vector<HWSemiBranch> GetBranches(HEvent *const Event, const HObject::HTag State);

    std::vector<HDoublet>  GetBdt(const HJets &Leptons, const fastjet::PseudoJet &MissingEt, const hanalysis::HReader &Reader);

    HWSemiBranch GetBranch(const hanalysis::HDoublet& Triplet) const;

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    };

private:

    void DefineVariables();


    HTag GetTag(const hanalysis::HDoublet& Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet& Doublet)const;

    std::vector<hanalysis::HDoublet> GetNeutrino(const HDoublet &Doublet, const HJets &Neutrinos, const HTag Tag)const;
    std::vector<hanalysis::HDoublet> GetDoublets(const hanalysis::HDoublet &Doublet, const HJets &Neutrinos, const hanalysis::HObject::HTag Tag);


    HWSemiBranch Branch;

    HJetTag JetTag;

    float WMassWindow;

};

#endif
