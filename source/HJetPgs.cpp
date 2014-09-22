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

    Print(1, "Analyse Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(2, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        Jet *JetClone = (Jet *)JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJetPt(JetClone));

	if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");

            BottomLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));
            BottomJetVector.push_back(GetPseudoJetPt(JetClone));


        } else {

            JetLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));

        }

    }

    Print(2, "Untagged jets", JetLorentzVectorVector.size());
    
    return 1;

}
