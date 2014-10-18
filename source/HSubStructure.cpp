# include "HSubStructure.hh"

HSubStructure::HSubStructure()
{

    Print(1, "Constructor");

//   Shift = 1;


}

HSubStructure::~HSubStructure()
{

    Print(1, "Destructor");

}

void HSubStructure::NewEvent(){
    
    SubJets = 0;
    
}

bool HSubStructure::GetSubJets(const PseudoJet &CandidateJet)
{
    
    SubJets = 1;

    Global.Mass = CandidateJet.m();
    Global.Pt = CandidateJet.pt();

    vector<PseudoJet> PiecesVector = CandidateJet.pieces();
    sort(PiecesVector.begin(), PiecesVector.end(), SortJetByMass());

    if (!(PiecesVector.size() == 2)) {

//         Print(1, "Wrong Number of SubJets", PiecesVector.size()); // TODO reenable in smarter way
        return 0;

    }

    // SubJets

    SubJet1.Mass = PiecesVector[0].m();
    SubJet2.Mass = PiecesVector[1].m();

    if (SubJet1.Mass <= 0 || SubJet2.Mass <= 0) {

        Print(2, "No SubJet Mass");
        return 0;

    }

    SubJet1.Pt = PiecesVector[0].pt();
    SubJet2.Pt = PiecesVector[1].pt();

    if (SubJet1.Pt <= 0 || SubJet2.Pt <= 0) {

        Print(1, "No SubJet Pt");
        return 0;

    }


    Global.DeltaR = PiecesVector[0].delta_R(PiecesVector[1]);

    SubJet1.DeltaR = PiecesVector[0].delta_R(CandidateJet);
    SubJet2.DeltaR = PiecesVector[1].delta_R(CandidateJet);

    //         float Asymmetry = SubJet2Pt * SubJetDeltaR / CandidateMass;

    // Get SubJet coordinates in Higgs Jet coordinates

    SubJet1.Eta = PiecesVector[0].eta() - CandidateJet.eta();
    SubJet2.Eta = PiecesVector[1].eta() - CandidateJet.eta();

    SubJet1.Phi = PiecesVector[0].delta_phi_to(CandidateJet);
    SubJet2.Phi = PiecesVector[1].delta_phi_to(CandidateJet);

    // move subjet1 together with subjet2 to origin

    SubJet2.Eta -= SubJet1.Eta;
    SubJet2.Phi -= SubJet1.Phi;

    // scale subjet distance to reference value

    const float SubJetDistance = GetDistance(SubJet2.Eta, SubJet2.Phi);
    SubJetRatio =  GetPosDistance() / SubJetDistance;

    if (SubJetDistance <= 0) {

        Print(1, "No subJet Distance", SubJetDistance);
        return 0;
    }


    return 1;

}

bool HSubStructure::GetConstituents(const PseudoJet &CandidateJet, ExRootTreeBranch * const ConstituentBranch)
{
    
    if (CandidateJet.constituents().size() < 1) {

        Print(1, "Not enough Constituents", CandidateJet.constituents().size());
        return 0;

    }
    
    if (!SubJets) GetSubJets(CandidateJet);
    const float Theta = atan2(SubJet2.Phi, SubJet2.Eta);

    float SumInverseEta = 0;
    float SumInversePhi = 0;

    for (const auto & ConstituentJet : CandidateJet.constituents()) {

        // Get Constituent coordinates in Higgs Jet coordinates

        float ConstEta = ConstituentJet.eta() - CandidateJet.eta();
        float ConstPhi = ConstituentJet.delta_phi_to(CandidateJet);

        // move subjet1 together with constituent to origin

        ConstEta -= SubJet1.Eta;
        ConstPhi = GetDeltaPhi(ConstPhi, SubJet1.Phi);

        // scale distance to reference value

        ConstEta = ConstEta * SubJetRatio;
        ConstPhi = ConstPhi * SubJetRatio;

        // rotate Constituent according to subjet2

        float ObservableEta = ConstEta * cos(Theta) + ConstPhi * sin(Theta);
        const float ObservablePhi = ConstEta * sin(Theta) - ConstPhi * cos(Theta);

        // move subjet2 to (1,0)
        ObservableEta -= Shift;


        HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
        Constituent->Eta = ObservableEta;
        Constituent->Phi = ObservablePhi;
        Constituent->Pt = ConstituentJet.pt();


        SumInverseEta += ConstituentJet.pt() / fabs(ObservableEta);
        SumInversePhi += ConstituentJet.pt() / fabs(ObservablePhi);

    }

    Global.Eta = CandidateJet.pt() / SumInverseEta;
    Global.Phi = CandidateJet.pt() / SumInversePhi;
    
    return 1;

}

bool HSubStructure::GetIsolation(const PseudoJet& CandidateJet,const vector<PseudoJet>& LeptonJetVector){
    
    // Get Position of SubJets
    
    vector<PseudoJet> PiecesVector = CandidateJet.pieces();
    sort(PiecesVector.begin(), PiecesVector.end(), SortJetByMass());
    
    if (!(PiecesVector.size() == 2)) {
        
        Print(1, "Wrong Number of SubJets", PiecesVector.size());
        return 0;
        
    }
    
    
    // Isolation
    
    int IsolationDeltaR = LargeNumber;
    
    PseudoJet ClosestLepton;
    PseudoJet ClosestPiece;
    
    for (const auto & Piece : PiecesVector) {
        
        for (const auto & LeptonJet : LeptonJetVector) {
            
            const float DeltaR = LeptonJet.delta_R(Piece);
            Print(4, "DeltaR", DeltaR);
            
            if (DeltaR < IsolationDeltaR) {
                
                IsolationDeltaR = DeltaR;
                ClosestLepton = LeptonJet;
                ClosestPiece = Piece;
                
            }
            
        }
        
    }

    if (IsolationDeltaR != LargeNumber) {
        
        Isolation.Eta = ClosestLepton.eta() - ClosestPiece.eta();
        Isolation.Phi = ClosestLepton.delta_phi_to(ClosestPiece);
        Isolation.Pt = ClosestLepton.pt() / ClosestPiece.pt();
        Isolation.DeltaR = ClosestLepton.delta_R(ClosestPiece);
        
    }
    
    return 1;
    
}
