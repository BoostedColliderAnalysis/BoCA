# pragma once

# include "HAnalysis.hh"


/**
 *
 * @brief HAnalysis subclass defining the W Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
namespace hwtagger
{
class HAnalysis : public analysis::HAnalysis
{

public:


    HAnalysis(analysis::Tagger &tagger);

    void SetFiles(const analysis::Object::Tag tag);

    inline std::string ProjectName() const {
        return  "WTagger-" + ColliderName(ColliderType()) + "-" + std::to_string(PreCut()) + "GeV-" + ProcessName(tt);
    }

    enum Decay {kLeptonic, kHadronic, kSemi};

    inline Decay WDecay() const {
        return kHadronic;
//         return kLeptonic;
//         return kSemi;
    }

protected:



    virtual inline std::string FilePath() const {
        return "~/Projects/Tagger/W/";
    }

    virtual inline std::string NameSpaceName() const {
        return "wtagger";
    }

    virtual inline std::string ClassName() const {
        return "Analysis";
    }

private:
    enum Process {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg, wg, wq, wc, wb, wu, wcb, wbu, ttlep, tthad, hh, ww, zz};
    enum Collider {LHC, FHC, LE};


    void NewSignalFile(const Process process) {
        analysis::HAnalysis::NewSignalFile(FileName(process));
    }

    void NewBackgroundFile(const Process process) {
        analysis::HAnalysis::NewBackgroundFile(FileName(process));
    }


    inline std::string FileName(const Process process) const {
        return ProcessName(process) + "_" + std::to_string(PreCut()) + "GeV";
//         return ProcessName(process);
    }

    // in GeV
    inline int PreCut() const {
        return 700;
//         return 1000;
    }

    // in GeV
    inline int UpperCut() const {
        switch (PreCut()) {
        case 700 :
            return 1000;
        case 1000 :
            return 1500;
        }
    }

    inline int EventNumberMax() const {
        //         return 1000000;
        //         return 100000;
//         return 10000;
        return 1000;
//         return 100;
//         return 10;
    }

    inline Collider ColliderType() const {
        //       return LHC;
        //       return FHC;
        return LE;
    }

    inline int BackgroundFileNumber() const {
        return 1;
        //         return 2;
        //       return 4;
        //       return 5;
        //       return 10;
    }


    inline analysis::File BackgroundFile(const Process process) const {
        return BackgroundFile(process, BackgroundFileNumber());
    }

    analysis::File BackgroundFile(const Process process, const int file_sum) const {
        Strings FileNames;
        for (int file_number = 0; file_number < file_sum; ++file_number) {
            FileNames.emplace_back(FileName(process));
        }
        return analysis::File(FileNames);
    }

    std::string BackgroundTree(const Process Process) const {
        return ProcessName(Process) + "_" + std::to_string(PreCut()) + "GeV" + "-run_01";
    }


    std::string ColliderName(const Collider collider) const;

    std::string ProcessName(const Process process) const;

    int PassPreCut(analysis::Event &event);

    /**
     * @brief Main Analysis function
     *
     */
    int Analysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag);

};

}
