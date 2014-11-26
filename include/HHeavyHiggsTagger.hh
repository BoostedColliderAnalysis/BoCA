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


class HHeavyHiggs
{

public:

    HHeavyHiggs(hdelphes::HSuperStructure NewPair1, hdelphes::HSuperStructure NewPair2) {
        Pair1 = NewPair1;
        Pair2 = NewPair2;
    };

    HHeavyHiggs(hdelphes::HSuperStructure NewPair1, hdelphes::HSuperStructure NewPair2, float NewMET) {
        Pair1 = NewPair1;
        Pair2 = NewPair2;
        MET = NewMET;
    };

    float GetDeltaR() const {
        return Pair1.GetPairJet().delta_R(Pair2.GetPairJet());
    }

    float GetInvariantMass() const {
        return GetPairJet().m();
    }

    fastjet::PseudoJet GetPairJet() const {
        return (Pair1.GetPairJet() + Pair2.GetPairJet());
    }
    
    float GetPtSum() const {
        return (Pair1.GetPtSum() + Pair2.GetPtSum());
    }

    float GetTopTag() const {
        return (Pair1.GetHeavyParticleTag() * Pair2.GetHeavyParticleTag());
    }
    
    float GetDeltaEta() const {
        return (Pair1.GetPairJet().rap() - Pair2.GetPairJet().rap());
    }
    
    float GetDeltaPhi() const {
        return (Pair1.GetPairJet().delta_phi_to(Pair2.GetPairJet()));
    }
    
    bool Tag;

private:

    hdelphes::HSuperStructure Pair1;
    hdelphes::HSuperStructure Pair2;
    float MET;

};

/**
 * @brief calculation regarding leptons
 *
 */
class hdelphes::HHeavyHiggsTagger : public hmva::HMva
{

public:

    HHeavyHiggsTagger();

    ~HHeavyHiggsTagger();

    std::vector<HMvaHeavyHiggsBranch *> GetHeavyHiggsTag(hanalysis::HEvent *const Event, const hanalysis::HObject::HState State, hdelphes::HBottomTagger *BottomTagger, hdelphes::HLeptonicTopTagger *TopTagger);

    HReaderStruct CutLoop(const ExRootTreeReader *const, HReaderStruct &) {
        HReaderStruct ReaderStruct;
        return ReaderStruct;
    };

    void ApplyBdt(const ExRootTreeReader *const, const std::string, const TFile *const, TMVA::Reader *) {};

    float GetBdt(TObject *Branch, TMVA::Reader *Reader);

    //     std::vector<HLeptonicTopBranch *> GetBottomTag(hanalysis::HEvent *const Event, const HState State);


//     template<typename TMva>
    void SetMva() {

        Print(HNotification, "Set Mva");

        Reader = new hmva::HReader(this);
        Reader->AddVariable();
        Reader->BookMVA();

    }

    float GetHeavyHiggsBdt(const HHeavyHiggs &HeavyHiggsTagger);

private:

    hmva::HReader *Reader;

    HMvaHeavyHiggsBranch *HeavyHiggs;

    hanalysis::HJetTag *JetTag;

    void DefineVariables();

    void FillHeavyHiggsBranch(const HHeavyHiggs &HeavyHiggs, HMvaHeavyHiggsBranch *HeavyHiggsRoot);

//     float GetDeltaR(const fastjet::PseudoJet &Jet);


    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsTagger";
    };

};

#endif
