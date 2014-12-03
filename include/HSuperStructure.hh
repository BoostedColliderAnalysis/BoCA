# ifndef HSuperStructure_hh
# define HSuperStructure_hh

# include "HPair.hh"
# include "HJetInfo.hh"

class HKinematics
{

public:

    HKinematics(const float NewPt, const float NewRap, const float NewPhi) {
        Pt = NewPt;
        Rap = NewRap;
        Phi = NewPhi;
    }

    float GetPt() const {
        return Pt;
    }
    float GetRap() const {
        return Rap;
    }
    float GetPhi() const {
        return Phi;
    }

private:

    float Pt;
    float Rap;
    float Phi;
};

class hanalysis::HSuperStructure : public hanalysis::HPair
{

public:

    HSuperStructure();

    HSuperStructure(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

    ~HSuperStructure();

    float GetPullAngle1() const;

    float GetPullAngle2() const;

    float GetPullAngle() const {
        return (GetPullAngle1() * GetPullAngle2());
    }

//     void SetJet1(const fastjet::PseudoJet &NewJet) {
//         Jet1 = NewJet;
//     }
//     void SetJet2(const fastjet::PseudoJet &NewJet) {
//         Jet2 = NewJet;
//     }

//     fastjet::PseudoJet GetJet1() const {
//         return Jet1;
//     }

//     fastjet::PseudoJet GetJet2() const {
//         return Jet2;
//     }

    float GetBdt() const {
        return (Jet1.user_info<hanalysis::HJetInfo>().GetBdt() * Jet2.user_info<hanalysis::HJetInfo>().GetBdt());
    }

//     float GetTag() const {
//         return (Jet1.user_info<hanalysis::HJetInfo>().GetTag() * Jet2.user_info<hanalysis::HJetInfo>().GetTag());
//     }

    std::vector< HKinematics > GetConstituents() const;

protected:


    std::vector< HKinematics > GetConstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const;

    virtual inline std::string ClassName() const {
        return "HSuperStructure";
    };

    virtual inline std::string NameSpaceName() const {
        return "hdephes";
    };

private:

    float GetReferenceAngle(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &ReferenceJet) const;

    float GetPull(const fastjet::PseudoJet &CandidateJet) const;

};




















// # include "fastjet/tools/Filter.hh"
//
// # include "HFourVector.hh"
//
// /**
//  * @brief Calculates the pull to each Bottom
//  *
//  */
// class hanalysis::HPull : public HFourVector
// {
//
// public:
//
//     /**
//      * @brief LorentzVector of the Bottom
//      *
//      */
//     TLorentzVector BottomLorentzVector;
//
//     /**
//      * @brief Pseudo Jet of Bottoms
//      *
//      */
//     fastjet::PseudoJet BottomJet;
//
//     /**
//      * @brief angle of the Pull Variable
//      *
//      */
//     float PullAngle(float, float);
//
//     /**
//      * @brief Pull calculation as definied in arXiv:1001.5027
//      *
//      * @param Jet
//      */
//     void BTagCalculation(const Jet&);
//
//     /**
//      * @brief Pull calculation as definied in arXiv:1001.5027
//      *
//      * @param Jet
//      */
//     float SubPull(const fastjet::PseudoJet&, const fastjet::PseudoJet&, const fastjet::PseudoJet&);
//
//     /**
//      * @brief DiPolarity as defined in arXiv:1102.1012
//      *
//      * @param  fastjet::PseudoJet Jet containig two subjets
//      * @return void
//      */
//     float CalculateDiPolarity(const fastjet::PseudoJet&, const fastjet::PseudoJet&, const fastjet::PseudoJet&);
//
//     float JingDipolarity(const fastjet::PseudoJet &CandidateJet);
//
// //     float DiPolarity;
//
//     /**
//      * @brief constructor
//      *
//      */
//     HPull();
//
//     /**
//      * @brief destructor
//      *
//      */
//     ~HPull();
//
// private:
//
//     int InitialValue;
//
//     /**
//      * @brief Phi component of the pull variable
//      *
//      */
//     float PullPhi;
//
//     /**
//      * @brief Y component of the pull variable
//      *
//      */
//     float PullRap;
//
//     float ConfineAngle(float);
// };

#endif
