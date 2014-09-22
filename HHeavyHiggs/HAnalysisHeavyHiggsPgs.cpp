# include "HAnalysisHeavyHiggsPgs.hh"

HAnalysisHeavyHiggsPgs::HAnalysisHeavyHiggsPgs()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggsPgs";

    EventNumberMax = 10000;

    Cut = 1;

}

void HAnalysisHeavyHiggsPgs::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    FileVector.push_back(new HFileFolder("Signal_5f"));
    FileVector.push_back(new HFileFolder("5f_10k_Pt20"));

    FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->FileSuffix = "_PGS.root";
    FileVector.front()->TreeString = "LHCO";

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysisHeavyHiggsPgs::NewFile()
{

    Print(0, "New File");
    

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());

    
    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void HAnalysisHeavyHiggsPgs::CloseFile()
{
    Print(0, "Close File");

    if (Cut) {

        Print(0, "EventCounter", EventCounter);
        Print(0, "JetCounter", JetCounter);
        Print(0, "DeltaEtaCounter", DeltaEtaCounter);
        Print(0, "BMassCounter", BMassCounter);
        Print(0, "Jet2Counter", Jet2Counter);
        Print(0, "TMassCounter", TMassCounter);

    }

}


bool HAnalysisHeavyHiggsPgs::Analysis()
{

    Print(1, "Analysis");
        
    Event->GetJets();
    
    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;
    
    
    Print(1, "Got B Jet Vector");
    
    if (BJets.size() > 1) {
        
        for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
            
            for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {
                
                PseudoJet FrontJet, BackJet;
                
                if (BJets[BJetNumber].eta() > BJets[BJetNumber2].eta()) {
                    
                    FrontJet = BJets[BJetNumber];
                    BackJet = BJets[BJetNumber2];
                    
                } else {
                    
                    FrontJet = BJets[BJetNumber2];
                    BackJet = BJets[BJetNumber];
                    
                }
                
                float FrontPt = FrontJet.pt();
                float FrontEta = FrontJet.eta();
                float FrontPhi = FrontJet.phi();
                
                float BackEta = BackJet.eta();
                float BackPt = BackJet.pt();
                float BackPhi = BackJet.phi();
                
                float InvMass = (FrontJet + BackJet).m();
                float DeltaEta = FrontEta - BackEta;
                float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);
                
                HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());
                
                HeavyHiggs->BottomEta1 = FrontEta;
                HeavyHiggs->BottomEta2 = BackEta;
                HeavyHiggs->BottomDeltaEta = DeltaEta;
                
                HeavyHiggs->BottomPhi1 = FrontPhi;
                HeavyHiggs->BottomPhi2 = BackPhi;
                HeavyHiggs->BottomDeltaPhi = DeltaPhi;
                
                HeavyHiggs->BottomPt1 = FrontPt;
                HeavyHiggs->BottomPt2 = BackPt;
                HeavyHiggs->BottomInvMass = InvMass;
                
                HeavyHiggs->BTag = BJets.size();
                HeavyHiggs->JetNumber = Event->Jets->JetVector.size();
                
            }
            
        }
        
        return 1;
        
    }
    
    return 0;

}
