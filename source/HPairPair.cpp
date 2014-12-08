# include "HPairPair.hh"

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2)
{
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
//     Bdt = Pair1.GetBdt() * Pair2.GetBdt();
//     Tag = Pair1.GetTag() * Pair2.GetTag();
}

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const fastjet::PseudoJet &NewMet)
{
//     DebugLevel = HObject::HDebug;
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
//     Bdt = Pair1.GetBdt() * Pair2.GetBdt();
//     Tag = Pair1.GetTag() * Pair2.GetTag();
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

    Print(HDebug, "Lepton 1 (p3)", GetJet(Structure.p3));
    Print(HDebug, "Lepton 2 (p4)" , GetJet(Structure.p4));
    Print(HDebug, "Jet 1 (p5)" , GetJet(Structure.p5));
    Print(HDebug, "Jet 2 (p6)" , GetJet(Structure.p6));
    Print(HDebug, "PMiss" , GetJet(Structure.pmiss));

    double P1[4][4], P2[4][4];
    int SolutionSum;
    solve22(Structure, Mass1, Mass2, Mass3, SolutionSum, P1, P2);
    Print(HDebug, "Number solutions", SolutionSum);

    std::vector<hanalysis::HTriplePair> TriplePairs;
    for (int SolutionNumber = 0; SolutionNumber < SolutionSum; ++SolutionNumber) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        HTriple Triple1(GetJet(P1[SolutionNumber]), Pair1);
        HTriple Triple2(GetJet(P2[SolutionNumber]), Pair2);
        HTriplePair TriplePair(Triple1, Triple2);
        if (TriplePair.GetInvariantMass() <= 0) continue;
//         TriplePair.SetBdt(Bdt);
        Print(HDebug,"TriplePair Bdt",TriplePair.GetBdt(),GetBdt());
        TriplePair.SetTag(Tag);
        TriplePairs.push_back(TriplePair);
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Pair1.GetLepton()).m(), (GetJet(P2[SolutionNumber]) + Pair2.GetLepton()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Pair1.GetLepton() + Pair1.GetJet()).m(), (GetJet(P2[SolutionNumber]) + Pair2.GetLepton() + Pair1.GetJet()).m());
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

    std::vector<HTriplePair> TriplePairs = GetTriplePairs();
    Print(HDebug, "Number Solutions", TriplePairs.size());

    if (TriplePairs.size() < 1) {
        HTriplePair TriplePair;
        return TriplePair;
    }

    if (Neutrinos.size() < 2) {
        Print(HError, "Neutrinos", Neutrinos.size());
        HTriplePair TriplePair;
        return TriplePair;
    }
    fastjet::PseudoJet NeutrinoSum = Neutrinos[0] + Neutrinos[1];
    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
    Print(HDebug, "Neutrino Sum", NeutrinoSum);
    Print(HDebug, "MET", Met);
//     Met = NeutrinoSum;

    for (auto & TriplePair : TriplePairs) {
        fastjet::PseudoJet Neutrino1 = TriplePair.GetTriple1().GetJet1();
        fastjet::PseudoJet Neutrino2 = TriplePair.GetTriple2().GetJet1();

        std::vector<float> Error1, Error2;
        for (const auto & Neutrino : Neutrinos) {
//             Print(HError, "Neutrino Mass", Neutrino.m());
            Error1.push_back(GetTransverseError(Neutrino, Neutrino1));
            Print(HDebug, "Neutrino 1 Error", GetTransverseError(Neutrino, Neutrino1));
            Error2.push_back(GetTransverseError(Neutrino, Neutrino2));
            Print(HDebug, "Neutrino 2 Error", GetTransverseError(Neutrino, Neutrino2));
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
        Print(HDebug,"TriplePair Bdt",TriplePair.GetBdt());
    }

    std::sort(TriplePairs.begin(), TriplePairs.end(), SortByError());
    for (const auto & TriplePair : TriplePairs) Print(HDebug, "Neutrino Error Sum", TriplePair.GetError());
    return TriplePairs.front();
}

float hanalysis::HPairPair::GetTransverseError(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) const
{
    return (Jet1 + Jet2).m();
    return std::sqrt(std::pow(Jet1.px() - Jet2.px(), 2) + std::pow(Jet1.py() - Jet2.py(), 2));
}
