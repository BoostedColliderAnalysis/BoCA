# ifndef HHeavyHiggsEvent_hh
# define HHeavyHiggsEvent_hh

# include "HObject.hh"

/**
 * @brief An octet composed of a sextet an a doublet
 *
 */
class HHeavyHiggsEvent : public hanalysis::HObject
{

public:

    HHeavyHiggsEvent();

    inline void SetScalarHt(const float NewScalarHt) {
        ScalarHt = NewScalarHt;
    }

    inline float GetScalarHt() const {
        return ScalarHt;
    }

    inline void SetJetNumber(const int NewJetNumber) {
        JetNumber = NewJetNumber;
    }

    inline int GetJetNumber()const {
        return JetNumber;
    }

    inline void SetBottomNumber(const int NewBottomNumber) {
        BottomNumber = NewBottomNumber;
    }

    inline int GetBottomNumber()const {
        return BottomNumber;
    }

    inline void SetLeptonNumber(const int NewLeptonNumber) {
        LeptonNumber = NewLeptonNumber;
    }

    inline int GetLeptonNumber()const {
        return LeptonNumber;
    }

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

protected:

    virtual inline std::string ClassName() const {
        return "HHeavyHiggsEvent";
    }

private:

    int LeptonNumber = 0;
    int JetNumber = 0;
    int BottomNumber = 0;
    float ScalarHt = 0;

};

#endif
