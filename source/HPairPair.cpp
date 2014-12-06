# include "HPairPair.hh"

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2)
{
//     Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
}

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const fastjet::PseudoJet &NewMet)
{
    DebugLevel = HObject::HDebug;
//     Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
}

hanalysis::HPairPair::~HPairPair()
{

//     Print(HInformation, "Destructor");

}

void hanalysis::HPairPair::SetMomentum(double p3[4], const fastjet::PseudoJet &Jet)
{
  p3[0] = Jet.E();
  p3[1] = Jet.px();
  p3[2] = Jet.py();
  p3[3] = Jet.pz();
}

std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs(float Mass1, float Mass2, float Mass3)
{

  SetMomentum(Structure.p3, Pair1.GetJet());
  SetMomentum(Structure.p4, Pair1.GetLepton());
  SetMomentum(Structure.p5, Pair2.GetJet());
  SetMomentum(Structure.p6, Pair2.GetLepton());
  SetMomentum(Structure.pmiss, Met);

  double p1[4][4], p2[4][4];
  int nsols;
//   solve22(Structure, Mass1, Mass2, Mass3, nsols, p1, p2);

  std::vector<hanalysis::HTriplePair> TriplePairs;
  for (int i = 0 ; i < nsols; ++i) {
    hanalysis::HTriple Triple1(GetJet(p1[i]), Pair1);
    hanalysis::HTriple Triple2(GetJet(p2[i]), Pair2);
    hanalysis::HTriplePair TriplePair(Triple1, Triple2);
    TriplePairs.push_back(TriplePair);
  }

  return TriplePairs;

}




















std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs() const
{}

std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs(HJets Neutrinos) const
{
    Print(HInformation, "Get Triple Pairs");
    event22 evt;
//     evt.SetP5(Pair1.GetJet());
//     evt.SetP3(Pair1.GetLepton());
//
//     evt.SetP6(Pair2.GetJet());
//     evt.SetP4(Pair2.GetLepton());

//     evt.SetPMiss(Met);
    fastjet::PseudoJet met;
//     evt.SetPMiss(std::accumulate(Neutrinos.begin(), Neutrinos.end(), met));

    Print(HDebug, "Lepton 1 (p3)", evt.p3[0] , evt.p3[1] , evt.p3[2] , evt.p3[3]);
    Print(HDebug, "Lepton 2 (p4)" , evt.p4[0] , evt.p4[1] , evt.p4[2] , evt.p4[3]);
    Print(HDebug, "Jet 1 (p5)" , evt.p5[0] , evt.p5[1] , evt.p5[2] , evt.p5[3]);
    Print(HDebug, "Jet 2 (p6)" , evt.p6[0] , evt.p6[1] , evt.p6[2] , evt.p6[3]);
    Print(HDebug, "PMiss" , evt.pmiss[0] , evt.pmiss[1] , evt.pmiss[2], evt.pmiss[3]);


    int nsols;
    double p1[4][4], p2[4][4];
//     solve22(evt, NeutrinoMass, WMass, TopMass, nsols, p1, p2);
    Print(HDebug, "Number solutions", nsols);

    std::vector<HTriplePair> TriplePairs;

    for (int isol = 0; isol < nsols; ++isol) {
        Print(HDebug, "solution ", isol);
        Print(HDebug, "Neutrino 1 (p1)" , p1[isol][0] , p1[isol][1] , p1[isol][2] , p1[isol][3]);
        Print(HDebug, "Neutrino 2 (p2)" , p2[isol][0] , p2[isol][1] , p2[isol][2] , p2[isol][3]);

        fastjet::PseudoJet Jet1(p1[isol][1], p1[isol][2], p1[isol][3], p1[isol][0]);
        HTriple Triple1(Jet1, Pair1);
        fastjet::PseudoJet Jet2(p2[isol][1], p2[isol][2], p2[isol][3], p2[isol][0]);
        HTriple Triple2(Jet2, Pair2);
        HTriplePair TriplePair(Triple1, Triple2);
        TriplePairs.push_back(TriplePair);

//         HPair Pair(Jet1,Jet2);
//         Print(HDebug, "Neutrino masses", Jet1.m(), Jet2.m());
//         Print(HDebug, "W masses", (Jet1 + Pair1.GetJet2()).m(), (Jet2 + Pair2.GetJet2()).m());
        Print(HDebug, "top masses", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1()).m(), (Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
//         Print(HDebug, "Higg mass", (Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return TriplePairs;

}



struct SortByMassDiffernece {
    inline bool operator()(const hanalysis::HTriplePair &Pair1, const hanalysis::HTriplePair &Pair2) {
        return (Pair1.GetMassDifferences(hanalysis::HObject::ElectronNeutrinoId, hanalysis::HObject::WId, hanalysis::HObject::TopId) < Pair2.GetMassDifferences(hanalysis::HObject::ElectronNeutrinoId, hanalysis::HObject::WId, hanalysis::HObject::TopId));
    }
};

struct SortByNeutrinoMass {
    inline bool operator()(const hanalysis::HTriplePair &Pair1, const hanalysis::HTriplePair &Pair2) {
        return (Pair1.GetMass() < Pair2.GetMass());
    }
};


// struct NeutrinoStruct{
//
//     float Mass;
//     int Pos1;
//     int Pos2;
// }

hanalysis::HTriplePair hanalysis::HPairPair::GetTriplePair(HJets Neutrinos) const
{
    Print(HError, "Get Triple Pair", Neutrinos.size());

    std::vector<HTriplePair> TriplePairs = GetTriplePairs(Neutrinos);
    Print(HError, "Number Solutions", TriplePairs.size());

    if (TriplePairs.size() < 1) {
        HTriplePair TriplePair;
        return TriplePair;
    }

    for (const auto & Neutrino : Neutrinos) Print(HDebug, "pN", Neutrino.E(), Neutrino.px(), Neutrino.py(), Neutrino.px());

    fastjet::PseudoJet MET = Neutrinos[0] + Neutrinos[1];
    Print(HDebug, "Met", MET);

    for (auto & TriplePair : TriplePairs) {
        fastjet::PseudoJet Neutrino1 = TriplePair.GetTriple1().GetJet1();
        fastjet::PseudoJet Neutrino2 = TriplePair.GetTriple2().GetJet1();
        if (Neutrino1.m() > 1) Print(HError, "Neutrino1 Mass", Neutrino1.m());
        if (Neutrino2.m() > 1) Print(HError, "Neutrino2 Mass", Neutrino2.m());

        std::vector<float> Masses1, Masses2;
        for (const auto & Neutrino : Neutrinos) {
//             Print(HError, "Neutrino Mass", Neutrino.m());
            Masses1.push_back((Neutrino + Neutrino1).m());
            Print(HError, "Neutrino 1 Error", (Neutrino + Neutrino1).m());
            Masses2.push_back((Neutrino + Neutrino2).m());
            Print(HError, "Neutrino 2 Error", (Neutrino + Neutrino2).m());
        }

        float Mass = LargeNumber;
        for (size_t i = 0; i < Masses1.size(); ++i) {
            for (size_t j = i + 1; j < Masses2.size(); ++j) {
                if (Masses1[i] + Masses2[j] < Mass) Mass = Masses1[i] + Masses2[j];
            }
        }
        for (size_t j = 0; j < Masses2.size(); ++j) {
            for (size_t i = j + 1; i < Masses1.size(); ++i) {
                if (Masses1[i] + Masses2[j] < Mass) Mass = Masses1[i] + Masses2[j];
            }
        }
        TriplePair.SetMass(Mass);
    }

    std::sort(TriplePairs.begin(), TriplePairs.end(), SortByNeutrinoMass());

    for (const auto & TriplePair : TriplePairs) Print(HError, "Neutrino Error Sum", TriplePair.GetMass());

    return TriplePairs.front();

}
