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



template <typename TypeName>
vector<TypeName> CutFlowOrder(
    vector<TypeName> const &Input,
    vector<pair<size_t, VectorIterator> > const &Reference
)
{

    size_t const OrderSum = Reference.size();
    vector<TypeName> Output(OrderSum);

    for (size_t OrderSize = 0; OrderSize < OrderSum; ++OrderSize) {

        Output[OrderSize] = Input[Reference[OrderSize].first];

    }

    return Output;
}


template<typename Template> void PrintData(Template PrintDataTemplate, const int &Width)
{
    const char Separator = ' ';
    cout << std::right << setw(Width) << setfill(Separator) << PrintDataTemplate;
}


template<typename Template> void PrintText(Template PrintDataTemplate, const int &Width)
{
    const char Separator = ' ';
    cout << left << setw(Width) << setfill(Separator) << PrintDataTemplate;
}


template<typename Template> void PrintUnit(Template PrintDataTemplate, const int &Width)
{
    std::stringstream ss;
    ss << " " << PrintDataTemplate;

    const char Separator = ' ';
    cout << left << setw(Width) << setfill(Separator) << ss.str();
}



/**
 * @brief Prepares multivariant analysis
 *
 */
class HReader : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HReader(HMva*);

    /**
     * @brief Destructor
     *
     */
    ~HReader();

private:

    /**
     * @brief Apllication of cuts
     *
     * @return void
     */
    void ApplyCuts(ExRootTreeReader *, TString);

    void AddVariable();

    void BookMVA();

    void MVALoop();

    void GetCuts();

    void CutLoop(ExRootTreeReader *);

    void ApplyBdt(ExRootTreeReader *, TString, TFile *);

    void LatexHeader();

    void LatexFooter();

    void LatexContent(TString);

    float Luminosity(float);

    float Scaling(float, int);

    float LuminosityError(float);

    float RoundToDigits(float, int);

    float RoundToDigits(float);
    
    float RoundToError(float, float);
    
    float RoundError(float);

    float Error(float);

    int HiggsSum;

    int TopSum;

    int EventSum;

    int FatJetSum;


    int TopEventSum;
    int HiggsEventSum;

    float Crosssection;

    float CrosssectionError;
    
    float EventGenerated;

    float CrosssectionNorm;

    float CrosssectionNormRelError;

    float LuminosityScalingError;

    float CrosssectionScaled;

    TString Verbose;

    TString Silent;

    TString VerboseLevel;

    TString VerbosityLevel;

    TString Color;

    vector<int> EventVector;

    vector<int> TopEventVector;

    vector<int> HiggsEventVector;

    vector<int> CutFlowVector;

    vector<int> FatJetVector;

    vector<int> HiggsVector;

    vector<int> TopVector;

    vector<double> CutsMin;

    vector<double> CutsMax;

    float Ratio(float, float);
    void TabularOutput();

    TMVA::Reader *Reader;

    vector<vector<double>> CutsMinMatrix;

    vector<vector<double>> CutsMaxMatrix;

    ofstream LatexFile;

    HMva *Mva;
        
    virtual TString ClassName() {
        return ("HReader");
    };


};

# endif
