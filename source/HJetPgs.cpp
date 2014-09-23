# include "HJetPgs.hh"

HJetPgs::HJetPgs()
{

    Print(0, "Constructor");

//     Debug = 4;

}

HJetPgs::~HJetPgs()
{

    Print(0, "Destructor");

}

bool HJetPgs::GetJets()
{

    Print(1, "Get Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(2, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJet(JetClone));

        if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");

            BottomLorentzVectorVector.push_back(GetLorentzVector(JetClone));
            BottomJetVector.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectorVector.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(2, "Untagged jets", JetLorentzVectorVector.size());
    
    return 1;

}
