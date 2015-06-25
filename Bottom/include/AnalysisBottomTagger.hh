# pragma once

# include "Analysis.hh"

namespace analysis {

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

    Analysis(Tagger &tagger);

     std::string ProjectName() const {
        return  ProductionChannelName(production_channel()) + DetectorName(detector()) + "_" + std::to_string(MadGraphCut()) + "GeV";
    }

protected:

    virtual  std::string NameSpaceName() const {
        return "bottom";
    }

private:

    enum Process {bb, cc, jj, ttjj, ttbb, ttcc, Hbb, tt, qq, gg, ttlep, tthad, hh, ww,zz};
    enum ProductionChannel {DYP, VBF, Associated};
    enum Detector {LHC, FHC, LE};


     int EventNumberMax() const {
        //         return 1000000;
//         return 100000;
//         return 10000;
        return 1000;
//         return 100;
    };

     Detector detector() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }

     ProductionChannel production_channel() const {
        return DYP;
        //         return VBF;
//         return Associated;
    }

<<<<<<< HEAD
    inline int LowerCut() const {
 //       return 1000;
        return 500;
=======
    // in GeV
    int LowerPtCut() const {
      //         return 350;
      //         return 700;
      //         return 800;
      return 1000;
>>>>>>> b97c434c9b33058b317927e1bde57465c8f846bd
    }

    // in GeV
    int UpperPtCut() const {
      switch (LowerPtCut()) {
        case 700 :
          return 1000;
        case 1000 :
          return 1500;
      }
    }

    // in GeV
    int MadGraphCut() const {
      switch (LowerPtCut()) {
        case 700 :
          return 700;
        case 1000 :
          return 1000;
      }
    }

    std::string DetectorName(const Detector detector) const;

     int BackgroundFileNumber() const {
        return 1;
    }

//      std::string FileName(const Process process) const {
//       return ProductionChannelName(production_channel()) + ProcessName(process) + "_" + DetectorName(detector()) + "_" + std::to_string(LowerCut()) + "GeV";
//     }


    std::string FileName(const Process process) const {
      return ProcessName(process) + "_" + std::to_string(MadGraphCut()) + "GeV";
    }

    std::string TreeName(const Process process) const {
        return FileName(process) + "-run_01";
    }

    void NewSignalFile(const Process process) {
      analysis::Analysis::NewSignalFile(FileName(process), NiceName(process));
    }

    void NewBackgroundFile(const Process process) {
      analysis::Analysis::NewBackgroundFile(FileName(process), NiceName(process));
    }

    virtual  std::string FilePath() const {
      return "~/Projects/Tagger/";
    }

    std::string ProductionChannelName(const ProductionChannel production_channel) const;

    std::string ProcessName(const Process process) const;

    void SetFiles(const Object::Tag Tag);

    int PassPreCut(Event &event);

    std::string NiceName(const Process process) const;

};

}

}
