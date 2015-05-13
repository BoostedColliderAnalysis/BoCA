# ifndef EventBottomTagger_hh
# define EventBottomTagger_hh

# include "BottomTagger.hh"
# include "HTag.hh"
# include "Reader.hh"

namespace hbottomsumtagger
{

class EventBottomMultiplet : public hanalysis::HTag
{
public:

//     float Bdt() const {
//       float bdt =0;
//       for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
//       return bdt;
//     }


    inline float TotalBottomBdt(const unsigned Number) const {
        if (JetsM.size() < Number) return 0;
        return JetsM.at(Number - 1).user_info<hanalysis::JetInfo>().Bdt();
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2) const {
        return TotalBottomBdt(Number1) + TotalBottomBdt(Number2);
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2, const unsigned Number3) const {
      return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3);
    }

    inline float TotalBottomBdt(const unsigned Number1, const unsigned Number2,const unsigned Number3, const unsigned Number4) const {
      return TotalBottomBdt(Number1) + TotalBottomBdt(Number2) + TotalBottomBdt(Number3) + TotalBottomBdt(Number4);
    }

    void SetJets(const Jets &NewJets) {
        JetsM = NewJets;
        float bdt = 0;
        for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
        SetBdt(bdt);
    }

private:

    Jets JetsM;

};


/**
 *
 * @brief event BDT for semi leptonic heavy higgs
 *
 */
class EventBottomTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    EventBottomTagger();

    bool TruthLevelCheck(const Jets &NewJets, hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    void SetTagger(const hanalysis::BottomTagger &NewBottomTagger);

    std::vector<EventBottomTaggerBranch> GetBranches(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);

    std::vector<EventBottomMultiplet> GetBdt(const Jets &jets, const hanalysis::Reader &eventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &eventClonesArray, const int Entry);

    EventBottomTaggerBranch GetBranch(const hbottomsumtagger::EventBottomMultiplet &event) const;

    hanalysis::BottomTagger bottom_tagger_;

    hanalysis::Reader BottomReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HEventBottomTagger";
    }

private:

    void DefineVariables();

//     std::vector<HOctet> GetHeavyHiggsevents(Jets &jets);

    EventBottomTaggerBranch Branch;
    hanalysis::HJetTag JetTag;

};
}
# endif
