# pragma once

# include "HBranchBTagger.hh"
# include "Analysis.hh"

/**
 * @brief Namespace for bottom analysis
 *
 */
namespace bottom {

/**
 *
 * @brief HAnalysis subclass defining the Bottom Tagger Analysis
 *
 * @author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:

    Analysis(analysis::Tagger &tagger);

    inline std::string ProjectName() const {
        return  ProductionChannelName(production_channel()) + DetectorName(detector()) + "_" + std::to_string(LowerCut()) + "GeV";
    }

protected:

    virtual inline std::string NameSpaceName() const {
        return "bottom";
    }

private:

    enum Process {bb, cc, jj, ttjj, ttbb, ttcc, Hbb, tt, qq, gg, ttlep, tthad, hh, ww};
    enum ProductionChannel {DYP, VBF, Associated};
    enum Detector {LHC, FHC, LE};


    inline int EventNumberMax() const {
        //         return 1000000;
//         return 100000;
//         return 10000;
        return 1000;
//         return 100;
    };

    inline Detector detector() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }

    inline ProductionChannel production_channel() const {
        return DYP;
        //         return VBF;
//         return Associated;
    }

    inline int LowerCut() const {
//         return 1000;
        return 500;
    }

    int UpperCut() const;

    std::string DetectorName(const Detector detector) const;

    inline int BackgroundFileNumber() const {
        return 1;
    }

    inline std::string FileName(const Process process) const {
      return ProductionChannelName(production_channel()) + ProcessName(process) + "_" + DetectorName(detector()) + "_" + std::to_string(LowerCut()) + "GeV";
    }

    std::string TreeName(const Process process) const {
        return FileName(process) + "-run_01";
    }

    void NewSignalFile(const Process process) {
      analysis::Analysis::NewSignalFile(FileName(process));
    }

    void NewBackgroundFile(const Process process) {
      analysis::Analysis::NewBackgroundFile(FileName(process));
    }

    virtual inline std::string FilePath() const {
      return "~/Projects/Tagger/Bottom/";
    }

    std::string ProductionChannelName(const ProductionChannel production_channel) const;

    std::string ProcessName(const Process process) const;

    void SetFiles(const analysis::Object::Tag Tag);

    int PassPreCut(analysis::Event &event);

};

}
