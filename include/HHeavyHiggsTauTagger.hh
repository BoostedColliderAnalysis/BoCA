# ifndef HHeavyHiggsTauTagger_hh
# define HHeavyHiggsTauTagger_hh

# include "HDoublet.hh"
# include "HTauTagger.hh"

/**
 * @brief Semi leptonic top BDT tagger
 *
 */
class hanalysis::HHeavyHiggsTauTagger : public HMva
{

public:

    HHeavyHiggsTauTagger();

    ~HHeavyHiggsTauTagger();

    void SetTagger(const HTauTagger &NewTauTagger);

    std::vector<HHeavyHiggsTauBranch> GetBranches(HEvent *const Event, const HObject::HTag State);

    std::vector<HDoublet>  GetBdt(const HJets &Jets, const fastjet::PseudoJet &MissingEt, const hanalysis::HReader &Reader);

    HHeavyHiggsTauBranch GetBranch(const hanalysis::HDoublet& Doublet) const;

    HTauTagger TauTagger;

    HReader TauReader;

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTauTagger";
    };

private:

    void DefineVariables();

    HTag GetTag(const hanalysis::HDoublet& Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet& Doublet)const;

    std::vector<hanalysis::HDoublet> GetNeutrino(const HDoublet &Doublet, const HJets &Neutrinos, const HTag Tag)const;

    std::vector<hanalysis::HDoublet> GetDoublets(const hanalysis::HDoublet &Doublet, const HJets &Neutrinos, const hanalysis::HObject::HTag Tag);

    HHeavyHiggsTauBranch Branch;

    HJetTag JetTag;

//     float WMassWindow;

};

#endif
