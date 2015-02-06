# ifndef HReader_hh
# define HReader_hh

# include <algorithm>
# include <iomanip>
# include <sstream>

# include "TFile.h"
# include "TDirectoryFile.h"
# include "TClonesArray.h"
# include "TObjArray.h"
# include "TTree.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "TMVA/Reader.h"
# include "TMVA/MethodCuts.h"

# include "HMva.hh"



class ResultStruct
{

public:
    ResultStruct() {
        Steps = 20;
        Events.resize(Steps, 0);
        Efficiency.resize(Steps, 0);
    }

    int Steps;
    std::vector<float> Events;
    std::vector<float> Efficiency;

};

typedef std::vector<int>::const_iterator VectorIterator;

struct PairOrder {
    bool operator()(
        std::pair<size_t, VectorIterator> const &First
        , std::pair<size_t, VectorIterator> const &Second
    ) {
        return *(First.second) > *(Second.second);
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
//     HReader(HMva *NewMva);

    /**
     * @brief Constructor
     *
     */
    HReader(hanalysis::HMva &NewMva);


    /**
     * @brief Destructor
     *
     */
    ~HReader();

    void operator=(const hanalysis::HReader &) {
        Print(HError, "invalid Reader copy!!","Dont end up here!!!");
    }

    void SetMva(hanalysis::HMva &NewMva);

//     template<typename TBranch, typename TParticle>
//     float GetBdt(TBranch * const Branch, const TParticle &Particle) const
    float Bdt() const {
        Print(HInformation, "Get Bdt");

//         Mva->FillBranch(&Branch, Particle);
        const float NewBdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(Mva->GetBdtMethodName());
        return (NewBdt + 1.);

    }

    float GetBdt2() const {

        Print(HInformation, "Get Bdt 2");
        const float NewBdt = const_cast<TMVA::Reader *>(&Reader)->EvaluateMVA(Mva->GetBdtMethodName());
        return NewBdt;

    }

    void SimpleMVALoop();

    void MVALoop();

    void AddVariable();

    void BookMva();

    TMVA::Reader Reader; // FIXME what is wrong here?



    HMva *Mva;


private:


    template <typename TCutFlow>
    std::vector<TCutFlow> SortByPriority(
        std::vector<TCutFlow> const &Input,
        std::vector<std::pair<size_t, VectorIterator> > const &Priority
    ) {

        size_t const OrderSum = Priority.size();
        std::vector<TCutFlow> Output(OrderSum);

        for (size_t OrderSize = 0; OrderSize < OrderSum; ++OrderSize) {

            Output[OrderSize] = Input[Priority[OrderSize].first];

        }

        return Output;
    }


    template<typename TData>
    void PrintData(const TData Data, const int Width) const {
        const char Separator = ' ';
        std::cout << std::right << std::setw(Width) << std::setfill(Separator) << Data;
    }


    template<typename TText>
    void PrintText(const TText Text, const int Width) const {
        const char Separator = ' ';
        std::cout << std::left << std::setw(Width) << std::setfill(Separator) << Text;
    }


    template<typename TData>
    void PrintUnit(const TData Data, const int Width) const {
        std::stringstream ss;
        ss << " " << Data;

        const char Separator = ' ';
        std::cout << std::left << std::setw(Width) << std::setfill(Separator) << ss.str();
    }

    /**
     * @brief Apllication of cuts
     *
     * @return void
     */
    void ApplyCuts(const ExRootTreeReader *const, const std::string);

    void GetCuts();

    void LatexHeader();

    void LatexFooter();

    void LatexContent(const std::string &TreeName);

    float GetLuminosity(const float) const;

    float GetScaling(const float, const int) const;

    float GetLuminosityError(const float) const;

    float RoundToDigits(const float, const int) const;

    float RoundToDigits(const float) const;

    float RoundToError(const float, const float) const;

    float RoundError(const float) const;

    float GetError(const float) const;

    int EventSum;

    float Crosssection;

    float CrosssectionError;

    float EventGenerated;

    float CrosssectionNorm;

    float CrosssectionNormRelError;

    float LuminosityScalingError;

    float CrosssectionScaled;

    std::string Verbose;

    std::string Silent;

    std::string VerboseLevel;

    std::string VerbosityLevel;

    std::string Color;

    HReaderStruct ReaderStruct;

    float GetRatio(const float, const float) const;

    void TabularOutput() const;

    std::vector<std::vector<double>> CutsMinMatrix;

    std::vector<std::vector<double>> CutsMaxMatrix;

    std::ofstream LatexFile;

    inline std::string ClassName() const {
        return "HReader";
    };

    float GetMass(const TFile *File, const std::string &TreeName);
    ResultStruct ApplyBdt(const TFile *File, const std::string &TreeName, const TFile *ExportFile);

//     std::vector<int> ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, const TMVA::Reader &Reader);

};

# endif
