# include "HReconstruction.hh"

void HReconstruction::GetMassDropVector()
{
    
    Print(2, "Get Mass Drop Jet Vector");
    
    
    
    for (int FatJetNumber = 0; FatJetNumber < FatJetSum(); ++FatJetNumber) {
        
        FatJetVector[FatJetNumber] = GetMassDropJet(FatJetVector[FatJetNumber]);
        
    }
    
    FatJetVector.erase(std::remove_if(FatJetVector.begin(), FatJetVector.end(), JetIsBad2), FatJetVector.end());
    
    FatJetVector.erase(std::remove_if(FatJetVector.begin(), FatJetVector.end(), JetIsBad), FatJetVector.end());
    
    
    //     for (int FatJetNumber = 0; FatJetNumber < FatJetSum(); ++FatJetNumber) {
    //
    //         PseudoJet FatJet = FatJetVector[FatJetNumber];
    //
    // //         if (FatJet.m() <= 10) {
    // //
    // //             Print(2, "Fat Jet Mass", FatJet.m());
    // //
    // //             FatJetVector.erase(FatJetVector.begin() + FatJetNumber);
    // //
    // //             continue;
    // //
    // //         }
    //
    //         vector<PseudoJet> FatJetPieces = FatJet.pieces();
    //
    // //         int PiecesSum = FatJetPieces.size();
    // //
    // //         if (PiecesSum != 2) {
    // //
    // //             Print(2, "Pieces Sum", PiecesSum);
    // //
    // //             FatJetVector.erase(FatJetVector.begin() + FatJetNumber);
    // //             continue;
    // //
    // //         }
    //
    //         FatJet = GetMassDropJet(FatJet);
    //
    //         if (FatJet.has_structure()) {
    //
    //             FatJetVector[FatJetNumber] = FatJet;
    //
    //         } else {
    //
    //             FatJetVector.erase(FatJetVector.begin() + FatJetNumber);
    //
    //             Print(2, "PseudoJet has no structure");
    //             continue;
    //
    //         }
    //
    //     }
    
}

PseudoJet HReconstruction::GetMassDropJet(PseudoJet FatJet)
{
    
    Print(3, "Get Mass Drop Jet");
    
    //     MassDropMin = Jing: 0.667; fastjet: 0.667; Paper: 0.67
    const float MassDropMin = 0.667;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;
    MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);
    
    return (MassDropJet);
    
}