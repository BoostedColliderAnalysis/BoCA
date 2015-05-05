# ifndef HAnalysisBottomSumTagger_hh
# define HAnalysisBottomSumTagger_hh

# include <sys/stat.h>
# include <string>

# include "HFileDelphes.hh"
# include "HAnalysis.hh"
# include "HEventDelphes.hh"
# include "HReader.hh"
# include "HFactory.hh"
# include "HJetTag.hh"

# include "HEventBottomTagger.hh"

namespace hbottomsumtagger
{

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class HAnalysis : public hanalysis::HAnalysis
{

public:

    /**
     * @brief Constructor
     *
     */
//     HAnalysis();

using hanalysis::HAnalysis::HAnalysis;

    hanalysis::HBottomTagger BottomTagger;
    HEventBottomTagger EventBottomSumTagger;

//     std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

//     void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::Tag Tag);

    void SetTrees();

    std::vector<hanalysis::HFile> Files(const hanalysis::HObject::Tag Tag);

    inline std::string ProjectName() const {
        return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector())  + "_" + std::to_string(Mass()) + "GeV";
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "hbottomsumtagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg, bbbb, bbjj, bbcc, bbqq, bbgg};
    enum HProductionChannel {DYP, VBF, Associated, Simple};
    enum HDetectorType {LHC, FHC, LE};

    inline int EventNumberMax() const {
//         return 1000000;
//         return 100000;
        return 10000;
//         return 1000;
//         return 100;
    };

    inline HProductionChannel ProductionChannel() const {
//         return DYP;
        return VBF;
//         return Associated;
//         return Simple;
    }

    inline HDetectorType Detector() const {
//       return LHC;
//       return FHC;
        return LE;
    }

    inline std::string DetectorName(const HDetectorType DetectorType) const {
        switch (DetectorType) {
        case LHC :
            return "14TeV";
        case FHC :
            return "100TeV";
        case LE :
            return "LE";
        default:
            Print(HError, "Detector Name", "unhandeld case");
            return "";
        }
    }


    inline std::string ProductionChannelName(const HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case Associated :
            return "llbb_";
        case DYP :
            return "pp_z_";
        case VBF :
            return "VBF_";
        case Simple :
            return "";
        default:
            Print(HError, "ProductionChannelName", "unhandeld case");
            return "";
        }
    }

    inline HParticleId MotherId(const HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case DYP :
            return ZId;
//             return GluonId;
        case VBF :
            return BottomId;
        case Associated :
            return GluonId;
        default:
            Print(HError, "MotherId", "unhandeld case");
            return EmptyId;
        }
    }

    std::string ProcessName(const ProcessType Process) const {
        switch (Process) {
        case bbbb :
            return "bbbb";
        case bbjj :
            return "bbjj";
        case bbcc :
            return "bbcc";
        case bbqq :
            return "bbqq";
        case bbgg :
            return "bbgg";
        case bb :
            return "bb";
        case cc:
            return "cc";
        case jj:
            return "jj";
        case qq:
            return "qq";
        case gg:
            return "gg";
        case Hbb:
            return "Hbb";
        case ttbb:
            return "ttbb";
        case ttcc:
            return "ttcc";
        case ttjj:
            return "ttjj";
        case ttqq:
            return "ttqq";
        case ttgg:
            return "ttgg";
        default:
            Print(HError, "ProcessName", "unhandeld case");
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

    inline int Mass() const {
            return 0;
        //     return 400;
        //     return 600;
//               return 1000;
        //         return 2000;
//       return 3000;
        //     return 4000;
//         return 5000;
        //     return 6000;
        //     return 7000;
        //     return 8000;
        //     return 9000;
        //         return 10000;
    }

    inline std::string NameString(const ProcessType Process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    inline hanalysis::HFile BackgroundFile(const ProcessType Process) const {
        return BackgroundFile(Process, BackgroundFileNumber());
    }

    hanalysis::HFile BackgroundFile(const ProcessType Process, const int) const {
        HStrings FileNames;
        FileNames.push_back(NameString(Process));
        return hanalysis::HFile(FileNames , BackgroundCrosssection(Process));
    }


    std:: string SignalName(const ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV";
    }

    std::string TreeName(const ProcessType Process) const {
        return NameString(Process) + "-run_01";
    }

    std:: string SignalTreeName(const ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV" + "-run_01";
    }

    float BackgroundCrosssection(const ProcessType) const {
        return 1;
    }

    hanalysis::HJetTag JetTag;
    hanalysis::HReader BottomReader;
    hanalysis::HReader EventBottomSumReader;

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    bool Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag);

//     bool GetBottomTag(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);
//     bool GetBottomReader(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag);
//
//     bool GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag);
//     bool GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag);

};
}
#endif

