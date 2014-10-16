# include "HAnalysisDiscriminator.hh"

HAnalysisDiscriminator::HAnalysisDiscriminator()
{

    Print(1, "Constructor");

    ProjectName = "Discriminator";

    LeptonEventCounter = 0;

//     DebugLevel = 3;

    EventNumberMax = 10000;

}

vector<string> HAnalysisDiscriminator::GetStudyNameVector()
{

//     vector<string> StudyNameVector = {"Higgs", "Top", "TwoTop","HiggsTop", "Jet", "Test"};
    vector<string> StudyNameVector = {"Higgs", "Top", "Jet", "Test"};
    //     vector<string> StudyNameVector = {"Top"};

    return StudyNameVector;

}

void HAnalysisDiscriminator::SetFileVector()
{

    Print(1, "Set File Vector", StudyName);

    if (StudyName != "Higgs") {

        HFileDelphes *Background = new HFileDelphes("pp-bbtt-bblvlv", "background");
        Background->Crosssection = 3.215; // pb
        Background->Error = 0.012; // pb
        FileVector.push_back(Background);

    }

    HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
    FileVector.push_back(Even);

    HFileDelphes *Mix = new HFileDelphes("pp-x0tt-bblvlv", "mix");
    Mix->Crosssection = 0.01172; // pb
    Mix->Error = 0.000045; // pb
    FileVector.push_back(Mix);

    HFileDelphes *Odd = new HFileDelphes("pp-x0tt-bblvlv", "odd");
    Odd->Crosssection = 0.008951; // pb
    Odd->Error = 0.000035; // pb
    FileVector.push_back(Odd);

    int AnalysisSum = FileVector.size();
    Print(1, "Files prepared", AnalysisSum);

}


void HAnalysisDiscriminator::NewFile()
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Lepton", HLeptonBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());

    LeptonEventCounter = 0;

}

void HAnalysisDiscriminator::CloseFile()
{
    Print(1, "Close File");

}

int HDiscriminatorJetTag::GetBranchId(const int ParticleId, int BranchId, int WhichMother) const
{

    Print(3, "Get Branch Id", ParticleId);
    
    if (ParticleId == -BranchId) {
        
        Print(4, "ID CONFILICT", ParticleId, BranchId);
        
    }
    
    if (
        RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles)
        && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
        && WhichMother == 2
    ) {
        BranchId = ParticleId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles)
        && WhichMother == 1
    ) {
        BranchId = ParticleId;
    }
    
    Print(3, "Branch Id", BranchId);
    
    return BranchId;

}

bool HAnalysisDiscriminator::Analysis()
{

    Print(2, "Analysis", StudyName);

    const vector<PseudoJet> LeptonVector = Leptons();

    if (LeptonVector.size() < 2) {

        Print(2, "Not enough Leptons", LeptonVector.size());
        return 0;

    }

    ++LeptonEventCounter;

    // Higgs stuff

    const HDiscriminatorJetTag *const DiscriminatorJetTag = new HDiscriminatorJetTag;
    const vector<PseudoJet> CandidateJets = Event->GetHiggsTopCandidates(DiscriminatorJetTag);
    delete DiscriminatorJetTag;

    Print(2, "Number of Candidates", CandidateJets.size());

//     for (const auto & CandidateJet : CandidateJets) {
//
//         Print(0,"JetMass",CandidateJet.m());
//     }


    if (CandidateJets.size() < 1) {

        Print(2, "No a Candidates");
        return 0;

    }

    int CandidateCounter = 0;
    bool HasCandidate = 0;
    bool HiggsCounter = 0;

    for (const auto & CandidateJet : CandidateJets) {

//         CandidateJet.user_info<HJetInfo>().PrintAllInfos();

        Print(3, "Candidate", CandidateJet.user_index());

        if (StudyName == "Higgs") {

            if (CandidateCounter > 0) {

                Print(2, "Number of Higgs", CandidateCounter);
                break;

            }

            if (CandidateJet.user_index() != CpvHiggsId) {

                Print(3, "Not a Higgs");
                continue;

            }

            ++CandidateCounter;

        }

        if (StudyName == "Top") {

            if (abs(CandidateJet.user_index()) != TopId) {

                Print(3, "Not a Top");
                continue;

            }

            if (CandidateCounter > 1) Print(1, "Number of Tops", CandidateCounter);
            ++CandidateCounter;
            Print(3, "Top", CandidateCounter);

        }

        if (StudyName == "Jet") {

            if (CandidateJet.user_index() == CpvHiggsId && HiggsCounter == 0) {

                HiggsCounter = 1;
                Print(3, "Not a light jet");
                continue;

            }

            if (abs(CandidateJet.user_index()) == TopId) {

                Print(3, "Not a light jet");
                continue;

            }

            if (CandidateCounter > 2) Print(1, "Number light jets", CandidateCounter);
            ++CandidateCounter;
            Print(2, "Jet", CandidateCounter);

        }

        const float CandidateMass = CandidateJet.m();
        const float CandidatePt = CandidateJet.perp();

        if (CandidateJet == 0 || CandidateMass <= 0 || CandidatePt <= 0) {

            Print(0, "Illeagal Candidate", CandidateMass);
            continue;

        }

        const float Shift = 1;
        const float Position2Eta = 2 * Shift;
        const float PosDistance = GetDistance(Position2Eta, 0); // Position2Eta

        const float CandidateEta = CandidateJet.eta();
        const float CandidatePhi = CandidateJet.phi_std();

//         float CandidateArea = 0;

//         if (CandidateJet.has_area()) {
//
//             float CandidateArea = CandidateJet.area();
//
//             cout << CandidateArea << endl;
//
// //             if (CandidateArea <= 0) {
// //
// //                 Print("HAnalysisDiscriminator", "Candidate has no Area");
// //                 continue;
// //
// //             }
//
//         } else {
//
//             cout << 0 << endl;
//
//         }

        // Get Position of SubJets

        vector<PseudoJet> PiecesVector = CandidateJet.pieces();
        sort(PiecesVector.begin(), PiecesVector.end(), SortJetByMass());

        if (!(PiecesVector.size() == 2 /*|| PiecesSum ==3*/)) {

            Print(1, "Wrong Number of SubJets", PiecesVector.size());
            continue;

        }




        // SubJets

        const PseudoJet SubJet1 = PiecesVector[0];
        const PseudoJet SubJet2 = PiecesVector[1];

        const float SubJet1Mass = SubJet1.m();
        const float SubJet2Mass = SubJet2.m();

        if (SubJet1Mass <= 0 || SubJet2Mass <= 0) {

            Print(2, "No SubJet Mass");
            continue;

        }

        const float SubJet1Pt = SubJet1.perp();
        const float SubJet2Pt = SubJet2.perp();

        if (SubJet1Pt <= 0 || SubJet2Pt <= 0) {

            Print(1, "No SubJet Pt");
            continue;

        }


        const float SubJetDeltaR = SubJet1.delta_R(SubJet2);

        const float SubJet1DeltaR = SubJet1.delta_R(CandidateJet);
        const float SubJet2DeltaR = SubJet2.delta_R(CandidateJet);

//         float Asymmetry = SubJet2Pt * SubJetDeltaR / CandidateMass;

        // Get SubJet coordinates in Higgs Jet coordinates

        const float SubJet1Eta = SubJet1.eta() - CandidateEta;
        const float SubJet1Phi = GetDeltaPhi(SubJet1.phi_std(), CandidatePhi);

        float SubJet2Eta = SubJet2.eta() - CandidateEta;
        float SubJet2Phi = GetDeltaPhi(SubJet2.phi_std(), CandidatePhi);

        // move subjet1 together with subjet2 to origin

        SubJet2Eta -= SubJet1Eta;
        SubJet2Phi -= SubJet1Phi;

        // scale subjet distance to reference value

        const float SubJetDistance = GetDistance(SubJet2Eta, SubJet2Phi);
        const float SubJetRatio =  PosDistance / SubJetDistance;

        if (SubJetDistance == 0) continue;

        const vector<PseudoJet> ConstituentVector = CandidateJet.constituents();

        if (ConstituentVector.size() < 1) {

            Print(1, "Not enough Constituents", ConstituentVector.size());
            continue;

        }






        // Isolation

        float IsolationDeltaR = LargeNumber;

        PseudoJet ClosestLepton;
        PseudoJet ClosestPiece;

        for (const auto & Piece : PiecesVector) {

            for (const auto & Lepton : LeptonVector) {

                const float DeltaR = Lepton.delta_R(Piece);
                Print(4, "DeltaR", DeltaR);

                if (DeltaR < IsolationDeltaR) {

                    IsolationDeltaR = DeltaR;
                    ClosestLepton = Lepton;
                    ClosestPiece = Piece;

                }

            }

        }

//         Print(3, "Closest Lepton", ClosestLepton);



        float IsolationEta = 0;
        float IsolationPhi = 0;
        float IsolationPt = 0;
        if (IsolationDeltaR != LargeNumber) {

            IsolationEta = ClosestLepton.eta() - ClosestPiece.eta();
            IsolationPhi = ClosestLepton.delta_phi_to(ClosestPiece);
            IsolationPt = ClosestLepton.pt() / ClosestPiece.pt();


        }







        float Theta = atan2(SubJet2Phi, SubJet2Eta);

        float SumInverseEta = 0;
        float SumInversePhi = 0;



        for (const auto & ConstituentJet : ConstituentVector) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());

            // Get Constituent coordinates in Higgs Jet coordinates

            float ConstEta = ConstituentJet.eta() - CandidateEta;
            float ConstPhi = GetDeltaPhi(ConstituentJet.phi_std(), CandidatePhi);

            // move subjet1 together with constituent to origin

            ConstEta -= SubJet1Eta;
            ConstPhi = GetDeltaPhi(ConstPhi, SubJet1Phi);

            // scale distance to reference value

            ConstEta = ConstEta * SubJetRatio;
            ConstPhi = ConstPhi * SubJetRatio;

            // rotate Constituent according to subjet2

            float ObservableEta = ConstEta * cos(Theta) + ConstPhi * sin(Theta);
            float ObservablePhi = ConstEta * sin(Theta) - ConstPhi * cos(Theta);

            // move subjet2 to (1,0)
            ObservableEta -= Shift;

            float ConstPt = ConstituentJet.perp();


            Constituent->Eta = ObservableEta;
            Constituent->Phi = ObservablePhi;
            Constituent->Pt = ConstPt;


            SumInverseEta += ConstPt / fabs(ObservableEta);
            SumInversePhi += ConstPt / fabs(ObservablePhi);

        }

        float SumEta = CandidatePt / SumInverseEta;
        float SumPhi = CandidatePt / SumInversePhi;





        HasCandidate = 1;

        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());



        Candidate->IsolationEta = IsolationEta ;
        Candidate->IsolationPhi = IsolationPhi;
        Candidate->IsolationPt = IsolationPt;

        Candidate->IsolationDeltaR = ClosestLepton.delta_R(ClosestPiece);
        Candidate->IsolationAngle = atan2(IsolationPhi, IsolationEta);

        Print(3, "Isolation", Candidate->IsolationDeltaR);


        Candidate->Mass = CandidateMass;
        Candidate->Pt = CandidatePt;
        Candidate->Eta = CandidateEta;
        Candidate->Phi = CandidatePhi;

        Print(3, "Candidate Mass", CandidateMass);

        // Tagging

        int UserIndex = CandidateJet.user_index();

        if (UserIndex == CpvHiggsId) {
            Candidate->HiggsTag = 1;
            Candidate->TopTag = 0;

        } else if (UserIndex == TopId) {

            Candidate->TopTag = 1;
            Candidate->HiggsTag = 0;

        } else {

            Candidate->TopTag = 0;
            Candidate->HiggsTag = 0;

        }

        Candidate->SubJet1Mass = SubJet1Mass / CandidateMass;
        Candidate->SubJet2Mass = SubJet2Mass / CandidateMass;
        Candidate->SubJet1Pt = SubJet1Pt / CandidatePt;
        Candidate->SubJet2Pt = SubJet2Pt / CandidatePt;
        Candidate->SubJetsDeltaR = SubJetDeltaR;
        Candidate->SubJet1DeltaR = SubJet1DeltaR / SubJetDeltaR ;
        Candidate->SubJet2DeltaR = SubJet2DeltaR / SubJetDeltaR ;
//         Candidate->Area = CandidateArea;



        Candidate->ConstEta = SumEta;
        Candidate->ConstPhi = SumPhi;

        //         Higgs->ConstDeltaR = pow(SumEta,2) + pow(SumPhi,2);
        Candidate->ConstDeltaR = GetDistance(SumEta, SumPhi);
        Candidate->ConstAngle = atan2(SumPhi, SumEta);



        Print(3, "Pull", Candidate->ConstDeltaR);

    }

    if (HasCandidate) return 1;

    Print(2, "No Candidates found");

    return 0;

}


vector<PseudoJet> HAnalysisDiscriminator::Leptons()
{

// Lepton Stuff
    vector<float> LeptonEta, LeptonPhi;

    Event->GetLeptons();

    vector<PseudoJet> LeptonVector = Event->Lepton->LeptonJets;
    vector<PseudoJet> AntiLeptonVector = Event->Lepton->AntiLeptonJets;

//     vector<TLorentzVector> LeptonVector = Event->Leptons->LeptonLorentzVectorVector;
//     vector<TLorentzVector> AntiLeptonVector = Event->Leptons->AntiLeptonLorentzVectorVector;

//     Event->GetParticles();
//     vector<TLorentzVector> LeptonVector = Event->Particle->LeptonVector();
//     vector<TLorentzVector> AntiLeptonVector = Event->Particle->AntiLeptonVector();

    sort(LeptonVector.begin(), LeptonVector.end(), SortJetByPt());
    sort(AntiLeptonVector.begin(), AntiLeptonVector.end(), SortJetByPt());

    bool HardestLepton = 1;
    for (const auto & LeptonJet : LeptonVector) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = LeptonJet.pt();
            Lepton->Eta = LeptonJet.eta();
            Lepton->Phi = LeptonJet.phi_std();
            Lepton->Charge = -1;
            Lepton->Mass = LeptonJet.m();
        }
        HardestLepton = 0;

        LeptonEta.push_back(LeptonJet.eta());
        LeptonPhi.push_back(LeptonJet.phi_std());

    }

    HardestLepton = 1;
    for (const auto & AntiLeptonJet : AntiLeptonVector) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = AntiLeptonJet.pt();
            Lepton->Eta = AntiLeptonJet.eta();
            Lepton->Phi = AntiLeptonJet.phi_std();
            Lepton->Charge = 1;
            Lepton->Mass = AntiLeptonJet.m();

        }
        HardestLepton = 0;

        LeptonEta.push_back(AntiLeptonJet.eta());
        LeptonPhi.push_back(AntiLeptonJet.phi_std());

    }

    LeptonVector.insert(LeptonVector.end(), AntiLeptonVector.begin(), AntiLeptonVector.end());

    Print(2, "Number of Leptons", LeptonVector.size());

    return LeptonVector;

}

