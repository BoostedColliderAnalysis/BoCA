# pragma once

# include "Analysis.hh"

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
class Analysis : public analysis::Analysis
{

public:

    using analysis::Analysis::Analysis;

//     analysis::BottomTagger bottom_tagger_;
//     analysis::JetPairTagger jet_pair_tagger;

//     std::string StudyName(const analysis::Analysis::HTagger Tagger) const;

//     void PrepareReader(const analysis::Analysis::HTagger Tagger, const analysis::Analysis::Tag Tag);

    void SetTrees();

    std::vector<analysis::File> Files(const analysis::Tag tag);

     std::string ProjectName() const {
        return  DetectorName(Detector()) + "-eta3.5";
//         return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector())  + "_" + std::to_string(Mass()) + "GeV";
    }

protected:

    virtual  std::string NameSpaceName() const {
        return "pairtagger";
    }

    virtual  std::string ClassName() const {
        return "Analysis";
    }

private:

    enum ProcessType {bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg};
    enum HProductionChannel {DYP, VBF, Associated};
    enum HDetectorType {LHC, FHC, LE};

     int EventNumberMax() const {
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
            Print(analysis::Severity::Error, "Detector Name", "unhandeld case");
            return "";
        }
    }


     std::string ProductionChannelName(const HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case Associated :
            return "llbb_";
        case DYP :
            return "pp_z_";
        case VBF :
            return "VBF_";
        default:
          Print(analysis::Severity::Error, "ProductionChannelName", "unhandeld case");
            return "";
        }
    }

     analysis::Id MotherId(const HProductionChannel NewProductionChannel) const {
        switch (NewProductionChannel) {
        case DYP :
          return analysis::Id::Z;
//             return Id::Gluon;
        case VBF :
          return analysis::Id::Bottom;
        case Associated :
          return analysis::Id::Gluon;
        default:
          Print(analysis::Severity::Error, "MotherId", "unhandeld case");
            return analysis::Id::Empty;
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
          Print(analysis::Severity::Error, "ProcessName", "unhandeld case");
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

     std::string NameString(const ProcessType Process) const {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

     std::string NameString(const ProcessType Process, const HProductionChannel ProductionChannel) const {
        return ProductionChannelName(ProductionChannel) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

     analysis::File BackgroundFile(const ProcessType Process, const HProductionChannel ProductionChannel) const {
        return BackgroundFile(Process, BackgroundFileNumber(), ProductionChannel);
    }

     analysis::File BackgroundFile(const ProcessType Process) const {
        return BackgroundFile(Process, BackgroundFileNumber());
    }

    analysis::File BackgroundFile(const ProcessType Process, const int) const {
      analysis::Strings FileNames;
        FileNames.emplace_back(NameString(Process));
        return analysis::File(FileNames , BackgroundCrosssection(Process));
    }

    analysis::File BackgroundFile(const ProcessType Process, const int, const HProductionChannel ProductionChannel) const {
      analysis::Strings FileNames;
        FileNames.emplace_back(NameString(Process, ProductionChannel));
        return analysis::File(FileNames , BackgroundCrosssection(Process));
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

    analysis::JetTag jet_tag;
    analysis::Reader BottomReader;
    analysis::Reader JetPairReader;

//     void NewBranches(exroot::TreeWriter &NewTreeWriter, const analysis::Analysis::HTagger Tagger);

//     int RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Tag tag);

//     bool GetBottomTag(analysis::Event &event, const analysis::Tag Tag);
//     bool GetBottomReader(analysis::Event &event, const analysis::Tag Tag);
//
//     bool GetJetPairTag(analysis::Event &event, const analysis::Tag Tag);
//     bool GetJetPairReader(analysis::Event &event, const analysis::Tag Tag);
//
//     bool GetTag(analysis::Event &event, const analysis::Tag tag);

};
}

