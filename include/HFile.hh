# ifndef HFile_hh
# define HFile_hh

# include "HObject.hh"

/**
 * @brief Class dealing with pathes to delphes and the root files
 *
 * ProcessFolder has to be set
 *
 */
class HFile : public HObject
{

public:

    /**
     * @brief constructor defining default path
     *
     */
    explicit HFile();

    /**
     * @brief constructor defining default path
     *
     */
    explicit HFile(const string Process);

    /**
     * @brief constructor defining default path
     *
     */
    explicit HFile(const string Process, const string Run);

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
    virtual string GetFilePath() const = 0;

    virtual string GetTreeName() const = 0;

    static string FileSuffix;

    static bool Snowmass;

protected:

    string MadGraphFilePath() const;


private:

    void  SetVariables();

    virtual string ClassName() const {

        return ("HFile");

    };

};

class HFileParton : public HFile
{

public:

    using HFile::HFile;

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

private:

    string ClassName() const {

        return ("HFileFlat");

    };

};

class HFilePgs : public HFile
{

public:

    using HFile::HFile;

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

private:

    string ClassName() const {

        return ("HFilePgs");

    };

};

class HFileDelphes : public HFile
{

public:
    using HFile::HFile;

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

private:

    string ClassName() const {

        return ("HFileDelphes");

    };

};

class HFileFolder : public HFile
{

public:
    using HFile::HFile;

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

    string GetTreeName() const;

private:

    string ClassName() const {

        return ("HFileFolder");

    };

};

# endif
