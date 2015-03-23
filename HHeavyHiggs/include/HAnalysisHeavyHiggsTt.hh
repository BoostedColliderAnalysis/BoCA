# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

#include <sys/stat.h>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"
# include "HEventTtSemiTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisTt : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysisTt();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;

    hanalysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

    hheavyhiggs::HEventTtSemiTagger EventSemiTagger;


    std::vector<hanalysis::HFile> Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProcessName() const {
        return "Fusion";
    }

    inline std::string ProjectName() const {
        return  ProcessName() + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }


    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt, H0};
//     enum HColliderType {LHC, FHC, LE};

    // in GeV
    inline int Mass() const {
        //     return 0;
        //     return 400;
        //     return 600;
//         return 1000;
//         return 2000;
//                 return 3000;
//         return 4000;
                return 5000;
//         return 6000;
        //     return 7000;
//             return 8000;
        //     return 9000;
        //         return 10000;
    }

    // in GeV
    inline int PreCut() const {
        //     return 30;
        //     return 80;
        //         return 150;
//         return 250;
//         return 300;
        return 1000;
//         return 1500;
//         return 2000;
//         return 2500;
    }

    inline int EventNumberMax() const {
//                 return 1000000;
//         return 100000;
        return 10000;
        //         return 1000;
//                 return 100;
    };

    inline HColliderType ColliderType() const {
//         return LHC;
        //       return FHC;
        return LE;
    }

    inline int BackgroundFileNumber() const {
        //         return 1;
        //         return 2;
        //       return 4;
//         return 5;
        //       return 10;
        return 32;
    }


    // in fb
    float SignalCrosssection() const {
        switch (ColliderType()) {
        case LHC:
            switch (Mass()) {
            case 400 :
                return 1463.1219866990498;
            case 500:
                return 512.5992335098167;
            case 1000:
                return 10.942712198242141;
            case 2000:
                return 0.10283305582403454;
            default:
                Print(HError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
                // tan beta = 2
            case 400 :
                return 48385.16604388162;
            case 700 :
                return 5388.806849750459;
            case 800:
                return 2987.6531326979493;
            case 1000:
                return 1062.9847850641604;
            case 1500:
                return 148.78718745483314;
            case 2000:
                return 33.76298845204924;
            case 3000:
                return 3.715444262833449;
            case 4000:
                return 0.7052693313851425;
            case 5000:
                return 0.1841745400744028;
            case 6000:
                return 0.058156868371520024;
            case 8000:
                return 0.008651760976852958;
            case 10000:
                return 0.0018198636858628185;
            case 12000:
                return 0.0004674423191995998;
                // tan beta = 10
//             case 400 :
//                 return 131.94947391305232;
//             case 700 :
//                 return 30.221882093141176;
//             case 800:
//                 return 17.100219340176437;
//             case 1000:
//                 return 6.146859900494059;
//             case 1500:
//                 return 0.8522475589106505;
//             case 2000:
//                 return 0.19108540463151014;
//             case 3000:
//                 return 0.020689601081729285;
//             case 4000:
//                 return 0.0038886961414115293;
//             case 5000:
//                 return 0.0010087505187664622;
//             case 6000:
//                 return 0.0003169949319582519;
//             case 8000:
//                 return 0.00004684534698668758;
//             case 10000:
//                 return 9.81016234854116e-6;
//             case 12000:
//                 return 2.5117159473593533e-6;
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
            Print(HError, "Background Crosssection",  "unhandled pre cut", PreCut());
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
        case H0:
            return "H0-ljbb";
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
    hanalysis::HReader WSemiReader;
    hanalysis::HReader WHadronicReader;
    hanalysis::HReader TopLeptonicReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopSemiReader;
    hanalysis::HReader HeavyHiggsSemiReader;
    hanalysis::HReader EventSemiReader;

    void ResetBranch();

    void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

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
    bool GetTopHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag);

};

#endif
