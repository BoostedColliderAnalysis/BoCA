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
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(3, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

        Print(4, "Jet Number", JetNumber);
        TRootJet *JetClone = (TRootJet *)JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJet(JetClone));

        if (JetClone->BTag > 0) {

            Print(4, "Has B Tag");

            BottomLorentzVectorVector.push_back(GetLorentzVector(JetClone));
            BottomJetVector.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectorVector.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(3, "Untagged jets", JetLorentzVectorVector.size());
    
    return 1;

}
