# pragma once

# include "HAnalysis.hh"
# include "HBranchHeavyHiggs.hh"
# include "HEventSemiTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisMva : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisMva();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HJetPairTagger JetPairTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

//     hanalysis::HTopLeptonicTagger TopLeptonicTagger;
    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;

//     hanalysis::HHeavyHiggsLeptonicTagger HeavyHiggsLeptonicTagger;
//     hanalysis::HHeavyHiggsHadronicTagger HeavyHiggsHadronicTagger;
    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

//     hheavyhiggs::HEventLeptonicTagger EventLeptonicTagger;
//     hheavyhiggs::HEventHadronicTagger EventHadronicTagger;

    hheavyhiggs::HSignatureSemiTagger SignatureSemiTagger;
    hheavyhiggs::HEventSemiTagger EventSemiTagger;

    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    std::vector<hanalysis::HFile> Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {
//        return  ProcessName() + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV-Eta2.5";
        return  ProcessName() + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }

    inline std::string ProcessName() const {
        return "Neutral";
    }

    // in GeV
    inline int Mass() const {
        //     return 300;
        //     return 400;
//            return 500;
        //     return 600;
        //     return 700;
//             return 800;
        //     return 900;
//         return 1000;
         return 2000;
//            return 3000;
//         return 4000;
//                 return 5000;
//                return 6000;
//             return 7000;
//         return 8000;
//             return 9000;
//                 return 10000;
//                 return 12000;
//                 return 15000;
//                 return 20000;
    }

    // in GeV
    inline int PreCut() const {
//        return 0;
        //     return 30;
        //     return 80;
// return 100;
        //     return 150;
         return 250;
//              return 300;
//            return 1000;
//         return 1500;
//        return 2000;
//         return 2500;
    }

    inline int EventNumberMax() const {
//            return 10000000;
//                   return 1000000;
//         return 100000;
       return 10000;
//                 return 1000;
//                         return 100;
    };

    inline HColliderType ColliderType() const {
         return LHC;
        //       return FHC;
//         return LE;
    }


    inline int BackgroundFileNumber() const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case  0 :
                return 79;
//                 return 2; // < this must be removed !!
            case  250 :
                return 41;
            }
        case LE :
            switch (PreCut()) {
            case  0 :
              return 98;
            case  100 :
                return 15;
            case  250 :
                return 15;
            case  300 :
                return 110;
            case  1000 :
                return 32;
            case  1500 :
                return 34;
            case  2000 :
                return 26;
            case  2500 :
                return 11;
            }
        }
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt};

    // in fb
    float SignalCrosssection() const {
        switch (ColliderType()) {
        case LHC:
            switch (Mass()) {
            case 400 :
                return 15.457345846238557;
            case 500:
                return 10.57186928542166;
            case 1000:
                return 0.6300105025483057;
            case 2000:
                return 0.011364910695033002;
            default:
                Print(HError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
            case 400 :
                return 465.78976127779805;
            case 500:
                return 403.1726637894434;
            case 600:
                return 272.6441648068077;
            case 800:
                return 122.80517218259386;
            case 1000:
                return 60.62802137818876;
            case 1500:
                return 14.625345866484361;
            case 2000:
                return 4.920796866551275;
            case 3000:
                return 0.9234071865754303;
            case 4000:
                return 0.25736547733711523;
            case 5000:
                return 0.08899831451027759;
            case 6000:
                return 0.03602204622881514;
            case 7000:
                return 0.01576206604679042;
            case 8000:
                return 0.0076693087930297206;
            case 9000:
                return 0.0039008532687324735;
            case 10000:
                return 0.002076042904956223;
            case 12000:
                return 0.0006621537122277095;
            case 15000:
                return 0.0001442241864611344;
            case 20000:
                return 0.000015425841205626978;
            default:
                Print(HError,  "Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Print(HError,  "Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    inline hanalysis::HFile BackgroundFile(const ProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    hanalysis::HFile BackgroundFile(const ProcessType Background, const int FileSum) const {
        std::string FileName = ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV";
        HStrings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
            FileNames.push_back(FileName + "_" + std::to_string(FileNumber));
        }
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const ProcessType Process) const {
        return ProcessName(Process) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
    }

    float BackgroundCrosssection(const ProcessType Process) const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 97.54 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                };
            case 30 :
                switch (Process) {
                case ttbb :
                    return 298.2;
                case ttcc:
                    return 264.6;
                case ttjj:
                    return 9999999999;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                };
            case 80 :
                switch (Process) {
                case ttbb :
                    return 89.32;
                case ttcc:
                    return 78.42;
                case ttjj:
                    return 9999999999;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 250 :
                switch (Process) {
                case tt :
                    return 5.698 * 2 * 1000;
                default :
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        case FHC:
            switch (PreCut()) {
            case 30 :
                switch (Process) {
                case ttbb :
                    return 2990;
                case ttcc:
                    return 2684;
                case ttjj:
                    return 9999999999;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 80 :
                switch (Process) {
                case ttbb :
                    return 1171.6;
                case ttcc:
                    return 1042.0;
                case ttjj:
                    return 9999999999;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Process) {
                case ttbb :
                    return 605.199003171 * 2;
                case ttcc:
                    return 468.061778817 * 2;
                case ttjj:
                    return 61.9287096863 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 300 :
                switch (Process) {
                case ttbb :
                    return 242;
                case ttcc:
                    return 176;
                case ttjj:
                    return 26000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        case LE:
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 3600 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Process) {
                case ttbb :
                    return 688;
                case ttcc:
                    return 534;
                case ttjj:
                    return 70289;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 300 :
                switch (Process) {
                case ttbb :
                    return 263;
                case ttcc:
                    return 192.82;
                case ttjj:
                    return 28200;
                case tt :
                    return 214.1 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1000 :
                switch (Process) {
                case tt :
                    return 1.532 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1500 :
                switch (Process) {
                case tt :
                    return 0.2447 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2000 :
                switch (Process) {
                case tt :
                    return 0.09014 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2500 :
                switch (Process) {
                case tt :
                    return 0.03038 * 2 * 1000;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        default:
            Print(HError, "Background Crosssection",  "unhandled case");
            return 1;
        }
    }

    std::string ColliderName(const HColliderType Collider) const {
        switch (Collider) {
        case LHC :
            return "14TeV";
        case FHC:
            return "100TeV";
        case LE:
            return "LE";
        default:
            Print(HError, "unhandled case");
            return "";
        }
    }

    std::string ProcessName(const ProcessType Process) const {
        switch (Process) {
        case Hbb:
            return "H0bb-ljbbbb";
        case ttbb :
            return "ttbb-ljbbbb";
        case ttcc:
            return "ttcc-ljbbcc";
        case ttjj:
            return "ttjj-ljbbjj";
        case tt:
            return "tt_inc";
        default:
            Print(HError, "unhandled case");
            return "";
        }
    }

    hanalysis::HJetTag JetTag;

    hanalysis::HReader BottomReader;
    hanalysis::HReader JetPairReader;
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WHadronicReader;
    hanalysis::HReader TopLeptonicReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader HeavyHiggsSemiReader;
    hanalysis::HReader HeavyHiggsLeptonicReader;
    hanalysis::HReader SignatureSemiReader;
    hanalysis::HReader EventSemiReader;
    hanalysis::HReader EventLeptonicReader;

    void NewBranches(ExRootTreeWriter &tree_writer, const hanalysis::HAnalysis::HTagger tagger);

    /**
     * @brief Main Analysis function
     *
     */
    bool Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    bool GetBottomTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetBottomReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWSemiReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetJetPairTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetJetPairReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopLeptonicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetHeavyHiggsHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsLeptonicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsLeptonicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventLeptonicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetEventHadronicTag(hanalysis::HEvent &Event, const HTag Tag);

    bool GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag);

    bool GetSignatureSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetSignatureSemiReader(hanalysis::HEvent &Event, const HTag Tag);

    bool GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventLeptonicReader(hanalysis::HEvent &Event, const HTag Tag);


};
