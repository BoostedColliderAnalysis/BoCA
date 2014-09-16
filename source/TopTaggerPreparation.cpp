# include "TopTaggerPreparation.hh"

taggedtopclass::taggedtopclass()
{

    
    Print(0, "Contructor");
    
    WMass = 80.39;
    TopMass = 173.5;
    
}

taggedtopclass::~taggedtopclass()
{
    
    Print(0, "Destructor");
    
}

void taggedtopclass::NewEvent(){
    
    Print(1, "New Event");
    
    TopLorentzVectorVector.clear();
    
    TopJetVector.clear();
    
    BottomJetVector.clear();
    
    FirstWJetVector.clear();
    
    SecondWJetVector.clear();
    
    NumberOfTop=0;
    
}

vector<PseudoJet> taggedtopclass::GranulateJets(vector<PseudoJet> &HadronVector, const float &CellEta, const float &CellPhi, const float &PtCutOff)
{
    
    Print(1, "Granulate Jets");
    
    HadronVector = sorted_by_pt(HadronVector);
    int HadronSum = HadronVector.size();
    if (Debug > 1) cout <<  "Number of Hadrons: " <<  HadronSum << endl;


    /// vector of containing only the hardest Jet Candidate
    vector<PseudoJet> GranulatedJetVector;
    GranulatedJetVector.clear();
    GranulatedJetVector.push_back(HadronVector[0]);
    int GranulatedJetSum = GranulatedJetVector.size();
    if (Debug > 1) cout <<  "Number of Granulated Jets: " <<  GranulatedJetSum << endl;

    /// Loop over all Hadrons
    for (int HadronNumber = 1; HadronNumber < HadronSum; HadronNumber++) {
        bool JetBool = false;

        /// Nested Loop over all Granulated Jets
        for (int GranulatedJetNumber = 0; GranulatedJetNumber < GranulatedJetSum; GranulatedJetNumber++) {

            float CellEtaDifference = abs(HadronVector[HadronNumber].pseudorapidity() - GranulatedJetVector[GranulatedJetNumber].pseudorapidity()) / CellEta;
            float CellPhiDifference = abs(HadronVector[HadronNumber].phi() - GranulatedJetVector[GranulatedJetNumber].phi());
            if (CellPhiDifference > Pi()) CellPhiDifference = 2 * Pi() - CellPhiDifference;
            CellPhiDifference = CellPhiDifference / CellPhi;

            if (CellEtaDifference < 1 && CellPhiDifference < 1) {

                JetBool = true;
                float TotalEnergy  = HadronVector[HadronNumber].e() + GranulatedJetVector[GranulatedJetNumber].e();
                float RescaleFactor = sqrt(pow(HadronVector[HadronNumber].px() + GranulatedJetVector[GranulatedJetNumber].px(), 2) + pow(HadronVector[HadronNumber].py() + GranulatedJetVector[GranulatedJetNumber].py(), 2) +
                                            pow(HadronVector[HadronNumber].pz() + GranulatedJetVector[GranulatedJetNumber].pz(), 2));
                float PxRescaled = TotalEnergy * (HadronVector[HadronNumber].px() + GranulatedJetVector[GranulatedJetNumber].px()) / RescaleFactor ;
                float PyRescaled = TotalEnergy * (HadronVector[HadronNumber].py() + GranulatedJetVector[GranulatedJetNumber].py()) / RescaleFactor ;
                float PzRescaled = TotalEnergy * (HadronVector[HadronNumber].pz() + GranulatedJetVector[GranulatedJetNumber].pz()) / RescaleFactor ;

                PseudoJet CombinedJet(PxRescaled, PyRescaled, PzRescaled, TotalEnergy);
                CombinedJet.set_user_index(HadronVector[HadronNumber].user_index() + GranulatedJetVector[GranulatedJetNumber].user_index());

                GranulatedJetVector.erase(GranulatedJetVector.begin() + GranulatedJetNumber);
                GranulatedJetVector.push_back(CombinedJet);
                break;

            }                                               //  Small R

        }                                                   //  Granulated Jet Loop

        if (!JetBool) {
            GranulatedJetVector.push_back(HadronVector[HadronNumber]);
            GranulatedJetVector = sorted_by_pt(GranulatedJetVector);
        }

    }                                                       //  Hadron Loop

    /// Loop over all Granulated Jets
    for (int GranulatedJetNumber = 0; GranulatedJetNumber < GranulatedJetSum; GranulatedJetNumber++) {

        if ((GranulatedJetVector[GranulatedJetNumber].perp() < PtCutOff)) {
            GranulatedJetVector.erase(GranulatedJetVector.begin() + GranulatedJetNumber);
            GranulatedJetNumber--;
        }
    }

    return (GranulatedJetVector);

}                                                           // granulated jets

void taggedtopclass::TaggingTop(vector< PseudoJet > HadronVector)
{
    
    Print(1, "Tagging Top");

    float CellEta = 0.1;
    float CellPhi = 0.1;
    float PtCutOff = 0.5;
    vector<PseudoJet> GranulatedHadronVector = GranulateJets(HadronVector, CellEta, CellPhi, PtCutOff);

    float ConeSize = 1.5;
    JetDefinition GranulatedHadronJetDefinition(cambridge_algorithm, ConeSize);

    ClusterSequence GranulatedHadronClusterSequence(GranulatedHadronVector, GranulatedHadronJetDefinition);

    float JetPtMin = 20.;
    vector<PseudoJet> JetVector = sorted_by_pt(GranulatedHadronClusterSequence.inclusive_jets(JetPtMin));

    /// Loop over all Top Jet Candidates
    int JetSum = JetVector.size();
    if (Debug > 1) cout << "Number of Top Jet Candidates: " <<  JetSum << endl;
    for (int JetNumber = 0; JetNumber < JetSum; JetNumber++) {

        bool debug = false;
        if (Debug > 2) debug = true;

        HEPTopTagger TopTag(GranulatedHadronClusterSequence, JetVector[JetNumber], TopMass, WMass,  debug);
        //         if (debug > 1) TopTag.debugg = true;
        TopTag.set_top_range(150., 200.);
        TopTag.run_tagger();

        if (TopTag.is_masscut_passed()) {
            PseudoJet TopJet = TopTag.top_candidate();
            TopJetVector.push_back(TopJet);
            BottomJetVector.push_back(TopTag.top_subjets().at(0));
            FirstWJetVector.push_back(TopTag.top_subjets().at(1));
            SecondWJetVector.push_back(TopTag.top_subjets().at(2));
            NumberOfTop = TopTag.top_count();
            if (Debug > 1) cout <<  "Top Mass: " << TopTag.top_candidate().m() <<   endl;
            if (Debug > 1) cout <<  "Bottom Mass: " << TopTag.top_subjets().at(0).m() <<   endl;
            if (Debug > 1) cout <<  "W Mass 1: " << TopTag.top_subjets().at(1).m() <<   endl;
            if (Debug > 1) cout <<  "W Mass 2: " << TopTag.top_subjets().at(2).m() <<   endl;
            if (Debug > 2) TopTag.get_setting();
            if (Debug > 1) TopTag.get_info();
//             if (debug > 1) cout <<  "  " <<  endl;

            TLorentzVector TopLorentzVector;
            TopLorentzVector.SetPxPyPzE(TopJet.px(), TopJet.py(), TopJet.pz(), TopJet.E());
            TopLorentzVectorVector.push_back(TopLorentzVector);

        }                                                   //  mass cut passed

    }                                                       //  loop over all jets

}                                                           // TaggingTop




void taggedtopclass::RemoveBottomComingFromTop(vector<HPull *> BottomClassVector)
{
    
   Print(1, "Remove Bottom Coming From Top");
    
    // loop over all bootom scomming from tops
    int BottomFromTopSum = BottomJetVector.size();
    for (int BottomFromTopNumber = 0; BottomFromTopNumber < BottomFromTopSum; BottomFromTopNumber++) {

        TLorentzVector BottomLorentzVector;
        BottomLorentzVector.SetPxPyPzE(BottomJetVector[BottomFromTopNumber].px(), BottomJetVector[BottomFromTopNumber].py(), BottomJetVector[BottomFromTopNumber].pz(), BottomJetVector[BottomFromTopNumber].E());
        vector<float> CylinderDistanceVector;

        // loop over all delphes bottoms to Calculates the cylinder distance
        float MinimalCylinderDistance = 9999999;
        int BottomSum = BottomClassVector.size();
        if (Debug > 1) cout << "BottomSum: " << BottomSum << endl;
        for (int BottomNumber = 0; BottomNumber < BottomSum; BottomNumber++) {

            float CylinderDistance = BottomClassVector[BottomNumber]->BottomLorentzVector.DeltaR(BottomLorentzVector);
            CylinderDistanceVector.push_back(CylinderDistance);
            if (CylinderDistance < MinimalCylinderDistance) MinimalCylinderDistance = CylinderDistance;

        }                                                 //  first loop

        // second over all delphes bottoms in order to remove the bootoms comming from tops
        for (int BottomNumber = 0; BottomNumber < BottomSum; BottomNumber++) {

            float CylinderDistance = CylinderDistanceVector[BottomNumber];
            if (Debug > 1) cout << "CylinderDistance: " << CylinderDistance << endl;

            // delete matching bottoms
            if (CylinderDistance == MinimalCylinderDistance && MinimalCylinderDistance < 0.1) {
                BottomClassVector.erase(BottomClassVector.begin() + BottomNumber);
                CylinderDistanceVector.erase(CylinderDistanceVector.begin() + BottomNumber);
            }

        }                                                 // second loop

        int BottomSum2 =  BottomClassVector.size();
        if (Debug > 1) cout << "BottomSum2: " << BottomSum2 << endl;

    }                                                     // loop over bottom from top

    if (Debug > 1 && BottomFromTopSum > 0) cout << "Bottom comming from top removed" << endl;
}
// RemoveBottomComingFromTop
