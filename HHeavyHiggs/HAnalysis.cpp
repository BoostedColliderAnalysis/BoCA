# include "HAnalysis.hh"

HAnalysis::HAnalysis()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggs";

    MvaNameVector = {"Test"};

    EventNumberMax = 100000;

    FillAnalysisVector();
           
    ClonesArrays = new HClonesArraySnowmass();

}


void HAnalysis::NewAnalysis()
{
    Print(0, "New Analysis");

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());

    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;


}

void HAnalysis::CleanAnalysis()
{
    Print(0, "Clean Analysis");

    cout << "EventCounter    " << EventCounter << endl;
    cout << "JetCounter      " << JetCounter << endl;
    cout << "DeltaEtaCounter " << DeltaEtaCounter << endl;
    cout << "BMassCounter    " << BMassCounter << endl;
    cout << "TMassCounter    " << TMassCounter << endl;

}

void HAnalysis::FillAnalysisVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    AnalysisVector.clear();
    
    AnalysisVector.push_back(new HPathFlat("Background"));
    AnalysisVector.push_back(new HPathFlat("400GeV"));
    AnalysisVector.push_back(new HPathFlat("500GeV"));
    AnalysisVector.push_back(new HPathFlat("600GeV"));
    AnalysisVector.push_back(new HPathFlat("700GeV"));
    AnalysisVector.push_back(new HPathFlat("800GeV"));
    AnalysisVector.push_back(new HPathFlat("900GeV"));
    AnalysisVector.push_back(new HPathFlat("1000GeV"));
    
      

    int AnalysisSum = AnalysisVector.size();
    Print(0, "Files prepared", AnalysisSum);

}



bool HAnalysis::Analysis()
{

    Print(1, "Analysis", AnalysisName);
    //     Event->GetLeptons();

    //     vector<PseudoJet> LeptonVector = Event->Leptons->LeptonJetVector;

    //     int LeptonSum = LeptonVector.size();
    //     if (LeptonSum < 1 ) return 0;

    ++EventCounter;

    Event->GetJets();

    vector<PseudoJet> BVector = Event->Jets->JetVector;
    int JetSum = BVector.size();
    if (JetSum > 1) {

        ++JetCounter;

        sort(BVector.begin(), BVector.end(), SortJetByEta());

        PseudoJet BMax = BVector.front();
        double EtaMax = BMax.eta();
        //         double MaxPt = BMax.pt();

        PseudoJet BMin = BVector.back();
        double EtaMin = BMin.eta();
        //         double MinPt = BMin.pt();

        PseudoJet Comb = BMax + BMin;
        double BMass = Comb.m();
        double DeltaEta = EtaMax - EtaMin;

        if (DeltaEta < 3) return 0;
        ++DeltaEtaCounter;

        if (BMass < 200) return 0;
        ++BMassCounter;

        HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

        //         HeavyHiggs->EtaMax = EtaMax;
        //         HeavyHiggs->EtaMin = EtaMin;
        //         HeavyHiggs->MaxPt = MaxPt;
        //         HeavyHiggs->MinPt = MinPt;
        HeavyHiggs->DeltaEta = DeltaEta;
        HeavyHiggs->BMass = BMass;

        if (JetSum > 3) {

            BVector.erase(BVector.begin());
            BVector.erase(BVector.end());

            PseudoJet NegJet;
            PseudoJet PosJet;

            for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

                PseudoJet Jet = BVector[JetNumber];

                if (Jet.eta() < 0) {

                    NegJet += Jet;

                } else if (Jet.eta() > 0) {

                    PosJet += Jet;

                } else {

                    cout << "perpinticular jet" << endl;

                }


            }

            PseudoJet RestJet = NegJet + PosJet;
            double TMass = RestJet.m();
            if (TMass < 400) return 0;
            ++TMassCounter;

            HeavyHiggs->TMass = TMass;

            double Phi1 = NegJet.phi_std();
            double Phi2 = PosJet.phi_std();

            double DeltaPhi = fabs(GetDeltaPhi(Phi2, Phi1));

            HeavyHiggs->DeltaPhi = DeltaPhi;

        }

        return 1;

    }

    return 0;

}
