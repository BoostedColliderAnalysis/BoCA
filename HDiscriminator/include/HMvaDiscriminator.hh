#pragma once


#include "Tagger.hh"
#include "TFile.h"
#include "HBranchDiscriminator.hh"

class ExRootTreeReader;
namespace exroot {
typedef ::ExRootTreeReader TreeReader;
}


namespace hcpvhiggs {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class HMva : public analysis::Tagger {

public:

    /**
    * @brief Constructor
    *
    */
    HMva();

    /**
    * @brief Destructor
    *
    */
    ~HMva();

//     ReaderStruct CutLoop(const exroot::TreeReader * const, ReaderStruct&);

    void ApplyBdt(const exroot::TreeReader* const TreeReader, const std::string& TreeName, const TFile* const ExportFile, const TMVA::Reader& Reader);

//     float GetBdt(TObject*, const TMVA::Reader&)
//     {
//         return 0;
//     };

protected:


private:

    HCandidateBranch* Candidate;

    virtual TClass& Class() const
    {
        return *HCandidateBranch::Class();
    }

    void DefineVariables();

};

}
