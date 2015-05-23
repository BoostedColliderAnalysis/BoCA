# pragma once

# include "libconfig.h++"
# include "Object.hh"

namespace analysis
{

class Configuration : public Object
{

public:

    Configuration();

    Configuration(const std::string &config_name);

    ~Configuration();

    // in GeV
    int Mass() const;

    // in GeV
    int PreCut() const;

    int EventNumberMax() const;

    int BackgroundFileNumber() const;

    enum ColliderType {LHC, FHC, LE};

    ColliderType collider_type() const;

private:
    // in GeV
    int Mass_();

    // in GeV
    int PreCut_();

    int EventNumberMax_();

    int BackgroundFileNumber_();

    ColliderType ColliderType_();

    void WriteConfig(const std::string &config_name);

    void ReadConfig(const std::string &config_name);

    libconfig::Config *config_ = NULL;

    int mass_;

    int pre_cut_;

    int event_number_max_;

    int background_file_number_;

    ColliderType collider_type_;

};

}
