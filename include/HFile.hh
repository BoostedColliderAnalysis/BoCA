# ifndef HFile_hh
# define HFile_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class Analysis::HFile : public HObject
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
    HFile(const string Process);

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const string Process, const string Run);

    ExRootTreeReader *GetTreeReader();

    /**
     * @brief destructor
     *
     */
    virtual ~HFile();

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
class Analysis::HParton::HFile : public Analysis::HFile
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
  HFile(const string Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string Process, const string Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

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
class Analysis::HPgs::HFile : public Analysis::HFile
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
  HFile(const string Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string Process, const string Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

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
class Analysis::HDelphes::HFile : public Analysis::HFile
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
  HFile(const string Process);

  /**
   * @brief constructor defining default path
   *
   */
  HFile(const string Process, const string Run);

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

protected:

    virtual inline string ClassName() const {

        return "HDelphes: HFile";

    };

private:

};

// /**
//  * @brief Delphes files in plain folder
//  *
//  */
// class Analysis::HFileFolder : public HFile
// {
//
// public:
//
//   /**
//    * @brief constructor defining default path
//    *
//    */
//   HFileFolder();
//
//   /**
//    * @brief constructor defining default path
//    *
//    */
//   HFileFolder(const string Process);
//
//   /**
//    * @brief constructor defining default path
//    *
//    */
//   HFileFolder(const string Process, const string Run);
//
//     /**
//      * @brief Compose file path
//      *
//      * @return string file path
//      */
//     string GetFilePath() const;
//
//     string GetTreeName() const;
//
// protected:
//
//     virtual inline string ClassName() const {
//
//         return ("HFileFolder");
//
//     };
//
// private:
//
// };

# endif
