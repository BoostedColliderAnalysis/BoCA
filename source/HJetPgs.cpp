# include "HJetPgs.hh"

HJetPgs::HJetPgs()
{

    Print(1, "Constructor");

//     Debug = 4;

}

HJetPgs::~HJetPgs()
{

    Print(1, "Destructor");

}

bool HJetPgs::GetJets()
{

    Print(2, "Get Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    Print(3, "Number of Jets", JetClonesArray->GetEntriesFast());

    for (int JetNumber = 0; JetNumber < JetClonesArray->GetEntriesFast(); ++JetNumber) {

        Print(4, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)JetClonesArray->At(JetNumber);

        Jets.push_back(GetPseudoJet(JetClone));

        if (JetClone->BTag > 0) {

            Print(4, "Has B Tag");

            BottomLorentzVectors.push_back(GetLorentzVector(JetClone));
            BottomJets.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectors.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(3, "Untagged jets", JetLorentzVectors.size());
    
    return 1;

}
