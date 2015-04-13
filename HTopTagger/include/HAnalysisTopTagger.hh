# pragma once

#include <sys/stat.h>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HTopHadronTagger.hh"
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
//     hanalysis::HWSemiTagger WSemiTagger;
    hanalysis::HWTagger WHadronicTagger;

    HTopHadronTagger TopHadronicTagger;
    HTopLeptonTagger TopLeptonTagger;


    std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

    void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    void SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag);

    std::vector<hanalysis::HFile> Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag);

    inline std::string ProjectName() const {

        return  "TopTagger-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + ProcessName(tt);
    }

    enum HDecay {Leptonic, Hadronic, Semi};

    inline HDecay TopDecay() const {
        return Hadronic;
//          return Leptonic;
//         return Semi;
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "htoptagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg, wg, wq, wc, wb, wu, wcb, wbu, ttlep, tthad, hh, ww, zz};
    enum HColliderType {LHC, FHC, LE};

    // in GeV
    inline int PreCut() const {
//             return 0;
//         return 1;
        //     return 30;
        //     return 80;
//                 return 150;
//         return 300;
        return 1000;
    }

    inline int EventNumberMax() const {
        //         return 1000000;
        //         return 100000;
        return 10000;
//         return 1000;
//         return 100;
//         return 10;
    }

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
            default:
                Print(HError, "Signal Crosssection", "unhandled case");
                return 1;
            } ;
        case FHC:
        case LE:
            switch (Mass()) {
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

        std::string FileName = ProcessName(Background) + "_" + std::to_string(PreCut()) + "GeV";
        HStrings FileNames;
        for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
//             FileNames.push_back(FileName + "_" + std::to_string(FileNumber));
            FileNames.push_back(FileName);
        }
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string BackgroundTree(const ProcessType Process) const {
        return ProcessName(Process) + "_" + std::to_string(PreCut()) + "GeV" + "-run_01";
    }

    float BackgroundCrosssection(const ProcessType Proccess) const {
        switch (ColliderType()) {
        case LHC :
            switch (PreCut()) {
            case 30 :
                switch (Proccess) {

                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                };
            case 80 :
                switch (Proccess) {

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

                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 80 :
                switch (Proccess) {

                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 150 :
                switch (Proccess) {

                default:
                    Print(HError, "Background Crosssection", "unhandled case");
                    return 1;
                }
            case 300 :
                switch (Proccess) {

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
//                 return "tt_hadronic_1TeV";
                return "tt_hadronic";
            case  Leptonic :
//                 return "tt_leptonic_1TeV";
                return "tt_leptonic";
            case Semi :
                return "tt_semi_nopre";
            }
        case ttlep:
            return "tt_leptonic";
        case tthad:
            return "tt_hadronic";
        case bb:
            return "bb";
        case cc:
            return "cc";
        case qq:
            return "qq";
        case gg:
            return "gg";
        case wg:
            return "wgg";
        case wq:
            return "wq";
        case wc:
            return "wc";
        case wcb:
            return "wc_b_pre";
        case wb:
            return "wb_u_pre";
        case wu:
            return "wu_b_pre";
        case wbu:
            return "wbu_nopre";
        case hh:
            return "hh";
        case ww:
          return "ww";
        case zz:
          return "zz";
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
