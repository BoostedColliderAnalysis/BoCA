# ifndef HFile_hh
# define HFile_hh

# include "HObject.hh"

/**
 * @brief Input file infos
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

    virtual string ClassName() const {

        return ("HFile");

    };


private:

    void  SetVariables();

};

/**
 * @brief unweighted MadGraph files
 *
 */
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

protected:

    virtual string ClassName() const {

        return ("HFileFlat");

    };

private:

};

/**
 * @brief PGS files
 *
 */
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

protected:

    virtual string ClassName() const {

        return ("HFilePgs");

    };

private:

};

/**
 * @brief Delphes files
 *
 */
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

protected:

    virtual string ClassName() const {

        return ("HFileDelphes");

    };

private:

};

/**
 * @brief Delphes files in plain folder
 *
 */
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

protected:

    virtual string ClassName() const {

        return ("HFileFolder");

    };

private:

};

# endif
