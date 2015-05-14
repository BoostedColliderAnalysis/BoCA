# ifndef HAnalysisCharged_hh
# define HAnalysisCharged_hh

#include <sys/stat.h>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "HJetTag.hh"

# include "HChargedEventSemiTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hheavyhiggs::HAnalysisCharged : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
//     HAnalysisCharged();

using hanalysis::HAnalysis::HAnalysis;

    hanalysis::BottomTagger bottom_tagger_;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::WHadronicTagger w_hadronic_tagger;

    hanalysis::TopHadronicTagger top_hadronic_tagger;
    hanalysis::HTopSemiTagger TopSemiTagger;

    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger JetPairTagger;

    hheavyhiggs::HChargedSignatureSemiTagger SignatureSemiTagger;
    hheavyhiggs::HChargedeventSemiTagger eventSemiTagger;

    std::vector< hanalysis::RootFile > Files(const hanalysis::HObject::Tag tag);

    inline std::string ProcessName()const {
        return "Charged";
    }

    inline std::string ProjectName() const {
        return  ProcessName() + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }

//     std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void SetTrees();

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum HProcessType {Htb, ttbb, ttcc, ttjj, tt};
//     enum HColliderType {LHC, FHC, LE};

    // in GeV
    inline int Mass() const {
        //     return 400;
//         return 500;
        //     return 600;
//             return 800;
//             return 1000;
//         return 1500;
//         return 2000;
         return 3000;
//             return 4000;
//             return 5000;
//         return 6000;
//             return 7000;
//         return 8000;
        //     return 9000;
//                 return 10000;
//                 return 12000;
//         return 15000;
//        return 20000;
    }

    // in GeV
    inline int PreCut() const {
        switch (ColliderType()) {
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
//         return 0;
//             return 30;
        //     return 80;
        //     return 150;
//         return 100;
//         return 250;
//         return 300;
//         return 1000;
//         return 1500;
//         return 2000;
//         return 2500;
    }


    float MissingEt() {
        switch (ColliderType()) {
        case LHC :
            return 30;
        case LE :
            return 60;
        default :
            return 0;
        }
    }

    float LeptonPt() {
        switch (ColliderType()) {
        case LHC :
            return 50;
        case LE :
            return 100;
        default :
            return 0;
        }
    }

    inline int EventNumberMax() const {
// return 10000000;
//         return 1000000;
//                 return 100000;
        return 10000;
//                 return 1000;
//         return 500;
//         return 100;
    };

    inline HColliderType ColliderType() const {
        return LHC;
        //       return FHC;
       // return LE;
    }


    inline int BackgroundFileNumber() const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case 0 :
//                 return 1;
                return 79; // < should be switched on
            case 250 :
                return 58; // < should be switched on
            default :
                return 1;
            }
        case LE :
            switch (PreCut()) {
            case 2500 :
                return 28;
            case 2000 :
                return 16;
            case 1500 :
                return 19;
            case 300 :
                return 61; // < should be switched on
//                 return 1;
            case 0 :
                return 118; // < should be switched on
//                 return 1;
            default :
                return 1;
            }
        default :
            return 1;
        }
    }

    // in fb
    float SignalCrosssection() const {
        switch (ColliderType()) {
        case LHC:
            switch (Mass()) {
            case 500:
                return 3.0495761279999996;
            case 1000:
                return 0.22623192864;
            case 2000:
                return 0.005720855039999999;
            case 3000:
                return 0.0003035467008;
            case 4000:
                return 0.000020556093312;
            default:
                Print(kError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
            case 500:
              return 247.86995327999998;
            case 700:
              return 109.26120959999999;
            case 1000:
              return 39.81212064;
            case 1500:
              return 10.639675008;
            case 2000:
              return 3.8189750399999998;
            case 3000:
              return 0.7737415487999998;
            case 4000:
              return 0.22421177856;
            case 5000:
              return 0.07985005056;
            case 6000:
              return 0.03297554496;
            case 8000:
              return 0.007364981375999998;
            case 10000:
              return 0.0020553163775999996;
            case 12000:
              return 0.0006632091647999999;
            case 15000:
              return 0.00014951794176;
            case 20000:
              return 0.000016388469792;
            default:
                Print(kError, "Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Print(kError, "Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    inline hanalysis::RootFile BackgroundFile(const HProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    hanalysis::RootFile BackgroundFile(const HProcessType Background, const int FileSum) const {
        std::string FileName = ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV";
        Strings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
            FileNames.emplace_back(FileName + "_" + std::to_string(FileNumber));
        }
        return hanalysis::RootFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const HProcessType Background) const {
        return ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
    }

    float BackgroundCrosssection(const HProcessType Process) const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case 0 :
                switch (Process) {
                case tt :
                    return 97.54 * 2 * 1000;
                default :
                    Print(kError, "unhandled case");
                };
            case 30 :
                switch (Process) {
                case ttbb :
                    return 298.2;
                case ttcc:
                    return 264.6;
                case ttjj:
                    return 9999999999;
                default :
                    Print(kError, "unhandled case");
                };
            case 80 :
                switch (Process) {
                case ttbb :
                    return 89.32;
                case ttcc:
                    return 78.42;
                case ttjj:
                    return 9999999999;
                default :
                    Print(kError, "unhandled case");
                    return 1;
                }
            case 250 :
                switch (Process) {
                case tt :
                    return 4.206 * 2 * 1000;
                default :
                    Print(kError, "unhandled case");
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
                default :
                    Print(kError, "unhandled case");
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
                default :
                    Print(kError, "unhandled case");
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
                default :
                    Print(kError, "unhandled case");
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
                default :
                    Print(kError, "unhandled case");
                    return 1;
                }
            }
        case LE: {
            switch (Process) {
            case tt:
                switch (PreCut()) {
                case 0 :
                    return 3564 * 2 * 1000;
                case 300 :
                    return 187.3 * 2 * 1000;
                case 1500 :
                    return 0.447 * 2 * 1000;
                case 2500 :
                    return 0.0442 * 2 * 1000;
                }
            case ttbb :
                switch (PreCut()) {
                case 300 :
                    return 263;
                }
            case ttcc:
                switch (PreCut()) {
                case 300 :
                    return 192.82;
                }
            case ttjj:
                switch (PreCut()) {
                case 300 :
                    return 28200;
                }
            default :
                Print(kError, "unhandled case");
                return 1;
            }
        }
        default :
            Print(kError, "unhandled case");
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
        default :
            Print(kError, "unhandled case");
            return "";
        }
    }

    std::string ProcessName(const HProcessType Process) const {
        switch (Process) {
        case Htb:
//             return "H+tb-bbbbjjlnu";
            return "H+tb-ljbbbb";
        case ttbb :
            return "ttbb-ljbbbb";
        case ttcc:
            return "ttcc-ljbbcc";
        case ttjj:
            return "ttjj-ljbbjj";
        case tt:
            return "tt_inc+";
        default :
            Print(kError, "unhandled case");
            return "";
        }
    }

    hanalysis::HJetTag JetTag;

    hanalysis::Reader BottomReader;
    hanalysis::Reader JetPairReader;
    hanalysis::Reader WSemiReader;
    hanalysis::Reader WHadronicReader;
    hanalysis::Reader TopLeptonicReader;
    hanalysis::Reader TopHadronicReader;
    hanalysis::Reader TopSemiReader;
    hanalysis::Reader ChargedHiggsSemiReader;
    hanalysis::Reader SignatureSemiReader;
    hanalysis::Reader eventSemiReader;

//     void NewBranches(ExRootTreeWriter &tree_writer, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::Tagger::Stage stage);

//     void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::Tag Tag);

    /**
     * @brief Main Analysis function
     *
     */
    int Analysis(hanalysis::Event &event, const hanalysis::Tagger::Stage stage, const Tag tag);

//     bool GetBottomTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetBottomReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetWSemiTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetWSemiReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetWTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetWReader(hanalysis::Event &event, const Tag Tag);
//     bool GetJetPairTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetJetPairReader(hanalysis::Event &event, const Tag Tag);
//     bool GetTopLeptonicTag(hanalysis::Event &event, hanalysis::HObject::Tag Tag);
//     bool GetTopLeptonicReader(hanalysis::Event &event, const Tag Tag);
//     bool GetTopHadronicTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetTopSemiTag(hanalysis::Event &event, hanalysis::HObject::Tag Tag);
//     bool GetTopHadronicReader(hanalysis::Event &event, const Tag Tag);
//     bool GetTopSemiReader(hanalysis::Event &event, const Tag Tag);
//     bool GetChargedHiggsSemiTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetChargdHiggsSemiReader(hanalysis::Event &event, const Tag Tag);
//     bool GetSignatureSemiTag(hanalysis::Event &event, const Tag Tag);
//     bool GetSignatureSemiReader(hanalysis::Event &event, const Tag Tag);
//     bool GeteventSemiTag(hanalysis::Event &event, const Tag Tag);
//     bool GeteventSemiReader(hanalysis::Event &event, const Tag Tag);

};

#endif
