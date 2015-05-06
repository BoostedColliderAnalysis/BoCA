# ifndef HEventBottomTagger_hh
# define HEventBottomTagger_hh

# include "HBottomTagger.hh"
# include "HTag.hh"

namespace hbottomsumtagger
{

class HEventBottomMultiplet : public hanalysis::HTag
{
public:

//     float Bdt() const {
//       float bdt =0;
//       for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
//       return bdt;
//     }


    inline float TotalBottomBdt(const unsigned Number) const {
        if (JetsM.size() < Number) return 0;
        return JetsM.at(Number - 1).user_info<hanalysis::HJetInfo>().Bdt();
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

    void SetJets(const HJets &NewJets) {
        JetsM = NewJets;
        float bdt = 0;
        for (int i = 1; i < 6; ++i) bdt += TotalBottomBdt(i);
        SetBdt(bdt);
    }

private:

    HJets JetsM;

};


/**
 *
 * @brief Event BDT for semi leptonic heavy higgs
 *
 */
class HEventBottomTagger : public hanalysis::Tagger
{

public:

    /**
    * @brief Constructor
    *
    */
    HEventBottomTagger();

    bool TruthLevelCheck(const HJets &NewJets, hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    void SetTagger(const hanalysis::HBottomTagger &NewBottomTagger);

    std::vector<HEventBottomTaggerBranch> GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);

    std::vector<HEventBottomMultiplet> GetBdt(const HJets &Jets, const hanalysis::Reader &EventSemiReader);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile);

    float ReadBdt(const TClonesArray &EventClonesArray, const int Entry);

    HEventBottomTaggerBranch GetBranch(const hbottomsumtagger::HEventBottomMultiplet &Event) const;

    hanalysis::HBottomTagger BottomTagger;

    hanalysis::Reader BottomReader;


protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HHEventBottomTagger";
    }

private:

    void DefineVariables();

//     std::vector<HOctet> GetHeavyHiggsEvents(HJets &Jets);

    HEventBottomTaggerBranch Branch;
    hanalysis::HJetTag JetTag;

};
}
# endif
