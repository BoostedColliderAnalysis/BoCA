# pragma once

# include "HBranchBTagger.hh"
# include "HAnalysis.hh"

/**
 *
 * @brief HAnalysis subclass defining the Bottom Tagger Analysis
 *
 * @author Jan Hajer
 *
 */
class hbtagger::HAnalysis : public hanalysis::HAnalysis
{

public:

    using hanalysis::HAnalysis::HAnalysis;

    void SetFiles(const hanalysis::HObject::Tag Tag);

    inline std::string ProjectName() const {
        return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector()) + "_" + std::to_string(PreCut()) + "GeV";
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "hbtagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum Process {bb, cc, jj, ttjj, ttbb, ttcc, Hbb, tt, qq, gg, ttlep, tthad, hh, ww};
    enum HProductionChannel {DYP, VBF, Associated};
    enum HDetectorType {LHC, FHC, LE};


    inline int EventNumberMax() const {
        //         return 1000000;
//         return 100000;
        return 10000;
//         return 1000;
//         return 100;
    };

    inline HDetectorType Detector() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }

    inline HProductionChannel ProductionChannel() const {
        return DYP;
        //         return VBF;
//         return Associated;
    }

    inline int PreCut() const {
//         return 1000;
        return 500;
    }

    inline std::string DetectorName(const HDetectorType DetectorType) const {
        switch (DetectorType) {
        case LHC :
            return "14TeV";
        case VBF :
            return "100TeV";
        case LE :
            return "LE";
        default:
            return "";
        }
    }


    inline std::string ProductionChannelName(const HProductionChannel PC) const {
        switch (PC) {
        case Associated :
            return "llbb_";
        case DYP :
            return "pp_z_";
        case VBF :
            return "VBF_";
        default:
            return "";
        }
    }

    inline int BackgroundFileNumber() const {
        return 1;
    }


    inline std::string FileName(const Process process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(process) + "_" + DetectorName(Detector()) + "_" + std::to_string(PreCut()) + "GeV";
    }

    std::string TreeName(const Process process) const {
        return FileName(process) + "-run_01";
    }

    void NewSignalFile(const Process process) {
      hanalysis::HAnalysis::NewSignalFile(ProcessName(process));
    }

    void NewBackgroundFile(const Process process) {
      hanalysis::HAnalysis::NewBackgroundFile(ProcessName(process));
    }


    std::string ProcessName(const Process process) const {
        switch (process) {
        case cc:
            return "cc";
        case jj:
            return "jj";
        case bb:
            return "bb";
        case Hbb:
            return "Hbb";
        case ttbb:
            return "ttbb";
        case ttcc:
            return "ttcc";
        case ttjj:
            return "ttjj";
        case tt:
            return "tt";
        case ttlep:
            return "tt_leptonic";
        case tthad:
            return "tt_hadronic";
        case hh:
            return "hh";
        case ww:
            return "ww";
        case qq:
            return "qq";
        case gg:
            return "gg";
        default :
            return "";
        }
    }

    bool Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag);

};
