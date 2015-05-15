# pragma once

# include <sys/stat.h>
# include <string>

# include "File.hh"
# include "HAnalysis.hh"
// # include "HEventDelphes.hh"
# include "Reader.hh"
# include "Factory.hh"
# include "HJetTag.hh"

# include "HJetPairTagger.hh"

namespace hpairtagger
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

    using hanalysis::HAnalysis::HAnalysis;

//     hanalysis::BottomTagger bottom_tagger_;
//     hanalysis::HJetPairTagger JetPairTagger;

//     std::string StudyName(const hanalysis::HAnalysis::HTagger Tagger) const;

//     void PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::Tag Tag);

    void SetTrees();

    std::vector<hanalysis::File> Files(const hanalysis::HObject::Tag tag);

    inline std::string ProjectName() const {
        return  DetectorName(Detector()) + "-eta3.5";
//         return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector())  + "_" + std::to_string(Mass()) + "GeV";
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "hpairtagger";
    }

    virtual inline std::string ClassName() const {
        return "HAnalysis";
    }

private:

    enum ProcessType {bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg};
    enum HProductionChannel {DYP, VBF, Associated};
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
            Print(kError, "Detector Name", "unhandeld case");
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
        default:
            Print(kError, "ProductionChannelName", "unhandeld case");
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
            Print(kError, "MotherId", "unhandeld case");
            return EmptyId;
        }
    }

    std::string ProcessName(const ProcessType Process) const {
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
            Print(kError, "ProcessName", "unhandeld case");
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

    inline std::string NameString(const ProcessType Process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    inline std::string NameString(const ProcessType Process, const HProductionChannel ProductionChannel) const {
        return ProductionChannelName(ProductionChannel) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    inline hanalysis::File BackgroundFile(const ProcessType Process, const HProductionChannel ProductionChannel) const {
        return BackgroundFile(Process, BackgroundFileNumber(), ProductionChannel);
    }

    inline hanalysis::File BackgroundFile(const ProcessType Process) const {
        return BackgroundFile(Process, BackgroundFileNumber());
    }

    hanalysis::File BackgroundFile(const ProcessType Process, const int) const {
        Strings FileNames;
        FileNames.emplace_back(NameString(Process));
        return hanalysis::File(FileNames , BackgroundCrosssection(Process));
    }

    hanalysis::File BackgroundFile(const ProcessType Process, const int, const HProductionChannel ProductionChannel) const {
        Strings FileNames;
        FileNames.emplace_back(NameString(Process, ProductionChannel));
        return hanalysis::File(FileNames , BackgroundCrosssection(Process));
    }


    std:: string SignalName(const ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV";
    }

    std::string TreeName(const ProcessType Process) const {
        return NameString(Process) + "-run_01";
    }

    std::string TreeName(const ProcessType Process, HProductionChannel ProductionChannel) const {
        return NameString(Process, ProductionChannel) + "-run_01";
    }

    std:: string SignalTreeName(const ProcessType Process) {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV" + "-run_01";
    }

    float BackgroundCrosssection(const ProcessType) const {
        return 1;
    }

    hanalysis::HJetTag JetTag;
    hanalysis::Reader BottomReader;
    hanalysis::Reader JetPairReader;

//     void NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger);

    int Analysis(hanalysis::Event &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag);

//     bool GetBottomTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetBottomReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//
//     bool GetJetPairTag(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//     bool GetJetPairReader(hanalysis::Event &event, const hanalysis::HObject::Tag Tag);
//
//     bool GetTag(hanalysis::Event &event, const hanalysis::HObject::Tag tag);

};
}

