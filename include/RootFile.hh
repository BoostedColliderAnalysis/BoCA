# pragma once

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "HObject.hh"

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class hanalysis::RootFile : public HObject
{

public:

    /**
     * @brief constructor
     *
     */
    RootFile();

    RootFile(const std::string &process);

    RootFile(const std::string &process, const float crosssection);

    RootFile(const std::string &process, const float crosssection, const float mass);

    RootFile(const std::string &process, const std::string &run_folder);

    RootFile(const Strings &processes);

    RootFile(const Strings &processes, const float crosssection);

    RootFile(const Strings &processes, const float crosssection, const float mass);

    RootFile(const std::string &process, const std::string &run_folder, const std::string &file_suffix);

    /**
     * @brief destructor
     *
     */
    virtual ~RootFile();

    ExRootTreeReader TreeReader();

    virtual hanalysis::ClonesArrays &GetClonesArrays();

    virtual hanalysis::HEvent &Event();

    void SetBasePath(const std::string &base_path) {
        base_path_ = base_path;
    }

    /**
     * @brief Name of Process
     *
     */
    std::string GetTitle() const;

    float crosssection() const {
        return crossection_;
    }

    void set_crosssection(const float crosssection) {
        crossection_ = crosssection;
    }

    void set_crosssection_error(const float crosssection_error) {
        crosssection_error_ = crosssection_error;
    }

    void set_mass(const float mass) {
        mass_ = mass;
    }

    void set_file_suffix(const std::string &file_suffix) {
        file_suffix_ = file_suffix;
    }

    float crosssection_error() const {
        return crosssection_error_;
    }

    float mass() const {
        return mass_;
    }


    void set_snow_mass(const bool snow_mass) {
        snow_mass_ = snow_mass;
    }

    void set_tree_name(const std::string &tree_name) {
        tree_name_ = tree_name;
    }

    /**
     * @brief Compose file path
     *
     * @return std::string file path
     */

    virtual std::string tree_name() const;

    virtual Strings Paths() const;

protected:

    void  SetVariables();

    std::string GetMadGraphFilePath() const;

    virtual inline std::string ClassName() const {
        return "HFile";
    };

    /**
     * @brief Path path to the MadGraph installation
     *
     */
    static std::string base_path_;

    /**
     * @brief Process name used in the file path
     *
     */
    Strings process_folders_;

    /**
     * @brief Run name use in the file path
     *
     */
    std::string run_folder_;

    /**
     * @brief Tag std::string used in the file name
     *
     */
    std::string tag_name_;

    /**
     * @brief String containing the name of the root tree
     *
     */
    static std::string tree_name_;

    /**
     * @brief Crosssection of the event
     *
     */
    float crossection_ = 1;

    /**
     * @brief Error of the Crosssection
     *
     */
    float crosssection_error_;

    float mass_;

    static std::string file_suffix_;

    static bool snow_mass_;

private:

    TChain *chain_ = NULL;

    HEvent *event_ = NULL;

    ClonesArrays *clones_array_ = NULL;
};
