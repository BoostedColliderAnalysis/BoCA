# include "HAnalysisHiggsCpv.hh"

// hhiggscpv::HAnalysis::HAnalysis()
// {
//
// //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     //JetTag = new analysis::HJetTag();
//
// }
//
// hhiggscpv::HAnalysis::~HAnalysis()
// {
//
//     Print(kNotification, "Destructor");
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
//     Print(kNotification, "Get Study Names", Tagger);
//
// //     Tagger = NewTagger;
//
//     if (Tagger == HBottomTagger) {
//         return {"Bottom", "NotBottom"};
//     } else if (Tagger == HTopLeptonicTagger) {
//         return  {"Top", "NotTop"};
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         return  {"Higgs", "NotHiggs"};
//     } else if (Tagger == EventTagger) {
//         return  {"Signal", "Background"};
//     } else {
//         Print(kError, "unexpected TaggerName", Tagger);
//         return {};
//     }
}

std::vector<analysis::File *> hhiggscpv::HAnalysis::GetFiles(const std::string &NewStudyName)
{
    Print(kNotification, "Set File Vector", NewStudyName);

    std::vector<analysis::File *> files;

//     hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.emplace_back(Test3);
//     return Files;

    if (NewStudyName != "Higgs" && NewStudyName != "Signal") {

//     hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
        //     Files.emplace_back(Test4);

//     hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
        //     Files.emplace_back(Test2);


      analysis::File *Background = new analysis::File("pp-bbtt-bblvlv", "background");
        Background->set_crosssection(3.215); // pb
        Background->set_crosssection_error(0.012); // pb
        files.emplace_back(Background);

    }

    analysis::File *Even = new analysis::File("pp-x0tt-bblvlv", "even");
    Even->set_crosssection(30.02079); // pb
    Even->set_crosssection_error(0.000078); // pb
//     Even->TagString="tag_2";
    files.emplace_back(Even);

    analysis::File *Mix = new analysis::File("pp-x0tt-bblvlv", "mix");
    Mix->set_crosssection(30.01172); // pb
    Mix->set_crosssection_error(0.000045); // pb
//     Mix->TagString="tag_2";
    files.emplace_back(Mix);

    analysis::File *Odd = new analysis::File("pp-x0tt-bblvlv", "odd");
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

    Print(kNotification, "Files prepared");




    bottom_tagger_ = analysis::BottomTagger();
    bottom_tagger_.set_analysis_name(ProjectName());
//     BottomTagger.SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//     BottomTagger.SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//     BottomTagger.SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});

    if (NewStudyName != "Bottom" && NewStudyName != "NotBottom") {

      BottomReader.set_tagger(bottom_tagger_);

      LeptonicTopTagger = analysis::HTopLeptonicTagger(bottom_tagger_);
        LeptonicTopTagger.set_analysis_name(ProjectName());
//         LeptonicTopTagger.SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         LeptonicTopTagger.SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
//         LeptonicTopTagger.SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});



        HiggsTagger = analysis::HMvaHiggsTagger(bottom_tagger_);
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
//     Print(kNotification, "New Branches", Tagger);
//
//     if (Tagger == HBottomTagger) {
//         bottom_branch = NewTreeWriter->NewBranch("Bottom", BottomBranch::Class());
//     } else if (Tagger == HTopLeptonicTagger) {
//         TopBranch = NewTreeWriter->NewBranch("Top", HTopLeptonicBranch::Class());
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         HiggsBranch = NewTreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
//         constituentBranch = NewTreeWriter->NewBranch("constituent", ParticleBranch::Class());
//     } else if (Tagger == EventTagger) {
//         eventBranch = NewTreeWriter->NewBranch("event", EventBranch::Class());
//     }
// //     } else {
// //         constituentBranch = TreeWriter->NewBranch("constituent", ParticleBranch::Class());
// }

int hhiggscpv::HAnalysis::Analysis(analysis::Event &event, const std::string &NewStudyName)
{

    Print(kInformation, "Analysis", NewStudyName);

//     if (Tagger == HBottomTagger) {
//         if (GetBottomTag(event, NewStudyName)) return 1;
//     } else if (Tagger == HTopLeptonicTagger) {
//         if (GetTopTag(event, NewStudyName)) return 1;
//     } else if (Tagger == HHiggsLeptonicTagger) {
//         if (GetHiggsTag(event, NewStudyName)) return 1;
//     } else if (Tagger == EventTagger) {
//         if (GetSignalTag(event, NewStudyName)) return 1;
//     } else {
//         Print(kError, "unknown Tagger", Tagger);
//     }

    return 0;

}


bool hhiggscpv::HAnalysis::GetBottomTag(analysis::Event &, const std::string &NewStudyName)
{

    Print(kDebug, "Get Bottom Tag", NewStudyName);

//     HTag State;
//     if (StudyName == "Bottom") State = kSignal;
//     if (StudyName == "NotBottom") State = HBackground;

//     std::vector<BottomBranch *> Bottoms = BottomTagger.GetBranches(event, State);
//
//     for (const auto & Bottom : Bottoms) {
//         BottomBranch *BTagger = static_cast<BottomBranch *>(bottom_branch->NewEntry());
//         *BTagger = *Bottom;
//     }

    return 1;

}


bool hhiggscpv::HAnalysis::GetTopTag(analysis::Event &event, const std::string &NewStudyName)
{

    Print(kInformation, "Get Tops", NewStudyName);

    Tag State;
    if (NewStudyName == "Top") State = kSignal;
    if (NewStudyName == "NotTop") State = kBackground;

    std::vector<HTopLeptonicBranch> Tops = LeptonicTopTagger.GetBranches(event, State);

    for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(TopBranch->NewEntry()) = Top;

    return 1;

}


bool hhiggscpv::HAnalysis::GetHiggsTag(analysis::Event &event, const std::string &NewStudyName)
{
    Print(kInformation, "Get Higgs Tag", NewStudyName);

    Tag State;
    if (NewStudyName == "Higgs") State = kSignal;
    if (NewStudyName == "NotHiggs") State = kBackground;

    std::vector<HHiggsBranch *> Higgses = HiggsTagger.GetBranches(event, State);

    for (const auto & Higgs : Higgses) {
        HHiggsBranch *HiggsBranch1 = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
        *HiggsBranch1 = *Higgs;
    }

    std::vector<ParticleBranch *> Constitents = HiggsTagger.GetconstituentBranches();

    for (const auto & constituent : Constitents) {
        ParticleBranch *constituentBranch1 = static_cast<ParticleBranch *>(constituentBranch->NewEntry());
        *constituentBranch1 = *constituent;
    }

    return 1;

}


struct SortHiggsCpv {
    inline bool operator()(const HHiggsCpv &event1, const HHiggsCpv &event2) {
        return (event1.Bdt() > event2.Bdt());
    }
};

bool hhiggscpv::HAnalysis::GetSignalTag(analysis::Event &event, const std::string &NewStudyName)
{
    Print(kInformation, "Get event", NewStudyName);

    Jets Leptons = event.leptons().GetLeptonJets();
    if (Leptons.size() < 2) {
        Print(kNotification, "Not enough Leptons", Leptons.size());
        return 0;
    }

    Jets jets = event.hadrons().GetStructuredJets();
    if (jets.size() < 4) {
        Print(kNotification, "Not enough Jets", jets.size());
        return 0;

    }

    for (auto & Jet : jets)  {
        analysis::JetInfo *jet_info = new analysis::JetInfo;
//         BottomTagger.Branch = BottomTagger.GetBranch(Jet); // FIXME reenable this
        jet_info->SetBdt(BottomReader.Bdt());
        Jet.set_user_info(jet_info);
    }

    std::vector<HHiggsCpv> HiggsCpvs;
    for (Jets::iterator Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (Jets::iterator Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            const Jets eventLeptons {
                (*Lepton1), (*Lepton2)
            };
            for (Jets::iterator Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1) {
                for (Jets::iterator Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
                    for (Jets::iterator Jet3 = Jet2 + 1; Jet3 != jets.end(); ++Jet3) {
                        for (Jets::iterator Jet4 = Jet3 + 1; Jet4 != jets.end(); ++Jet4) {
                            const Jets eventJets = {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                            std::vector<HHiggsCpv> NewHiggsCpvs = GetHiggsCpvs(eventJets, eventLeptons);
                            HiggsCpvs.insert(HiggsCpvs.end(), NewHiggsCpvs.begin(), NewHiggsCpvs.end());
                        }
                    }
                }
            }
        }
    }

    std::sort(HiggsCpvs.begin(), HiggsCpvs.end(), SortHiggsCpv());

    EventBranch *eventTagger = static_cast<EventBranch *>(eventBranch->NewEntry());

    eventTagger->ScalarHt = event.hadrons().GetScalarHt();
    eventTagger->JetNumber = event.hadrons().GetJets().size();
    eventTagger->BottomNumber = event.hadrons().GetBottomJets().size();
    eventTagger->LeptonNumber = event.leptons().GetLeptonJets().size();
    eventTagger->HeavyParticleTag = HiggsCpvs.front().Bdt();
    eventTagger->TopDeltaRap = HiggsCpvs.front().GetTopDeltaRap();
    eventTagger->TopDeltaPhi = HiggsCpvs.front().GetTopDeltaPhi();
    eventTagger->TopDeltaR = HiggsCpvs.front().GetTopDeltaR();
    if (NewStudyName == "Signal") {
        eventTagger->Signal = 1;
    } else {
        eventTagger->Signal = 0;
    }

    return 1;

}

std::vector< HHiggsCpv > hhiggscpv::HAnalysis::GetHiggsCpvs(const Jets &jets, const Jets &Leptons)
{

    std::vector<HHiggsCpv> HiggsCpvs;

    analysis::Doublet HiggsPair01 = analysis::Doublet(jets[0], jets[1]);
    HiggsTagger.FillBranch(HiggsPair01);
    HiggsPair01.SetBdt(HiggsReader.Bdt());
    analysis::Doublet HiggsPair02 = analysis::Doublet(jets[0], jets[2]);
    HiggsTagger.FillBranch(HiggsPair02);
    HiggsPair02.SetBdt(HiggsReader.Bdt());
    analysis::Doublet HiggsPair03 = analysis::Doublet(jets[0], jets[3]);
    HiggsTagger.FillBranch(HiggsPair03);
    HiggsPair03.SetBdt(HiggsReader.Bdt());
    analysis::Doublet HiggsPair12 = analysis::Doublet(jets[1], jets[2]);
    HiggsTagger.FillBranch(HiggsPair12);
    HiggsPair12.SetBdt(HiggsReader.Bdt());
    analysis::Doublet HiggsPair13 = analysis::Doublet(jets[1], jets[3]);
    HiggsTagger.FillBranch(HiggsPair13);
    HiggsPair13.SetBdt(HiggsReader.Bdt());
    analysis::Doublet HiggsPair23 = analysis::Doublet(jets[2], jets[3]);
    HiggsTagger.FillBranch(HiggsPair23);
    HiggsPair23.SetBdt(HiggsReader.Bdt());

    analysis::Doublet Top0 = analysis::Doublet(jets[0], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top0);
    Top0.SetBdt(TopReader.Bdt());
    analysis::Doublet Top1 = analysis::Doublet(jets[1], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top1);
    Top1.SetBdt(TopReader.Bdt());
    analysis::Doublet Top2 = analysis::Doublet(jets[2], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top2);
    Top2.SetBdt(TopReader.Bdt());
    analysis::Doublet Top3 = analysis::Doublet(jets[3], Leptons[0]);
    LeptonicTopTagger.GetBranch(Top3);
    Top3.SetBdt(TopReader.Bdt());

    analysis::Doublet AntiTop0 = analysis::Doublet(jets[0], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop0);
    AntiTop0.SetBdt(TopReader.Bdt());
    analysis::Doublet AntiTop1 = analysis::Doublet(jets[1], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop1);
    AntiTop1.SetBdt(TopReader.Bdt());
    analysis::Doublet AntiTop2 = analysis::Doublet(jets[2], Leptons[1]);
    LeptonicTopTagger.GetBranch(AntiTop2);
    AntiTop2.SetBdt(TopReader.Bdt());
    analysis::Doublet AntiTop3 = analysis::Doublet(jets[3], Leptons[1]);
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
