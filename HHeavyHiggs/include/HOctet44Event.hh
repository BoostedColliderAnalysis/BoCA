# ifndef HEventMultiplet_hh
# define HEventMultiplet_hh

# include "HOctet44.hh"
// # include "HOctet.hh"

struct HEventStruct {

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;

};


/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
template <typename TMultiplet>
class HEventMultiplet : public hanalysis::HTag
{

public:

  HEventMultiplet(const TMultiplet &NewOctet){
    Octet44M = NewOctet;
    SetBdt(Octet44M.Bdt());
    SetTag(Octet44M.Tag());

  };

  HEventMultiplet(const TMultiplet &NewOctet, const HEventStruct &NewEventStruct){
    Octet44M = NewOctet;
    EventM = NewEventStruct;
    SetBdt(Octet44M.Bdt());
    SetTag(Octet44M.Tag());
  };

  inline TMultiplet Octet()const {
        return Octet44M;
    }

    inline fastjet::PseudoJet OctetJet() const {
        return Octet44M.Jet();
    }

    inline fastjet::PseudoJet Jet() const {
        return OctetJet() + RestJet();
    }

    inline float Ht() const {
        float ht = Octet().Ht();
        for (const auto & jet : Jets) ht += jet.pt();
        return ht;
    }

    inline void SetScalarHt(const float NewScalarHt) {
        EventM.ScalarHt = NewScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        EventM.JetNumber = NewJetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        EventM.BottomNumber = NewBottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        EventM.LeptonNumber = NewLeptonNumber;
    }

    inline float ScalarHt() const {
        return EventM.ScalarHt;
    }

    inline int JetNumber()const {
        return EventM.JetNumber;
    }

    inline int BottomNumber()const {
        return EventM.BottomNumber;
    }

    inline int LeptonNumber()const {
        return EventM.LeptonNumber;
    }

    inline HEventStruct EventStruct()const {
        return EventM;
    }

    inline void SetEventStruct(const HEventStruct &NewEventStruct) {
        EventM = NewEventStruct;
    }

    HEventStruct EventM;

    inline void AddRestJet(const fastjet::PseudoJet &NewJet) {
        BdtM *= JetNumber() + 1;
        Jets.push_back(NewJet);
        BdtM += NewJet.user_info<hanalysis::HJetInfo>().Bdt();
        BdtM /= JetNumber() + 1;
    }

    inline int RestNumber() const {
        return Jets.size();
    }

    fastjet::PseudoJet RestJet() const {
        fastjet::PseudoJet jet;
        return std::accumulate(Jets.begin(), Jets.end(), jet);
    }

    float RestHt() const {
        float ht = 0;
        for (const auto & jet : Jets)ht += jet.pt();
        return ht;
    }

    float RestBdt() const {
        if (RestNumber() < 1) return 0;
        float bdt = 0;
        for (const auto & jet : Jets)bdt += jet.user_info<hanalysis::HJetInfo>().Bdt();
        return bdt / RestNumber();
    }

    void SetLeptons(const HJets &NewLeptons) {
        LeptonsM = NewLeptons;
    }

    float LeptonHt() const {
        float ht = 0;
        for (const auto & jet : LeptonsM)ht += jet.pt();
        return ht;
    }

    float DeltaPt() const {
        return OctetJet().pt() - RestJet().pt();
    }

    float DeltaPhi() const {
        return OctetJet().delta_phi_to(RestJet());
    }

    float DeltaRap() const {
        float NewDeltaRap = OctetJet().rap() - RestJet().rap();
        if (std::abs(NewDeltaRap) > 100) NewDeltaRap = 0;
        return NewDeltaRap;
    }

    float DeltaR() const {
        float NewDeltaR = OctetJet().delta_R(RestJet());
        if (std::abs(NewDeltaR) > 100) NewDeltaR = 0;
        return NewDeltaR;
    }


protected:

    virtual inline std::string ClassName() const {
        return "HEventMultiplet";
    }

private:

    TMultiplet Octet44M;

    HJets Jets;

    HJets LeptonsM;

};

#endif
