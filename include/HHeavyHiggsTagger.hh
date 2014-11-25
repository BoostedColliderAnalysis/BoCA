# ifndef HHeavyHiggsTagger_hh
# define HHeavyHiggsTagger_hh

# include "HMva.hh"
# include "HBranch.hh"
# include "HEvent.hh"
# include "HJetTag.hh"
# include "HReader.hh"
// # include "HBottomTagger.hh"
# include "HLeptonicTopTagger.hh"
# include "HSuperStructure.hh"

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HHeavyHiggsTagger : public hmva::HMva
{

public:

    HHeavyHiggsTagger();

    ~HHeavyHiggsTagger();

    std::vector<HHeavyHiggsBranch*> GetHeavyHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, hdelphes::HLeptonicTopTagger *TopTagger);

    HReaderStruct CutLoop(const ExRootTreeReader * const, HReaderStruct&){ HReaderStruct ReaderStruct; return ReaderStruct;};

    void ApplyBdt(const ExRootTreeReader * const, const std::string, const TFile * const, TMVA::Reader *){};

    float GetBdt(TObject *Branch, TMVA::Reader *Reader);

    //     std::vector<HLeptonicTopBranch *> GetBottomTag(hanalysis::HEvent *const Event, const HState State);


//     template<typename TMva>
    void SetMva() {

        Print(HNotification,"Set Mva");

        Reader = new hmva::HReader(this);
        Reader->AddVariable();
        Reader->BookMVA();

    }

    float GetHeavyHiggsBdt(const hdelphes::HSuperStructure &Higgs);

private:

    hmva::HReader *Reader;

    HHeavyHiggsBranch *HeavyHiggs;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    void FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHeavyHiggsBranch *HeavyHiggsTagger);

//     float GetDeltaR(const fastjet::PseudoJet &Jet);


    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTagger";
    };

};

#endif
