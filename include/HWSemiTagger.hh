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

    std::vector<HWSemiBranch *> GetBranches(HEvent *const Event, const HObject::HTag State);

    void FillBranch(const hanalysis::HDoublet& Doublet);

    std::vector< HDoublet > GetTruthBdt(HJets& Leptons, const fastjet::PseudoJet& MissingEt, const hanalysis::HReader*const Reader);

    std::vector< HDoublet > GetBdt(HJets& Leptons, const fastjet::PseudoJet& MissingEt, const hanalysis::HReader*const Reader);


    std::vector<hanalysis::HDoublet>  GetTruthDoublets(const hanalysis::HReader* Reader, hanalysis::HEvent*const Event);

protected:

    virtual inline std::string ClassName() const {
        return "HWSemiTagger";
    };

private:

    void DefineVariables();

    void FillBranch(HWSemiBranch*const WSemiBranch, const hanalysis::HDoublet& Triplet);

    HTag GetTag(const hanalysis::HDoublet& Doublet) const;

    std::vector< HDoublet > GetNeutrinos(const hanalysis::HDoublet& Doublet)const;

//     HBottomTagger *BottomTagger;

//     HReader *BottomReader;

    HWSemiBranch *Branch;

    HJetTag *JetTag;

};

#endif
