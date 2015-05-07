# ifndef HFileDelphes_hh
# define HFileDelphes_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "ClonesArrays.hh"
# include "RootFile.hh"

/**
 * @brief Delphes files
 *
 */
class hanalysis::hdelphes::HFile : public hanalysis::RootFile
{

public:

    /**
     * @brief constructor defining default path
     *
     */
    HFile();

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const std::string &Process);

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const std::string &Process, const std::string &Run);

    /**
     * @brief Compose file path
     *
     */
    Strings Paths() const;

//     std::shared_ptr<hanalysis::HEvent> Event();

//     std::shared_ptr<hanalysis::HClonesArray> ClonesArrays();

protected:

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    virtual inline std::string ClassName() const {
        return "HFile";
    };

private:

};


# endif
