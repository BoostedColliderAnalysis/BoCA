# ifndef HTopLeptonicTagger_hh
# define HTopLeptonicTagger_hh

# include "BottomTagger.hh"
# include "Doublet.hh"
# include "Reader.hh"

/**
 * @brief Top leptonic BDT tagger
 *
 */
class analysis::HTopLeptonicTagger : public Tagger
{

public:

    HTopLeptonicTagger();

    HTopLeptonicTagger(const BottomTagger &NewBottomTagger);

    ~HTopLeptonicTagger();

    std::vector< HTopLeptonicBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< Doublet> GetBdt(const Jets &jets, Jets &Leptons, const analysis::Reader & Reader);

    HTopLeptonicBranch GetBranch(const analysis::Doublet &doublet);

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

    JetTag jet_tag;

};

#endif
