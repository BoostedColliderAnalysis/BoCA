# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief Top leptonic BDT tagger
 *
 */
class hanalysis::HTopLeptonicTagger : public Tagger
{

public:

    HTopLeptonicTagger();

    HTopLeptonicTagger(const BottomTagger &NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector< HTopLeptonicBranch > GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    std::vector< Doublet> GetBdt(const Jets &jets, Jets &Leptons, const hanalysis::Reader & Reader);

    HTopLeptonicBranch GetBranch(const hanalysis::Doublet &doublet);

protected:

    virtual inline std::string ClassName() const {
        return "HTopLeptonicTagger";
    };

private:

    void DefineVariables();

    Tag GetTag(const Doublet &doublet);

    BottomTagger bottom_tagger_;

    Reader BottomReader;

    HTopLeptonicBranch Branch;

    HJetTag JetTag;

};

#endif
