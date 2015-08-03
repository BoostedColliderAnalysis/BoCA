#pragma once

#include "Analysis.hh"

namespace analysis
{

/**
 * @brief Namespace for the fusion pair analysis
 *
 */
namespace fusionpair
{

/**
 *
 * @brief Analysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template <typename Tagger>
class Analysis : public analysis::Analysis<Tagger>
{

public:

    enum ProcessType {bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg};
    enum HProductionChannel {DYP, VBF, Associated};
    enum HDetectorType {LHC, FHC, LE};

    Analysis() {
        this->tagger().SetAnalysisName(ProjectName());
    }

    void SetFiles(const Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, bb, VBF);
            break;
        case Tag::background :
            this->NewFile(tag, bb, DYP);
            this->NewFile(tag, cc, DYP);
            this->NewFile(tag, cc, VBF);
            this->NewFile(tag, jj, DYP);
            this->NewFile(tag, jj, VBF);
            break;
        }
    }

    std::string ProjectName() const {
        return  DetectorName(Detector()) + "-eta3.5";
//         return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector())  + "_" + std::to_string(Mass()) + "GeV";
    }

private:

    long EventNumberMax() const {
//         return 1000000;
//         return 100000;
        return 10000;
//         return 1000;
//         return 100;
    };

    HProductionChannel ProductionChannel() const {
//         return DYP;
        return VBF;
//         return Associated;
    }

    HDetectorType Detector() const {
//       return LHC;
//       return FHC;
        return LE;
    }

    std::string DetectorName(const HDetectorType DetectorType) const {
        switch (DetectorType) {
        case LHC :
            return "14TeV";
        case FHC :
            return "100TeV";
        case LE :
            return "LE";
        default:
            Error("Detector Name", "unhandeld case");
            return "";
        }
    }


    std::string ProductionChannelName(HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case Associated :
            return "llbb_";
        case DYP :
            return "pp_z_";
        case VBF :
            return "VBF_";
        default:
            Error("ProductionChannelName", "unhandeld case");
            return "";
        }
    }

    Id MotherId(HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case DYP :
            return Id::Z;
//             return Id::gluon;
        case VBF :
            return Id::bottom;
        case Associated :
            return Id::gluon;
        default:
            Error("MotherId", "unhandeld case");
            return Id::empty;
        }
    }

    int PassPreCut(const Event&, Tag) const {
        return 1;
    };

    std::string ProcessName() const {
        return "Fusion Pair";
    }

    std::string ProcessName(ProcessType Process) const {
        switch (Process) {
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
            Error("ProcessName", "unhandeld case");
            return "";
        }
    }

    int BackgroundFileNumber() const {
        return 1;
    }

    // in fb
    float SignalCrosssection() const {
        return 1;
    }

    int Mass() const {
        //     return 400;
        //     return 600;
//               return 1000;
        //         return 2000;
//       return 3000;
        //     return 4000;
        return 5000;
        //     return 6000;
        //     return 7000;
        //     return 8000;
        //     return 9000;
        //         return 10000;
    }

    std::string FilePath() const final {
        return "~/Projects/FusionPair/Analysis/";
    }

    void NewFile(Tag tag, ProcessType process, HProductionChannel production) {
        AnalysisBase::NewFile(tag, NameString(process, production));
    }


    std::string NameString(ProcessType Process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    std::string NameString(ProcessType Process, HProductionChannel ProductionChannel) const {
        return ProductionChannelName(ProductionChannel) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    File BackgroundFile(ProcessType Process, HProductionChannel ProductionChannel) const {
        return BackgroundFile(Process, BackgroundFileNumber(), ProductionChannel);
    }

    File BackgroundFile(ProcessType Process) const {
        return BackgroundFile(Process, BackgroundFileNumber());
    }

    File BackgroundFile(ProcessType Process, const int) const {
        Strings FileNames;
        FileNames.emplace_back(NameString(Process));
        return File(FileNames , BackgroundCrosssection(Process));
    }

    File BackgroundFile(ProcessType Process, const int, HProductionChannel ProductionChannel) const {
        Strings FileNames;
        FileNames.emplace_back(NameString(Process, ProductionChannel));
        return File(FileNames , BackgroundCrosssection(Process));
    }


    std:: string SignalName(ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV";
    }

    std::string TreeName(ProcessType Process) const {
        return NameString(Process) + "-run_01";
    }

    std::string TreeName(ProcessType Process, HProductionChannel ProductionChannel) const {
        return NameString(Process, ProductionChannel) + "-run_01";
    }

    std:: string SignalTreeName(ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV" + "-run_01";
    }

    float BackgroundCrosssection(ProcessType) const {
        return 1;
    }

};

}

}
