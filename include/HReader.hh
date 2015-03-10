# ifndef HReader_hh
# define HReader_hh

# include "TDirectoryFile.h"
# include "TTree.h"
# include "TCanvas.h"
# include "TGraph.h"
# include "TMultiGraph.h"
# include "TLine.h"

# include "TMVA/Reader.h"
# include "TMVA/MethodCuts.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HMva.hh"


class HMvaResult : hanalysis::HObject
{

public:

    HMvaResult()  {
        Steps = 2000;
        Events.resize(Steps, 0);
        Efficiency.resize(Steps, 0);
        AnalysisEventNumber.resize(Steps, 0);
        Bdt.resize(Steps, 0);
    }

    int Steps;
    std::vector<float> Events;
    std::vector<float> Efficiency;
    std::vector<int> AnalysisEventNumber;
    std::vector<float> Bdt;
    int TotalEventNumber;

    std::vector<int> CutIntegral(const std::vector<int> &Vector) const {
        std::vector<int> Integrals(Steps, 0);
        Integrals.at(Steps - 1) = Vector.at(Steps - 1);
        for (int BinNumber = Steps - 2; BinNumber >= 0; --BinNumber) Integrals.at(BinNumber) = Integrals.at(BinNumber + 1) + Vector.at(BinNumber);
        return Integrals;
    }

};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class hanalysis::HReader : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HReader();

    /**
     * @brief Constructor
     *
     */
    HReader(hanalysis::HMva &NewMva);

    void operator=(const hanalysis::HReader &) {
        Print(HError, "invalid assigmnent operator!!", "Dont end up here!!!", "Actually it still seems to work");
    }

    void SetMva(hanalysis::HMva &NewMva);

    void SimpleMVALoop();

    float Bdt() const {
        Print(HInformation, "Get Bdt");
        const float NewBdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(Mva->GetBdtMethodName());
        return (NewBdt + 1.);
    }

private:

    HMva *Mva;

    TMVA::Reader Reader;

    HMva *Tagger() const {
        return Mva;
    }

    void BookMva();

    void AddVariable();

    HInfoBranch InfoBranch(const TFile &File, const std::string &TreeName) const;

    std::vector<int> BdtDistribution(const ExRootTreeReader &TreeReader, const std::string &TreeName, const TFile &ExportFile) const;

    HMvaResult BdtResult(const TFile &File, const std::string &TreeName, const TFile &ExportFile) const;

    void LatexHeader(ofstream &LatexFile) const;

    void LatexFooter(std::ofstream &LatexFile) const;

    inline std::string ClassName() const {
        return "HReader";
    }

};

# endif
