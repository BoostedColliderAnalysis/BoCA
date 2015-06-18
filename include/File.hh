# pragma once

# include  "exroot/ExRootAnalysis.hh"
# include "ClonesArrays.hh"
# include "Event.hh"

namespace analysis{

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class File : public Object
{

public:

    /**
     * @brief constructor
     *
     */
    File();

    File(const std::string &process);

    File(const std::string &process, const float crosssection);

    File(const std::string &process, const float crosssection, const float mass);

    File(const std::string &process, const std::string &run_folder);

    File(const Strings &processes);

    File(const Strings &processes, const float crosssection);

    File(const Strings &processes, const float crosssection, const float mass);

    File(const std::string &process, const std::string &run_folder, const std::string &file_suffix);

    File(const std::string &process, const std::string &run_folder, const std::string &file_suffix, const std::string &nice_name);

    File(const std::string &process, const std::string &run_folder, const std::string &file_suffix, const float crosssection);

    /**
     * @brief destructor
     *
     */
    ~File();

    exroot::TreeReader TreeReader();

    ClonesArrays clones_arrays();

    Event event();

    /**
     * @brief Name of Process
     *
     */
    std::string Title() const;

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

    std::string file_suffix() const;

    float crosssection_error() const {
        return crosssection_error_;
    }

    float mass() const {
        return mass_;
    }
    ClonesArrays::Source source() const {
        return source_;
    }

    std::string tree_name() const;

    std::string nice_name() const{
      return nice_name_;
    }

    Strings Paths() const;

protected:

    void  SetVariables();

    std::string MadGraphFilePath() const;

    virtual inline std::string ClassName() const {
        return "File";
    }

private:

    std::string base_path_ = "$HOME/Development/MadGraph/";

    Strings process_folders_;

    std::string run_folder_;

    std::string tag_name_;

    std::string tree_name_;

    float crossection_ = 1;

    float crosssection_error_ = 0;

    float mass_ = 0;

    std::string file_suffix_ = ".root";

    std::string nice_name_;

    ClonesArrays::Source source_ = ClonesArrays::ClonesArrays::kDelphes;

    TChain *chain_ = NULL;

};

}
