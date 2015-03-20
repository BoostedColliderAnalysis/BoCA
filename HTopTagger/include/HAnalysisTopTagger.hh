# ifndef HAnalysisTopTagger_hh
# define HAnalysisTopTagger_hh

#include <sys/stat.h>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HTopHadronicTagger.hh"
# include "HTopLeptonTagger.hh"


/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
namespace htoptagger
{
class HAnalysis : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

    hanalysis::HBottomTagger BottomTagger;
    hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

    hanalysis::HTopHadronicTagger TopHadronicTagger;
    HTopLeptonTagger TopLeptonTagger;


    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    std::vector<hanalysis::HFile> Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {
        return  "TopTagger-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "TeV-" + std::to_string(Mass()) + "GeV-" + ProcessName(tt);
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "htoptagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg};
    enum HColliderType {LHC, FHC, LE};
    enum HDecay {Leptonic, Hadronic, Semi};

    inline HDecay TopDecay() const {
      return Hadronic;
//       return Leptonic;
    }

    // in GeV
    inline int Mass() const {
        //     return 0;
        //     return 400;
        //     return 600;
        //         return 1000;
                return 2000;
//         return 3000;
        //     return 4000;
        //         return 5000;
        //     return 6000;
        //     return 7000;
        //     return 8000;
        //     return 9000;
        //         return 10000;
    }

    // in GeV
    inline int PreCut() const {
//             return 0;
        //     return 30;
        //     return 80;
//                 return 150;
//         return 300;
        return 1;
    }

    inline int EventNumberMax() const {
        //         return 1000000;
        //         return 100000;
//         return 10000;
        return 1000;
//         return 100;
    };

    inline HColliderType ColliderType() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }

    inline int BackgroundFileNumber() const {
        return 1;
        //         return 2;
        //       return 4;
        //       return 5;
        //       return 10;
    }

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
//         std::string FileName = ProcessName(Background) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "TeV";
        std::string FileName = ProcessName(Background) + "_" + std::to_string(PreCut()) + "TeV";
        HStrings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
//             FileNames.push_back(FileName + "_" + std::to_string(FileNumber));
            FileNames.push_back(FileName);
        }
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const ProcessType Process) const {
//         return ProcessName(Process) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "TeV-run_01";
        return ProcessName(Process) + "_" + std::to_string(PreCut()) + "TeV-run_01";
    }

    float BackgroundCrosssection(const ProcessType Proccess) const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case 30 :
                switch (Proccess) {
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
                switch (Proccess) {
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
            }
        case FHC:
            switch (PreCut()) {
            case 30 :
                switch (Proccess) {
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
                switch (Proccess) {
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
                switch (Proccess) {
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
                switch (Proccess) {
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
            case 300 :
                switch (Proccess) {
                case ttbb :
                    return 263;
                case ttcc:
                    return 192.82;
                case ttjj:
                    return 28200;
                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Proccess) {
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
        case bbjj:
            return "bbjj";
        case tt:
          switch (TopDecay()) {
            case Hadronic :
                return "tt_hadronic";
            case  Leptonic :
                return "tt_leptonic";
            case Semi :
                return "tt";
            }
        case bb:
            return "bb";
        case cc:
            return "cc";
        case qq:
            return "qq";
        case gg:
            return "gg";
        default:
            Print(HError, "unhandled case");
            return "";
        }
    }

    hanalysis::HJetTag JetTag;

    hanalysis::HReader BottomReader;
//     hanalysis::HReader WSemiReader;
    hanalysis::HReader WHadronicReader;
    hanalysis::HReader TopHadronicReader;
    hanalysis::HReader TopLeptonReader;

    void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    /**
     * @brief Main Analysis function
     *
     */
    bool Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    bool GetBottomTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetBottomReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
//     bool GetWSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
//     bool GetWSemiReader(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetWReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopHadronicTag(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag);
    bool GetTopSemiTag(hanalysis::HEvent &Event, hanalysis::HObject::HTag Tag);
    bool GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag);
    bool GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag);

};

}

#endif
