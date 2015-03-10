# ifndef HAnalysisCharged_hh
# define HAnalysisCharged_hh

#include <sys/stat.h>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HBranchHeavyHiggs.hh"
# include "HReader.hh"
# include "HFactory.hh"
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
    HAnalysisCharged();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

    hanalysis::HTopHadronicTagger TopHadronicTagger;
    hanalysis::HTopSemiTagger TopSemiTagger;

    hanalysis::HChargedHiggsSemiTagger ChargedHiggsSemiTagger;
    hanalysis::HChargedJetPairTagger JetPairTagger;

    hheavyhiggs::HChargedSignatureSemiTagger SignatureSemiTagger;
    hheavyhiggs::HChargedEventSemiTagger EventSemiTagger;

    std::vector< hanalysis::HFile > Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {
        return  "Charged-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }

    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

protected:

    virtual inline std::string NameSpaceName() const {
        return "hheavyhiggs";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum HProcessType {Htb, ttbb, ttcc, ttjj, tt};
    enum HColliderType {LHC, FHC, LE};

    // in GeV
    inline int Mass() const {
        //     return 400;
        //     return 600;
        //     return 1000;
//         return 2000;
//         return 3000;
//             return 4000;
//             return 5000;
            return 6000;
//             return 7000;
//         return 8000;
        //     return 9000;
        //         return 10000;
    }

    // in GeV
    inline int PreCut() const {
        //     return 30;
        //     return 80;
        //     return 150;
//         return 300;
        return 1000;
    }

    inline int EventNumberMax() const {
//         return 1000000;
        //         return 100000;
        return 10000;
        //         return 1000;
//                 return 100;
    };

    inline HColliderType ColliderType() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }


    inline int BackgroundFileNumber() const {
//         return 1;
//         return 2;
        //       return 4;
        return 5;
        //       return 10;
    }

    // in fb
    float SignalCrosssection() const {
        switch (ColliderType()) {
        case LHC:
            switch (Mass()) {
            case 400 :
                return 5.442745880581412;
            case 500:
                return 2.8815551913608317;
            case 1000:
                return 0.21859989068163246;
            case 2000:
                return 0.005602117167462312;
            case 3000:
                return 0.00029931623544508237;
            case 4000:
                return 0.000020365970226322686;
            default:
                Print(HError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
            case 1000:
                return 38.501952876819495;
            case 2000:
                return 3.7429107249252125;
            case 3000:
                return 0.7636108315783771;
            case 4000:
                return 0.22232809767415665;
            case 5000:
                return 0.07946706739238736;
            case 6000:
                return 0.03291534649650638;
            case 7000:
                return 0.013177693;
            case 8000:
                return 0.00738551034925011;
            case 10000:
                return 0.002068335074918064;
            case 12000:
                return 0.0006693740636689783;
            case 15000:
                return 0.00015145887990818783;
            case 20000:
                return 0.000016677670760729152;
            case 25000:
                return 2.2075388746962393e-6;
            default:
                Print(HError, "Signal Crosssection", "unhandled case");
                return 1;
            }
        default:
            Print(HError, "Signal Crosssection", "unhandled case");
            return 1;
        }
    }

    inline hanalysis::HFile BackgroundFile(const HProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    hanalysis::HFile BackgroundFile(const HProcessType Background, const int FileSum) const {
        std::string FileName = ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV";
        HStrings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
            FileNames.push_back(FileName + "_" + std::to_string(FileNumber));
        }
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const HProcessType Background) const {
        return ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
    }

    float BackgroundCrosssection(const HProcessType Process) const {
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
                default :
                    Print(HError, "unhandled case");
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
                    Print(HError, "unhandled case");
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
                    Print(HError, "unhandled case");
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
                    Print(HError, "unhandled case");
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
                    Print(HError, "unhandled case");
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
                    Print(HError, "unhandled case");
                    return 1;
                }
            }
        case LE: {
            switch (PreCut()) {
            case 300 :
                switch (Process) {
                case ttbb :
                    return 263;
                case ttcc:
                    return 192.82;
                case ttjj:
                    return 28200;
                default :
                    Print(HError, "unhandled case");
                    return 1;
                }
            case 1000 :
                switch (Process) {
                case tt :
                    return 2.973 * 2 * 1000;
                default :
                    Print(HError, "unhandled case");
                    return 1;
                }
            }
            default :
                Print(HError, "unhandled case");
                return 1;
            }
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
            Print(HError, "unhandled case");
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
    hanalysis::HReader ChargedHiggsSemiReader;
    hanalysis::HReader SignatureSemiReader;
    hanalysis::HReader EventSemiReader;

    void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

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
    bool GetTopLeptonicTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetChargedHiggsSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetChargdHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetSignatureSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetSignatureSemiReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag);
    bool GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag);

};

#endif
