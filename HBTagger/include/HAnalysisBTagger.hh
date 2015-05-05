# ifndef HAnalysisBTagger_hh
# define HAnalysisBTagger_hh

# include <sys/stat.h>
# include <string>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HBottomTaggerSimple.hh"

# include "HBranchBTagger.hh"

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class hbtagger::HAnalysis : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
//     HAnalysis();

using hanalysis::HAnalysis::HAnalysis;

    HBottomTaggerSimple BottomTagger;

//     std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

//     void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::Tag Tag);

    void SetTrees();

    std::vector<hanalysis::HFile> Files(const hanalysis::HObject::Tag Tag);

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

    enum ProcessType {bb, cc, jj, ttjj, ttbb, ttcc, Hbb, tt, qq, gg, ttlep, tthad, hh, ww};
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

    // in fb
    float SignalCrosssection() const {
        return 1;
    }


    inline std::string FileName(const ProcessType Process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector()) + "_" + std::to_string(PreCut()) + "GeV";
    }

    inline hanalysis::HFile BackgroundFile(const ProcessType Background) const {
        return BackgroundFile(Background, BackgroundFileNumber());
    }

    hanalysis::HFile BackgroundFile(const ProcessType Background, const int) const {
        HStrings FileNames;
        FileNames.push_back(FileName(Background));
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Background));
    }

    std::string TreeName(const ProcessType Process) const {
        return FileName(Process) + "-run_01";
    }

    float BackgroundCrosssection(const ProcessType) const {
        return 1;
    }

    std::string ProcessName(const ProcessType Process) const {
        switch (Process) {
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

    hanalysis::HJetTag JetTag;
    hanalysis::HReader BottomReader;

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    bool Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag);

//     bool GetBottomTag(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);
//     bool GetBottomReader(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);


};

#endif
