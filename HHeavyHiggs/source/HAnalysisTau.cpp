# include "HAnalysisTau.hh"

// hheavyhiggs::HAnalysisTau::HAnalysisTau()
// {
//     Print(kNotification, "Constructor");
//     TauTagger.SetAnalysisName(ProjectName());
// //     JetPairTagger.SetAnalysisName(ProjectName());
// //     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     HiggsTauTagger.SetAnalysisName(ProjectName());
// //     top_hadronic_tagger.SetAnalysisName(ProjectName());
// //     TopSemiTagger.SetAnalysisName(ProjectName());
// //     ChargedHiggsSemiTagger.SetAnalysisName(ProjectName());
// //     eventSemiTagger.SetAnalysisName(ProjectName());
// }

// hheavyhiggs::HAnalysisTau::~HAnalysisTau()
// {
//     Print(kNotification, "Destructor");
// }


// std::string hheavyhiggs::HAnalysisTau::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case HTauTagger :
//         return "Tau";
//     case HTauReader :
//         return "TauReader";
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case HHeavyHiggsTauTagger:
//         return  "HeavyHiggsTau";
//     case HHeavyHiggsTauReader:
//         return  "HeavyHiggsTauReader";
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         return  "eventLeptonic";
//     case EventHadronicTagger:
//         return  "eventHadronic";
//     case EventSemiTagger:
//         return  "ChargedSemi";
//     case EventLeptonicReader:
//         return  "ChargdLeptonicReader";
//     case EventSemiReader:
//         return  "ChargedSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<analysis::File> hheavyhiggs::HAnalysisTau::Files(const Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;

    std::vector<analysis::File> BackgroundLeptonicFiles;

    std::vector<analysis::File> SignalSemiFiles;

//     SignalSemiFiles.emplace_back(analysis::File("1TeV",38.501952876819495,1000));
    //     SignalSemiFiles.emplace_back(analysis::File("2TeV",3.7429107249252125,2000));
    //     SignalSemiFiles.emplace_back(analysis::File("3TeV",0.7636108315783771,3000));
    SignalSemiFiles.emplace_back(analysis::File("Tau_4000", 0.22232809767415665, 4000));
    //     SignalSemiFiles.emplace_back(analysis::File("5TeV",0.07946706739238736,5000));
    //     SignalSemiFiles.emplace_back(analysis::File("6TeV",0.03291534649650638,6000));
    //     SignalSemiFiles.emplace_back(analysis::File("8TeV",0.00738551034925011,8000));
    //     SignalSemiFiles.emplace_back(analysis::File("10TeV",0.002068335074918064,10000));
//     SignalSemiFiles.emplace_back(analysis::File("12TeV",0.0006693740636689783,12000));
//     SignalSemiFiles.emplace_back(analysis::File("15TeV",0.00015145887990818783,15000));
//     SignalSemiFiles.emplace_back(analysis::File("20TeV",0.000016677670760729152,20000));

    std::vector<analysis::File> BackgroundSemiFiles;
    BackgroundSemiFiles.emplace_back(analysis::File("ttjj_400_0", 35.04));

    std::vector<analysis::File> SignalHadronicFiles;
//     SignalHadronicFiles.emplace_back(analysis::File("1TeV_Hbb_ttbb_jjbbbb");

    std::vector<analysis::File> BackgroundHadronicFiles;
//     BackgroundHadronicFiles.emplace_back(analysis::File("BG_jjbbbb");



    std::vector<analysis::File> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<analysis::File> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<analysis::File> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<analysis::File> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<analysis::File> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<analysis::File> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<analysis::File> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<analysis::File> NewFiles;

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
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case EventSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         Print(kError, "unknown tagger name");
//     }

    switch (tag) {
      case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case Object::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

//     NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
//     NewFiles.front().set_file_suffix(".root");

    Print(kNotification, "Files prepared");

    SetTrees();

//     PrepareReader(Tagger, Tag);

    return NewFiles;

}

void hheavyhiggs::HAnalysisTau::SetTrees()
{

    Strings SignalLeptonicTrees {
    };
    Strings BackgroundLeptonicTrees {
    };

    Strings SignalSemiTrees {
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

    Strings BackgroundSemiTrees {
        "ttjj_400_0-run_01"
//         "BG_ttcc_ljbbcc-run_01"
    };

    Strings SignalHadronicTree {
        //       "1TeV_Hbb_ttbb_jjbbbb-run_01"
    };
    Strings BackgroundHadronicTrees {
        //       "BG_jjbbbb-run_01"
    };


    Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

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
// //         if (Tag == kSignal) JetPairTagger.SetTagger(TauTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
// //         break;
// //     case HJetPairReader :
// //         break;
// //     case WHadronicTagger:
// //         w_hadronic_tagger.SetSignalTreeNames(NotLeptonicTrees);
// //         w_hadronic_tagger.SetBackgroundTreeNames(NotLeptonicTrees);
// //         if (Tag == kSignal) w_hadronic_tagger.SetTagger(TauTagger);
// //         break;
// //     case HWHadronicReader :
// //         TauTagger.SetSignalTreeNames(CombinedTrees);
// //         TauTagger.SetBackgroundTreeNames(CombinedTrees);
// //         if (Tag == kSignal) w_hadronic_tagger.SetTagger(TauTagger);
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
// //     case TopHadronicTagger :
// //         if (Tag == kSignal) top_hadronic_tagger.SetTagger(TauTagger, w_hadronic_tagger);
// //         top_hadronic_tagger.SetSignalTreeNames(NotLeptonicTrees);
// //         top_hadronic_tagger.SetBackgroundTreeNames(NotLeptonicTrees);
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
// //         if (Tag == kSignal) ChargedHiggsSemiTagger.SetTagger(TauTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
// //         ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         ChargedHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
// //         break;
// //     case HHeavyHiggsSemiReader :
// //         break;
// //     case EventSemiTagger :
// //         if (Tag == kSignal) eventSemiTagger.SetTagger(TauTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger);
// //         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
// //     case EventSemiReader :
// //         if (Tag == kSignal) eventSemiTagger.SetTagger(TauTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger);
// //         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
//     default :
//         Print(kError, "unhandled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void hheavyhiggs::HAnalysisTau::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(kInformation, "Prepare Reader", Tagger);
//
//     if (Tag == kBackground) return;
//
//     switch (Tagger) {
//     case HTauTagger:
//         break;
//     case HTauReader:
//         TauReader.set_tagger(TauTagger);
//         break;
// //     case WHadronicTagger:
// //         w_hadronic_tagger.BottomTagger.SetTagger();
// //         w_hadronic_tagger.BottomReader.set_tagger(w_hadronic_tagger.BottomTagger);
// //         break;
// //     case HWHadronicReader:
// //         TauReader.set_tagger(TauTagger);
// //         WHadronicReader.set_tagger(w_hadronic_tagger);
// //         break;
//     case HHeavyHiggsTauTagger :
//         HiggsTauTagger.TauTagger.SetTagger();
//         HiggsTauTagger.TauReader.set_tagger(HiggsTauTagger.TauTagger);
//         break;
//     case HHeavyHiggsTauReader :
//         TauReader.set_tagger(TauTagger);
//         HeavyHiggsTauReader.set_tagger(HiggsTauTagger);
//         break;
// //     case TopHadronicTagger :
// //         top_hadronic_tagger.BottomTagger.SetTagger();
// //         top_hadronic_tagger.BottomReader.set_tagger(top_hadronic_tagger.BottomTagger);
// //         top_hadronic_tagger.WTagger.SetTagger(TauTagger);
// //         top_hadronic_tagger.WReader.set_tagger(top_hadronic_tagger.WTagger);
// //         break;
// //     case HTopHadronicReader :
// //         TauReader.set_tagger(TauTagger);
// //         WHadronicReader.set_tagger(w_hadronic_tagger);
// //         TopHadronicReader.set_tagger(top_hadronic_tagger);
// //         break;
// //     case HTopSemiTagger :
// //         TopSemiTagger.BottomTagger.SetTagger();
// //         TopSemiTagger.BottomReader.set_tagger(TopSemiTagger.BottomTagger);
// //         TopSemiTagger.WSemiTagger.SetTagger();
// //         TopSemiTagger.WSemiReader.set_tagger(TopSemiTagger.WSemiTagger);
// //         break;
// //     case HTopSemiReader :
// //         TauReader.set_tagger(TauTagger);
// //         WSemiReader.set_tagger(WSemiTagger);
// //         TopSemiReader.set_tagger(TopSemiTagger);
// //         break;
// //     case HHeavyHiggsSemiTagger :
// //         ChargedHiggsSemiTagger.BottomTagger.SetTagger();
// //         ChargedHiggsSemiTagger.BottomReader.set_tagger(ChargedHiggsSemiTagger.BottomTagger);
// //         ChargedHiggsSemiTagger.WSemiTagger.SetTagger();
// //         ChargedHiggsSemiTagger.WSemiReader.set_tagger(ChargedHiggsSemiTagger.WSemiTagger);
// //         ChargedHiggsSemiTagger.WTagger.SetTagger(TauTagger);
// //         ChargedHiggsSemiTagger.WReader.set_tagger(ChargedHiggsSemiTagger.WTagger);
// //         ChargedHiggsSemiTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         ChargedHiggsSemiTagger.TopSemiReader.set_tagger(ChargedHiggsSemiTagger.TopSemiTagger);
// //         ChargedHiggsSemiTagger.top_hadronic_tagger.SetTagger(TauTagger, w_hadronic_tagger);
// //         ChargedHiggsSemiTagger.TopHadronicReader.set_tagger(ChargedHiggsSemiTagger.top_hadronic_tagger);
// //         break;
// //     case HHeavyHiggsSemiReader  :
// //         TauReader.set_tagger(TauTagger);
// //         WSemiReader.set_tagger(WSemiTagger);
// //         TopSemiReader.set_tagger(TopSemiTagger);
// //         WHadronicReader.set_tagger(w_hadronic_tagger);
// //         TopHadronicReader.set_tagger(top_hadronic_tagger);
// //         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
// //         break;
// //     case HJetPairTagger :
// //         JetPairTagger.BottomTagger.SetTagger();
// //         JetPairTagger.BottomReader.set_tagger(JetPairTagger.BottomTagger);
// //         JetPairTagger.WSemiTagger.SetTagger();
// //         JetPairTagger.WSemiReader.set_tagger(JetPairTagger.WSemiTagger);
// //         JetPairTagger.WTagger.SetTagger(TauTagger);
// //         JetPairTagger.WReader.set_tagger(JetPairTagger.WTagger);
// //         JetPairTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         JetPairTagger.TopSemiReader.set_tagger(JetPairTagger.TopSemiTagger);
// //         JetPairTagger.top_hadronic_tagger.SetTagger(TauTagger, w_hadronic_tagger);
// //         JetPairTagger.TopHadronicReader.set_tagger(JetPairTagger.top_hadronic_tagger);
// //         break;
// //     case HJetPairReader :
// //         TauReader.set_tagger(TauTagger);
// //         WSemiReader.set_tagger(WSemiTagger);
// //         TopSemiReader.set_tagger(TopSemiTagger);
// //         WHadronicReader.set_tagger(w_hadronic_tagger);
// //         TopHadronicReader.set_tagger(top_hadronic_tagger);
// //         JetPairReader.set_tagger(JetPairTagger);
// //         break;
// //     case EventSemiTagger :
// //         eventSemiTagger.BottomTagger.SetTagger();
// //         eventSemiTagger.BottomReader.set_tagger(eventSemiTagger.BottomTagger);
// //         eventSemiTagger.WSemiTagger.SetTagger();
// //         eventSemiTagger.WSemiReader.set_tagger(eventSemiTagger.WSemiTagger);
// //         eventSemiTagger.WTagger.SetTagger(TauTagger);
// //         eventSemiTagger.WReader.set_tagger(eventSemiTagger.WTagger);
// //         eventSemiTagger.TopSemiTagger.SetTagger(TauTagger, WSemiTagger);
// //         eventSemiTagger.TopSemiReader.set_tagger(eventSemiTagger.TopSemiTagger);
// //         eventSemiTagger.top_hadronic_tagger.SetTagger(TauTagger, w_hadronic_tagger);
// //         eventSemiTagger.TopHadronicReader.set_tagger(eventSemiTagger.top_hadronic_tagger);
// //         eventSemiTagger.ChargedHiggsSemiTagger.SetTagger(TauTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
// //         eventSemiTagger.ChargedHiggsSemiReader.set_tagger(eventSemiTagger.ChargedHiggsSemiTagger);
// //         eventSemiTagger.ChargedJetPairTagger.SetTagger(TauTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
// //         eventSemiTagger.ChargedJetPairReader.set_tagger(eventSemiTagger.ChargedJetPairTagger);
// //         break;
// //     case EventSemiReader :
// //         TauReader.set_tagger(TauTagger);
// //         WSemiReader.set_tagger(WSemiTagger);
// //         TopSemiReader.set_tagger(TopSemiTagger);
// //         WHadronicReader.set_tagger(w_hadronic_tagger);
// //         TopHadronicReader.set_tagger(top_hadronic_tagger);
// //         JetPairReader.set_tagger(JetPairTagger);
// //         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
// //         eventSemiReader.set_tagger(eventSemiTagger);
// //         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }

// void hheavyhiggs::HAnalysisTau::ResetBranch()
// {
    //         Branch.reset();
// }

// void hheavyhiggs::HAnalysisTau::NewBranches(ExRootTreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger)
// {
//     Print(kNotification, "New Branches", Tagger);
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
// //     case WHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
// //         break;
// //     case HWHadronicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
// //         break;
// //     case HTopLeptonicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
// //         break;
// //     case HTopLeptonicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
// //         break;
// //     case TopHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
// //         break;
// //     case HTopSemiTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
// //         break;
// //     case HTopHadronicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
// //         break;
// //     case HTopSemiReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
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
// //     case EventLeptonicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventLeptonicBranch::Class());
// //         break;
// //     case EventHadronicTagger :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventHadronicBranch::Class());
// //         break;
// //     case EventSemiTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
// //         break;
// //     case EventSemiReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
// //         break;
// //     case EventLeptonicReader :
// // //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventLeptonicBranch::Class());
// //         break;
//     default :
//         Print(kError, "No Branch filled");
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

int hheavyhiggs::HAnalysisTau::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{

    Print(kInformation, "Analysis", stage);

//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    Jets Leptons = fastjet::sorted_by_pt(event.leptons().GetLeptonJets());

//     if (Leptons.empty()) return 0;
//     if (Leptons.front().pt() < 300 || MissingEt.pt() < 400) return 0;
//     if (Leptons.front().pt() < 300) return 0;
    ++event_sum_;

//     switch (stage) {
//     case HTauTagger :
//         return GetTauTag(event, tag);
//     case HTauReader:
//         return GetTauReader(event, tag);
// //     case HJetPairTagger :
// //         return GetJetPairTag(event, Tag);
// //     case HJetPairReader :
// //         return GetJetPairReader(event, Tag);
// //     case WHadronicTagger :
// //         return GetWTag(event, Tag);
// //     case HWHadronicReader :
// //         return GetWReader(event, Tag);
//     case HHeavyHiggsTauTagger :
//         return GetHeavyHiggsTauTag(event, tag);
//     case HHeavyHiggsTauReader :
//         return GetHeavyHiggsTauReader(event, tag);
// //     case HTopLeptonicTagger :
// //         return GetTopLeptonicTag(event, Tag);
// //     case TopHadronicTagger :
// //         return GetTopHadronicTag(event, Tag);
// //     case HTopSemiTagger :
// //         return GetTopSemiTag(event, Tag);
// //     case HTopHadronicReader :
// //         return GetTopHadronicReader(event, Tag);
// //     case HTopLeptonicReader :
// //         return GetTopLeptonicReader(event, Tag);
// //     case HTopSemiReader :
// //         return GetTopSemiReader(event, Tag);
// //     case HHeavyHiggsLeptonicTagger :
// // //         return GetHeavyHiggsLeptonicTag(event, Tag);
// //     case HHeavyHiggsHadronicTagger :
// // //         return GetHeavyHiggsHadronicTag(event, Tag);
// //     case HHeavyHiggsSemiTagger :
// //         return GetChargedHiggsSemiTag(event, Tag);
// //     case HHeavyHiggsSemiReader :
// //         return GetChargdHiggsSemiReader(event, Tag);
// //     case HHeavyHiggsLeptonicReader :
// // //         return GetHeavyHiggsLeptonicReader(event, Tag);
// //     case EventLeptonicTagger :
// // //         return GeteventLeptonicTag(event, Tag);
// //     case EventHadronicTagger :
// // //         return GeteventHadronicTag(event, Tag);
// //     case EventSemiTagger :
// //         return GeteventSemiTag(event, Tag);
// //     case EventSemiReader :
// //         return GeteventSemiReader(event, Tag);
// //     case EventLeptonicReader :
// //         return GeteventLeptonicReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", stage);
//         return 0;
    //     }
    return tagger_.GetBranches(event, stage, tag);
}


// bool hheavyhiggs::HAnalysisTau::GetTauTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Tau Tag", Tag);
//     std::vector<HTauBranch> Taus = TauTagger.GetBranches(event, Tag);
//     if (Taus.empty()) return 0;
//     for (const auto & Tau : Taus) *static_cast<HTauBranch *>(Branch->NewEntry()) = Tau;
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisTau::GetTauReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Tau Reader", Tag);
//     Jets jets = TauTagger.GetJets(event, JetTag);
//     jets = TauTagger.GetJetBdt(jets, TauReader);
//
//     Jets Particles = event.partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(TauId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < 0.4) static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) continue;
//         *static_cast<HTauBranch *>(Branch->NewEntry()) = TauTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTau::GetHeavyHiggsTauTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get HeavyHiggs Tau Tag", Tag);
//     std::vector<HHeavyHiggsTauBranch> HeavyHiggses = HiggsTauTagger.GetBranches(event, Tag);
//     if (HeavyHiggses.empty()) return 0;
//     for (const auto & Higgs : HeavyHiggses) *static_cast<HHeavyHiggsTauBranch *>(Branch->NewEntry()) = Higgs;
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTau::GetHeavyHiggsTauReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Reader", Tag);
//
//     Jets jets = TauTagger.GetJets(event, JetTag);
//     jets = TauTagger.GetJetBdt(jets, TauReader);
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//
//     std::vector<analysis::Doublet> doublets = HiggsTauTagger.GetBdt(jets, MissingEt, HeavyHiggsTauReader);
//
//     if (doublets.empty()) return 0;
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) *static_cast<HHeavyHiggsTauBranch *>(Branch->NewEntry()) = HiggsTauTagger.GetBranch(doublet);
//
//     return 1;
// }
//
// // bool hheavyhiggs::HAnalysisTau::GetWTag(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kDebug, "Get W Tag", Tag);
// //     std::vector<WHadronicBranch> Ws = w_hadronic_tagger.GetBranches(event, Tag);
// //     if (Ws.empty()) return 0;
// //     for (const auto & W : Ws) *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetWReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = TauTagger.GetJets(event);
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //
// //     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //
// //     for (const auto & Jet : jets)  {
// //         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 2);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
// //         doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
// //     }
// //
// //     for (const auto & Jet : jets)  {
// //         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 3);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
// //         doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
// //     }
// //
// //
// //     if (doublets.size() > 1) {
// //         std::sort(doublets.begin(), doublets.end());
// //         doublets.erase(doublets.begin() + 1, doublets.end());
// //     }
// //
// //     for (const auto & doublet : doublets) *static_cast<WHadronicBranch *>(Branch->NewEntry()) = w_hadronic_tagger.GetBranch(doublet);
// //
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopLeptonicTag(analysis::Event &event,  HTag Tag)
// // {
// //     Print(kInformation, "Get leptonic top", Tag);
// //     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopLeptonicReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = event.hadrons().GetStructuredJets();
// //     jets = TauTagger.GetBdt(jets, TauReader);
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     if (doublets.size() > 1) {
// //         std::sort(doublets.begin(), doublets.end());
// //         doublets.erase(doublets.begin() + 1, doublets.end());
// //     }
// //
// //     for (const auto & doublet : doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(doublet);
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopHadronicTag(analysis::Event &event,  HTag Tag)
// // {
// //     Print(kInformation, "Get hadronic tops", Tag);
// //     std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
// //         *TopTagger = Top;
// //     }
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopHadronicReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = top_hadronic_tagger.GetJets(event);
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
// //
// //     for (const auto & Jet : jets)  {
// //         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 2);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
// //         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
// //         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
// //     }
// //
// //     for (const auto & Jet : jets)  {
// //         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 3);
// //         Pieces = TauTagger.GetJetBdt(Pieces, TauReader);
// //         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
// //         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
// //         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
// //     }
// //
// //
// //     if (triplets.size() > 1) {
// //         std::sort(triplets.begin(), triplets.end());
// //         triplets.erase(triplets.begin() + 1, triplets.end());
// //     }
// //
// //     for (const auto & triplet : triplets) {
// //         TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
// //         *TopTagger = top_hadronic_tagger.GetBranch(triplet);
// //     }
// //
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopSemiTag(analysis::Event &event,  HTag Tag)
// // {
// //     Print(kInformation, "Get Tops", Tag);
// //     std::vector<TopSemiBranch> Tops = TopSemiTagger.GetBranches(event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetTopSemiReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// // //     Jets jets = event.hadrons().GetStructuredJets();
// //
// //     Jets jets = TauTagger.GetJets(event);
// //
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);
// //
// //     if (triplets.size() > 1) {
// //         std::sort(triplets.begin(), triplets.end());
// //         triplets.erase(triplets.begin() + 1, triplets.end());
// //     }
// //
// //     for (const auto & triplet : triplets) *static_cast<TopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
// //
// //     return 1;
// // }
// //
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetJetPairTag(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kDebug, "Get JetPair Tag", Tag);
// //     std::vector<HChargedJetPairBranch> JetPairs = JetPairTagger.GetBranches(event, Tag);
// //     if (JetPairs.empty()) return 0;
// //     for (const auto & JetPair : JetPairs) *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPair;
// //     return 1;
// // }
// //
// //
// // bool hheavyhiggs::HAnalysisTau::GetJetPairReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kDebug, "Get JetPair Reader", Tag);
// //     Jets jets = TauTagger.GetJets(event);
// // //     Jets jets = event.hadrons().GetStructuredJets();
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //
// // //     Jets Leptons = event.leptons().GetLeptonJets();
// // //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// // //     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// // //     std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
// //
// // //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());
// //
// //     std::vector<analysis::HQuartet31> Quartets = JetPairTagger.GetBdt(triplets, jets, JetPairReader);
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
// // bool hheavyhiggs::HAnalysisTau::GetChargedHiggsSemiTag(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get Semi HeavyHiggs Tag", Tag);
// //     std::vector<HChargedHiggsSemiBranch> Higgses = ChargedHiggsSemiTagger.GetBranches(event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GetChargdHiggsSemiReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = TauTagger.GetJets(event);
// //
// // //     Jets jets = event.hadrons().GetStructuredJets();
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //
// // //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// // //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
// // //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());
// //
// //     std::vector<analysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(triplets, jets, ChargedHiggsSemiReader);
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
// // bool hheavyhiggs::HAnalysisTau::GeteventSemiTag(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //     std::vector<hheavyhiggs::HChargedSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
// //     if (Semievents.empty()) return 0;
// //     for (const auto & Semievent : Semievents) *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = Semievent;
// //     return 1;
// // }
// //
// // bool hheavyhiggs::HAnalysisTau::GeteventSemiReader(analysis::Event &event, const HTag Tag)
// // {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = TauTagger.GetJets(event);
// //     jets = TauTagger.GetJetBdt(jets, TauReader);
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
// // //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());
// //
// //     std::vector<analysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);
// //
// //     std::vector<analysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(tripletsHadronic, jets, JetPairReader);
// //
// //     HChargedevent_struct event_struct;
// //     event_struct.LeptonNumber = Leptons.size();
// //     event_struct.JetNumber = jets.size();
// //     event_struct.BottomNumber = event.hadrons().GetBottomJets().size();
// //     event_struct.ScalarHt = event.hadrons().GetScalarHt();
// //     if (event_struct.LeptonNumber > 0) event_struct.LeptonPt = fastjet::sorted_by_pt(event.leptons().GetLeptonJets()).front().pt();
// //
// //     std::vector<HOctet44> Octets = eventSemiTagger.GetBdt(HiggsQuartets, JetQuartets, jets, event_struct, eventSemiReader);
// //     if (Octets.empty()) return 0;
// //     Octets.front().SetTag(Tag);
// //
// //     *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(Octets.front());
// //     return 1;
// // }
