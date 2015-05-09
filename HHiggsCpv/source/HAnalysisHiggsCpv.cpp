# include "HAnalysisHiggsCpv.hh"

// hhiggscpv::HAnalysis::HAnalysis()
// {
//
// //     DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     //JetTag = new hanalysis::HJetTag();
//
// }
//
// hhiggscpv::HAnalysis::~HAnalysis()
// {
//
//     Print(HNotification, "Destructor");
//
//     //delete JetTag;
//
// //     if (!BottomTagger)delete BottomTagger;
// //     if (!LeptonicTopTagger) delete LeptonicTopTagger;
// //     if (!HiggsTagger) delete HiggsTagger;
// //     if (!LeptonicTopTagger) delete LeptonicTopTagger;
//
// //     if (!BottomReader) delete BottomReader;
// //     if (!HiggsReader) delete HiggsReader;
//
// }

Strings hhiggscpv::HAnalysis::GetStudyNames()
{
//     Print(HNotification, "Get Study Names", Tagger);
//
// //     Tagger = NewTagger;
//
//     if (Tagger == HBottomTagger) {
//         return {"Bottom", "NotBottom"};
//     } else if (Tagger == HTopLeptonicTagger) {
//         return  {"Top", "NotTop"};
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         return  {"Higgs", "NotHiggs"};
//     } else if (Tagger == HEventTagger) {
//         return  {"Signal", "Background"};
//     } else {
//         Print(HError, "unexpected TaggerName", Tagger);
//         return {};
//     }
}

std::vector<hanalysis::RootFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &NewStudyName)
{
    Print(HNotification, "Set File Vector", NewStudyName);

    std::vector<hanalysis::RootFile *> files;

//     hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.emplace_back(Test3);
//     return Files;

    if (NewStudyName != "Higgs" && NewStudyName != "Signal") {

//     hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
        //     Files.emplace_back(Test4);

//     hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
        //     Files.emplace_back(Test2);


      hanalysis::hdelphes::HFile *Background = new hanalysis::hdelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->set_crosssection(3.215); // pb
        Background->set_crosssection_error(0.012); // pb
        files.emplace_back(Background);

    }

    hanalysis::hdelphes::HFile *Even = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->set_crosssection(30.02079); // pb
    Even->set_crosssection_error(0.000078); // pb
//     Even->TagString="tag_2";
    files.emplace_back(Even);

    hanalysis::hdelphes::HFile *Mix = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->set_crosssection(30.01172); // pb
    Mix->set_crosssection_error(0.000045); // pb
//     Mix->TagString="tag_2";
    files.emplace_back(Mix);

    hanalysis::hdelphes::HFile *Odd = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->set_crosssection(30.008951); // pb
    Odd->set_crosssection_error(0.000035); // pb
//     Odd->TagString="tag_2";
    files.emplace_back(Odd);

//     hdelphes::HFile *Test = new hdelphes::HFile("pp-hjj-bbjj");
//     Files.emplace_back(Test);
//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.emplace_back(Signal);

    Print(HNotification, "Files prepared");




    bottom_tagger_ = hanalysis::BottomTagger();
    bottom_tagger_.set_analysis_name(ProjectName());
//     BottomTagger.SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//     BottomTagger.SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//     BottomTagger.SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});

    if (NewStudyName != "Bottom" && NewStudyName != "NotBottom") {

      BottomReader.set_tagger(bottom_tagger_);

      LeptonicTopTagger = hanalysis::HTopLeptonicTagger(bottom_tagger_);
        LeptonicTopTagger.set_analysis_name(ProjectName());
//         LeptonicTopTagger.SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         LeptonicTopTagger.SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         LeptonicTopTagger.SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});



        HiggsTagger = hanalysis::HMvaHiggsTagger(bottom_tagger_);
        HiggsTagger.set_analysis_name(ProjectName());
//         HiggsTagger.SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         HiggsTagger.SetSignalTreeNames( {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         HiggsTagger.SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});

        if (NewStudyName != "Top" && NewStudyName != "NotTop" && NewStudyName != "Higgs" && NewStudyName != "NotHiggs") {
          HiggsReader.set_tagger(HiggsTagger);
          TopReader.set_tagger(LeptonicTopTagger);
        }

    }

    return files;

}


// void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *NewTreeWriter, const HTagger Tagger)
// {
//     Print(HNotification, "New Branches", Tagger);
//
//     if (Tagger == HBottomTagger) {
//         BottomBranch = NewTreeWriter->NewBranch("Bottom", HBottomBranch::Class());
//     } else if (Tagger == HTopLeptonicTagger) {
//         TopBranch = NewTreeWriter->NewBranch("Top", HTopLeptonicBranch::Class());
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         HiggsBranch = NewTreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
//         ConstituentBranch = NewTreeWriter->NewBranch("Constituent", HParticleBranch::Class());
//     } else if (Tagger == HEventTagger) {
//         EventBranch = NewTreeWriter->NewBranch("Event", HEventBranch::Class());
//     }
// //     } else {
// //         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
// }

int hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent &Event, const std::string &NewStudyName)
{

    Print(HInformation, "Analysis", NewStudyName);

//     if (Tagger == HBottomTagger) {
//         if (GetBottomTag(Event, NewStudyName)) return 1;
//     } else if (Tagger == HTopLeptonicTagger) {
//         if (GetTopTag(Event, NewStudyName)) return 1;
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         if (GetHiggsTag(Event, NewStudyName)) return 1;
//     } else if (Tagger == HEventTagger) {
//         if (GetSignalTag(Event, NewStudyName)) return 1;
//     } else {
//         Print(HError, "unknown Tagger", Tagger);
//     }

    return 0;

}


bool hhiggscpv::HAnalysis::GetBottomTag(hanalysis::HEvent &, const std::string &NewStudyName)
{

    Print(HDebug, "Get Bottom Tag", NewStudyName);

//     HTag State;
//     if (StudyName == "Bottom") State = kSignal;
//     if (StudyName == "NotBottom") State = HBackground;

//     std::vector<HBottomBranch *> Bottoms = BottomTagger.GetBranches(Event, State);
//
//     for (const auto & Bottom : Bottoms) {
//         HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
//         *BTagger = *Bottom;
//     }

    return 1;

}


bool hhiggscpv::HAnalysis::GetTopTag(hanalysis::HEvent &Event, const std::string &NewStudyName)
{

    Print(HInformation, "Get Tops", NewStudyName);

    Tag State;
    if (NewStudyName == "Top") State = kSignal;
    if (NewStudyName == "NotTop") State = kBackground;

    std::vector<HTopLeptonicBranch> Tops = LeptonicTopTagger.GetBranches(Event, State);

    for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(TopBranch->NewEntry()) = Top;

    return 1;

}


bool hhiggscpv::HAnalysis::GetHiggsTag(hanalysis::HEvent &Event, const std::string &NewStudyName)
{
    Print(HInformation, "Get Higgs Tag", NewStudyName);

    Tag State;
    if (NewStudyName == "Higgs") State = kSignal;
    if (NewStudyName == "NotHiggs") State = kBackground;

    std::vector<HHiggsBranch *> Higgses = HiggsTagger.GetBranches(Event, State);

    for (const auto & Higgs : Higgses) {
        HHiggsBranch *HiggsBranch1 = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
        *HiggsBranch1 = *Higgs;
    }

    std::vector<HParticleBranch *> Constitents = HiggsTagger.GetConstituentBranches();

    for (const auto & Constituent : Constitents) {
        HParticleBranch *ConstituentBranch1 = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
        *ConstituentBranch1 = *Constituent;
    }

    return 1;

}


struct SortHiggsCpv {
    inline bool operator()(const HHiggsCpv &Event1, const HHiggsCpv &Event2) {
        return (Event1.Bdt() > Event2.Bdt());
    }
};

bool hhiggscpv::HAnalysis::GetSignalTag(hanalysis::HEvent &Event, const std::string &NewStudyName)
{
    Print(HInformation, "Get Event", NewStudyName);

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) {
        Print(HNotification, "Not enough Leptons", Leptons.size());
        return 0;
    }

    Jets jets = Event.GetJets()->GetStructuredJets();
    if (jets.size() < 4) {
        Print(HNotification, "Not enough Jets", jets.size());
        return 0;

    }

    for (auto & Jet : jets)  {
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
//         BottomTagger.Branch = BottomTagger.GetBranch(Jet); // FIXME reenable this
        JetInfo->SetBdt(BottomReader.Bdt());
        Jet.set_user_info(JetInfo);
    }

    std::vector<HHiggsCpv> HiggsCpvs;
    for (Jets::iterator Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (Jets::iterator Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            const Jets EventLeptons {
                (*Lepton1), (*Lepton2)
            };
            for (Jets::iterator Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1) {
                for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
                    for (Jets::iterator Jet3 = Jet2 + 1; Jet3 != jets.end(); ++Jet3) {
                        for (Jets::iterator Jet4 = Jet3 + 1; Jet4 != jets.end(); ++Jet4) {
                            const Jets EventJets = {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                            std::vector<HHiggsCpv> NewHiggsCpvs = GetHiggsCpvs(EventJets, EventLeptons);
                            HiggsCpvs.insert(HiggsCpvs.end(), NewHiggsCpvs.begin(), NewHiggsCpvs.end());
                        }
                    }
                }
            }
        }
    }

    std::sort(HiggsCpvs.begin(), HiggsCpvs.end(), SortHiggsCpv());

    HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());

    EventTagger->ScalarHt = Event.GetJets()->GetScalarHt();
    EventTagger->JetNumber = Event.GetJets()->GetJets().size();
    EventTagger->BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventTagger->LeptonNumber = Event.GetLeptons()->GetLeptonJets().size();
    EventTagger->HeavyParticleTag = HiggsCpvs.front().Bdt();
    EventTagger->TopDeltaRap = HiggsCpvs.front().GetTopDeltaRap();
    EventTagger->TopDeltaPhi = HiggsCpvs.front().GetTopDeltaPhi();
    EventTagger->TopDeltaR = HiggsCpvs.front().GetTopDeltaR();
    if (NewStudyName == "Signal") {
        EventTagger->Signal = 1;
    } else {
        EventTagger->Signal = 0;
    }

    return 1;

}

std::vector< HHiggsCpv > hhiggscpv::HAnalysis::GetHiggsCpvs(const Jets &jets, const Jets &Leptons)
{

    std::vector<HHiggsCpv> HiggsCpvs;

    hanalysis::HDoublet HiggsPair01 = hanalysis::HDoublet(jets[0], jets[1]);
    HiggsTagger.FillBranch(HiggsPair01);
    HiggsPair01.SetBdt(HiggsReader.Bdt());
    hanalysis::HDoublet HiggsPair02 = hanalysis::HDoublet(jets[0], jets[2]);
    HiggsTagger.FillBranch(HiggsPair02);
    HiggsPair02.SetBdt(HiggsReader.Bdt());
    hanalysis::HDoublet HiggsPair03 = hanalysis::HDoublet(jets[0], jets[3]);
    HiggsTagger.FillBranch(HiggsPair03);
    HiggsPair03.SetBdt(HiggsReader.Bdt());
    hanalysis::HDoublet HiggsPair12 = hanalysis::HDoublet(jets[1], jets[2]);
    HiggsTagger.FillBranch(HiggsPair12);
    HiggsPair12.SetBdt(HiggsReader.Bdt());
    hanalysis::HDoublet HiggsPair13 = hanalysis::HDoublet(jets[1], jets[3]);
    HiggsTagger.FillBranch(HiggsPair13);
    HiggsPair13.SetBdt(HiggsReader.Bdt());
    hanalysis::HDoublet HiggsPair23 = hanalysis::HDoublet(jets[2], jets[3]);
    HiggsTagger.FillBranch(HiggsPair23);
    HiggsPair23.SetBdt(HiggsReader.Bdt());

    hanalysis::HDoublet Top0 = hanalysis::HDoublet(jets[0], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top0);
    Top0.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet Top1 = hanalysis::HDoublet(jets[1], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top1);
    Top1.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet Top2 = hanalysis::HDoublet(jets[2], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top2);
    Top2.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet Top3 = hanalysis::HDoublet(jets[3], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top3);
    Top3.SetBdt(TopReader.Bdt());

    hanalysis::HDoublet AntiTop0 = hanalysis::HDoublet(jets[0], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop0);
    AntiTop0.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet AntiTop1 = hanalysis::HDoublet(jets[1], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop1);
    AntiTop1.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet AntiTop2 = hanalysis::HDoublet(jets[2], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop2);
    AntiTop2.SetBdt(TopReader.Bdt());
    hanalysis::HDoublet AntiTop3 = hanalysis::HDoublet(jets[3], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop3);
    AntiTop3.SetBdt(TopReader.Bdt());


    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair01, Top2, AntiTop3));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair01, Top3, AntiTop2));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair02, Top1, AntiTop3));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair02, Top3, AntiTop1));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair03, Top1, AntiTop2));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair03, Top2, AntiTop1));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair12, Top0, AntiTop3));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair12, Top3, AntiTop0));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair13, Top0, AntiTop2));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair13, Top2, AntiTop0));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair23, Top0, AntiTop1));
    HiggsCpvs.emplace_back(HHiggsCpv(HiggsPair23, Top1, AntiTop0));

    return HiggsCpvs;

}
