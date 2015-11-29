/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "libconfig.h++"
#include "physics/Units.hh"

namespace boca
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

    boca::Mass Mass();

    Momentum PreCut();

    long TrainNumberMax();

    int BackgroundFileNumber();

    boca::ColliderType ColliderType();

private:

    void WriteConfig(std::string const& config_name);

    void ReadConfig(std::string const& config_name);

    std::string ConfigFile(std::string const& config_name);

    libconfig::Config& config() {
        return config_;
    }

    libconfig::Config config_;

};

}
