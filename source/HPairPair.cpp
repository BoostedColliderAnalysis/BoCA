# include "HPairPair.hh"

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2)
{
//     Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
}

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const fastjet::PseudoJet &NewMet)
{
//     DebugLevel = HObject::HDebug;
//     Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
}

hanalysis::HPairPair::~HPairPair()
{

//     Print(HInformation, "Destructor");

}

void hanalysis::HPairPair::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}

std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs(const float Mass1, const float Mass2, const float Mass3)
{
        Print(HInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Pair1.GetLepton());
    SetMomentum(Structure.p4, Pair2.GetLepton());
    SetMomentum(Structure.p5, Pair1.GetJet());
    SetMomentum(Structure.p6, Pair2.GetJet());
    SetMomentum(Structure.pmiss, Met);

    Print(HDebug, "Lepton 1 (p3)", Structure.p3[0] , Structure.p3[1] , Structure.p3[2] , Structure.p3[3]);
    Print(HDebug, "Lepton 2 (p4)" , Structure.p4[0] , Structure.p4[1] , Structure.p4[2] , Structure.p4[3]);
    Print(HDebug, "Jet 1 (p5)" , Structure.p5[0] , Structure.p5[1] , Structure.p5[2] , Structure.p5[3]);
    Print(HDebug, "Jet 2 (p6)" , Structure.p6[0] , Structure.p6[1] , Structure.p6[2] , Structure.p6[3]);
    Print(HDebug, "PMiss" , Structure.pmiss[0] , Structure.pmiss[1] , Structure.pmiss[2], Structure.pmiss[3]);

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(Structure, Mass1, Mass2, Mass3, SolutionSum, P1, P2);
    Print(HDebug, "Number solutions", SolutionSum);

    std::vector<hanalysis::HTriplePair> TriplePairs;
    for (int SolutionNumber = 0 ; SolutionNumber < SolutionSum; ++SolutionNumber) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , P1[SolutionNumber][0] , P1[SolutionNumber][1] , P1[SolutionNumber][2] , P1[SolutionNumber][3]);
        Print(HDebug, "Neutrino 2 (p2)" , P2[SolutionNumber][0] , P2[SolutionNumber][1] , P2[SolutionNumber][2] , P2[SolutionNumber][3]);

        HTriple Triple1(GetJet(P1[SolutionNumber]), Pair1);
        HTriple Triple2(GetJet(P2[SolutionNumber]), Pair2);
        HTriplePair TriplePair(Triple1, Triple2);
        TriplePairs.push_back(TriplePair);
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        //         Print(HDebug, "W masses", (Jet1 + Pair1.GetJet2()).m(), (Jet2 + Pair2.GetJet2()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Pair1.GetJet2() + Pair1.GetJet1()).m(), (GetJet(P2[SolutionNumber]) + Pair2.GetJet2() + Pair1.GetJet1()).m());
        //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return TriplePairs;

}


std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs()
{
    return GetTriplePairs(NeutrinoMass, WMass, TopMass);
}

struct SortByError {
    inline bool operator()(const hanalysis::HTriplePair &Pair1, const hanalysis::HTriplePair &Pair2) {
        return (Pair1.GetError() < Pair2.GetError());
    }
};


hanalysis::HTriplePair hanalysis::HPairPair::GetTriplePair(HJets Neutrinos)
{
    Print(HInformation, "Get Triple Pair");
    fastjet::PseudoJet NeutrinoSum = Neutrinos[0] + Neutrinos[1];
//     Met = MET;

    std::vector<HTriplePair> TriplePairs = GetTriplePairs();
    Print(HDebug, "Number Solutions", TriplePairs.size());

    if (TriplePairs.size() < 1) {
        HTriplePair TriplePair;
        return TriplePair;
    }

    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino.E(), Neutrino.px(), Neutrino.py(), Neutrino.px());

    Print(HDebug, "Neutrino Sum", NeutrinoSum);

    for (auto & TriplePair : TriplePairs) {
        fastjet::PseudoJet Neutrino1 = TriplePair.GetTriple1().GetJet1();
        fastjet::PseudoJet Neutrino2 = TriplePair.GetTriple2().GetJet1();

        std::vector<float> Error1, Error2;
        for (const auto & Neutrino : Neutrinos) {
//             Print(HError, "Neutrino Mass", Neutrino.m());
            Error1.push_back(GetTransverseError(Neutrino,Neutrino1));
            Print(HDebug, "Neutrino 1 Error", GetTransverseError(Neutrino,Neutrino1));
            Error2.push_back(GetTransverseError(Neutrino,Neutrino2));
            Print(HDebug, "Neutrino 2 Error", GetTransverseError(Neutrino,Neutrino2));
        }

        float Error = LargeNumber;
        for (size_t i = 0; i < Error1.size(); ++i) {
            for (size_t j = i + 1; j < Error2.size(); ++j) {
                if (Error1[i] + Error2[j] < Error) Error = Error1[i] + Error2[j];
            }
        }
        for (size_t j = 0; j < Error2.size(); ++j) {
            for (size_t i = j + 1; i < Error1.size(); ++i) {
                if (Error1[i] + Error2[j] < Error) Error = Error1[i] + Error2[j];
            }
        }
        TriplePair.SetError(Error);
    }

    std::sort(TriplePairs.begin(), TriplePairs.end(), SortByError());

    for (const auto & TriplePair : TriplePairs) Print(HDebug, "Neutrino Error Sum", TriplePair.GetError());

    return TriplePairs.front();

}

float hanalysis::HPairPair::GetTransverseError(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) const {
    return std::sqrt(std::pow(Jet1.px() - Jet2.px(),2) + std::pow(Jet1.py() - Jet2.py(),2));
}
