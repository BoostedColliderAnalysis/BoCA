# ifndef HSextetEvent_hh
# define HSextetEvent_hh

# include "HDoublet.hh"
# include "HSextet.hh"


struct HEventStruct {

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;
    float RestHt = 0;
    float RestM = 0;
    float RestPt = 0;
    float RestRap = 0;
    float RestPhi = 0;
    int RestBTag = 0;
    float RestBBdt = 0;
    float MaxBBdt = 0;
    float TotalBBdt = 0;
    float ThirdBBdt = 0;
    float LeptonPt = 0;

};

class HSextetEventPrivate;

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HSextetEvent : public hanalysis::HTag
{

public:

//     HSextetEvent() {};

    HSextetEvent(const hanalysis::HSextet &NewSextet);

    HSextetEvent(const hanalysis::HSextet &NewSextet, const HEventStruct &NewEventStruct);

    inline hanalysis::HSextet Sextet()const {
        return SextetM;
    }

    inline fastjet::PseudoJet SextetJet() const {
        return SextetM.Jet();
    }


    inline fastjet::PseudoJet Jet() const {
        return SextetJet();
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


protected:

    virtual inline std::string ClassName() const {
        return "HSextetEvent";
    }

private:

    hanalysis::HSextet SextetM;

};

#endif
