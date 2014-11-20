# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

    SubStructure = new hdelphes::HSubStructure();

    BottomTag = new hhiggscpv::HBottomTag();

    PairTag = new hhiggscpv::HPairTag();

//     DebugLevel = hanalysis::HObject::HDebug;

}

// void hhiggscpv::HAnalysis::SetMva(hmva::HMva *NewMva){
//
//     Mva = NewMva;
//
//     Reader = new hmva::HReader(Mva);
//
//     Reader->AddVariable();
//
//     Reader->BookMVA();
//
//
// };

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    delete Reader;

    delete Mva;

    delete BottomTag;

    delete PairTag;

    delete SubStructure;

}

std::vector<std::string> hhiggscpv::HAnalysis::GetStudyNames(const std::string &TaggerName) const
{

    if (TaggerName == "BTagger") {

        return {"Bottom", "LightJet"};

    } else if (TaggerName == "JetPair") {

        return  {"Higgs", "Pair"};

    } else if (TaggerName == "Event") {

        return  {"Signal", "Background"};
    }


}

std::vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &StudyName) const
{
    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

    hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.push_back(Test3);
//     return Files;

    hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
//     Files.push_back(Test4);

    hdelphes::HFile *Background = new hdelphes::HFile("pp-bbtt-bblvlv", "background");
    Background->SetCrosssection(3.215); // pb
    Background->SetError(0.012); // pb
    Files.push_back(Background);

    hdelphes::HFile *Even = new hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(30.02079); // pb
    Even->SetError(0.000078); // pb
//     Even->TagString="tag_2";
    Files.push_back(Even);

    hdelphes::HFile *Mix = new hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(30.01172); // pb
    Mix->SetError(0.000045); // pb
//     Mix->TagString="tag_2";
//     Files.push_back(Mix);

    hdelphes::HFile *Odd = new hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(30.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
//     Files.push_back(Odd);

    hdelphes::HFile *Test = new hdelphes::HFile("pp-hjj-bbjj");
//     Files.push_back(Test);

    hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
//     Files.push_back(Test2);

//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.push_back(Signal);

    Print(HNotification, "Files prepared");

    return Files;

}


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(HNotification, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HEventBranch::Class());
    PairBranch = TreeWriter->NewBranch("Pair", HPairBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
    BTaggerBranch = TreeWriter->NewBranch("BTagger", HBTaggerBranch::Class());

}

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Analysis", StudyName);
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    if (StudyName == "Bottom" || StudyName == "LightJet") {

        if (GetBTag(Event, StudyName)) return 1;

    } else if (StudyName == "Higgs" || StudyName == "Pair") {

        if (GetPair(Event, StudyName)) return 1;

    } else if (StudyName == "Event") {

        if (GetEvent(Event, StudyName)) return 1;

    }

    return 0;

}


bool hhiggscpv::HAnalysis::GetBTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Analysis", StudyName);

    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(BottomTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (StudyName == "Bottom") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            Print(HInformation, "Truth Level", (*it).user_info<hanalysis::HJetInfo>().GetMaximalId());
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId || (*it).user_info<hanalysis::HJetInfo>().GetMaximalFraction() < .8) {
                it = Jets.erase(it);
            } else {
                //               (*it).user_info<hanalysis::HJetInfo>().SetBTag(1.);
                ++it;
            }
        }


    } else if (StudyName == "LightJet") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
                it = Jets.erase(it);
            } else {
                //               (*it).user_info<hanalysis::HJetInfo>().SetBTag(0.);
                ++it;
            }
        }

    }


    if (Jets.size() < 1) {
        Print(HInformation, "Not Jets");
        return 0;
    }
    Print(HInformation, "Number Jets", Jets.size());

    for (const auto & Jet : Jets) {

        HBTaggerBranch *BTagger = static_cast<HBTaggerBranch *>(BTaggerBranch->NewEntry());


        FillBTagger(Jet, BTagger);

    }


    return 1;

}

void hhiggscpv::HAnalysis::FillBTagger(const fastjet::PseudoJet &Jet, HBTaggerBranch *BTagger)
{

    BTagger->JetMass = Jet.m();

    Print(HInformation, "Mass", Jet.m());
    //         if (Jet.has_constituents()) {
    //             BTagger->Pull = SubStructure->GetDiPolarity(Jet);
    //             BTagger->DeltaR = SubStructure->GetDeltaR();
    //         }
    if (Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HInformation, "Has Info", BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
        BTagger->VertexNumber = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
    }

}





struct SortByInvMass {

    inline bool operator()(const hdelphes::HSuperStructure &JetPair1,
                           const hdelphes::HSuperStructure &JetPair2) {

        return (JetPair1.GetHiggsDeltaM() < JetPair2.GetHiggsDeltaM());

    }

};



struct SortByLikeliness {

    inline bool operator()(const fastjet::PseudoJet &Jet1,
                           const fastjet::PseudoJet &Jet2) {

        return (Jet1.user_info<hanalysis::HJetInfo>().GetFraction(hanalysis::HObject::HParticleId::CpvHiggsId) < Jet2.user_info<hanalysis::HJetInfo>().GetFraction(hanalysis::HObject::HParticleId::CpvHiggsId));

    }

};


bool hhiggscpv::HAnalysis::GetPair(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    PairTag->SetHeavyParticles( {CpvHiggsId, HiggsId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(PairTag);
    if (Jets.size() < 2) return 0;

    HJets HiggsJets;
    HJets OtherJets;
    for (const auto & Jet : Jets) {
        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == CpvHiggsId) {
            HiggsJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }

    Print(HInformation, "Higgsness", Jets[0].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId), Jets[1].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId));

    for (auto & Jet : Jets) {

        HBTaggerBranch *BTagger = new HBTaggerBranch();
        FillBTagger(Jet, BTagger);
        Print(HInformation, "Get Bdt from Mva", Mva->TaggerName);
        float Bdt = Mva->GetBdt(BTagger, Reader->Reader);

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        JetInfo->SetBTag(Bdt);
        Jet.set_user_info(JetInfo);

        Print(HInformation, "B Bdt", Bdt);
    }

    std::vector<hdelphes::HSuperStructure> JetPairs;

    if (StudyName == "Higgs") {
        Print(HInformation, "Higgs Jets", HiggsJets.size());
        if (HiggsJets.size() < 2) return 0;
        for (HJets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
    }

    if (StudyName == "Pair") {
        if (OtherJets.size() < 2 || (OtherJets.size() < 1 && HiggsJets.size() < 1)) return 0;
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Got pairs", JetPairs.size());


    if (JetPairs.size() <= 1) {
        Print(HInformation, "Number of Jet Pairs", JetPairs.size());
        return 0;
    }


    for (const auto & Pair : JetPairs) {
        HPairBranch *Candidate = static_cast<HPairBranch *>(PairBranch->NewEntry());
        FillPairTagger(Pair, Candidate);
    }

    return 1;

}

void hhiggscpv::HAnalysis::FillPairTagger(const hdelphes::HSuperStructure &Pair, HPairBranch *PairTagger)
{

    PairTagger->InvMass = Pair.GetInvariantMass();
    PairTagger->DeltaR = Pair.GetDeltaR();
    PairTagger->BTag = Pair.GetBTag();
}


struct SortPairsByLikeliness {
    inline bool operator()(const hdelphes::HSuperStructure &Pair1, const hdelphes::HSuperStructure &Pair2) {
        return (Pair1.Tag < Pair1.Tag);
    }
};

bool hhiggscpv::HAnalysis::GetEvent(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    HJets Jets = Event->GetJets()->GetStructuredJets();

    if (Jets.size() < 2) return 0;
    std::vector<hdelphes::HSuperStructure> JetPairs;
    for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
            JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
            JetPairs.push_back(JetPair);
        }
    }


    for (auto & JetPair : JetPairs) {

        HPairBranch *PairBranch = new HPairBranch();

        FillPairTagger(JetPair, PairBranch);
        float Bdt = Mva->GetBdt(PairBranch, Reader->Reader);
        JetPair.Tag = Bdt;

        Print(HInformation, "B Bdt", Bdt);
    }

    std::sort(JetPairs.begin(), JetPairs.end(), SortPairsByLikeliness());



    HEventBranch *Candidate = static_cast<HEventBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJets()->GetScalarHt();
    Candidate->JetNumber = Event->GetJets()->GetJets().size();
    Candidate->BottomNumber = Event->GetJets()->GetBottomJets().size();
    Candidate->HiggsTag = JetPairs.front().Tag;

    return 1;
}
//     if (JetPairs.size() > 0) {
//         Print(HInformation, "Pair1", JetPairs.at(0).GetPosition1(), JetPairs.at(0).GetPosition2(), JetPairs.at(0).GetInvariantMass());
//         FillCandidate(JetPairs.at(0), &Candidate->InvMass1, &Candidate->DeltaR1, &Candidate->Pull1, &Candidate->BTag1);
//         if (JetPairs.size() > 1) {
//             FillCandidate(JetPairs.at(1), &Candidate->InvMass2, &Candidate->DeltaR2, &Candidate->Pull2, &Candidate->BTag2);
//             if (JetPairs.size() > 2) {
//                 FillCandidate(JetPairs.at(2), &Candidate->InvMass3, &Candidate->DeltaR3, &Candidate->Pull3, &Candidate->BTag3);
//             }
//
//         }
//
//         if (Candidate->Pull3 != -10)return 1;
//
//     }



// void hhiggscpv::HAnalysis::FillCandidate(
//     const hdelphes::HSuperStructure &JetPair,
//     float *const InvMass,
//     float *const DeltaR,
//     float *const Pull,
//     float *const BTag
// ) const
// {
//
//     Print(HInformation, "FillCandidate", JetPair.GetPosition1(), JetPair.GetPosition2());
//
//     *InvMass = JetPair.GetInvariantMass();
//     *DeltaR = JetPair.GetDeltaR();
//     if (JetPair.GetJet1().has_constituents()) *Pull = JetPair.GetPullAngle();
//
//     *BTag = JetPair.GetBTag();
//
//
//
// }






//         HVectors ConstituentVectors = FirstPair.GetConstituents();
//         for (const auto & ConstituentVector : ConstituentVectors) {
//
//
//           if (std::abs(ConstituentVector.Eta()) > LargeNumber) {
//             Print(HError, "ERROR");
//             continue;
//           }
//
//             HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
//             Constituent->Eta = ConstituentVector.Eta();
//             Constituent->Phi = ConstituentVector.Phi();
//             Constituent->Pt = ConstituentVector.Pt();
//
//         }


//     std::sort(Jets.begin(), Jets.end(), SortJetByPt());

// std::vector<hdelphes::HSuperStructure> JetPairs;
// for (unsigned JetPosition1 = 0; JetPosition1 < Jets.size(); ++JetPosition1)
// {
// 
//     //         if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
//     //         hanalysis::HJetInfo = Jets[JetPosition1].user_info<hanalysis::HJetInfo>();
//     //         if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;
// 
//     //         Print(HDebug, "Distance", Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement());
//     for (unsigned JetPosition2 = JetPosition1 + 1; JetPosition2 < Jets.size() ; ++JetPosition2) {
// 
//         //             if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
//         //             if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;
// 
//         hdelphes::HSuperStructure JetPair(Jets[JetPosition1], Jets[JetPosition2]);
//         JetPair.SetPosition1(JetPosition1);
//         JetPair.SetPosition2(JetPosition2);
//         JetPair.SetBTag(Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetBTag(), Jets[JetPosition2].user_info<hanalysis::HJetInfo>().GetBTag());
//         JetPairs.push_back(JetPair);
//     }
// }
// 
// 
// std::sort(JetPairs.begin(), JetPairs.end(), SortByInvMass());
// 
// Print(HInformation, "Got pairs", JetPairs.size());
// 
// for (std::vector<hdelphes::HSuperStructure>::iterator it = JetPairs.begin(); it != JetPairs.end(); ++it)
// {
//     for (std::vector<hdelphes::HSuperStructure>::iterator it2 = JetPairs.begin(); it2 != JetPairs.end();) {
//         if ((*it).IsSamePair(*it2) && it2 > it) {
//             it2 = JetPairs.erase(it2);
//         } else {
//             ++it2;
//         }
//     }
//     if (it == JetPairs.end()) break;
// }
// 
// 
// if (JetPairs.size() <= 1)
// {
//     Print(HInformation, "Number of Jet Pairs", JetPairs.size());
//     return 0;
// }
