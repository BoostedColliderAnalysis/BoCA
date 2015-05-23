# ifndef HAnalysisHiggsCpv_hh
# define HAnalysisHiggsCpv_hh

#include <sys/stat.h>

# include "File.hh"
# include "Analysis.hh"
// # include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "HJetTag.hh"
# include "HEventTtSemiTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisTt : public analysis::Analysis
{

public:

    /**
     * @brief Constructor
     *
     */
//     HAnalysisTt();

using analysis::Analysis::Analysis;

    analysis::BottomTagger bottom_tagger_;
    analysis::WSemiTagger w_semi_tagger;
    analysis::WHadronicTagger w_hadronic_tagger;

    analysis::TopHadronicTagger top_hadronic_tagger;
    analysis::TopSemiTagger top_semi_tagger;

    analysis::HHeavyHiggsSemiTagger HeavyHiggsSemiTagger;

    hheavyhiggs::EventTtSemiTagger eventSemiTagger;


    std::vector<analysis::File> Files(const analysis::Object::Tag Tag);

    inline std::string ProcessName() const {
        return "Fusion";
    }

    inline std::string ProjectName() const {
        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }


//     std::string StudyName(const analysis::HAnalysis::Tagger Tagger) const;

//     void PrepareReader(const analysis::HAnalysis::HTagger Tagger, const analysis::HAnalysis::Tag Tag);

    void SetTrees();

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt, H0};
    enum ColliderType {LHC, FHC, LE};

    // in GeV
    inline int Mass() const {
        //     return 0;
        //     return 400;
             return 500;
        //     return 600;
//            return 800;
//           return 1000;
//         return 2000;
//                 return 3000;
//         return 4000;
//                return 5000;
//         return 6000;
        //     return 7000;
//             return 8000;
        //     return 9000;
//        return 10000;
//                 return 12000;
//                 return 15000;
//                 return 20000;
    }

    // in GeV
    inline int PreCut() const {
        switch (collider_type()) {
        case LHC :
            switch (Mass()) {
            case 500 :
                return 0;
            case 1000 :
                return 250;
            case 2000 :
                return 250;
            case 3000 :
                return 250;
            default :
                return 0;
            }
        case LE :
            switch (Mass()) {
            case 500 :
                return 0;
            case 1000 :
                return 300;
            case 2000 :
                return 300;
            case 4000 :
                return 1500;
            case 6000 :
                return 2500;
            case 10000 :
                return 2500;
            case 15000 :
                return 2500;
            case 20000 :
                return 2500;
            default :
                return 0;
            }
        default :
            return 0;
        }
//            return 0;
        //     return 30;
        //     return 80;
        //         return 150;
// return 100;
//         return 250;
//          return 300;
//        return 1000;
//         return 1500;
//         return 2000;
//             return 2500;
    }

    inline int EventNumberMax() const {
//                 return 1000000;
//         return 100000;
        return 10000;
        //         return 1000;
//                 return 100;
    };

    inline ColliderType collider_type() const {
//         return LHC;
        //       return FHC;
        return LE;
    }

    inline int BackgroundFileNumber() const {
        switch (collider_type()) {
        case LHC :
            switch (PreCut()) {
            case  0 :
                return 79;
                //                 return 1; // < this must be removed !!
            case  250 :
                return 41;
            }
        case LE :
            switch (PreCut()) {
            case  0 :
//                   return 98;
                return 1; // < this must be removed !!
            case  100 :
                return 15;
            case  250 :
                return 15;
            case  300 :
//                   return 110;
                return 1; // < this must be removed !!
            case  1000 :
                return 32;
            case  1500 :
//                   return 34;
                return 1; // < this must be removed !!
            case  2000 :
                return 26;
            case  2500 :
//                   return 11;
                return 1; // < this must be removed !!
            }
        default :
            return 1;
        }
    }


    // in fb
    float SignalCrosssection() const {
        switch (collider_type()) {
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
            case 3000:
                return 0.003583086718061121;
            case 4000:
                return 0.00020344209136808554;
            default:
                Print(kError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
                // tan beta = 2
            case 400 :
                return 48385.16604388162;
            case 500 :
                return 21753.261647408788;
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
            case 15000:
                return 0.000046; //<this is just wrong get the right numbers
            case 20000:
                return 0.0000046; //<this is just wrong get the right numbers
            default:
                Print(kError,  "Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Print(kError,  "Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    float MissingEt() {
        switch (collider_type()) {
        case LHC :
            return 30;
        case LE :
            return 60;
        default :
            return 0;
        }
    }

    float LeptonPt() {
        switch (collider_type()) {
        case LHC :
            return 50;
        case LE :
            return 100;
        default :
            return 0;
        }
    }

    inline analysis::File BackgroundFile(const ProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    analysis::File BackgroundFile(const ProcessType Background, const int FileSum) const {
        std::string FileName = ProcessName(Background) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV";
        Strings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
            FileNames.emplace_back(FileName + "_" + std::to_string(FileNumber));
        }
        return analysis::File(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const ProcessType Process) const {
        return ProcessName(Process) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
    }

    float BackgroundCrosssection(const ProcessType Process) const {
        switch (collider_type()) {
        case LHC :
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 97.54 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 250 :
                switch (Process) {
                case tt :
                    return 5.698 * 2 * 1000;
                default :
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        case LE:
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt:
                    return 3600 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
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
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1000 :
                switch (Process) {
                case tt :
                    return 1.532 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 1500 :
                switch (Process) {
                case tt :
                    return 0.2447 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2000 :
                switch (Process) {
                case tt :
                    return 0.09014 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 2500 :
                switch (Process) {
                case tt :
                    return 0.03038 * 2 * 1000;
                default:
                    Print(kError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            }
        default:
            Print(kError, "Background Crosssection",  "unhandled pre cut", PreCut());
            return 1;
        }
    }

    std::string ColliderName(const ColliderType Collider) const {
        switch (Collider) {
        case LHC :
            return "14TeV";
        case FHC:
            return "100TeV";
        case LE:
            return "LE";
        default:
            Print(kError, "unhandled case");
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
            Print(kError, "unhandled case");
            return "";
        }
    }

    analysis::HJetTag JetTag;

    analysis::Reader BottomReader;
    analysis::Reader WSemiReader;
    analysis::Reader WHadronicReader;
    analysis::Reader TopLeptonicReader;
    analysis::Reader TopHadronicReader;
    analysis::Reader TopSemiReader;
    analysis::Reader HeavyHiggsSemiReader;
    analysis::Reader eventSemiReader;

    void ResetBranch();

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger);

    /**
     * @brief Main Analysis function
     *
     */
    int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag);

//     bool GetBottomTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetBottomReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWSemiTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWSemiReader(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetWReader(analysis::Event &event, const Tag Tag);
//     bool GetTopHadronicTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetTopSemiTag(analysis::Event &event, analysis::Object::Tag Tag);
//     bool GetTopHadronicReader(analysis::Event &event, const Tag Tag);
//     bool GetTopSemiReader(analysis::Event &event, const Tag Tag);
//     bool GetHeavyHiggsSemiTag(analysis::Event &event, const analysis::Object::Tag Tag);
//     bool GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag);
//     bool GeteventSemiTag(analysis::Event &event, const Tag Tag);
//     bool GeteventSemiReader(analysis::Event &event, const Tag Tag);

};

#endif
