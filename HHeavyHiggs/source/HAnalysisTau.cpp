# include "HAnalysisTau.hh"

// hheavyhiggs::HAnalysisTau::HAnalysisTau()
// {
//     Print(HNotification, "Constructor");
//     TauTagger.SetAnalysisName(ProjectName());
// //     JetPairTagger.SetAnalysisName(ProjectName());
// //     WHadronicTagger.SetAnalysisName(ProjectName());
//     HiggsTauTagger.SetAnalysisName(ProjectName());
// //     TopHadronicTagger.SetAnalysisName(ProjectName());
// //     TopSemiTagger.SetAnalysisName(ProjectName());
// //     ChargedHiggsSemiTagger.SetAnalysisName(ProjectName());
// //     EventSemiTagger.SetAnalysisName(ProjectName());
// }

// hheavyhiggs::HAnalysisTau::~HAnalysisTau()
// {
//     Print(HNotification, "Destructor");
// }


// std::string hheavyhiggs::HAnalysisTau::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case HTauTagger :
//         return "Tau";
//     case HTauReader :
//         return "TauReader";
//     case  HBottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case HHeavyHiggsTauTagger:
//         return  "HeavyHiggsTau";
//     case HHeavyHiggsTauReader:
//         return  "HeavyHiggsTauReader";
//     case HWHadronicTagger:
//         return  "WHadronic";
//     case HWHadronicReader:
//         return  "WHadronicReader";
//     case HJetPairTagger:
//         return  "ChargedJetPair";
//     case HJetPairReader:
//         return  "ChargedJetPairReader";
//     case HTopLeptonicTagger:
//         return  "TopLeptonic";
//     case HTopLeptonicReader:
//         return  "TopLeptonicReader";
//     case HTopHadronicTagger:
//         return  "TopHadronic";
//     case HTopSemiTagger:
//         return  "TopSemi";
//     case HTopHadronicReader:
//         return  "TopHadronicReader";
//     case HTopSemiReader:
//         return  "TopSemiReader";
//     case HHeavyHiggsLeptonicTagger:
//         return  "ChargedHiggsLeptonic";
//     case HHeavyHiggsHadronicTagger:
//         return  "ChargedHiggsHadronic";
//     case HHeavyHiggsSemiTagger:
//         return  "ChargedHiggsSemi";
//     case HHeavyHiggsSemiReader:
//         return  "ChargedHiggsSemiReader";
//     case HHeavyHiggsLeptonicReader:
//         return  "ChargedHiggsLeptonicReader";
//     case HEventLeptonicTagger:
//         return  "EventLeptonic";
//     case HEventHadronicTagger:
//         return  "EventHadronic";
//     case HEventSemiTagger:
//         return  "ChargedSemi";
//     case HEventLeptonicReader:
//         return  "ChargdLeptonicReader";
//     case HEventSemiReader:
//         return  "ChargedSemiReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<hanalysis::HFile> hheavyhiggs::HAnalysisTau::Files(const Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;

    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;

    std::vector<hanalysis::HFile> SignalSemiFiles;

//     SignalSemiFiles.push_back(hanalysis::HFile("1TeV",38.501952876819495,1000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("2TeV",3.7429107249252125,2000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("3TeV",0.7636108315783771,3000));
    SignalSemiFiles.push_back(hanalysis::HFile("Tau_4000", 0.22232809767415665, 4000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("5TeV",0.07946706739238736,5000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("6TeV",0.03291534649650638,6000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("8TeV",0.00738551034925011,8000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("10TeV",0.002068335074918064,10000));
//     SignalSemiFiles.push_back(hanalysis::HFile("12TeV",0.0006693740636689783,12000));
//     SignalSemiFiles.push_back(hanalysis::HFile("15TeV",0.00015145887990818783,15000));
//     SignalSemiFiles.push_back(hanalysis::HFile("20TeV",0.000016677670760729152,20000));

    std::vector<hanalysis::HFile> BackgroundSemiFiles;
    BackgroundSemiFiles.push_back(hanalysis::HFile("ttjj_400_0", 35.04));

    std::vector<hanalysis::HFile> SignalHadronicFiles;
//     SignalHadronicFiles.push_back(hanalysis::HFile("1TeV_Hbb_ttbb_jjbbbb");

    std::vector<hanalysis::HFile> BackgroundHadronicFiles;
//     BackgroundHadronicFiles.push_back(hanalysis::HFile("BG_jjbbbb");



    std::vector<hanalysis::HFile> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<hanalysis::HFile> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::HFile> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::HFile> NewFiles;

//     switch (Tagger) {
//     case  HTauTagger :
//         NewFiles = CombinedFiles;
//         break;
//     case  HTauReader :
//         NewFiles = CombinedFiles;
//         break;
//     case HJetPairTagger:
//         if (Tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = CombinedFiles;
//         break;
//     case HJetPairReader:
//         if (Tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = CombinedFiles;
//         break;
//     case HHeavyHiggsTauTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HHeavyHiggsTauReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HWHadronicTagger:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HWHadronicReader:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopHadronicTagger:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HTopHadronicReader:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HHeavyHiggsLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = HadronicFiles;
//         break;
//     case HHeavyHiggsSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;//BackgroundSemiFiles;
//         break;
//     case HHeavyHiggsSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case HEventSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         Print(HError, "unknown tagger name");
//     }

    switch (tag) {
      case HObject::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case HObject::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    NewFiles.front().SetFileSuffix(".root");

    Print(HNotification, "Files prepared");

    SetTrees();

//     PrepareReader(Tagger, Tag);

    return NewFiles;

}

void hheavyhiggs::HAnalysisTau::SetTrees()
{

    HStrings SignalLeptonicTrees {
    };
    HStrings BackgroundLeptonicTrees {
    };

    HStrings SignalSemiTrees {
//                 "1TeV-run_01",
//                       "2TeV-run_01",
//                       "3TeV-run_01"
        "Tau_4000-run_01"
//         "5TeV-run_01"
//                 "6TeV-run_01"
//               "7TeV-run_01"
//                 "8TeV-run_01"
//                 "9TeV-run_01"
//         "10TeV-run_01"
//         "12TeV-run_01"
//         "15TeV-run_01"
        //         "zbb-run_01"
    };

    HStrings BackgroundSemiTrees {
        "ttjj_400_0-run_01"
//         "BG_ttcc_ljbbcc-run_01"
    };

    HStrings SignalHadronicTree {
        //       "1TeV_Hbb_ttbb_jjbbbb-run_01"
    };
    HStrings BackgroundHadronicTrees {
        //       "BG_jjbbbb-run_01"
    };


    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);

//     switch (Tagger) {
//     case HTauTagger:
//         TauTagger.SetSignalTreeNames(CombinedTrees);
//         TauTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal)  TauTagger.SetTagger();
//         break;
//     case HTauReader:
//         break;
// //     case HJetPairTagger :
// //         JetPairTagger.SetSignalTreeNames(CombinedTrees);
// //         JetPairTagger.SetBackgroundTreeNames(CombinedTrees);
// //         if (Tag == kSignal) JetPairTagger.SetTagger(TauTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
// //         break;
// //     case HJetPairReader :
// //         break;
// //     case HWHadronicTagger:
// //         WHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
// //         WHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
// //         if (Tag == kSignal) WHadronicTagger.SetTagger(TauTagger);
// //         break;
// //     case HWHadronicReader :
// //         TauTagger.SetSignalTreeNames(CombinedTrees);
// //         TauTagger.SetBackgroundTreeNames(CombinedTrees);
// //         if (Tag == kSignal) WHadronicTagger.SetTagger(TauTagger);
// //         break;
//     case HHeavyHiggsTauTagger :
//         HiggsTauTagger.SetSignalTreeNames(SignalSemiTrees);
//         HiggsTauTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) HiggsTauTagger.SetTagger(TauTagger);
//         break;
//     case HHeavyHiggsTauReader :
//         TauTagger.SetSignalTreeNames(CombinedTrees);
//         TauTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal) HiggsTauTagger.SetTagger(TauTagger);
//         break;
// //     case HTopHadronicTagger :
// //         if (Tag == kSignal) TopHadronicTagger.SetTagger(TauTagger, WHadronicTagger);
// //         TopHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
// //         TopHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
// //         break;
// //     case HTopHadronicReader :
// //         break;
// //     case HTopSemiTagger :
// //         if (Tag == kSignal) TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         TopSemiTagger.SetSignalTreeNames(SemiTrees);
// //         TopSemiTagger.SetBackgroundTreeNames(SemiTrees);
// //         break;
// //     case HTopSemiReader :
// //         break;
// //     case HHeavyHiggsSemiTagger  :
// //         if (Tag == kSignal) ChargedHiggsSemiTagger.SetTagger(TauTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
// //         ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         ChargedHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
// //         break;
// //     case HHeavyHiggsSemiReader :
// //         break;
// //     case HEventSemiTagger :
// //         if (Tag == kSignal) EventSemiTagger.SetTagger(TauTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
// //         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
// //     case HEventSemiReader :
// //         if (Tag == kSignal) EventSemiTagger.SetTagger(TauTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
// //         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
//     default :
//         Print(HError, "unhandled case");
    //     }
    tagger_.SetSignalTreeNames(SignalSemiTrees);
    tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void hheavyhiggs::HAnalysisTau::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(HInformation, "Prepare Reader", Tagger);
//
//     if (Tag == kBackground) return;
//
//     switch (Tagger) {
//     case HTauTagger:
//         break;
//     case HTauReader:
//         TauReader.SetMva(TauTagger);
//         break;
// //     case HWHadronicTagger:
// //         WHadronicTagger.BottomTagger.SetTagger();
// //         WHadronicTagger.BottomReader.SetMva(WHadronicTagger.BottomTagger);
// //         break;
// //     case HWHadronicReader:
// //         TauReader.SetMva(TauTagger);
// //         WHadronicReader.SetMva(WHadronicTagger);
// //         break;
//     case HHeavyHiggsTauTagger :
//         HiggsTauTagger.TauTagger.SetTagger();
//         HiggsTauTagger.TauReader.SetMva(HiggsTauTagger.TauTagger);
//         break;
//     case HHeavyHiggsTauReader :
//         TauReader.SetMva(TauTagger);
//         HeavyHiggsTauReader.SetMva(HiggsTauTagger);
//         break;
// //     case HTopHadronicTagger :
// //         TopHadronicTagger.BottomTagger.SetTagger();
// //         TopHadronicTagger.BottomReader.SetMva(TopHadronicTagger.BottomTagger);
// //         TopHadronicTagger.WTagger.SetTagger(TauTagger);
// //         TopHadronicTagger.WReader.SetMva(TopHadronicTagger.WTagger);
// //         break;
// //     case HTopHadronicReader :
// //         TauReader.SetMva(TauTagger);
// //         WHadronicReader.SetMva(WHadronicTagger);
// //         TopHadronicReader.SetMva(TopHadronicTagger);
// //         break;
// //     case HTopSemiTagger :
// //         TopSemiTagger.BottomTagger.SetTagger();
// //         TopSemiTagger.BottomReader.SetMva(TopSemiTagger.BottomTagger);
// //         TopSemiTagger.WSemiTagger.SetTagger();
// //         TopSemiTagger.WSemiReader.SetMva(TopSemiTagger.WSemiTagger);
// //         break;
// //     case HTopSemiReader :
// //         TauReader.SetMva(TauTagger);
// //         WSemiReader.SetMva(WSemiTagger);
// //         TopSemiReader.SetMva(TopSemiTagger);
// //         break;
// //     case HHeavyHiggsSemiTagger :
// //         ChargedHiggsSemiTagger.BottomTagger.SetTagger();
// //         ChargedHiggsSemiTagger.BottomReader.SetMva(ChargedHiggsSemiTagger.BottomTagger);
// //         ChargedHiggsSemiTagger.WSemiTagger.SetTagger();
// //         ChargedHiggsSemiTagger.WSemiReader.SetMva(ChargedHiggsSemiTagger.WSemiTagger);
// //         ChargedHiggsSemiTagger.WTagger.SetTagger(TauTagger);
// //         ChargedHiggsSemiTagger.WReader.SetMva(ChargedHiggsSemiTagger.WTagger);
// //         ChargedHiggsSemiTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         ChargedHiggsSemiTagger.TopSemiReader.SetMva(ChargedHiggsSemiTagger.TopSemiTagger);
// //         ChargedHiggsSemiTagger.TopHadronicTagger.SetTagger(TauTagger, WHadronicTagger);
// //         ChargedHiggsSemiTagger.TopHadronicReader.SetMva(ChargedHiggsSemiTagger.TopHadronicTagger);
// //         break;
// //     case HHeavyHiggsSemiReader  :
// //         TauReader.SetMva(TauTagger);
// //         WSemiReader.SetMva(WSemiTagger);
// //         TopSemiReader.SetMva(TopSemiTagger);
// //         WHadronicReader.SetMva(WHadronicTagger);
// //         TopHadronicReader.SetMva(TopHadronicTagger);
// //         ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
// //         break;
// //     case HJetPairTagger :
// //         JetPairTagger.BottomTagger.SetTagger();
// //         JetPairTagger.BottomReader.SetMva(JetPairTagger.BottomTagger);
// //         JetPairTagger.WSemiTagger.SetTagger();
// //         JetPairTagger.WSemiReader.SetMva(JetPairTagger.WSemiTagger);
// //         JetPairTagger.WTagger.SetTagger(TauTagger);
// //         JetPairTagger.WReader.SetMva(JetPairTagger.WTagger);
// //         JetPairTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         JetPairTagger.TopSemiReader.SetMva(JetPairTagger.TopSemiTagger);
// //         JetPairTagger.TopHadronicTagger.SetTagger(TauTagger, WHadronicTagger);
// //         JetPairTagger.TopHadronicReader.SetMva(JetPairTagger.TopHadronicTagger);
// //         break;
// //     case HJetPairReader :
// //         TauReader.SetMva(TauTagger);
// //         WSemiReader.SetMva(WSemiTagger);
// //         TopSemiReader.SetMva(TopSemiTagger);
// //         WHadronicReader.SetMva(WHadronicTagger);
// //         TopHadronicReader.SetMva(TopHadronicTagger);
// //         JetPairReader.SetMva(JetPairTagger);
// //         break;
// //     case HEventSemiTagger :
// //         EventSemiTagger.BottomTagger.SetTagger();
// //         EventSemiTagger.BottomReader.SetMva(EventSemiTagger.BottomTagger);
// //         EventSemiTagger.WSemiTagger.SetTagger();
// //         EventSemiTagger.WSemiReader.SetMva(EventSemiTagger.WSemiTagger);
// //         EventSemiTagger.WTagger.SetTagger(TauTagger);
// //         EventSemiTagger.WReader.SetMva(EventSemiTagger.WTagger);
// //         EventSemiTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         EventSemiTagger.TopSemiReader.SetMva(EventSemiTagger.TopSemiTagger);
// //         EventSemiTagger.TopHadronicTagger.SetTagger(TauTagger, WHadronicTagger);
// //         EventSemiTagger.TopHadronicReader.SetMva(EventSemiTagger.TopHadronicTagger);
// //         EventSemiTagger.ChargedHiggsSemiTagger.SetTagger(TauTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
// //         EventSemiTagger.ChargedHiggsSemiReader.SetMva(EventSemiTagger.ChargedHiggsSemiTagger);
// //         EventSemiTagger.ChargedJetPairTagger.SetTagger(TauTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
// //         EventSemiTagger.ChargedJetPairReader.SetMva(EventSemiTagger.ChargedJetPairTagger);
// //         break;
// //     case HEventSemiReader :
// //         TauReader.SetMva(TauTagger);
// //         WSemiReader.SetMva(WSemiTagger);
// //         TopSemiReader.SetMva(TopSemiTagger);
// //         WHadronicReader.SetMva(WHadronicTagger);
// //         TopHadronicReader.SetMva(TopHadronicTagger);
// //         JetPairReader.SetMva(JetPairTagger);
// //         ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
// //         EventSemiReader.SetMva(EventSemiTagger);
// //         break;
//     default :
//         Print(HError, "unhandled case");
//     }
//
// }

// void hheavyhiggs::HAnalysisTau::ResetBranch()
// {
    //         Branch.reset();
// }

// void hheavyhiggs::HAnalysisTau::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
// {
//     Print(HNotification, "New Branches", Tagger);
//
//     switch (Tagger) {
//     case HTauTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTauBranch::Class());
//         break;
//     case HTauReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTauBranch::Class());
//         break;
// //     case HJetPairTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
// //         break;
// //     case HJetPairReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
// //         break;
//     case HHeavyHiggsTauTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsTauBranch::Class());
//         break;
//     case HHeavyHiggsTauReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsTauBranch::Class());
//         break;
// //     case HWHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
// //         break;
// //     case HWHadronicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
// //         break;
// //     case HTopLeptonicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
// //         break;
// //     case HTopLeptonicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
// //         break;
// //     case HTopHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
// //         break;
// //     case HTopSemiTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
// //         break;
// //     case HTopHadronicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
// //         break;
// //     case HTopSemiReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
// //         break;
// //     case HHeavyHiggsLeptonicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
// //         break;
// //     case HHeavyHiggsLeptonicReader:
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
// //         break;
// //     case HHeavyHiggsHadronicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
// //         break;
// //     case HHeavyHiggsSemiTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
// //         break;
// //     case HHeavyHiggsSemiReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
// //         break;
// //     case HEventLeptonicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
// //         break;
// //     case HEventHadronicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventHadronicBranch::Class());
// //         break;
// //     case HEventSemiTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
// //         break;
// //     case HEventSemiReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
// //         break;
// //     case HEventLeptonicReader :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
// //         break;
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }


// struct MinPt {
//   MinPt(const float NewPt) {
//     this->Pt = NewPt;
//   }
//   bool operator()(const fastjet::PseudoJet &Jet) {
//     return (Jet.pt() < Pt);
//   }
//   float Pt;
// };

int hheavyhiggs::HAnalysisTau::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{

    Print(HInformation, "Analysis", stage);

//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    HJets Leptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());

//     if (Leptons.empty()) return 0;
//     if (Leptons.front().pt() < 300 || MissingEt.pt() < 400) return 0;
//     if (Leptons.front().pt() < 300) return 0;
    ++event_sum_;

//     switch (stage) {
//     case HTauTagger :
//         return GetTauTag(Event, tag);
//     case HTauReader:
//         return GetTauReader(Event, tag);
// //     case HJetPairTagger :
// //         return GetJetPairTag(Event, Tag);
// //     case HJetPairReader :
// //         return GetJetPairReader(Event, Tag);
// //     case HWHadronicTagger :
// //         return GetWTag(Event, Tag);
// //     case HWHadronicReader :
// //         return GetWReader(Event, Tag);
//     case HHeavyHiggsTauTagger :
//         return GetHeavyHiggsTauTag(Event, tag);
//     case HHeavyHiggsTauReader :
//         return GetHeavyHiggsTauReader(Event, tag);
// //     case HTopLeptonicTagger :
// //         return GetTopLeptonicTag(Event, Tag);
// //     case HTopHadronicTagger :
// //         return GetTopHadronicTag(Event, Tag);
// //     case HTopSemiTagger :
// //         return GetTopSemiTag(Event, Tag);
// //     case HTopHadronicReader :
// //         return GetTopHadronicReader(Event, Tag);
// //     case HTopLeptonicReader :
// //         return GetTopLeptonicReader(Event, Tag);
// //     case HTopSemiReader :
// //         return GetTopSemiReader(Event, Tag);
// //     case HHeavyHiggsLeptonicTagger :
// // //         return GetHeavyHiggsLeptonicTag(Event, Tag);
// //     case HHeavyHiggsHadronicTagger :
// // //         return GetHeavyHiggsHadronicTag(Event, Tag);
// //     case HHeavyHiggsSemiTagger :
// //         return GetChargedHiggsSemiTag(Event, Tag);
// //     case HHeavyHiggsSemiReader :
// //         return GetChargdHiggsSemiReader(Event, Tag);
// //     case HHeavyHiggsLeptonicReader :
// // //         return GetHeavyHiggsLeptonicReader(Event, Tag);
// //     case HEventLeptonicTagger :
// // //         return GetEventLeptonicTag(Event, Tag);
// //     case HEventHadronicTagger :
// // //         return GetEventHadronicTag(Event, Tag);
// //     case HEventSemiTagger :
// //         return GetEventSemiTag(Event, Tag);
// //     case HEventSemiReader :
// //         return GetEventSemiReader(Event, Tag);
// //     case HEventLeptonicReader :
// //         return GetEventLeptonicReader(Event, Tag);
//     default :
//         Print(HError, "unknown Tagger", stage);
//         return 0;
    //     }
    return tagger_.GetBranches(event, stage, tag);
}


// bool hheavyhiggs::HAnalysisTau::GetTauTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Tau Tag", Tag);
//     std::vector<HTauBranch> Taus = TauTagger.GetBranches(Event, Tag);
//     if (Taus.empty()) return 0;
//     for (const auto & Tau : Taus) *static_cast<HTauBranch *>(Branch->NewEntry()) = Tau;
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisTau::GetTauReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Tau Reader", Tag);
//     HJets Jets = TauTagger.GetJets(Event, JetTag);
//     Jets = TauTagger.GetJetBdt(Jets, TauReader);
//
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(TauId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         if (Jets.front().delta_R(Particle) < 0.4) static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         *static_cast<HTauBranch *>(Branch->NewEntry()) = TauTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTau::GetHeavyHiggsTauTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get HeavyHiggs Tau Tag", Tag);
//     std::vector<HHeavyHiggsTauBranch> HeavyHiggses = HiggsTauTagger.GetBranches(Event, Tag);
//     if (HeavyHiggses.empty()) return 0;
//     for (const auto & Higgs : HeavyHiggses) *static_cast<HHeavyHiggsTauBranch *>(Branch->NewEntry()) = Higgs;
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTau::GetHeavyHiggsTauReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get W Semi Reader", Tag);
//
//     HJets Jets = TauTagger.GetJets(Event, JetTag);
//     Jets = TauTagger.GetJetBdt(Jets, TauReader);
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//
//     std::vector<hanalysis::HDoublet> Doublets = HiggsTauTagger.GetBdt(Jets, MissingEt, HeavyHiggsTauReader);
//
//     if (Doublets.empty()) return 0;
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) *static_cast<HHeavyHiggsTauBranch *>(Branch->NewEntry()) = HiggsTauTagger.GetBranch(Doublet);
//
//     return 1;
// }
//
// // bool hheavyhiggs::HAnalysisTau::GetWTag(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HDebug, "Get W Tag", Tag);
// //     std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
// //     if (Ws.empty()) return 0;
// //     for (const auto & W : Ws) *static_cast<HWBranch *>(Branch->NewEntry()) = W;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetWReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = TauTagger.GetJets(Event);
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //
// //     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //
// //     for (const auto & Jet : Jets) {
// //         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
// //         Doublets.insert(Doublets.end(), PieceDoublets.begin(), PieceDoublets.end());
// //     }
// //
// //     for (const auto & Jet : Jets) {
// //         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
// //         Doublets.insert(Doublets.end(), PieceDoublets.begin(), PieceDoublets.end());
// //     }
// //
// //
// //     if (Doublets.size() > 1) {
// //         std::sort(Doublets.begin(), Doublets.end());
// //         Doublets.erase(Doublets.begin() + 1, Doublets.end());
// //     }
// //
// //     for (const auto & Doublet : Doublets) *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
// //
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopLeptonicTag(hanalysis::HEvent &Event,  HTag Tag)
// // {
// //     Print(HInformation, "Get leptonic top", Tag);
// //     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = Event.GetJets()->GetStructuredJets();
// //     Jets = TauTagger.GetBdt(Jets, TauReader);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);
// //
// //     if (Doublets.size() > 1) {
// //         std::sort(Doublets.begin(), Doublets.end());
// //         Doublets.erase(Doublets.begin() + 1, Doublets.end());
// //     }
// //
// //     for (const auto & Doublet : Doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopHadronicTag(hanalysis::HEvent &Event,  HTag Tag)
// // {
// //     Print(HInformation, "Get hadronic tops", Tag);
// //     std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(Branch->NewEntry());
// //         *TopTagger = Top;
// //     }
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = TopHadronicTagger.GetJets(Event);
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
// //
// //     for (const auto & Jet : Jets) {
// //         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
// //         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
// //         Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
// //     }
// //
// //     for (const auto & Jet : Jets) {
// //         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
// //         std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
// //         Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
// //     }
// //
// //
// //     if (Triplets.size() > 1) {
// //         std::sort(Triplets.begin(), Triplets.end());
// //         Triplets.erase(Triplets.begin() + 1, Triplets.end());
// //     }
// //
// //     for (const auto & Triplet : Triplets) {
// //         HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(Branch->NewEntry());
// //         *TopTagger = TopHadronicTagger.GetBranch(Triplet);
// //     }
// //
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
// // {
// //     Print(HInformation, "Get Tops", Tag);
// //     std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// // //     HJets Jets = Event.GetJets()->GetStructuredJets();
// //
// //     HJets Jets = TauTagger.GetJets(Event);
// //
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);
// //
// //     if (Triplets.size() > 1) {
// //         std::sort(Triplets.begin(), Triplets.end());
// //         Triplets.erase(Triplets.begin() + 1, Triplets.end());
// //     }
// //
// //     for (const auto & Triplet : Triplets) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
// //
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetJetPairTag(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HDebug, "Get JetPair Tag", Tag);
// //     std::vector<HChargedJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
// //     if (JetPairs.empty()) return 0;
// //     for (const auto & JetPair : JetPairs) *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPair;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetJetPairReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HDebug, "Get JetPair Reader", Tag);
// //     HJets Jets = TauTagger.GetJets(Event);
// // //     HJets Jets = Event.GetJets()->GetStructuredJets();
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //
// // //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// // //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// // //     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// // //     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
// //
// //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
// //
// // //     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());
// //
// //     std::vector<hanalysis::HQuartet31> Quartets = JetPairTagger.GetBdt(Triplets, Jets, JetPairReader);
// //
// //     if (Quartets.size() > 1) {
// //         std::sort(Quartets.begin(), Quartets.end());
// //         Quartets.erase(Quartets.begin() + 1, Quartets.end());
// //     }
// //
// //     for (const auto & Quartet : Quartets) *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Quartet);
// //
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetChargedHiggsSemiTag(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);
// //     std::vector<HChargedHiggsSemiBranch> Higgses = ChargedHiggsSemiTagger.GetBranches(Event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetChargdHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = TauTagger.GetJets(Event);
// //
// // //     HJets Jets = Event.GetJets()->GetStructuredJets();
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
// //
// // //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// // //     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
// // //     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());
// //
// //     std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(Triplets, Jets, ChargedHiggsSemiReader);
// //
// //     if (Quartets.size() > 1) {
// //         std::sort(Quartets.begin(), Quartets.end());
// //         Quartets.erase(Quartets.begin() + 1, Quartets.end());
// //     }
// //
// //     for (const auto & Quartet : Quartets) *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = ChargedHiggsSemiTagger.GetBranch(Quartet);
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //     std::vector<hheavyhiggs::HChargedSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
// //     if (SemiEvents.empty()) return 0;
// //     for (const auto & SemiEvent : SemiEvents) *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = SemiEvent;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = TauTagger.GetJets(Event);
// //     Jets = TauTagger.GetJetBdt(Jets, TauReader);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
// //
// //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
// // //     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());
// //
// //     std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);
// //
// //     std::vector<hanalysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(TripletsHadronic, Jets, JetPairReader);
// //
// //     HChargedEventStruct EventStruct;
// //     EventStruct.LeptonNumber = Leptons.size();
// //     EventStruct.JetNumber = Jets.size();
// //     EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
// //     EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
// //     if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets()).front().pt();
// //
// //     std::vector<HOctet44> Octets = EventSemiTagger.GetBdt(HiggsQuartets, JetQuartets, Jets, EventStruct, EventSemiReader);
// //     if (Octets.empty()) return 0;
// //     Octets.front().SetTag(Tag);
// //
// //     *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Octets.front());
// //     return 1;
// // }
