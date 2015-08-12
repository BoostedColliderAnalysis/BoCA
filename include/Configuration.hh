#pragma once

#include "libconfig.h++"


namespace analysis
{

enum class ColliderType
{
    LHC, FHC, LE
};

class Configuration
{

public:

    Configuration();

    Configuration(std::string const& config_name);

    Configuration& operator=(const Configuration& configuration);

    // in GeV
    int Mass() const;

    // in GeV
    int PreCut() const;

    int EventNumberMax() const;

    int BackgroundFileNumber() const;


    ColliderType collider_type() const;

private:
    // in GeV
    int Mass_();

    // in GeV
    int PreCut_();

    int EventNumberMax_();

    int BackgroundFileNumber_();

    ColliderType ColliderType_();

    void WriteConfig(std::string const& config_name);

    void ReadConfig(std::string const& config_name);

    libconfig::Config config_;

    libconfig::Config& config() {
        return config_;
    }

    int mass_;

    int pre_cut_;

    int event_number_max_;

    int background_file_number_;

    ColliderType collider_type_;

    std::string ConfigFile(std::string const& config_name);

};

}
