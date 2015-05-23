# ifndef HLeptoniceventTagger_hh
# define HLeptoniceventTagger_hh

# include "BranchHeavyHiggs.hh"
# include "HChargedHiggsLeptonicTagger.hh"
# include "Octet44.hh"
# include "Sextet.hh"
# include "WIMPMASS.h"

/**
 *
 * @brief event BDT Tagger for leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedLeptonicTagger : public analysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedLeptonicTagger(analysis::BottomTagger *const NewBottomTagger, analysis::HTopLeptonicTagger *const NewTopTagger, analysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger);

    HChargedLeptonicTagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedLeptonicTagger();

    std::vector<hheavyhiggs::HChargedLeptonicBranch *> GetBranches(analysis::Event &event, const analysis::Object::Tag Tag);

    std::vector< int > ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader);

    void FillBranch(const Octet44 &octet);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    };

    virtual inline std::string ClassName() const {
        return "HChargedLeptonicTagger";
    };


private:

  void SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet);

  inline fastjet::PseudoJet GetJet(const double Momentum[4]) const {
    // wimpmass (E,px,py,pz)
    // fastjet (px,py,pz,E)
    fastjet::PseudoJet Jet(Momentum[1], Momentum[2], Momentum[3], Momentum[0]);
    return Jet;
  }

  event22 Structure;

    void DefineVariables();

    void FillBranch(hheavyhiggs::HChargedLeptonicBranch *eventLeptonicBranch, const Octet44 &octet);

    std::vector<Octet44> GetHeavyHiggsevents(const Jets &jets, const Jets &Leptons);

    std::vector<hheavyhiggs::HOctet44> GetOctets(const analysis::Sextet &sextet, const fastjet::PseudoJet &MissingEt);

    Octet44 GetOctet(analysis::Sextet sextet, fastjet::PseudoJet MissingEt, const Jets &Neutrinos, const analysis::Object::Tag Tag);

    analysis::BottomTagger *BottomTagger;

    analysis::HTopLeptonicTagger *TopLeptonicTagger;

    analysis::HChargedHiggsLeptonicTagger *ChargedHiggsLeptonicTagger;

    analysis::Reader BottomReader;

    analysis::Reader TopLeptonicReader;

    analysis::Reader ChargedHiggsLeptonicReader;

    hheavyhiggs::HChargedLeptonicBranch Branch;

};

# endif
