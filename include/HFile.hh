# ifndef HFile_hh
# define HFile_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "HClonesArray.hh"

// # include "HEvent.hh"
# include "HEventDelphes.hh"
# include "HEventParton.hh"
# include "HEventPgs.hh"

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class hanalysis::HFile : public HObject
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
    HFile(const string &Process);

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const string &Process, const string &Run);

    ExRootTreeReader *GetTreeReader();

    /**
     * @brief destructor
     *
     */
    virtual ~HFile();
    
    virtual HClonesArray *GetClonesArrays() const;
    
    virtual HEvent *GetEvent() const;

    /**
     * @brief Path path to the MadGraph installation
     *
     */
    static string BasePath;

    /**
     * @brief Process name used in the file path
     *
     */
    string ProcessFolder;

    /**
     * @brief Run name use in the file path
     *
     */
    string RunFolder;

    /**
     * @brief Tag string used in the file name
     *
     */
    string TagString;

    /**
     * @brief String containing the name of the root tree
     *
     */
    static string TreeString;

    /**
     * @brief Name of Process
     *
     */
    string Title() const;

    /**
     * @brief Crosssection of the event
     *
     */
    float Crosssection;

    /**
     * @brief Error of the Crosssection
     *
     */
    float Error;

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    virtual string GetFilePath() const;

    virtual string GetTreeName() const;

    static string FileSuffix;

    static bool Snowmass;

protected:

  void  SetVariables();

    string MadGraphFilePath() const;

    virtual inline string ClassName() const {

        return "HFile";

    };


private:

  TFile* ImportFile;
  TTree* ImportTree;


};

/**
 * @brief unweighted MadGraph files
 *
 */
class hanalysis::hparton::HFile : public hanalysis::HFile
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
  HFile(const string &Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string &Process, const string &Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;
    
    hanalysis::HEvent *GetEvent() const;

protected:

    virtual inline string ClassName() const {

        return "HParton: HFile";

    };

private:

};

/**
 * @brief PGS files
 *
 */
class hanalysis::hpgs::HFile : public hanalysis::HFile
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
  HFile(const string &Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string &Process, const string &Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;
    
    hanalysis::HEvent *GetEvent() const;

protected:

    virtual inline string ClassName() const {

        return "HPgs: HFile";

    };

private:

};

/**
 * @brief Delphes files
 *
 */
class hanalysis::hdelphes::HFile : public hanalysis::HFile
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
  HFile(const string &Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string &Process, const string &Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;
    
    hanalysis::HEvent *GetEvent() const;
    
    hanalysis::HClonesArray *GetClonesArrays() const;

protected:

    virtual inline string ClassName() const {

        return "HDelphes: HFile";

    };

private:

};


# endif
