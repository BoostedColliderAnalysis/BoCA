# include "HJetDiscriminator.hh"

HJetDiscriminator::HJetDiscriminator()
{

    Print(1, "Constructor");

    ProjectName = "JetProperties";

    LeptonEventCounter = 0;

    EventNumberMax = 10000;

    HDiscriminatorTag = new HDiscriminatorJetTag();

//     DebugLevel = 2;

}

HJetDiscriminator::~HJetDiscriminator()
{


    delete HDiscriminatorTag;
    Print(1, "Destructor");

}

vector<string> HJetDiscriminator::GetStudyNameVector()
{

//     vector<string> StudyNameVector = {"Higgs", "Top", "Isr"};
    vector<string> StudyNameVector = {"Higgs", "Top"};
//     vector<string> StudyNameVector = {"Top"};

    return StudyNameVector;

}

void HJetDiscriminator::SetFileVector()
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


void HJetDiscriminator::NewFile()
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidates", HJetPropertiesBranch::Class());
    SmallCandidateBranch = TreeWriter->NewBranch("MiniCandidates", HJetPropertiesBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());

}

void HJetDiscriminator::CloseFile()
{
    Print(1, "Close File");

}





HBranchStruct HDiscriminatorJetTag::GetBranchId(const int ParticleId, HBranchStruct BranchStruct) const
{

    Print(3, "Get Branch Id", ParticleId);

    if (InitialState.find(abs(ParticleId)) != end(InitialState) && MotherParticle.find(abs(BranchStruct.Id)) == end(MotherParticle)) {
        BranchStruct.Id = IsrId;
    } else if (MotherParticle.find(abs(ParticleId)) != end(MotherParticle) && MotherParticle.find(abs(BranchStruct.Id)) == end(MotherParticle)) {
        BranchStruct.Id = ParticleId;
    }

    Print(3, "Branch Id", BranchStruct.Id);

    //     if (BranchId == 0) Print(0, "ParticleId", ParticleId);
    if (abs(ParticleId) == TopId && BranchStruct.Id == CpvHiggsId) Print(0, "Higgs overwritten by top");

//     if (ParticleId  < 0 && (ChargeParticle.find(abs(ParticleId)) == end(ChargeParticle) && NeutralParticle.find(abs(ParticleId)) == end(NeutralParticle)) ) Print(0, "Charged Particle" , ParticleId);

//     if (ChargeParticle.find(abs(ParticleId)) != end(ChargeParticle)) BranchStruct.Charge += sgn(ParticleId);

    return BranchStruct;

}


bool HJetDiscriminator::Analysis()
{

    Print(3, "Analysis");

    Event->GetTaggedEFlow(HDiscriminatorTag);

    float EventPt = 0;
    for (const auto & EFlowJet : Event->Jets->EFlowJetVector) {

        EventPt += EFlowJet.pt();

    }

    vector<int> IdVector;
    if (StudyName == "Top") IdVector = { TopId, -TopId};
    if (StudyName == "Higgs") IdVector = {CpvHiggsId};
    if (StudyName == "Isr") IdVector = {IsrId};

    for (const auto & Id : IdVector) {

        vector<PseudoJet> EFlowJetVector;
        std::copy_if(Event->Jets->EFlowJetVector.begin(), Event->Jets->EFlowJetVector.end(), std::back_inserter(EFlowJetVector),
        [Id](const PseudoJet & EFlowJet) {

            if (EFlowJet.user_index() == Id) return 1;

            if (EFlowJet.user_index() != 5000000 && abs(EFlowJet.user_index()) != 6 && EFlowJet.user_index() != 10) cout << "EFlowId " << EFlowJet.user_index() << endl;

            return 0;

        });

        if (EFlowJetVector.size() == 0) {

            Print(0, "NoEflow", Id);

            return 0;

        }

        float CandidatePt = 0;
        for (const auto & EFlowJet : EFlowJetVector) {

            CandidatePt += EFlowJet.pt();

        }

        const PseudoJet CandidateJet = fastjet::join(EFlowJetVector);

        map<float, PseudoJet> JetMap;

        for (const auto & EFlowJet : EFlowJetVector) {

            JetMap.insert(std::pair<float, PseudoJet>(CandidateJet.delta_R(EFlowJet), EFlowJet));

        }


        if (JetMap.size() == 0) {

            Print(0, "NoEflow", Id);

            return 0;

        }

        float SigmaPt = 0;
        float SigmaRadius = 0;

        Print(1, "Max Pt", CandidatePt);
        vector<PseudoJet> MiniJetVector;
        map<float, PseudoJet>::iterator Counter = JetMap.begin();
        do {

            SigmaRadius = (*Counter).first;
            MiniJetVector.push_back(Counter->second);
            SigmaPt += (*Counter).second.pt();

            Print(2, "EFlow", SigmaRadius, SigmaPt);

            ++Counter;

        }   while (SigmaPt <= (TwoSigma * CandidatePt) && Counter != JetMap.end());



        Print(1, "Eflowsize", EFlowJetVector.size());
        Print(1, "Radius", SigmaRadius);

        Counter = JetMap.end();
        --Counter;
        const float MaxRadius = (*Counter).first;
        Print(1, "MaxRadius", MaxRadius);

        Print(1, "mini size", MiniJetVector.size());



        const PseudoJet MiniCandidateJet = fastjet::join(MiniJetVector);

        HJetPropertiesBranch *Jet = static_cast<HJetPropertiesBranch *>(CandidateBranch->NewEntry());

//         Print(-1,"size",DistanceVector.size());

        Jet->Mass = CandidateJet.m();
        Jet->Pt = CandidateJet.pt();
        Jet->Eta = CandidateJet.eta();
        Jet->Phi = CandidateJet.phi_std();
        Jet->Radius = MaxRadius;
        Jet->EventPt = 1. / EventPt;

        HJetPropertiesBranch *MiniJet = static_cast<HJetPropertiesBranch *>(SmallCandidateBranch->NewEntry());

        //         Print(-1,"size",DistanceVector.size());

        MiniJet->Mass = MiniCandidateJet.m();
        MiniJet->Pt = MiniCandidateJet.pt();
        MiniJet->Eta = MiniCandidateJet.eta();
        MiniJet->Phi = MiniCandidateJet.phi_std();
        MiniJet->Radius = SigmaRadius;
        MiniJet->EventPt = 1. / EventPt;

        for (const auto & EFlowJet : EFlowJetVector) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJet.eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }
    }

    return 1;

}



