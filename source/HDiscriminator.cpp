# include "HDiscriminator.hh"

HDiscriminator::HDiscriminator()
{

    Print(0, "Constructor");

    Debug = 1;

    MinDeltaR = LargeNumber;

    Overlap = 0;

    HasHiggs = 0;

    LostHiggs = 0;

}

HDiscriminator::~HDiscriminator()
{

    Print(0, "Destructor");

}

void HDiscriminator::NewFile()
{

    Print(1, "New Analysis");

    MinDeltaR = LargeNumber;

    Overlap = 0;

    LostHiggs = 0;


}

void HDiscriminator::CloseFile()
{

    Print(1, "Clean Analysis");

    Print(1, "Minimal Max DeltaR", MinDeltaR);
    Print(1, "Top and Higgs overlap", Overlap);
    Print(1, "LostHiggs", LostHiggs);

}



void HDiscriminator::NewEvent()
{

    Print(3, " ");
    Print(1, "New Event");

    EFlowJetVector.clear();
    HiggsParticleVector.clear();
    TopParticleVector.clear();
    FatJetVector.clear();

    HasHiggs = 0;

}

vector<PseudoJet> HDiscriminator::GetTaggedCandidateJets(
    vector<PseudoJet> NewEFlowJetVector,
    vector<PseudoJet> NewHiggsParticleVector,
    vector<PseudoJet> NewTopParticleVector)
{

    Print(1, "Get Tagged Candidate Jets");

    EFlowJetVector = NewEFlowJetVector;
    HiggsParticleVector = NewHiggsParticleVector;
    TopParticleVector = NewTopParticleVector;

    const vector<PseudoJet> Jets;

    if (EFlowJetSum() == 0) {

        Print(1, "No EFlow Jets");
        return Jets;

    }

    if (!HiggsParticleChecker()) return Jets;

    if (!TopParticleChecker()) return Jets;

    HiggsParticleChecker();
    TopParticleChecker();

    const int FatJetGoal = 3;
    int FatJetPseudoGoal = FatJetGoal - 1;

    while (FatJetSum() < FatJetGoal) {

        ++FatJetPseudoGoal;
        if (!GetSuperFatJetVector(FatJetPseudoGoal)) {

            return Jets;

            Print(0, "Not enough valid jets");

        }

        GetMassDropVector();

    }

    FatJetTagger();

    sort(FatJetVector.begin(), FatJetVector.end(), SortJetByMass());

    return FatJetVector;

}


bool HDiscriminator::HiggsParticleChecker()
{

    Print(1, "Higgs Particle Checker");

    Print(3, "Higgs Particles", HiggsParticleSum());

    if (HiggsParticleSum() != 1) {

        if (HiggsParticleSum() == 0) {

            Print(2, "No Higgs Particles", HiggsParticleSum());

            return 1;

        } else if (HiggsParticleSum() > 1) {

            Print(0, "Number of Higgs Particles", HiggsParticleSum());

            return 0;

        }

    }

    HasHiggs = 1;

    return 1;

}


bool HDiscriminator::TopParticleChecker()
{

    Print(1, "Top Particle Checker");


    if (TopParticleSum() != 2) {

        Print(0, "Number of Top Particles", TopParticleSum());

        return 0;

    }

    return 1;

}

bool HDiscriminator::GetSuperFatJetVector(int FatJetGoal)
{

    Print(1, "Get Super Fat Jet Vector", FatJetGoal);

    float DeltaR = 0;
    TestFatJetVector(DeltaR);
    int FatJetSumMax = FatJetSum();

    Print(2, "MaxNumber of Jets", FatJetSumMax);

    if (FatJetSumMax < FatJetGoal) return 0;


    while (FatJetSum() > FatJetGoal) {

        DeltaR += 1;

        TestFatJetVector(DeltaR);

    }


    Print(2, "Second Loop");

    DeltaR -= 1;
    TestFatJetVector(DeltaR);

    while (FatJetSum() > FatJetGoal) {

        DeltaR += .1;

        TestFatJetVector(DeltaR);

    }


    Print(2, "Third Loop");

    DeltaR -= .1;
    TestFatJetVector(DeltaR);

    while (FatJetSum() > FatJetGoal) {

        DeltaR += .01;

        TestFatJetVector(DeltaR);

    }

    GetFatJetVector(DeltaR);

    return 1;

}


void HDiscriminator::TestFatJetVector(float DeltaR)
{

    Print(3, "Test Fat Jet with DeltaR", DeltaR);

    JetDefinition FatJetDefinition(fastjet::cambridge_algorithm, DeltaR);
    ClusterSequence FatJetClusterSequence(EFlowJetVector, FatJetDefinition);

    const float FatJetPtMin = 0;
    FatJetVector = FatJetClusterSequence.inclusive_jets(FatJetPtMin);

    Print(3, "Number of Fat Jets", FatJetSum());

}

void HDiscriminator::GetFatJetVector(float DeltaR)
{

    Print(1, "Get Fat Jet Vector", DeltaR);

    JetDefinition FatJetDefinition(fastjet::cambridge_algorithm, DeltaR);
    ClusterSequence *FatJetClusterSequence = new ClusterSequence(EFlowJetVector, FatJetDefinition);

    const float FatJetPtMin = 0;
    FatJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

    Print(2, "Number of Fat Jets", FatJetSum());

    if (FatJetSum() > 0) FatJetClusterSequence->delete_self_when_unused();

}


bool HDiscriminator::JetIsBad(const PseudoJet &Jet)
{

    if (abs(Jet.m()) <= 1) {
             
//         Print(1, "Fat Jet Mass", Jet.m());
        
        return 1;
        
    }
    
    
    if (Jet.pieces().size() != 2) {
        
//         Print(1, "Pieces Sum", Jet.pieces().size());
        
        return 1;
        
    }
    
//     if (!Jet.has_structure()) {
//                 
// //         Print(1, "PseudoJet has no structure");
//         
//         return 1;
//         
//     }
    
    
   return 0;

}

bool HDiscriminator::JetIsBad2(const PseudoJet &Jet)
{
    
    
        if (Jet.has_structure()) return 0;
                    
//             Print(1, "PseudoJet has no structure");
            
            return 1;
        
}


void HDiscriminator::GetMassDropVector()
{

    Print(1, "Get Mass Drop Jet Vector");


    
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
// //             Print(1, "Fat Jet Mass", FatJet.m());
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
// //             Print(1, "Pieces Sum", PiecesSum);
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
//             Print(1, "PseudoJet has no structure");
//             continue;
// 
//         }
// 
//     }

}

PseudoJet HDiscriminator::GetMassDropJet(PseudoJet FatJet)
{

    Print(2, "Get Mass Drop Jet");

//     MassDropMin = Jing: 0.667; fastjet: 0.667; Paper: 0.67
    const float MassDropMin = 0.667;
//     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;
    MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);

    return (MassDropJet);

}


void HDiscriminator::HiggsTagger()
{

    Print(1, "Higgs Tagger");

    PseudoJet HiggsParticle = HiggsParticleVector[0];

    Print(3, "EFlow Jets", EFlowJetSum());
    int HiggsParticlePosition;

    float HiggsJetParticleDistance = LargeNumber;
    for (int EFlowNumber = 0; EFlowNumber < EFlowJetSum(); ++EFlowNumber) {

        PseudoJet EFlowJet = EFlowJetVector[EFlowNumber];

        float EFlowHiggsDistance = EFlowJet.delta_R(HiggsParticle);

        if (EFlowHiggsDistance < HiggsJetParticleDistance) {

            HiggsJetParticleDistance = EFlowHiggsDistance;
            HiggsParticlePosition = EFlowNumber;

        }

    }

    EFlowJetVector[HiggsParticlePosition].set_user_index(HiggsUserIndex);

    Print(1, "Higgs Tagged", HiggsParticlePosition);

}


void HDiscriminator::TopTagger()
{

    Print(1, "Top Tagger");

    for (int TopParticleNumber = 0; TopParticleNumber < TopParticleSum(); ++TopParticleNumber) {

        PseudoJet TopParticle = TopParticleVector[TopParticleNumber];

        int TopParticlePosition;

        float TopJetParticleDistance = LargeNumber;
        for (int EFlowNumber = 0; EFlowNumber < EFlowJetSum(); ++EFlowNumber) {

            PseudoJet EFlowJet = EFlowJetVector[EFlowNumber];

            float EFlowHiggsDistance = EFlowJet.delta_R(TopParticle);

            if (EFlowHiggsDistance < TopJetParticleDistance) {

                TopJetParticleDistance = EFlowHiggsDistance;
                TopParticlePosition = EFlowNumber;

            }

        }

        EFlowJetVector[TopParticlePosition].set_user_index(TopUserIndex);

        Print(1, "Top Tagged", TopParticlePosition);

    }

}

void HDiscriminator::TagFatJets()
{

    Print(1, "Tag FatJets");

    bool HiggsLost = 1;

    for (int FatJetNumber = 0; FatJetNumber < FatJetSum(); ++FatJetNumber) {

        PseudoJet FatJet = FatJetVector[FatJetNumber];

        vector<PseudoJet> ConstituentsVector = FatJet.constituents();
        int ConstituentsSum = ConstituentsVector.size();

        int UserIndex = 0;

        for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ++ConstituentsNumber) {

            int ConstUserIndex = ConstituentsVector[ConstituentsNumber].user_index();

            if (ConstUserIndex > 0) {

                UserIndex += ConstUserIndex;

                if (ConstUserIndex == HiggsUserIndex) HiggsLost = 0;

            }

        }

        if (UserIndex > 0) FatJetVector[FatJetNumber].set_user_index(UserIndex);

        if (UserIndex == HiggsUserIndex + TopUserIndex) Overlap++;

        if (HasHiggs && HiggsLost) {

//             cout << "Higgs Lost" << endl;

            ++LostHiggs;

        }

        if (UserIndex > 0) Print(1, "Tagged FatJet", UserIndex);

    }

}

void HDiscriminator::FatJetTagger()
{

    Print(1, "FatJetTagger");


    if (HasHiggs) {

        PseudoJet HiggsParticle = HiggsParticleVector.front();

        Print(3, "Fat Jets", FatJetSum());
        int HiggsParticlePosition = -1;

        float HiggsJetParticleDistance = LargeNumber;
        for (int FatJetNumber = 0; FatJetNumber < FatJetSum(); ++FatJetNumber) {

            PseudoJet FatJet = FatJetVector[FatJetNumber];

            float FatJetHiggsDistance = FatJet.delta_R(HiggsParticle);

            if (FatJetHiggsDistance < HiggsJetParticleDistance) {

                HiggsJetParticleDistance = FatJetHiggsDistance;
                HiggsParticlePosition = FatJetNumber;

            }

        }
        
//         PseudoJet Jet = FatJetVector[HiggsParticlePosition];

//         if (Jet.delta_R(HiggsParticle) > (Jet.pieces()[0]).delta_R(Jet.pieces()[1]))
//             Print(-1,"Higgs too far away", Jet.delta_R(HiggsParticle) / (Jet.pieces()[0]).delta_R(Jet.pieces()[1]));
        
        FatJetVector[HiggsParticlePosition].set_user_index(HiggsUserIndex);
        Print(1, "Higgs Tagged", HiggsParticlePosition);
        

    }

    if (TopParticleSum() != 2) {

        Print(0, "Number of Top Particles", TopParticleSum());
        return ;

    }

    for (int TopParticleNumber = 0; TopParticleNumber < TopParticleSum(); ++TopParticleNumber) {

        PseudoJet TopParticle = TopParticleVector[TopParticleNumber];

        int TopParticlePostion = LargeNumber;

        float TopJetParticleDistance = LargeNumber;
        for (int FatJetNumber = 0; FatJetNumber < FatJetSum(); ++FatJetNumber) {

            PseudoJet FatJet = FatJetVector[FatJetNumber];

            float FatJetDistance = FatJet.delta_R(TopParticle);

            if (FatJetDistance < TopJetParticleDistance) {

                TopJetParticleDistance = FatJetDistance;
                TopParticlePostion = FatJetNumber;

            }

        }

        if (TopParticlePostion != LargeNumber) {

            int UserIndex = FatJetVector[TopParticlePostion].user_index();

            if (UserIndex > 0) {

                UserIndex += TopUserIndex;
                FatJetVector[TopParticlePostion].set_user_index(UserIndex);

            } else {

                FatJetVector[TopParticlePostion].set_user_index(TopUserIndex);

            }

        }

        Print(1, "Top Tagged", TopParticlePostion);

    }


}
