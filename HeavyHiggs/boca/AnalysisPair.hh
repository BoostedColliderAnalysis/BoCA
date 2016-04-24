#pragma once

#include "boca/Analysis.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

/**
 * @brief Fusion pair analysis
 *
 */
namespace fusionpair
{

enum class Process
{
    bb, cc, jj, qq, gg, Hbb, ttbb, ttcc, ttjj, ttqq, ttgg
};

std::string Name(Process process);

enum class Production
{
    DYP, VBF, Associated
};

std::string Name(Production production_channel);

enum class Detector
{
    LHC, FHC, LE
};

std::string Name(Detector detector_type);

/**
 *
 * @brief Analysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
template <typename Tagger>
class Analysis : public boca::Analysis<Tagger>
{

public:

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::bb, Production::VBF);
            break;
        case Tag::background :
            this->NewFile(tag, Process::bb, Production::DYP);
            this->NewFile(tag, Process::cc, Production::DYP);
            this->NewFile(tag, Process::cc, Production::VBF);
            this->NewFile(tag, Process::jj, Production::DYP);
            this->NewFile(tag, Process::jj, Production::VBF);
            break;
        }
    }

    std::string AnalysisName() const override {
      return  Name(DetectorType()) + "-eta3.5";
      //         return  ProductionChannelName(ProductionChannel()) + DetectorName(DetectorType())  + "_" + Name(Mass());
    }

private:

    long TrainNumberMax() const override {
        return 1000000;
        return 100000;
        return 10000;
        return 1000;
        return 100;
    };

    Production ProductionChannel() const {
        //         return Production::DYP;
        return Production::VBF;
        //         return Production::Associated;
    }

    Detector DetectorType() const {
        //       return Detector::LHC;
        //       return Detector::FHC;
        return Detector::LE;
    }

    Id MotherId(Production production) const {
        switch (production) {
        case Production::DYP : return Id::Z;
        case Production::VBF : return Id::bottom;
        case Production::Associated : return Id::gluon;
        DEFAULT(to_int(production), Id::none);
        }
    }

    int BackgroundFileNumber() const override {
        return 1;
    }

    Crosssection SignalCrosssection() const {
        return pb;
    }

    boca::Mass Mass() const {
        return 400_GeV;
        return 600_GeV;
        return 1000_GeV;
        return 2000_GeV;
        return 3000_GeV;
        return 4000_GeV;
        return 5000_GeV;
        return 6000_GeV;
        return 7000_GeV;
        return 8000_GeV;
        return 9000_GeV;
        return 10000_GeV;
    }

    void NewFile(Tag tag, Process process, Production production) {
        AnalysisBase::NewFile(tag, NameString(process, production));
    }


    std::string NameString(Process process) const {
      return Name(ProductionChannel()) + Name(process) + "_" + Name(DetectorType());
    }

    std::string NameString(Process process, Production production) const {
      return Name(production) + Name(process) + "_" + Name(DetectorType());
    }

    File BackgroundFile(Process process, Production production) const {
        return BackgroundFile(process, BackgroundFileNumber(), production);
    }

    File BackgroundFile(Process process) const {
        return BackgroundFile(process, BackgroundFileNumber());
    }

    File BackgroundFile(Process process, int) const {
        std::vector<std::string> names;
        names.emplace_back(NameString(process));
        return File(names , BackgroundCrosssection(process));
    }

    File BackgroundFile(Process process, int, Production production) const {
        std::vector<std::string> names;
        names.emplace_back(NameString(process, production));
        return File(names , BackgroundCrosssection(process));
    }


    std:: string SignalName(Process process) {
      return  NameString(process) + "_" + Name(Mass());
    }

    std::string TreeName(Process process) const {
      return NameString(process) + "-run_01";
    }

    std::string TreeName(Process process, Production production) const {
      return NameString(process, production) + "-run_01";
    }

    std:: string SignalTreeName(Process process) {
      return  NameString(process) + "_" + Name(Mass()) + "-run_01";
    }

    Crosssection BackgroundCrosssection(Process) const {
        return pb;
    }

};

}

}
