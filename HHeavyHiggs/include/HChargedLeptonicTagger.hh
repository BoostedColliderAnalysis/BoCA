# ifndef HLeptonicEventTagger_hh
# define HLeptonicEventTagger_hh

# include "HBranchHeavyHiggs.hh"
# include "HChargedHiggsLeptonicTagger.hh"
# include "HOctet44.hh"
# include "HSextet.hh"
# include "WIMPMASS.h"

/**
 *
 * @brief Event BDT Tagger for leptonic heavy higgs
 *
 */
class hheavyhiggs::HChargedLeptonicTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HChargedLeptonicTagger(hanalysis::HBottomTagger *const NewBottomTagger, hanalysis::HTopLeptonicTagger *const NewTopTagger, hanalysis::HHeavyHiggsLeptonicTagger *const NewHeavyHiggsTagger);

    HChargedLeptonicTagger();

    /**
    * @brief Destructor
    *
    */
    ~HChargedLeptonicTagger();

    std::vector<hheavyhiggs::HChargedLeptonicBranch *> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector< int > ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader);

    void FillBranch(const HOctet44 &Octet);

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

    void FillBranch(hheavyhiggs::HChargedLeptonicBranch *EventLeptonicBranch, const HOctet44 &Octet);

    std::vector<HOctet44> GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons);

    std::vector<hheavyhiggs::HOctet44> GetOctets(const hanalysis::HSextet &Sextet, const fastjet::PseudoJet &MissingEt);

    HOctet44 GetOctet(hanalysis::HSextet Sextet, fastjet::PseudoJet MissingEt, const HJets &Neutrinos, const hanalysis::HObject::Tag Tag);

    hanalysis::HBottomTagger *BottomTagger;

    hanalysis::HTopLeptonicTagger *TopLeptonicTagger;

    hanalysis::HChargedHiggsLeptonicTagger *ChargedHiggsLeptonicTagger;

    hanalysis::HReader BottomReader;

    hanalysis::HReader TopLeptonicReader;

    hanalysis::HReader ChargedHiggsLeptonicReader;

    hheavyhiggs::HChargedLeptonicBranch Branch;

};

# endif
