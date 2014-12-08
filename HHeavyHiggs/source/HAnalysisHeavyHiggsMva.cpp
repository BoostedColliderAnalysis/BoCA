# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{

//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");

    JetTag = new hanalysis::HJetTag();

}

hheavyhiggs::HAnalysisMva::~HAnalysisMva()
{

    Print(HNotification, "Destructor");

    delete JetTag;

}

HStrings hheavyhiggs::HAnalysisMva::GetStudyNames(const HTagger Tagger)
{
    Print(HNotification, "Get Study Names", Tagger);

    if (Tagger == HBottomTagger) {
        return {"Bottom", "NotBottom"};
    } else if (Tagger == HTopTagger) {
        return  {"Top", "NotTop"};
    } else if (Tagger == HHiggsTagger) {
        return  {"HeavyHiggs", "NotHeavyHiggs"};
    } else if (Tagger == HEventTagger) {
        return  {"Signal", "Background"};
    } else {
        Print(HError, "unexpected TaggerName", Tagger);
        return {};
    }
}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const std::string &StudyName)
{
    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

    if (StudyName != "HeavyHiggs" && StudyName != "Signal") Files.push_back(new hanalysis::HFile("BG"));
    Files.push_back(new hanalysis::HFile("1TeV_h2bb"));
    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_ttbb_wwbbbb_llbbbb.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});

    if (StudyName != "Bottom" && StudyName != "NotBottom") {

        BottomReader = new hanalysis::HReader(BottomTagger);

        LeptonicTopTagger = new hanalysis::HLeptonicTopTagger(BottomTagger);
        LeptonicTopTagger->SetAnalysisName(GetProjectName());
        LeptonicTopTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
        LeptonicTopTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
        LeptonicTopTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});

        if (StudyName != "Top" && StudyName != "NotTop") {

            TopReader = new hanalysis::HReader(LeptonicTopTagger);

            HeavyHiggsTagger = new hanalysis::HHeavyHiggsTagger(BottomTagger, LeptonicTopTagger);
            HeavyHiggsTagger->SetAnalysisName(GetProjectName());
            HeavyHiggsTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
            HeavyHiggsTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
            HeavyHiggsTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});

            Print(HError, "StudyName", StudyName);

            if (StudyName != "HeavyHiggs" && StudyName != "NotHeavyHiggs") {

                HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsTagger);

                HeavyHiggsEventTagger = new hheavyhiggs::HMvaEvent(BottomTagger, LeptonicTopTagger, HeavyHiggsTagger);
                HeavyHiggsEventTagger->SetAnalysisName(GetProjectName());
                HeavyHiggsEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
                HeavyHiggsEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
                HeavyHiggsEventTagger->SetBackgroundTreeNames( {"BG-run_01"});
            }
        }
    }
    return Files;

}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const HTagger Tagger, const HState State)
{
    Print(HNotification, "Set File Vector", Tagger);

    std::vector<hanalysis::HFile *> Files;

    if ((Tagger != HEventTagger && Tagger != HHiggsTagger) || State == HBackground) Files.push_back(new hanalysis::HFile("BG"));
    Files.push_back(new hanalysis::HFile("1TeV_h2bb"));
    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_ttbb_wwbbbb_llbbbb_Delphes.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

    if (Tagger != HBottomTagger) {

        BottomReader = new hanalysis::HReader(BottomTagger);

        LeptonicTopTagger = new hanalysis::HLeptonicTopTagger(BottomTagger);
        LeptonicTopTagger->SetAnalysisName(GetProjectName());
        LeptonicTopTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
        LeptonicTopTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
        LeptonicTopTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

        if (Tagger != HTopTagger) {

            TopReader = new hanalysis::HReader(LeptonicTopTagger);

            HeavyHiggsTagger = new hanalysis::HHeavyHiggsTagger(BottomTagger, LeptonicTopTagger);
            HeavyHiggsTagger->SetAnalysisName(GetProjectName());
            HeavyHiggsTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
            HeavyHiggsTagger->SetSignalTreeNames( {"h2bb-run_01"});
            HeavyHiggsTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

            Print(HError, "StudyName", Tagger);

            if (Tagger != HHiggsTagger) {

                HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsTagger);

                HeavyHiggsEventTagger = new hheavyhiggs::HMvaEvent(BottomTagger, LeptonicTopTagger, HeavyHiggsTagger);
                HeavyHiggsEventTagger->SetAnalysisName(GetProjectName());
                HeavyHiggsEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
                HeavyHiggsEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
                HeavyHiggsEventTagger->SetBackgroundTreeNames( {"BG-run_01"});
            }
        }
    }
    return Files;

}


void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    if (Tagger == HBottomTagger) {
        BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
    } else if (Tagger == HTopTagger) {
        TopBranch = TreeWriter->NewBranch("Top", HLeptonicTopBranch::Class());
    } else if (Tagger == HHiggsTagger) {
        HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());
    } else if (Tagger == HEventTagger) {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    }
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger)
{

    Print(HInformation, "Analysis", StudyName);

    HState State;
    if (Tagger == HBottomTagger) {
        if (StudyName == "Bottom") State = HSignal;
        if (StudyName == "NotBottom") State = HBackground;
        if (GetBottomTag(Event, State)) return 1;
    } else if (Tagger == HTopTagger) {
        if (StudyName == "Top") State = HSignal;
        if (StudyName == "NotTop") State = HBackground;
        if (GetTopTag(Event, State)) return 1;
    } else if (Tagger == HHiggsTagger) {
        if (StudyName == "HeavyHiggs") State = HSignal;
        if (StudyName == "NotHeavyHiggs") State = HBackground;
        if (GetHeavyHiggsTag(Event, State)) return 1;
    } else if (Tagger == HEventTagger) {
        if (StudyName == "Signal") State = HSignal;
        if (StudyName == "Background") State = HBackground;
        if (GetSignalTag(Event, State)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
    }

    return 0;

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const HTagger Tagger, const HState State)
{

    Print(HInformation, "Analysis", Tagger);

    if (Tagger == HBottomTagger) {
        if (GetBottomTag(Event, State)) return 1;
    } else if (Tagger == HTopTagger) {
        if (GetTopTag(Event, State)) return 1;
    } else if (Tagger == HHiggsTagger) {
        if (GetHeavyHiggsTag(Event, State)) return 1;
    } else if (Tagger == HEventTagger) {
        if (GetSignalTag(Event, State)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
    }

    return 0;

}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent *const Event, const HState State)
{

    Print(HDebug, "Get Bottom Tag", State);

    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBranches(Event, State);

    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get Tops", State);

    std::vector<HLeptonicTopBranch *> Tops = LeptonicTopTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get HeavyHiggs Tag", State);


    std::vector<HHeavyHiggsBranch *> Higgses = HeavyHiggsTagger->GetBranches(Event, State);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsBranch *HiggsTagger = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}




bool hheavyhiggs::HAnalysisMva::GetSignalTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Event", State);


    std::vector<hheavyhiggs::HEventBranch *> Events = HeavyHiggsEventTagger->GetBranches(Event, State);
    if (Events.size() < 1) return 0;

    for (const auto & Event : Events) {
        HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());
        *EventTagger = *Event;
    }

    return 1;



}
