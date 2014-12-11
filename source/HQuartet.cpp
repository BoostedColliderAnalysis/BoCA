# include "HQuartet.hh"

hanalysis::HQuartet::HQuartet(const HDoublet &NewPair1, const HDoublet &NewPair2)
{
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
//     Bdt = Pair1.GetBdt() * Pair2.GetBdt();
//     Tag = Pair1.GetTag() * Pair2.GetTag();
}

hanalysis::HQuartet::HQuartet(const HDoublet &NewPair1, const HDoublet &NewPair2, const fastjet::PseudoJet &NewMet)
{
//     DebugLevel = HObject::HDebug;
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
//     Bdt = Pair1.GetBdt() * Pair2.GetBdt();
//     Tag = Pair1.GetTag() * Pair2.GetTag();
}

hanalysis::HQuartet::~HQuartet()
{

//     Print(HInformation, "Destructor");

}

void hanalysis::HQuartet::SetMomentum(double Momentum[4], const fastjet::PseudoJet &Jet)
{
    Momentum[0] = Jet.E();
    Momentum[1] = Jet.px();
    Momentum[2] = Jet.py();
    Momentum[3] = Jet.pz();
}

std::vector<hanalysis::HSextet> hanalysis::HQuartet::GetTriplePairs(const float Mass1, const float Mass2, const float Mass3)
{
    Print(HInformation, "Get Triple Pairs");

    SetMomentum(Structure.p3, Pair1.GetJet2());
    SetMomentum(Structure.p4, Pair2.GetJet2());
    SetMomentum(Structure.p5, Pair1.GetJet1());
    SetMomentum(Structure.p6, Pair2.GetJet1());
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

    std::vector<hanalysis::HSextet> TriplePairs;
    for (int SolutionNumber = 0; SolutionNumber < SolutionSum; ++SolutionNumber) {
        Print(HDebug, "Solution ", SolutionNumber);
        Print(HDebug, "Neutrino 1 (p1)" , GetJet(P1[SolutionNumber]));
        Print(HDebug, "Neutrino 2 (p2)" , GetJet(P2[SolutionNumber]));

        HTriplet Triple1(Pair1,GetJet(P1[SolutionNumber]));
        HTriplet Triple2(Pair2,GetJet(P2[SolutionNumber]));
        HSextet TriplePair(Triple1, Triple2);
        if (TriplePair.GetSextetJet().m() <= 0) continue;
//         TriplePair.SetBdt(Bdt);
        Print(HDebug,"TriplePair Bdt",TriplePair.GetBdt(),GetBdt());
        TriplePair.SetTag(Tag);
        TriplePairs.push_back(TriplePair);
        //         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
        Print(HDebug, "W masses", (GetJet(P1[SolutionNumber]) + Pair1.GetJet2()).m(), (GetJet(P2[SolutionNumber]) + Pair2.GetJet2()).m());
        Print(HDebug, "top masses", (GetJet(P1[SolutionNumber]) + Pair1.GetJet2() + Pair1.GetJet1()).m(), (GetJet(P2[SolutionNumber]) + Pair2.GetJet2() + Pair1.GetJet1()).m());
        //         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return TriplePairs;

}


std::vector<hanalysis::HSextet> hanalysis::HQuartet::GetTriplePairs()
{
    return GetTriplePairs(NeutrinoMass, WMass, TopMass);
}

struct SortByError {
    inline bool operator()(const hanalysis::HSextet &Pair1, const hanalysis::HSextet &Pair2) {
        return (Pair1.GetError() < Pair2.GetError());
    }
};


hanalysis::HSextet hanalysis::HQuartet::GetTriplePair(HJets Neutrinos)
{
    Print(HInformation, "Get Triple Pair");

    std::vector<HSextet> TriplePairs = GetTriplePairs();
    Print(HDebug, "Number Solutions", TriplePairs.size());

    if (TriplePairs.size() < 1) {
        HSextet TriplePair;
        return TriplePair;
    }

    if (Neutrinos.size() < 2) {
        Print(HError, "Neutrinos", Neutrinos.size());
        HSextet TriplePair;
        return TriplePair;
    }
    fastjet::PseudoJet NeutrinoSum = Neutrinos[0] + Neutrinos[1];
    for (const auto & Neutrino : Neutrinos) Print(HDebug, "Neutrino", Neutrino);
    Print(HDebug, "Neutrino Sum", NeutrinoSum);
    Print(HDebug, "MET", Met);
//     Met = NeutrinoSum;

    for (auto & TriplePair : TriplePairs) {
        fastjet::PseudoJet Neutrino1 = TriplePair.GetTriplet1().GetJet();
        fastjet::PseudoJet Neutrino2 = TriplePair.GetTriplet2().GetJet();

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

float hanalysis::HQuartet::GetTransverseError(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) const
{
    return (Jet1 + Jet2).m();
    return std::sqrt(std::pow(Jet1.px() - Jet2.px(), 2) + std::pow(Jet1.py() - Jet2.py(), 2));
}
