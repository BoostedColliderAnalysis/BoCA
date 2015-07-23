#pragma once

#include <sys/stat.h>
#include <string>

#include "File.hh"
#include "Analysis.hh"
// #include "HEventDelphes.hh"
#include "Reader.hh"
#include "Factory.hh"
#include "JetTag.hh"

#include "HEventBottomTagger.hh"

namespace hbottomsumtagger {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class HAnalysis { //: public analysis::Analysis

public:

    /**
     * @brief Constructor
     *
     */
//     HAnalysis();



// using analysis::Analysis::Analysis;

    analysis::BottomTagger bottom_tagger_;

//     EventBottomTagger eventBottomSumTagger;

//     std::string StudyName(const analysis::HAnalysis::HTagger Tagger) const;

//     void PrepareReader(const analysis::HAnalysis::HTagger Tagger, const analysis::HAnalysis::Tag Tag);

    void SetTrees();

    std::vector<analysis::File> Files(const analysis::Tag tag);

    std::string ProjectName() const
    {
        return  ProductionChannelName(ProductionChannel()) + DetectorName(Detector())  + "_" + std::to_string(Mass()) + "GeV";
    }

private:
    void SetFiles(const analysis::Tag ) {};

    enum ProcessType {bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg, bbbb, bbjj, bbcc, bbqq, bbgg};
    enum HProductionChannel {DYP, VBF, Associated, Simple};
    enum HDetectorType {LHC, FHC, LE};

    long EventNumberMax() const
    {
//         return 1000000;
//         return 100000;
        return 10000;
//         return 1000;
//         return 100;
    };

    HProductionChannel ProductionChannel() const
    {
//         return DYP;
        return VBF;
//         return Associated;
//         return Simple;
    }

    HDetectorType Detector() const
    {
//       return LHC;
//       return FHC;
        return LE;
    }

    std::string DetectorName(const HDetectorType DetectorType) const
    {
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


    std::string ProductionChannelName(const HProductionChannel NewProductionChannel) const
    {
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
            Error("ProductionChannelName", "unhandeld case");
            return "";
        }
    }

    analysis::Id MotherId(const HProductionChannel NewProductionChannel) const
    {
        switch (NewProductionChannel) {
        case DYP :
            return analysis::Id::Z;
        case VBF :
            return analysis::Id::bottom;
        case Associated :
            return analysis::Id::gluon;
        default:
            Error("MotherId", "unhandeld case");
            return analysis::Id::empty;
        }
    }

    std::string ProcessName(const ProcessType Process) const
    {
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
            Error("ProcessName", "unhandeld case");
            return "";
        }
    }

    int BackgroundFileNumber() const
    {
        return 1;
    }

    // in fb
    float SignalCrosssection() const
    {
        return 1;
    }

    int Mass() const
    {
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

    std::string NameString(const ProcessType Process) const
    {
        return ProductionChannelName(ProductionChannel()) + ProcessName(Process) + "_" + DetectorName(Detector());
    }

    analysis::File BackgroundFile(const ProcessType Process) const
    {
        return BackgroundFile(Process, BackgroundFileNumber());
    }

    analysis::File BackgroundFile(const ProcessType Process, const int) const
    {
        analysis::Strings FileNames;
        FileNames.emplace_back(NameString(Process));
        return analysis::File(FileNames , BackgroundCrosssection(Process));
    }


    std:: string SignalName(const ProcessType Process)
    {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV";
    }

    std::string TreeName(const ProcessType Process) const
    {
        return NameString(Process) + "-run_01";
    }

    std:: string SignalTreeName(const ProcessType Process)
    {
        return  NameString(Process) + "_" + std::to_string(Mass()) + "GeV" + "-run_01";
    }

    float BackgroundCrosssection(const ProcessType) const
    {
        return 1;
    }

    analysis::JetTag jet_tag;
//     analysis::Reader BottomReader;
//     analysis::Reader eventBottomSumReader;

//     void NewBranches(exroot::TreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger);

//     int RunAnalysis(analysis::Event &event, const analysis::Stage stage,  Tag tag);

//     bool GetBottomTag(analysis::Event &event, Tag tag);
//     bool GetBottomReader(analysis::Event &event, Tag tag);
//
//     bool GeteventSemiTag(analysis::Event &event, const Tag Tag);
//     bool GeteventSemiReader(analysis::Event &event, const Tag Tag);

};
}
