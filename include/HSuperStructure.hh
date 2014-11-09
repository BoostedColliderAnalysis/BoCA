# ifndef HSuperStructure_hh
# define HSuperStructure_hh

# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HObject.hh"
# include "HBranch.hh"

class hanalysis::HSuperStructure : public hanalysis::HObject
{

public:

    HSuperStructure();

//     HSuperStructure(const HSuperStructure &other);

    void operator=(const HSuperStructure &other);

    ~HSuperStructure();

    inline float GetInvariantMass() const {
        return (Jet1 + Jet2).m();
    };

    inline float GetHiggsDeltaM() const {
        return GetDeltaM(HiggsMass);
    };

    inline float GetDeltaM(const int ParticleMass) const {
        return std::abs(GetInvariantMass() - ParticleMass);
    };

    float GetPullAngle1() const;

    float GetPullAngle2() const;

    void SetJet1(const PseudoJet &NewJet) {
        Jet1 = NewJet;
    }
    void SetJet2(const PseudoJet &NewJet) {
        Jet2 = NewJet;
    }
    PseudoJet GetJet1() const {
        return Jet1;
    }
    PseudoJet GetJet2() const {
        return Jet2;
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

    bool GetConstituents(ExRootTreeBranch *const ConstituentBranch);

protected:

    PseudoJet Jet1;

    PseudoJet Jet2;

    int Position1;

    int Position2;

    virtual inline string ClassName() const {

        return ("HSuperStructure");

    };

private:

    float GetReferenceAngle(const PseudoJet &Jet, const PseudoJet &ReferenceJet) const;

    float GetPull(const PseudoJet &CandidateJet) const;

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
//     PseudoJet BottomJet;
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
//     float SubPull(const PseudoJet&, const PseudoJet&, const PseudoJet&);
//
//     /**
//      * @brief DiPolarity as defined in arXiv:1102.1012
//      *
//      * @param  PseudoJet Jet containig two subjets
//      * @return void
//      */
//     float CalculateDiPolarity(const PseudoJet&, const PseudoJet&, const PseudoJet&);
//
//     float JingDipolarity(const PseudoJet &CandidateJet);
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
