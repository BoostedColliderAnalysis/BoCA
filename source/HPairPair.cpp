# include "HPairPair.hh"

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2) {
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
}

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const fastjet::PseudoJet &NewMet) {
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
}

hanalysis::HPairPair::~HPairPair()
{

    Print(HInformation, "Destructor");

}


std::vector<hanalysis::HTriplePair> hanalysis::HPairPair::GetTriplePairs() const {
    event22 evt;
    evt.SetP5(Pair1.GetJet1());
    evt.SetP3(Pair1.GetJet2());
    evt.SetP6(Pair2.GetJet1());
    evt.SetP4(Pair2.GetJet2());
    evt.SetPMiss(Met);



//     std::cout << "Visible momenta and the missing transverse momentum:" << std::endl;
//     std::cout << "p3 = " << evt.p3[0] << "   " << evt.p3[1] << "   "
//               << evt.p3[2] << "   " << evt.p3[3] << std::endl;
//     std::cout << "p4 = " << evt.p4[0] << "   " << evt.p4[1] << "   "
//               << evt.p4[2] << "   " << evt.p4[3] << std::endl;
//     std::cout << "p5 = " << evt.p5[0] << "   " << evt.p5[1] << "   "
//               << evt.p5[2] << "   " << evt.p5[3] << std::endl;
//     std::cout << "p6 = " << evt.p6[0] << "   " << evt.p6[1] << "   "
//               << evt.p6[2] << "   " << evt.p6[3] << std::endl;
//     std::cout << "pmiss x,y = " << "   " << evt.pmiss[1] << "   " << evt.pmiss[2] << std::endl;


    int nsols;
    double p1[4][4], p2[4][4];
    evt.solve22(evt, NeutrinoMass, WMass, TopMass, nsols, p1, p2);

    std::vector<HTriplePair> TriplePairs;

    for (int isol = 0; isol < nsols; isol ++) {
//         std::cout << std::endl << "solution " << isol << std::endl;
//         std::cout << "p1 = " << p1[isol][0] << "  " << p1[isol][1] << "  " << p1[isol][2] << "  " << p1[isol][3] << std::endl;
//         std::cout << "p2 = " << p2[isol][0] << "  " << p2[isol][1] << "  " << p2[isol][2] << "  " << p2[isol][3] << std::endl;

        fastjet::PseudoJet Jet1(p1[isol][1],p1[isol][2],p1[isol][3],p1[isol][0]);
        HTriple Triple1(Jet1,Pair1);
        fastjet::PseudoJet Jet2(p1[isol][1],p1[isol][2],p1[isol][3],p1[isol][0]);
        HTriple Triple2(Jet2,Pair2);
        HTriplePair TriplePair(Triple1,Triple2);
        TriplePairs.push_back(TriplePair);

//         HPair Pair(Jet1,Jet2);
        Print(HDebug,"Neutrino masses",Jet1.m(),Jet2.m());
        Print(HDebug,"W masses",(Jet1 + Pair1.GetJet2()).m(),(Jet2 + Pair2.GetJet2() ).m());
        Print(HDebug,"top masses",(Jet1 + Pair1.GetJet2() + Pair1.GetJet1()).m(),(Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
        Print(HDebug,"Higg masses",(Jet1 + Pair1.GetJet2() + Pair1.GetJet1() + Jet2 + Pair2.GetJet2() + Pair1.GetJet1()).m());
    }

    return TriplePairs;

}



struct SortByMassDiffernece {
  inline bool operator()(const hanalysis::HTriplePair &Pair1, const hanalysis::HTriplePair &Pair2) {
    return (Pair1.GetMassDifferences(hanalysis::HObject::ElectronNeutrinoId,hanalysis::HObject::WId,hanalysis::HObject::TopId) < Pair2.GetMassDifferences(hanalysis::HObject::ElectronNeutrinoId,hanalysis::HObject::WId,hanalysis::HObject::TopId));
  }
};



hanalysis::HTriplePair hanalysis::HPairPair::GetTriplePair() const {
  
  std::vector<HTriplePair> TriplePairs = GetTriplePairs();
  
  if(TriplePairs.size()<1) {
    HTriplePair TriplePair;
    return TriplePair;
    
  }
  
  std::sort(TriplePairs.begin(),TriplePairs.end(),SortByMassDiffernece());
    
  return TriplePairs.front();
  
}
