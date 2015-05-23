# ifndef HHeavyHiggsLeptonicTagger_hh
# define HHeavyHiggsLeptonicTagger_hh

# include "Quartet22.hh"
# include "Sextet.hh"
# include "HTopLeptonicTagger.hh"
# include "WIMPMASS.h"

/**
 * @brief Leptonic heavy higgs BDT tagger
 *
 */
class analysis::HHeavyHiggsLeptonicTagger : public Tagger
{

public:

    HHeavyHiggsLeptonicTagger();

    HHeavyHiggsLeptonicTagger(const analysis::BottomTagger &NewBottomTagger, const analysis::HTopLeptonicTagger &NewTopLeptonicTagger);

    ~HHeavyHiggsLeptonicTagger();

    std::vector< HHeavyHiggsLeptonicBranch > GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector<analysis::Sextet> GetBdt(const std::vector< analysis::Doublet > &doublets, const fastjet::PseudoJet &MissingEt, const analysis::Reader & Reader);

    HHeavyHiggsLeptonicBranch GetBranch(const analysis::Sextet &sextet);


protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsLeptonicTagger";
    }

private:

    void DefineVariables();

    void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);
    analysis::Object::Tag GetTag(const Quartet22 &quartet);

    inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
        // wimpmass (E,px,py,pz)
        // fastjet (px,py,pz,E)
        fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
        return Jet;
    }

    std::vector< Sextet > Getsextet(const analysis::Quartet22 &quartet, const fastjet::PseudoJet &MissingEt, const Jets &Neutrinos, const analysis::Object::Tag Tag);

    std::vector<Sextet> Getsextets(const analysis::Quartet22 &quartet, const fastjet::PseudoJet &MissingEt);

    event22 Structure;

    BottomTagger bottom_tagger_;

    HTopLeptonicTagger TopLeptonicTagger;

    Reader BottomReader;

    Reader TopLeptonicReader;

    HHeavyHiggsLeptonicBranch Branch;

    JetTag jet_tag;

};

#endif
