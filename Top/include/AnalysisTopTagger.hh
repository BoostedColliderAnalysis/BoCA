# pragma once

# include "Analysis.hh"

namespace analysis
{

namespace top
{

/**
 *
 * @brief HAnalysis subclass defining the Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:


    Analysis(Tagger &tagger);

    void SetFiles(const Object::Tag tag);

    inline std::string ProjectName() const {
        return  "TopTagger-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + ProcessName(tt);
    }

    enum Decay {kLeptonic, kHadronic, kSemi};

    inline Decay TopDecay() const {
        return kHadronic;
//         return kLeptonic;
//         return kSemi;
    }

protected:

    virtual inline std::string FilePath() const {
        return "~/Projects/Tagger/Top/";
    }

    virtual inline std::string NameSpaceName() const {
        return "top";
    }

private:
    enum Process {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg, wg, wq, wc, wb, wu, wcb, wbu, ttlep, tthad, hh, ww, zz};
    enum Collider {LHC, FHC, LE};


    void NewSignalFile(const Process process) {
        analysis::Analysis::NewSignalFile(FileName(process));
    }

    void NewBackgroundFile(const Process process) {
        analysis::Analysis::NewBackgroundFile(FileName(process));
    }


    inline std::string FileName(const Process process) const {
        return ProcessName(process) + "_" + std::to_string(PreCut()) + "GeV";
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

    inline Collider collider_type() const {
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


    inline File BackgroundFile(const Process process) const {
        return BackgroundFile(process, BackgroundFileNumber());
    }

    File BackgroundFile(const Process process, const int file_sum) const {
        Strings FileNames;
        for (int file_number = 0; file_number < file_sum; ++file_number) {
            FileNames.emplace_back(FileName(process));
        }
        return File(FileNames);
    }

    std::string BackgroundTree(const Process Process) const {
        return ProcessName(Process) + "_" + std::to_string(PreCut()) + "GeV" + "-run_01";
    }


    std::string ColliderName(const Collider collider) const;

    std::string ProcessName(const Process process) const;

    int PassPreCut(Event &event);

    /**
     * @brief Main Analysis function
     *
     */
    int RunAnalysis(Event &event, const Tagger::Stage stage, const Tag tag);

};

}

}
