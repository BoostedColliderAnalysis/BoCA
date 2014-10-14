# include "HJetDiscriminator.hh"

HJetDiscriminator::HJetDiscriminator()
{

    Print(1, "Constructor");

    ProjectName = "JetProperties";

    EventNumberMax = 10000;

    HDiscriminatorTag = new HDiscriminatorJetTag();

}

HJetDiscriminator::~HJetDiscriminator()
{

    Print(1, "Destructor");

    delete HDiscriminatorTag;

}

vector<string> HJetDiscriminator::GetStudyNameVector()
{

//     vector<string> StudyNameVector = {"Higgs", "Top", "Isr"};
//     vector<string> StudyNameVector = {"Higgs", "Top"};
    vector<string> StudyNameVector = {"Top"};

    return StudyNameVector;

}

void HJetDiscriminator::SetFileVector()
{

    Print(1, "Set File Vector", StudyName);

//     if (StudyName != "Higgs") {
// 
//         HFileDelphes *Background = new HFileDelphes("pp-bbtt-bblvlv", "background");
//         Background->Crosssection = 3.215; // pb
//         Background->Error = 0.012; // pb
//         FileVector.push_back(Background);
// 
//     }

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

    ParticleBranch = TreeWriter->NewBranch("Particle", HJetPropertiesBranch::Class());
    TrimmedBranch = TreeWriter->NewBranch("Trimmed", HJetPropertiesBranch::Class());
    CAFatJetBranch = TreeWriter->NewBranch("CAFatJet", HJetPropertiesBranch::Class());
    CAMassDropBranch = TreeWriter->NewBranch("CAMassDrop", HJetPropertiesBranch::Class());
    AktFatJetBranch = TreeWriter->NewBranch("AktFatJet", HJetPropertiesBranch::Class());
    AktMassDropBranch = TreeWriter->NewBranch("AktMassDrop", HJetPropertiesBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituents", HConstituentBranch::Class());
    EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());

}

void HJetDiscriminator::CloseFile()
{
    Print(1, "Close File");

}

int HDiscriminatorJetTag::GetBranchId(const int ParticleId, int BranchId) const
{

    Print(3, "Get Branch Id", ParticleId);

    if (ParticleId == -BranchId){
        
        Print(2,"");
        Print(2,"");
        Print(2,"");
        Print(2,"");
        Print(2,"");
        Print(2,"");
        Print(0, "ID CONFILICT", ParticleId, BranchId,999999999999);
        
    }

    if (
        RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles)
//         && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}


bool HJetDiscriminator::Analysis()
{

    Print(3, "Analysis");

    Event->GetTaggedEFlow(HDiscriminatorTag);

    float EventPt = 0;
    for (const auto & EFlowJet : Event->Jets->EFlowJetVector) {

        EventPt += EFlowJet.pt();

    }

    HEventBranch *EventB = static_cast<HEventBranch *>(EventBranch->NewEntry());
    EventB->ScalarPtSum = 1. / EventPt;

    vector<int> IdVector;
    if (StudyName == "Top") IdVector = { TopId, -TopId};
//     if (StudyName == "Top") IdVector = { TopId};
    if (StudyName == "Higgs") IdVector = {CpvHiggsId};
    if (StudyName == "Isr") IdVector = {IsrId};

    for (const auto & Id : IdVector) {

        vector<PseudoJet> EFlowJets;
        std::copy_if(Event->Jets->EFlowJetVector.begin(), Event->Jets->EFlowJetVector.end(), std::back_inserter(EFlowJets),
        [Id](const PseudoJet & EFlowJet) {

            if (EFlowJet.user_index() == Id) return 1;
            if (EFlowJet.user_index() != 5000000 && abs(EFlowJet.user_index()) != 6 && EFlowJet.user_index() != 10) cout << "EFlowId " << EFlowJet.user_index() << endl;
            return 0;

        });

        if (EFlowJets.size() == 0) {

            Print(0, "NoEflow", Id);
            continue;

        }
        Print(1, "Eflowsize", EFlowJets.size());

        const PseudoJet CandidateJet = fastjet::join(EFlowJets);

        map<float, PseudoJet> JetMap;
        for (const auto & EFlowJet : EFlowJets) {

            JetMap.insert(std::pair<float, PseudoJet>(CandidateJet.delta_R(EFlowJet), EFlowJet));

        }


        if (JetMap.size() == 0) {

            Print(0, "No JetMap", Id);
            continue;

        }

        map<float, PseudoJet>::iterator JetPair = JetMap.end();
        --JetPair;
        const float MaxRadius = (*JetPair).first;
        Print(1, "MaxRadius", MaxRadius);

        HJetPropertiesBranch *Jet = static_cast<HJetPropertiesBranch *>(ParticleBranch->NewEntry());
        Jet->Mass = CandidateJet.m();
        Jet->Pt = CandidateJet.pt();
        Jet->Eta = CandidateJet.eta();
        Jet->Phi = CandidateJet.phi_std();
        Jet->Radius = MaxRadius;

        float CandidatePt = 0;
        for (const auto & EFlowJet : EFlowJets) {

            CandidatePt += EFlowJet.pt();

        }
        Print(1, "Max Pt", CandidatePt);

        vector<PseudoJet> TrimmedJets;
        float SigmaPt = 0;
        float SigmaRadius = 0;
        JetPair = JetMap.begin();
        do {

            SigmaRadius = (*JetPair).first;
            TrimmedJets.push_back(JetPair->second);
            SigmaPt += (*JetPair).second.pt();

            Print(2, "EFlow", SigmaRadius, SigmaPt);

            ++JetPair;

        }   while (SigmaPt <= (TwoSigma * CandidatePt) && JetPair != JetMap.end());



        Print(1, "Radius", SigmaRadius);
        Print(1, "mini size", TrimmedJets.size());
        const PseudoJet MiniCandidateJet = fastjet::join(TrimmedJets);

        HJetPropertiesBranch *TrimmedJet = static_cast<HJetPropertiesBranch *>(TrimmedBranch->NewEntry());
        TrimmedJet->Mass = MiniCandidateJet.m();
        TrimmedJet->Pt = MiniCandidateJet.pt();
        TrimmedJet->Eta = MiniCandidateJet.eta();
        TrimmedJet->Phi = MiniCandidateJet.phi_std();
        TrimmedJet->Radius = SigmaRadius;


        JetDefinition CAJetDefinition(cambridge_algorithm, MaxRadius);

        ClusterSequence CAClusterSequence(EFlowJets, CAJetDefinition);
        vector<PseudoJet> CAInclusiveJets = CAClusterSequence.inclusive_jets(0);
        Print(3, "InclusiveJets Number", CAInclusiveJets.size());

        for (const auto & CAInclusiveJet : CAInclusiveJets) {

            if (CAInclusiveJet == 0 || CAInclusiveJet.m() <= 0) continue;

            float DeltaR = 0;
            for (const auto & Constituent : CAInclusiveJet.constituents()) {

                const float deltar = CAInclusiveJet.delta_R(Constituent);

                if (deltar > DeltaR) DeltaR = deltar;

            }


            HJetPropertiesBranch *CAFatJet = static_cast<HJetPropertiesBranch *>(CAFatJetBranch->NewEntry());
            CAFatJet->Mass = CAInclusiveJet.m();
            CAFatJet->Pt = CAInclusiveJet.pt();
            CAFatJet->Eta = CAInclusiveJet.eta();
            CAFatJet->Phi = CAInclusiveJet.phi_std();
            CAFatJet->Radius = DeltaR;


            fastjet::MassDropTagger MDT(0.67, 0.09);

            PseudoJet MDJet = MDT(CAInclusiveJet);
            if (MDJet == 0 && MDJet.m() <= 0) continue;

            HJetPropertiesBranch *CAMassDropJet = static_cast<HJetPropertiesBranch *>(CAMassDropBranch->NewEntry());
            CAMassDropJet->Mass = MDJet.m();
            CAMassDropJet->Pt = MDJet.pt();
            CAMassDropJet->Eta = MDJet.eta();
            CAMassDropJet->Phi = MDJet.phi_std();
            CAMassDropJet->Radius = DeltaR;


        }





        JetDefinition AktJetDefinition(antikt_algorithm, MaxRadius);

        ClusterSequence AktClusterSequence(EFlowJets, AktJetDefinition);
        vector<PseudoJet> AktInclusiveJets = AktClusterSequence.inclusive_jets(0);
        Print(3, "InclusiveJets Number", AktInclusiveJets.size());

        for (const auto & AktInclusiveJet : AktInclusiveJets) {

            if (AktInclusiveJet == 0 || AktInclusiveJet.m() <= 0) continue;

            float DeltaR = 0;
            for (const auto & Constituent : AktInclusiveJet.constituents()) {

                const float deltar = AktInclusiveJet.delta_R(Constituent);

                if (deltar > DeltaR) DeltaR = deltar;

            }


            HJetPropertiesBranch *AktFatJet = static_cast<HJetPropertiesBranch *>(AktFatJetBranch->NewEntry());
            AktFatJet->Mass = AktInclusiveJet.m();
            AktFatJet->Pt = AktInclusiveJet.pt();
            AktFatJet->Eta = AktInclusiveJet.eta();
            AktFatJet->Phi = AktInclusiveJet.phi_std();
            AktFatJet->Radius = DeltaR;


            fastjet::MassDropTagger MDT(0.67, 0.09);

            PseudoJet MDJet = MDT(AktInclusiveJet);
            if (MDJet == 0 && MDJet.m() <= 0) continue;

            HJetPropertiesBranch *AktMassDropJet = static_cast<HJetPropertiesBranch *>(AktMassDropBranch->NewEntry());
            AktMassDropJet->Mass = MDJet.m();
            AktMassDropJet->Pt = MDJet.pt();
            AktMassDropJet->Eta = MDJet.eta();
            AktMassDropJet->Phi = MDJet.phi_std();
            AktMassDropJet->Radius = DeltaR;


        }

        for (const auto & EFlowJet : EFlowJets) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJet.eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }


    }

    return 1;

}



