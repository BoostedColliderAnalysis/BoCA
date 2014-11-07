# ifndef HSuperStructure_hh
# define HSuperStructure_hh

# include "HObject.hh"

class hanalysis::HSuperStructure : public hanalysis::HObject
{

public:

    HSuperStructure();

    void operator=(const HSuperStructure &other);

    ~HSuperStructure();

    inline float InvMass() const {
        return (Jet1 + Jet2).m();
    };

    inline float HiggsDistance() const {
        return GetDeltaM(HiggsMass);
    };

    inline float GetDeltaM(const int ParticleMass) const {
        return abs(InvMass() - ParticleMass);
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

protected:

    PseudoJet Jet1;

    PseudoJet Jet2;

    int Position1;

    int Position2;

    virtual inline string ClassName() const {

        return ("HSuperStructure");

    };

private:

    inline float GetAngle1() const {

        return (atan2(Jet2.delta_phi_to(Jet1), Jet1.rap() - Jet2.rap()));

    };

    inline float GetAngle2() const {

        return (atan2(Jet1.delta_phi_to(Jet2), Jet2.rap() - Jet1.rap()));

    };

    float GetPull(const PseudoJet &CandidateJet) const;

};











// # include "fastjet/tools/Filter.hh"
//
// # include "HFourVector.hh"
//
// using std::min;
// using std::vector;
//
// using TMath::Pi;
//
// using fastjet::SelectorNHardest;
// using fastjet::antikt_algorithm;
// using fastjet::JetDefinition;
// using fastjet::Selector;
// using fastjet::Filter;
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
