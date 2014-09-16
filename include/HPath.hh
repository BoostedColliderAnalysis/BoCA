# ifndef HPath_hh
# define HPath_hh

# include "HObject.hh"

/**
 * @brief Class dealing with pathes to delphes and the root files
 *
 * ProcessFolder has to be set
 *
 */
class HPathBase : public HObject
{

public:

    /**
     * @brief constructor defining default path
     *
     */
    explicit HPathBase();

    /**
     * @brief constructor defining default path
     *
     */
    explicit HPathBase(TString Process);

    /**
     * @brief constructor defining default path
     *
     */
    explicit HPathBase(TString Process, TString Run);

    /**
     * @brief destructor
     *
     */
    virtual ~HPathBase();

    /**
     * @brief Path path to the MadGraph installation
     *
     */
    TString MadGraphPath;

    /**
     * @brief Process name used in the file path
     *
     */
    TString ProcessFolder;

    /**
     * @brief Run name use in the file path
     *
     */
    TString RunFolder;

    /**
     * @brief Tag string used in the file name
     *
     */
    TString TagString;

    /**
     * @brief String containing the name of the root tree
     *
     */
    TString TreeString;

    /**
     * @brief Name of Process
     *
     */
    TString Title;

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
     * @return TString file path
     */
    virtual TString FilePath() = 0;

    virtual TString GetTreeString() = 0;

protected:

    virtual TString MadGraphFilePath() {

        return (MadGraphPath + ProcessFolder + "/Events/" + RunFolder + "/");

    };

private:

    void  SetVariables();

    virtual TString ClassName() {
        return ("HPathBase");
    };

};

class HPathDelphes : public HPathBase
{

public:
    using HPathBase::HPathBase;

    /**
     * @brief Compose file path
     *
     * @return TString file path
     */
    TString FilePath();

    TString GetTreeString();

private:
    virtual TString ClassName() {
        return ("HPathDelphes");
    };

};

class HPathFlat : public HPathBase
{

public:
    using HPathBase::HPathBase;

    /**
     * @brief Compose file path
     *
     * @return TString file path
     */
    TString FilePath();

    TString GetTreeString();

private:
    virtual TString ClassName() {
        return ("HPathFlat");
    };

};

class HPathPgs : public HPathBase
{

public:
    
    using HPathBase::HPathBase;

    /**
     * @brief Compose file path
     *
     * @return TString file path
     */
    TString FilePath();

    TString GetTreeString();

private:
    virtual TString ClassName() {
        return ("HPathFlat");
    };

};

class HPathParton : public HPathBase
{

public:
    using HPathBase::HPathBase;

    /**
     * @brief Compose file path
     *
     * @return TString file path
     */
    TString FilePath();

    TString GetTreeString();

private:
    virtual TString ClassName() {
        return ("HPathFlat");
    };

};



# endif
