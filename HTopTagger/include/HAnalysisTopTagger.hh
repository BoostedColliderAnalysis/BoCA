# pragma once

# include "HTopHadronTagger.hh"
# include "HTopLeptonTagger.hh"
# include "HAnalysis.hh"


/**
 *
 * @brief HAnalysis subclass defining the Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
namespace htoptagger
{
class HAnalysis : public hanalysis::HAnalysis
{

public:


    HAnalysis(hanalysis::Tagger &tagger);

    void SetFiles(const hanalysis::HObject::Tag tag);

    inline std::string ProjectName() const {
        return  "TopTagger-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + ProcessName(tt) + "Test";
    }

    enum Decay {kLeptonic, kHadronic, kSemi};

    inline Decay TopDecay() const {
//         return kHadronic;
        return kLeptonic;
//         return kSemi;
    }

protected:



    virtual inline std::string FilePath() const {
        return "~/Projects/HTopTagger/";
    }

    virtual inline std::string NameSpaceName() const {
        return "htoptagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:
    enum Process {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg, wg, wq, wc, wb, wu, wcb, wbu, ttlep, tthad, hh, ww, zz};
    enum Collider {LHC, FHC, LE};


    void NewSignalFile(const Process process) {
        hanalysis::HAnalysis::NewSignalFile(FileName(process));
    }

    void NewBackgroundFile(const Process process) {
        hanalysis::HAnalysis::NewBackgroundFile(FileName(process));
    }


    inline std::string FileName(const Process process) const {
        return ProcessName(process) + "_" + std::to_string(PreCut()) + "GeV";
    }

    // in GeV
    inline int PreCut() const {
        return 700;
//         return 1000;
    }

    // in GeV
    inline int UpperCut() const {
        switch (PreCut()) {
        case 700 :
            return 1000;
        case 1000 :
            return 1500;
        }
    }

    inline int EventNumberMax() const {
        //         return 1000000;
        //         return 100000;
//         return 10000;
//         return 1000;
        return 100;
//         return 10;
    }

    inline Collider ColliderType() const {
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


    inline hanalysis::RootFile BackgroundFile(const Process process) const {
        return BackgroundFile(process, BackgroundFileNumber());
    }

    hanalysis::RootFile BackgroundFile(const Process process, const int file_sum) const {


        Strings FileNames;
        for (int FileNumber = 0; FileNumber < file_sum; ++FileNumber) {
            FileNames.emplace_back(FileName(process));
        }
        return hanalysis::RootFile(FileNames);
    }

    std::string BackgroundTree(const Process Process) const {
        return ProcessName(Process) + "_" + std::to_string(PreCut()) + "GeV" + "-run_01";
    }


    std::string ColliderName(const Collider collider) const {
        switch (collider) {
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

    std::string ProcessName(const Process process) const {
        switch (process) {
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
            case kHadronic :
//                 return "tt_hadronic_1TeV";
                return "tt_hadronic";
            case  kLeptonic :
//                 return "tt_leptonic_1TeV";
                return "tt_leptonic";
            case kSemi :
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
            Print(kError, "unhandled case");
            return "";
        }
    }

    int PassPreCut(hanalysis::HEvent &event);

    /**
     * @brief Main Analysis function
     *
     */
    int Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag);

};

}
