# ifndef HSuperStructure_hh
# define HSuperStructure_hh

# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HObject.hh"
# include "HBranch.hh"

class hdelphes::HSuperStructure : public hanalysis::HObject
{

public:

    HSuperStructure();

    HSuperStructure(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2);

    ~HSuperStructure();

    inline float GetInvariantMass() const {
        return ((Jet1 + Jet2).m());
    };

    inline float GetHiggsDeltaM() const {
        return GetDeltaM(HiggsMass);
    };

    inline float GetDeltaM(const int ParticleMass) const {
        return std::abs(GetInvariantMass() - ParticleMass);
    };

    inline float GetDeltaR() const {
        return (Jet1.delta_R(Jet2));
    }

    inline float GetDeltaEta() const {
        return (std::abs(Jet1.rap() - Jet2.rap()));
    }

    inline float GetPhiDelta() const {
        return (Jet1.delta_phi_to(Jet2));
    }

    inline float GetPtSum() const {
        return (Jet1.pt() + Jet2.pt());
    }

    float GetPullAngle1() const;

    float GetPullAngle2() const;

    float GetPullAngle() const {
        return (GetPullAngle1() * GetPullAngle2());
    }

    void SetJet1(const fastjet::PseudoJet &NewJet) {
        Jet1 = NewJet;
    }
    void SetJet2(const fastjet::PseudoJet &NewJet) {
        Jet2 = NewJet;
    }
    fastjet::PseudoJet GetJet1() const {
        return Jet1;
    }
    fastjet::PseudoJet GetJet2() const {
        return Jet2;
    }

    void SetPositions(const int NewPosition1, const int NewPosition2) {
        Position1 = NewPosition1;
        Position2 = NewPosition2;
    }

    void SetPosition1(const int NewPosition) {
        Position1 = NewPosition;
    }

    void SetPosition2(const int NewPosition) {
        Position2 = NewPosition;
    }
    int GetPosition1() const {
        return Position1;
    }
    int GetPosition2() const {
        return Position2;
    }

    bool IsSamePair(const HSuperStructure &Pair) const {

        if (Pair.GetPosition1() == Position1 || Pair.GetPosition1() == Position2 || Pair.GetPosition2() == Position1 || Pair.GetPosition2() == Position2) return 1;

        return 0;

    }

    void SetBTag(const float BTag1, const float BTag2) {
        BTag = BTag1 * BTag2;
    }

    void SetBTag(const float NewBTag) {
        BTag = NewBTag;
    }

    float GetBTag() const {
        return BTag;
    }

    HVectors GetConstituents() const;

    float Tag;

protected:

    fastjet::PseudoJet Jet1;

    fastjet::PseudoJet Jet2;

    int Position1;

    int Position2;

    HVectors GetConstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const;

    virtual inline std::string ClassName() const {
        return "HSuperStructure";
    };

    virtual inline std::string NameSpaceName() const {
        return "HDelphes";
    };

private:

    float BTag;

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
