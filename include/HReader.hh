# ifndef HReader_hh
# define HReader_hh

# include <algorithm>
# include <iomanip>
# include <sstream>

# include "TFile.h"
# include "TClonesArray.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "TMVA/Reader.h"
# include "TMVA/MethodCuts.h"

# include "HMva.hh"

using std::cout;
using std::endl;
using std::sort;
using std::pair;
using std::size_t;
using std::left;
using std::setw;
using std::setfill;

typedef vector<int>::const_iterator VectorIterator;

struct PairOrder {
    bool operator()(
        pair<size_t, VectorIterator> const &First
        , pair<size_t, VectorIterator> const &Second
    ) {
        return *(First.second) > *(Second.second);
    }
};

/**
 * @brief Presents result of multivariant analysis
 *
 */
class HReader : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HReader(HMva *);

    /**
     * @brief Destructor
     *
     */
    ~HReader();

private:



    template <typename TCutFlow>
    vector<TCutFlow> CutFlowOrder(
        vector<TCutFlow> const &Input,
        vector<pair<size_t, VectorIterator> > const &Reference
    )
    {

        size_t const OrderSum = Reference.size();
        vector<TCutFlow> Output(OrderSum);

        for (size_t OrderSize = 0; OrderSize < OrderSum; ++OrderSize) {

            Output[OrderSize] = Input[Reference[OrderSize].first];

        }

        return Output;
    }


    template<typename TData>
    void PrintData(const TData Data, const int Width) const
    {
        const char Separator = ' ';
        std::cout << std::right << setw(Width) << setfill(Separator) << Data;
    }


    template<typename TText>
    void PrintText(const TText Text, const int Width) const
    {
        const char Separator = ' ';
        std::cout << left << setw(Width) << setfill(Separator) << Text;
    }


    template<typename TData>
    void PrintUnit(const TData Data, const int Width) const
    {
        std::stringstream ss;
        ss << " " << Data;

        const char Separator = ' ';
        std::cout << left << setw(Width) << setfill(Separator) << ss.str();
    }

    /**
     * @brief Apllication of cuts
     *
     * @return void
     */
    void ApplyCuts(const ExRootTreeReader * const, const string);

    void AddVariable();

    void BookMVA();

    void MVALoop();

    void GetCuts();

    void LatexHeader();

    void LatexFooter();

    void LatexContent(const string);

    float Luminosity(const float) const;

    float Scaling(const float, const int) const;

    float LuminosityError(const float) const;

    float RoundToDigits(const float, const int) const;

    float RoundToDigits(const float) const;

    float RoundToError(const float, const float) const;

    float RoundError(const float) const;

    float Error(const float) const;

//     int HiggsSum;

//     int TopSum;

    int EventSum;

//     int FatJetSum;

//     int TopEventSum;

//     int HiggsEventSum;

    float Crosssection;

    float CrosssectionError;

    float EventGenerated;

    float CrosssectionNorm;

    float CrosssectionNormRelError;

    float LuminosityScalingError;

    float CrosssectionScaled;

    string Verbose;

    string Silent;

    string VerboseLevel;

    string VerbosityLevel;

    string Color;

//     vector<int> EventVector;

//     vector<int> TopEventVector;

//     vector<int> HiggsEventVector;

//     vector<int> CutFlowVector;

//     vector<int> FatJetVector;

//     vector<int> HiggsVector;

//     vector<int> TopVector;

//     vector<double> CutsMin;

//     vector<double> CutsMax;

    HReaderStruct ReaderStruct;

    float Ratio(const float, const float) const;

    void TabularOutput() const;

    TMVA::Reader *Reader;

    vector<vector<double>> CutsMinMatrix;

    vector<vector<double>> CutsMaxMatrix;

    ofstream LatexFile;

    HMva * Mva;

    string ClassName() const {

        return ("HReader");

    };


};

# endif
